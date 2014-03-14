obj-m += pps_gpio_rpi.o
KERNEL_DIR="~/rpi/linux"

modules:
	make -C $(KERNEL_DIR) M=$(PWD) modules

modules_install:
	make -C ${KERNEL_DIR} M=${PWD} modules_install

clean:
	make -C ${KERNEL_DIR} M=$(PWD) clean
