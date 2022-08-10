obj-m:=pcd_platform_driver.o pcd_device_setup.o

PWD := $(shell pwd)
CROSS=/home/cuong/Desktop/work/gcc-11.1.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-
KER_DIR=/home/cuong/Desktop/work/kernelbuildscripts/deploy/lib/modules/5.4.182-bone64/build
HOST_KERN_DIR=/lib/modules/$(shell uname -r)/build/

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KER_DIR) M=$(PWD) modules
clean:
	make -C $(KER_DIR) M=$(PWD) clean
host:
	make -C $(HOST_KERN_DIR) M=$(PWD) modules
