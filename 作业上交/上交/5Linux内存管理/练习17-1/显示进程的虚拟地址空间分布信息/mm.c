#include <linux/version.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/seq_file.h>
#include <linux/mm.h>
char modname[] = "mm";

static int my_seq_show(struct seq_file *m, void *p)
{
	struct task_struct	*tsk = current;
	struct mm_struct	*mm = tsk->mm;
	unsigned long		stack_size = (mm->stack_vm << PAGE_SHIFT);
	unsigned long		down_to = mm->start_stack - stack_size;	
	
	seq_printf( m, "Info from the Memory Management structure " );
	seq_printf( m, "for task \'%s\' ", tsk->comm );
	seq_printf( m, "(pid=%d) \n", tsk->pid );
	seq_printf( m, "   pgd=%08lX  ", (unsigned long)mm->pgd );
	seq_printf( m, "mmap=%08lX  ", (unsigned long)mm->mmap );
	seq_printf( m, "map_count=%d  ", mm->map_count );
	seq_printf( m, "mm_users=%d  ", mm->mm_users.counter );
	seq_printf( m, "mm_count=%d  ", mm->mm_count.counter );
	seq_printf( m, "\n" );

	seq_printf( m, "   task_size=0x%08lX  ", mm->task_size );
	seq_printf( m, "\n" );

	seq_printf( m, "    start_code=%08lX  ", mm->start_code );
	seq_printf( m, " end_code=%08lX  ", mm->end_code );
    seq_printf( m, " len_code=%08lX\n", mm->end_code - mm->start_code );
	seq_printf( m, "    start_data=%08lX  ", mm->start_data );
	seq_printf( m, " end_data=%08lX  ", mm->end_data );
    seq_printf( m, " len_data=%08lX\n", mm->end_data - mm->start_data );
	seq_printf( m, "     start_brk=%08lX  ", mm->start_brk );
	seq_printf( m, "      brk=%08lX\n", mm->brk );
	seq_printf( m, "     arg_start=%08lX  ", mm->arg_start );
	seq_printf( m, "  arg_end=%08lX\n", mm->arg_end );
	seq_printf( m, "     env_start=%08lX  ", mm->env_start );
	seq_printf( m, "  env_end=%08lX\n", mm->env_end );
	seq_printf( m, "   start_stack=%08lX  ", mm->start_stack );
	seq_printf( m, "  down_to=%08lX ", down_to );
	seq_printf( m, " <--- stack grows downward \n" );
	
	return	0;
}

static void * my_seq_start(struct seq_file *m, loff_t *pos)
{
  if (0 == *pos)
  {
     ++*pos;
     return (void *)1;
  }

  return NULL;
}
static void * my_seq_next(struct seq_file *m, void *p, loff_t *pos)
{
        return NULL;
}

static void my_seq_stop(struct seq_file *m, void *p)
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

static int __init my_init( void )
{
	struct proc_dir_entry* my_proc_entry;
	printk( "<1>\nInstalling \'%s\' module\n", modname );
	my_proc_entry = proc_create(modname, 0, NULL, &my_proc);
	if (NULL == my_proc_entry)
	{
	    return -ENOMEM;
	}
	//SUCCESS
    return	0;
}

static void __exit my_exit(void )
{
	remove_proc_entry( modname, NULL );

	printk( "<1>Removing \'%s\' module\n", modname );
}

module_init( my_init );
module_exit( my_exit );
MODULE_AUTHOR("weilinfox <201901060401@sdust.edu.cn>");
MODULE_LICENSE("GPL");

