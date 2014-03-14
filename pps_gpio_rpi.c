/*
 * Raspberry Pi PPS GPIO module
 *
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/pps-gpio.h>
#include <linux/platform_device.h>

#define VERSION "0.1"

static unsigned int pin = 16; /* Default to pin 4 */

module_param(pin, uint, 0444);
MODULE_PARM_DESC(pin, "GPIO pin to use for PPS data");

static struct pps_gpio_platform_data pdata = {
	.gpio_pin = 0,
};

static void pps_gpio_rpi_release(struct device *dev)
{
	/* nothing to do */
}

static struct platform_device pdev = {
	.name = "pps-gpio",
	.id = -1,
	.dev = {
		.platform_data = &pdata,
		.release = pps_gpio_rpi_release,
	},
}; 


static int __init pps_gpio_rpi_init(void)
{
	int err;

	printk("Raspberry Pi PPS GPIO v" VERSION ": initialising on pin %d\n", pin);

	pdata.gpio_pin = pin;
	
	err = platform_device_register(&pdev);
	if (err) 
		goto err;

	printk("Raspberry Pi PPS GPIO v" VERSION ": platform device registered\n");
	return 0;

err:
	return err;
}

static void __exit pps_gpio_rpi_exit(void)
{
	printk("Raspberry Pi PPS GPIO v" VERSION ": unloading\n");

	platform_device_unregister(&pdev);

	return;
}

module_init(pps_gpio_rpi_init);
module_exit(pps_gpio_rpi_exit);

MODULE_AUTHOR("Neil Greatorex <neil@fatboyfat.co.uk>");
MODULE_DESCRIPTION("PPS over GPIO for Raspberry Pi");
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");

