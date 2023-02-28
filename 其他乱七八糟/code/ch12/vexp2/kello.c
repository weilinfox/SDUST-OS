//-----------------------------------------------------------------
//kello.c. ��ʾprintk �� KERN_EMERG�������
// ����Ҳ���Ը���log_level�Լ�����ȼ����۲�ʵ������
//	��������: $ make kello ���� $ make
//	��װ����: $ sudo insmod kello.ko
//  �ں���־��Ϣ��ʾ���  $ dmesg
//  ������� $ sudo rmmod kello
// ��<CTRL>+<ALT>+F1���߰�<CTRL>+<ALT>+F7�л�ͼ�ν��棬֧���ں������Ϣ��ʾ��������
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

