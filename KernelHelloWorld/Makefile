obj-m := KernelHelloWorld.o
KDIR := /lib/modules/$(shell uname -r)/build
GCOV := /sys/kernel/debug/gcov$(shell pwd)
PWD := $(shell pwd)
FLLE := KernelHelloWorld
GCOV_PATH := coverage

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR)  M=$(PWD) clean
gcov:
	cp -a $(GCOV) ./$(GCOV_PATH)/
	cd $(GCOV_PATH)/$(FILE)
	lcov --directory . --capture  --output-file $(FILE).info
	genhtml $(FILE).info