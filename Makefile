obj-m += char_device.o
_CFLAGS += -g -DDEBUG
ccflags-y += ${_CFLAGS}

KERNEL_BUILD := /lib/modules/$(shell uname -r)/build
CC_PREFIX :=arm-none-linux-gnueabihf-
CC := $(CC_PREFIX)gcc
CC += ${_CFLAGS}

TEST_FILE := device_test

compile:
	make -C $(KERNEL_BUILD) M=$(shell pwd) modules ARCH=arm CROSS_COMPILE=$(CC_PREFIX)
	$(CC) $(TEST_FILE).c -o $(TEST_FILE)

debug:
	make -C $(KERNEL_BUILD) M=$(shell pwd) modules ARCH=arm CROSS_COMPILE=$(CC_PREFIX)
	EXTRA_CFLAGS="${_CFLAGS}"

clean:
	make -C $(KERNEL_BUILD) M=$(shell pwd) clean ARCH=arm CROSS_COMPILE=$(CC_PREFIX)
	rm $(TEST_FILE)
