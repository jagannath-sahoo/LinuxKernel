obj-m := my_dev_procfs.o


HOST_DIR=/lib/modules/${shell uname -r}/build

all:
	make -C ${HOST_DIR} M=${PWD} modules

clean:
	make -C ${HOST_DIR} M=${PWD} clean
