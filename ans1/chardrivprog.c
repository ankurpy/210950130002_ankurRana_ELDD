#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>

#define RD_VALUE _IOR('a','b',int32_t*)
 
int32_t value = 0;

MODULE_LICENSE("GPL");
int my_open(struct inode *inode, struct file *filp);
int my_release(struct inode *inode, struct file *filp);
ssize_t my_read(struct file  *filp,char __user *ubuff, size_t count, loff_t *offp);
ssize_t my_write(struct file  *filp,const char __user *ubuff, size_t count, loff_t *offp);
static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg);

struct file_operations fops=
{
    .open=my_open,
    .release=my_release,
    .read=my_read,
    .write=my_write,
    .unlocked_ioctl = my_ioctl
};

struct cdev *mycdev;

static int __init entry_fun(void)
{
    printk(KERN_INFO "In init fun\n");
    dev_t devnum;
    int maj,min;
    int result;
    devnum = MKDEV(255,0);  //create device number
    maj=MAJOR(devnum);
    min=MINOR(devnum);
    result=register_chrdev_region(devnum,1,"mychardriver");     //register device region
    if(result<0)
    {
        printk(KERN_INFO "device registration failed\n");
        return (-1);
    }
    mycdev=cdev_alloc();    //allocate m/m to char device structure
    mycdev->ops=&fops;  //linking file operations to char device
    result=cdev_add(mycdev,devnum,1);
    if(result<0)
    {
        printk(KERN_INFO "device not added\n");
        unregister_chrdev_region(devnum,1);
        return (-1);
    }

    return 0;
}

static void __exit exit_fun(void)
{
    printk(KERN_INFO "In cleanup fun\n");
    dev_t devnum;
    int maj,min;
    devnum = MKDEV(255,0);  //create device number
    maj=MAJOR(devnum);
    min=MINOR(devnum);
    unregister_chrdev_region(devnum,1);
    cdev_del(mycdev);

}

int my_open(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "i'm in open fun\n");
    return 0;
}

int my_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "i'm in release fun\n");
    return 0;
}

ssize_t my_read(struct file  *filp,char __user *ubuff, size_t count, loff_t *offp)
{
    char kbuff[]="this is kernel buffer";
    unsigned long result;
    ssize_t retval;
    result=copy_to_user((char *)ubuff,(char *)kbuff,count);
    value=0;
    if(result==0)
    {
        printk(KERN_INFO "read successfull\n");
        retval=count;
        return retval;

    }
    else if(result>0)
    {
        printk(KERN_INFO "read subpart \n");
        retval=(count-result);
        return retval;

    }
    else
    {
        printk(KERN_INFO "error in reading\n");
        retval=-EFAULT;
        return retval;
    }
}

ssize_t my_write(struct file  *filp,const char __user *ubuff, size_t count, loff_t *offp)
{
    char kbuff[50];
    unsigned long result;
    ssize_t retval;
    result=copy_from_user((char *)kbuff,(char *)ubuff,count);
    value=1;
    if(result==0)
    {
        printk(KERN_INFO "write successfull\n");
        retval=count;
        return retval;

    }
    else if(result>0)
    {
        printk(KERN_INFO "write subpart \n");
        retval=(count-result);
        return retval;

    }
    else
    {
        printk(KERN_INFO "error in writing\n");
        retval=-EFAULT;
        return retval;
    }
}

static long my_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
         switch(cmd) {

                case RD_VALUE:
                        if( copy_to_user((int32_t*) arg, &value, sizeof(value)) )
                        {
                                printk(KERN_INFO"Data Read : Err!\n");
                        }
                        break;
                default:
                        printk(KERN_INFO"Default\n");
                        break;
        }
        return 0;
}

module_init(entry_fun);
module_exit(exit_fun);
