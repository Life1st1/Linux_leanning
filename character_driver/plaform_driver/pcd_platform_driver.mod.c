#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
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
__used __section("__versions") = {
	{ 0xcb440b5e, "module_layout" },
	{ 0x8eab5523, "class_destroy" },
	{ 0x2b2bd200, "platform_driver_unregister" },
	{ 0x4797fac4, "__platform_driver_register" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x109c449a, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x85401a17, "device_create" },
	{ 0x4c75eeab, "cdev_add" },
	{ 0xc3a1cc09, "cdev_init" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0x8bd65ff4, "kmem_cache_alloc_trace" },
	{ 0xc83492ef, "kmalloc_caches" },
	{ 0x92997ed8, "_printk" },
	{ 0x37a0cba, "kfree" },
	{ 0xe1d71654, "cdev_del" },
	{ 0x37fd21cc, "device_destroy" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "17877A2998F2EDFEB0DB03F");
