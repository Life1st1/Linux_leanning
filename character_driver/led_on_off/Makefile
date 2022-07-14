obj-m:=exam_cdev.o

PWD := $(shell pwd)
CROSS=/home/cuong/Desktop/work/gcc-11.1.0-nolibc/arm-linux-gnueabi/bin/arm-linux-gnueabi-
KER_DIR=/home/cuong/Desktop/work/kernelbuildscripts/deploy/lib/modules/5.4.182-bone64/build

all:
	make ARCH=arm CROSS_COMPILE=$(CROSS) -C $(KER_DIR) M=$(PWD) modules
clean:
	make -C $(KER_DIR) M=$(PWD) clean
