#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/uaccess.h>

// #if CONFIG_MODVERSIONS==1 
// #define MODVERSIONS 
// #include "linux/version.h" 
// #endif 

#define DEVICE_NAME "sky_driver"
#define BUF_LEN 100


static int my_open(struct inode *inode,struct file *filp);
static int my_release(struct inode *inode,struct file *filp);
static ssize_t my_read(struct file *file,char *buffer,size_t length,loff_t *offset);
static ssize_t my_write(struct file *file,const char *buff,size_t len,loff_t *off);

static struct file_operations my_fops = {
    .read = my_read,
    .write = my_write,
    .open = my_open,
    .release = my_release,
};

static int Major = 0;
static int Device_Open = 0;
static char msg[BUF_LEN];
static int counter = 0;  //记录设备打开的次数

//所有打开设备的函数原型都是这样，一个设备的inode，还有一个与设备文件对应的file结构体
static int my_open(struct inode *inode,struct file *filp)
{
    if(Device_Open) 
        return -1;
    Device_Open++; 
    try_module_get(THIS_MODULE);  //增加内核模块的引用的计数
    return 0;
}
//释放设备
static int my_release(struct inode *inode,struct file *filp)
{
    if(Device_Open != 0)
    {
        Device_Open--;   //更改设备打开状态
        module_put(THIS_MODULE);  //减少内核模块的引用计数
    }
    return 0;
}
//内核空间和用户空间的数据拷贝使用copy_to_user和copy_from_user两个函数实现 
//读文件
static ssize_t my_read(struct file *file,char *buffer,size_t length,loff_t *offset)
{   
    sprintf(msg,"I already told you %d times Hello world\n",++counter);
    return copy_to_user(buffer,msg,length); //把msg指向的内容拷贝到buffer中
}
//写文件
static ssize_t my_write(struct file *file,const char *buff,size_t len,loff_t *off)
{   
    return copy_from_user(msg,buff,BUF_LEN);
}
//内核模块初始化
static int __init my_init(void)
{
    //注册设备驱动，随机产生主设备号
    Major = register_chrdev(0,DEVICE_NAME,&my_fops);
    if(Major < 0) {
        printk("Registering the character device failed with %d\n",Major);
        return -1;
    }
    printk("<1> I was assigned major number %d ",Major);
    printk("<1> the drive,create a dev file");
    printk("<1> mknod /dev/hello c %d 0.\n",Major);
    printk("<1> I was assigned major number %d ",Major);
    printk("<1> the device file\n");
    printk("<1> Remove the file device and module when done\n");
    return 0;
}
//内核模块注销
static void __exit my_exit(void)
{
    unregister_chrdev(Major,DEVICE_NAME);
    printk("<1>unloading the device\n");
}

module_init(my_init);
module_exit(my_exit)
MODULE_LICENSE("GPL");