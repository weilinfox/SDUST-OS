#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/highmem.h>
#include <asm/uaccess.h>
#include <linux/version.h>

#define START_KERNEL_map 0xC0000000
char modname[] = "myshowgdt";
loff_t 	ram_size;
unsigned short 	gdtr[3];
unsigned long	gdt_virt_address; 
unsigned long	gdt_phys_address;

static int my_seqshow(struct seq_file *m, void *v)
{	

	int	n_elts, i;
	int	frame_number, frame_indent;
	struct page	*pp;
	unsigned long long		*from;
	unsigned long long	descriptor;

	asm(" sgdt gdtr ");

	gdt_virt_address = *(unsigned long*)(gdtr+1);
	gdt_phys_address = gdt_virt_address - START_KERNEL_map;

	n_elts = (1 + gdtr[0])/8;
	seq_printf(m,  "GDT segment descriptors' number is %d\n", n_elts );
	seq_printf(m,  "gdt_virt_address=%08lX ", gdt_virt_address );
	seq_printf(m,  "gdt_phys_address=%08lX ", gdt_phys_address );
	seq_printf(m,  "\n" );

	if ( gdt_phys_address >= ram_size ) return 0;

	frame_number = gdt_phys_address / PAGE_SIZE;
	frame_indent = gdt_phys_address % PAGE_SIZE;
        pp = pfn_to_page( frame_number);

	from = (unsigned long long*)(kmap( pp ) + frame_indent);
	for (i = 0; i < n_elts; i++)
		{
		if ( ( i % 4 ) == 0 ) seq_printf(m, "\n %04X: ", i*8 );
		descriptor = *from;
		seq_printf(m,  "%016llX ", descriptor );
		from++;
		}

	seq_printf(m, "\n" );
	kunmap( pp );
	return 0;
}


static int my_open(struct inode *inode, struct file *file)  
{  
    return single_open(file, my_seqshow, NULL);
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
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release    = single_release,
}; 
#endif

static int __init my_init( void )
{
	struct proc_dir_entry* my_proc_entry;
	printk( "<1>\nInstalling \'%s\' module\n", modname );	
	my_proc_entry = proc_create(modname, 0x644, NULL, &my_proc);
	ram_size = (loff_t)totalram_pages << PAGE_SHIFT;
	printk( "<1>ram_size is %llu\n",ram_size  );
	return	0;  //SUCCESS
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


