#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
char modname[] = "segselector";

short  _cs, _ds, _es, _fs, _gs, _ss;

static int my_seqshow(struct seq_file *m, void *v)
{
	asm(" mov  %cs, _cs  \n  mov %ds, _ds ");
	asm(" mov  %es, _es  \n  mov %fs, _fs ");
	asm(" mov  %gs, _gs  \n  mov %ss, _ss ");
	seq_printf(m, "CS=%04X  DS=%04X \n", _cs, _ds );
	seq_printf(m, "ES=%04X  FS=%04X \n", _es, _fs );
	seq_printf(m, "GS=%04X  SS=%04X \n", _gs, _ss );
	return 0;
}

static int my_open(struct inode *inode, struct file *file)  
{  
    return single_open(file, my_seqshow, NULL);
}  

// replace struct file_operations with struct proc_ops for kernel version 5.6 or later
#include <linux/version.h>
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
	.read	    = seq_read,
	.llseek	    = seq_lseek,
	.release    = single_release,
}; 
#endif

static int __init showgdtmod_init( void )
{
	struct proc_dir_entry* my_proc_entry;
	printk( "<1>\nInstalling \'%s\' module\n", modname );
	my_proc_entry = proc_create(modname, 0x644, NULL, &my_proc);
	return	0;
}


static void __exit showgdtmod_exit(void )
{
	remove_proc_entry( modname, NULL );

	printk( "<1>Removing \'%s\' module\n", modname );
}

module_init( showgdtmod_init );
module_exit( showgdtmod_exit );
MODULE_AUTHOR("weilinfox <201901060401@sdust.edu.cn>");
MODULE_LICENSE("GPL"); 

