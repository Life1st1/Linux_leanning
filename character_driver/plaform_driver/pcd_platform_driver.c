#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>

#define DEVICE		5
#define AUTHOR		"Phu Luu An luuanphu@gmail.com"
#define DESC		"A example character device driver"
#define DEVICE_NAME     "char_dd"

#undef pr_fmt
#define pr_fmt(fmt) "%s : " fmt,__func__

static int my_open(struct inode *inode, struct file *file)
{
	return 0;
}

static int my_close(struct inode *inode, struct file *file)
{
	return 0;
}

static ssize_t my_write(struct file *flip, const char __user *user_buf, size_t len, loff_t *offs)
{
	return 0;
}

static ssize_t my_read(struct file *flip, char __user *user_buf, size_t len, loff_t *offs)
{
	return 0;
}


static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write,
	//.unlocked_ioctl = my_ioctl,
};

int pcd_platform_driver_probe(struct platform_device *pdev)
{

    return 0;
}


int pcd_platform_driver_remove(struct platform_device *pdev)
{

    return 0;
}

struct platform_driver pcd_platform_driver = 
{
    .probe = pcd_platform_driver_probe,
    .remove = pcd_platform_driver_remove,
    .driver = {
            .name = "pseudo-char-device"
    }
};



static int __init platform_driver_init(void)
{
    platform_driver_register(&pcd_platform_driver);

    pr_info("Platform driver loaded! \n"); 

    return 0;
}

static void __exit platform_driver_exit(void)
{
    platform_driver_unregister(&pcd_platform_driver);
}

module_init(platform_driver_init);
module_exit(platform_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_VERSION("0.01");