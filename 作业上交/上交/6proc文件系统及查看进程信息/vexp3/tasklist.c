#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/version.h>

char modname[] = "tasklist";
struct task_struct  *task;
int  taskcounts=0;

static void * my_seq_start(struct seq_file *m, loff_t *pos)
{
	if ( *pos == 0 )
	{
	   task = &init_task;
	   return &task;
	} else {
		if (task == &init_task )
			return NULL;
		return (void*)pos;
	}
}
static int my_seq_show(struct seq_file *m, void *v)
{
  seq_printf( m,  "#%-3d ", taskcounts++ );
  seq_printf( m,  "%5d ", task->pid );
  seq_printf( m,  "%lu ", task->state );
  seq_printf( m,  "%-15s ", task->comm );
  //优先级
  seq_printf( m,  "%-5d ", task->prio);
  seq_printf( m,  "%-5d ", task->static_prio);
  seq_printf( m,  "%-5d ", task->normal_prio);
  seq_printf( m,  "%-5d ", task->rt_priority);
  //调度策略
  seq_printf( m,  "%u ", task->policy);
  //上下文切换
  seq_printf( m,  "%lu ", task->nvcsw);
	seq_printf( m,  "%lu ", task->nivcsw);
    //运行时间
	seq_printf( m,  "%llu ", task->utime);
	seq_printf( m,  "%llu ", task->stime);
    // real_start_time (represented as struct timespec until 3.17,
    // replaced with u64 nanosecond timestamps) now start_boottime in kernel 5.6+
	seq_printf( m,  "%llu ", task->start_boottime);
  seq_puts( m, "\n" );
  return 0; 
}

static void * my_seq_next(struct seq_file *m, void *v, loff_t *pos)
{
  (*pos)++;    
  task= next_task(task);
  return NULL;

}
static void my_seq_stop(struct seq_file *m, void *v)
{
}

static struct seq_operations my_seq_fops = {
        .start  = my_seq_start,
        .next   = my_seq_next,
        .stop   = my_seq_stop,
        .show   = my_seq_show
};

static int my_open(struct inode *inode, struct file *file)  
{  
    return seq_open(file, &my_seq_fops);
}  

// replace struct file_operations with struct proc_ops for kernel version 5.6 or later
#if LINUX_VERSION_CODE >= KERNEL_VERSION(5,6,0)
static const struct proc_ops my_proc = {
	.proc_open = my_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = seq_release
};
#else
static const struct file_operations my_proc =   
{
	.owner      = THIS_MODULE,  
	.open       = my_open,
	.read       = seq_read,     
	.llseek     = seq_lseek,
	.release    = seq_release  	    
}; 
#endif

int __init my_init( void )
{
	struct proc_dir_entry* my_proc_entry;
	printk( "<1>\nInstalling \'%s\' module\n", modname );
	my_proc_entry = proc_create(modname, 0x644, NULL, &my_proc);
	if (NULL == my_proc_entry)
	{
	    return -ENOMEM;
	}
	return	0;
}

void __exit my_exit( void )
{
	remove_proc_entry( modname, NULL );
	printk( "<1>Removing \'%s\' module\n", modname );
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("weilinfox <201901060401@sdust.edu.cn>");
MODULE_LICENSE("GPL"); 

