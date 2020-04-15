obj-m += char_device.o
_CFLAGS += -g -DDEBUG
ccflags-y += ${_CFLAGS}
CC += ${_CFLAGS}

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
	$(CC) device_test.c -o device_test
debug:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
	EXTRA_CFLAGS="${_CFLAGS}"

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
	rm device_test