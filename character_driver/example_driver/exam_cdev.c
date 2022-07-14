#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

#define DEVICE		5
#define AUTHOR		"Phu Luu An luuanphu@gmail.com"
#define DESC		"A example character device driver"
#define DEVICE_NAME     "char_dd"

#define MAGIC_NO	100
#define SEND_DATA_CMD	_IOW(MAGIC_NO, 1, char*)
#define IOCTL_DATA_LEN 1024

static dev_t dev_num;
struct class *my_class;
struct device *my_dev;
struct cdev my_cdev;
char data[128];
bool first_oper;
char config_data[IOCTL_DATA_LEN];

static int my_open(struct inode *inode, struct file *file)
{
	pr_info("%s, %d\n", __func__, __LINE__);

	return 0;
}

static int my_close(struct inode *inode, struct file *file)
{
	pr_info("%s, %d\n", __func__, __LINE__);

	return 0;
}

static ssize_t my_write(struct file *flip, const char __user *user_buf, size_t len, loff_t *offs)
{
	memset(data, 0, sizeof(data));
	copy_from_user(data, user_buf, len);
	pr_info("%s, %d, data is: %s\n", __func__, __LINE__, data);

	return len;
}

static ssize_t my_read(struct file *flip, char __user *user_buf, size_t len, loff_t *offs)
{
	int read_len = strlen(data);
	if (len > read_len)
	{
		pr_info("%s, %d, read data is: %s\n", __func__, __LINE__, data);
		copy_to_user(user_buf, data, read_len);
		return read_len;
	}

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

static int __init func_init(void)
{
	memset(data, 0, sizeof(data));
	pr_info("%s, %d,\n", __func__, __LINE__, data);
	alloc_chrdev_region(&dev_num, 0, DEVICE, DEVICE_NAME);
	my_class = class_create(THIS_MODULE, DEVICE_NAME);
	cdev_init(&my_cdev, &fops);
	my_cdev.owner = THIS_MODULE;
	cdev_add(&my_cdev, dev_num, 1);
	device_create(my_class, NULL, dev_num, NULL, DEVICE_NAME);

	return 0;
}

static void __exit func_exit(void)
{
	cdev_del(&my_cdev);
	device_destroy(my_class, dev_num);
	class_destroy(my_class);
	unregister_chrdev(dev_num, DEVICE_NAME);
}

module_init(func_init);
module_exit(func_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESC);
MODULE_VERSION("0.01");

