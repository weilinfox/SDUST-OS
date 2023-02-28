//-------------------------------------------------------------------

//  编译命令： make 
//  内核模块添加：$sudo insmod processfs.ko
//  添加内核模块后读取信息： $ dmesg
//  内核模块删除：$sudo rmmod processfs
//	NOTE: Written and tested with Linux kernel version 3.13.0 and.3.2.0
//-------------------------------------------------------------------
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs_struct.h>
#include <linux/path.h>
#include <linux/mount.h>
#include <linux/fs.h>
#include <asm-generic/current.h>

int processfs_init( void )
{
	struct fs_struct *fs;
	struct vfsmount *mnt;
	struct super_block *mnt_sb;
	struct file_system_type *s_type;
	read_lock(&current->fs->lock);
	fs = current->fs;
	mnt = (&fs->pwd)->mnt;
	mnt_sb = mnt->mnt_sb;
	s_type = mnt_sb->s_type;
	printk(" \n PWD File System Type is: %s\n", s_type->name);
	printk(" \n PWD File System Block Size = %ld\n", mnt_sb->s_blocksize);
	read_unlock(&current->fs->lock);
	return 0;
}

void processfs_exit( void )
{
        printk("\n  End!\n");
}

MODULE_AUTHOR("SDUSTOS");
MODULE_LICENSE("GPL");
module_init(processfs_init);
module_exit(processfs_exit);
