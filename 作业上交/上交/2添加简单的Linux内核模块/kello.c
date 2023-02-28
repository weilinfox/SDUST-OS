// kello.c

#include <linux/module.h>

int hello_init( void )
{
	printk("\n Hello kernel space \n");
	return 0;
}

void hello_exit( void )
{
	printk("\n Goodbye\n");
}

MODULE_AUTHOR("weilinfox <201901060401@sdust.edu.cn>");
MODULE_LICENSE("GPL");
module_init(hello_init);
module_exit(hello_exit);

