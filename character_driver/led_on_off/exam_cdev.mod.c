#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0x64511672, "module_layout" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xcf9e4e60, "class_destroy" },
	{ 0x8c027195, "device_destroy" },
	{ 0x49fa8385, "cdev_del" },
	{ 0xe97c4103, "ioremap" },
	{ 0x88cae38, "device_create" },
	{ 0xffc33b5c, "cdev_add" },
	{ 0x38d114dd, "cdev_init" },
	{ 0x1305450c, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xae353d77, "arm_copy_from_user" },
	{ 0x51a910c0, "arm_copy_to_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x2cfde9a2, "warn_slowpath_fmt" },
	{ 0x5f754e5a, "memset" },
	{ 0x2d6fcc06, "__kmalloc" },
	{ 0xc5850110, "printk" },
	{ 0xb1ad28e0, "__gnu_mcount_nc" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "E6346854C5B57054DA26632");
