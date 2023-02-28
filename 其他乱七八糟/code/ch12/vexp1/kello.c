//-----------------------------------------------------------------
//kello.c.：演示了一个最简单的内核模块框架：只有初始化和撤销函数。
// 注意 printk函数
// 按如下步骤操作：
//	编译命令: $ make kello 或者 $ make
//	安装命令: $ sudo insmod kello.ko
//  内核日志信息显示命令：  $ dmesg
//  撤销命令： $ sudo rmmod kello
//programmer: sdustos
//written on: Oct 2014
//-----------------------------------------------------------------

#include <linux/module.h>		// for printk()

int kello_init( void )
{
	printk( "\n   Hello, students from SDUST! This is in kernel space! \n" );

	return	0;
}

void kello_exit( void )
{
	printk( "\n   Goodbye now... students from SDUST! \n" );	

}

MODULE_AUTHOR("SDUSTOS <fangs99@126.com>");
MODULE_LICENSE("GPL");
module_init(kello_init);
module_exit(kello_exit);

