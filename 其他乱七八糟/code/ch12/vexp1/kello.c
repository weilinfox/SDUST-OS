//-----------------------------------------------------------------
//kello.c.����ʾ��һ����򵥵��ں�ģ���ܣ�ֻ�г�ʼ���ͳ���������
// ע�� printk����
// �����²��������
//	��������: $ make kello ���� $ make
//	��װ����: $ sudo insmod kello.ko
//  �ں���־��Ϣ��ʾ���  $ dmesg
//  ������� $ sudo rmmod kello
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

