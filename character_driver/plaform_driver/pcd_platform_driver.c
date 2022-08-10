#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include "platform.h"

#define DEVICE		5
#define AUTHOR		"Phu Luu An luuanphu@gmail.com"
#define DESC		"A example character device driver"
#define DEVICE_NAME     "char_dd"
#define MAX_DEVICES 10

#undef pr_fmt
#define pr_fmt(fmt) "%s : " fmt,__func__

/* Device private data structure */
struct pcdev_private_data
{
    struct pcdev_platform_data pdata;
    char *buffer;
    dev_t dev_num;
    struct cdev cdev;
};

/* Driver private data structure */
struct pcdrv_private_data
{
    int total_devices;
    dev_t device_num_base;
    struct class *class_pcd;
    struct device *device_pcd;
};

struct pcdrv_private_data pcdrv_data;

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


static struct file_operations pcd_fops = {
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write,
	//.unlocked_ioctl = my_ioctl,
};

int pcd_platform_driver_probe(struct platform_device *pdev)
{
    int ret;
    struct pcdev_private_data *dev_data = NULL;

    struct pcdev_platform_data *pdata = NULL;

    pr_info("Device is detected! \n");

    /* 1. Get platform data */
    pdata = (struct pcdev_platform_data*)dev_get_platdata(&pdev->dev);
    if(!pdata){
        pr_info("No platform data available!");
        ret = -EINVAL;
        goto out;
    }

    /* 2. Dymically allocate memory for device private data */
    dev_data = kzalloc(sizeof(struct pcdev_private_data), GFP_KERNEL);
    if(!dev_data){
        pr_info("Cannot allocate memory \n");
        ret = -ENOMEM;
        goto out;
    }

    /* save device private data pointer in platform device structure */
    dev_set_drvdata(&pdev->dev, dev_data);

    dev_data->pdata.size = pdata->size;
    dev_data->pdata.perm = pdata->perm;
    dev_data->pdata.serial_number = pdata->serial_number;

    pr_info("Device seriall number: %s\n", dev_data->pdata.serial_number);
    pr_info("Device size: %d\n", dev_data->pdata.size);
    pr_info("Device permission: %d\n", dev_data->pdata.perm);


    /* 3. Dynamically allocate memory for the device buffer using size information from platform data */
    dev_data->buffer = kzalloc(dev_data->pdata.size, GFP_KERNEL);
    if(!dev_data->buffer){
        pr_err("Cannot allocate memory \n");
        ret = -ENOMEM;
        goto dev_data_free;
    }

    /* 4. Get device number */
    dev_data->dev_num = pcdrv_data.device_num_base + pdev->id;

    /* 5. Do cdev init and cdev add */
    cdev_init(&dev_data->cdev, &pcd_fops);
    dev_data->cdev.owner = THIS_MODULE;
    
    ret = cdev_add(&dev_data->cdev, dev_data->dev_num, 1);
    if(ret < 0){
        pr_err("Cdev add failed\n");
        goto buffer_free;
    }

    /* 6. Create device for detected platform device */
    pcdrv_data.device_pcd = device_create(pcdrv_data.class_pcd, NULL, dev_data->dev_num, NULL, "pcdev-%d", pdev->id);
    if(IS_ERR(pcdrv_data.device_pcd)){
        pr_err("Device creation failed! \n");
        ret = PTR_ERR(pcdrv_data.device_pcd);
        goto cdev_del;
    }
    pcdrv_data.total_devices++;
    pr_info("Probe is successfull! \n");

    return 0;

    /* 7. Error handling*/
cdev_del:
    cdev_del(&dev_data->cdev);
buffer_free:
    kfree(dev_data->buffer);
dev_data_free:
    kfree(dev_data);
out:
    pr_info("Device probe failed! \n");
    return ret;
}


int pcd_platform_driver_remove(struct platform_device *pdev)
{
    struct pcdev_private_data *dev_data = dev_get_drvdata(&pdev->dev);
    /* 1. Remove device  that was created with device_create() */
    device_destroy(pcdrv_data.class_pcd, dev_data->dev_num);
    /* 2. Remove cdev entry from the system */
    cdev_del(&dev_data->cdev);
    /* 3. Remove memory held by device */
    kfree(dev_data->buffer);
    kfree(dev_data);

    pcdrv_data.total_devices--;
    pr_info("Device is removed! \n");

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
    int ret;
    /* 1. Dynamically allocate device number for MAX_DEVICE*/
    ret = alloc_chrdev_region(&pcdrv_data.device_num_base, 0, MAX_DEVICES, "pcdevs");
    if(ret < 0){
        pr_err("Allocate pcdev failed! \n");
        return ret;
    }

    /* 2. Create device class under /sys/class */
    pcdrv_data.class_pcd = class_create(THIS_MODULE, "pcd_class");
    if(IS_ERR(pcdrv_data.class_pcd)){
        pr_err("Class creation failed! \n");
        ret = PTR_ERR(pcdrv_data.class_pcd);
        unregister_chrdev_region(pcdrv_data.device_num_base,  MAX_DEVICES);
        return ret;
    }

    /* 3. Register platform driver */
    platform_driver_register(&pcd_platform_driver);

    pr_info("Platform driver loaded! \n"); 

    return 0;
}

static void __exit platform_driver_cleanup(void)
{
    /* 1. Unregister platform driver */
    platform_driver_unregister(&pcd_platform_driver);

    /* 2.Class destroy */
    class_destroy(pcdrv_data.class_pcd);

    /* 3.Unregister device numbers for MAX_DEVICES*/
    unregister_chrdev_region(pcdrv_data.device_num_base,  MAX_DEVICES);

    pr_info("pcd platform driver unload \n");
}

module_init(platform_driver_init);
module_exit(platform_driver_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_VERSION("0.01");