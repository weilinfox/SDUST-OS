//-----------------------------------------------------------------
//kello.c. 演示printk 中 KERN_EMERG宏的作用
// 读者也可以根据log_level自己定义等级，观察实验现象
//	编译命令: $ make kello 或者 $ make
//	安装命令: $ sudo insmod kello.ko
//  内核日志信息显示命令：  $ dmesg
//  撤销命令： $ sudo rmmod kello
// 按<CTRL>+<ALT>+F1或者按<CTRL>+<ALT>+F7切换图形界面，支持内核输出信息显示在命令行
// 
//programmer: sdustos
//written on: Oct 2014
//-----------------------------------------------------------------

#include <linux/module.h>		// for printk()

int kello_init( void )
{
	//printk( "\n   Kello, The Students from SDUST! \n\n" );
	printk( KERN_EMERG "\n   Kello, The Students from SDUST! \n\n" );
	return	0;
}

void kello_exit( void )
{
	//printk( "\n   The Students from SDUST! Goodbye now... \n\n" );
	printk( KERN_EMERG "\n   The Students from SDUST! Goodbye now... \n\n" );

}

MODULE_AUTHOR("SDUSTOS <fangs99@126.com>");
MODULE_LICENSE("GPL");
module_init(kello_init);
module_exit(kello_exit);

