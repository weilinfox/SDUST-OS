#include <linux/miscdevice.h>
#include <linux/delay.h>  
#include <linux/kernel.h>  
#include <linux/module.h>  
#include <linux/init.h>  
#include <linux/mm.h>  
#include <linux/fs.h>  
#include <linux/types.h>  
#include <linux/delay.h>  
#include <linux/moduleparam.h>  
#include <linux/slab.h>  
#include <linux/errno.h>  
#include <linux/ioctl.h>  
#include <linux/cdev.h>  
#include <linux/string.h>  
#include <linux/list.h>  
#include <linux/pci.h>  
#include <linux/gpio.h>  
  
  
#define DEVICE_NAME "mymap"

static unsigned char *buffer;    
  
static int my_open(struct inode *inode, struct file *file)  
{  
    printk("open miscdev");
    return 0;  
}  
  
  
static int my_map(struct file *filp, struct vm_area_struct *vma)  
{      
    unsigned long page;   
    unsigned long start = (unsigned long)vma->vm_start;   
    unsigned long size = (unsigned long)(vma->vm_end - vma->vm_start);  
    vma->vm_flags |= VM_IO;
    vma->vm_flags |= (VM_DONTEXPAND | VM_DONTDUMP); //VM_RESERVED
  
    //得到物理地址  
    page = virt_to_phys(buffer);      
    //将用户空间的一个vma虚拟内存区映射到以page开始的一段连续物理页面上  
    if(remap_pfn_range(vma,start,page>>PAGE_SHIFT,size,PAGE_SHARED))
        return -1;
      
    return 0;  
}  
  
  
static struct file_operations dev_fops = {  
    .owner    = THIS_MODULE,  
    .open    = my_open,  
    .mmap   = my_map,  
};  
  
static struct miscdevice misc = {  
    .minor = MISC_DYNAMIC_MINOR,  
    .name = DEVICE_NAME,  
    .fops = &dev_fops,  
};    
  
static int __init dev_init(void)  
{  
    int ret;        
    ret = misc_register(&misc);  //注册混杂设备
    buffer = (unsigned char *)kmalloc(PAGE_SIZE,GFP_KERNEL);//内存分配       
    SetPageReserved(virt_to_page(buffer));//将该段内存设置为保留   
    return ret;  
}  
  
  
static void __exit dev_exit(void)  
{  
    //注销设备  
    misc_deregister(&misc);  
    //清除保留  
    ClearPageReserved(virt_to_page(buffer));  
    //释放内存  
    kfree(buffer);  
}  
  
  
module_init(dev_init);  
module_exit(dev_exit);  
MODULE_LICENSE("GPL");  
MODULE_AUTHOR("weilinfox <201901060401@sdust.edu.cn>");

