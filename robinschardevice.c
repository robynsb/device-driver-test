#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
MODULE_LICENSE("Dual BSD/GPL");

dev_t dev;
unsigned int COUNT = 4;
int major_number;

static int hello_init(void) {
	printk(KERN_INFO "robin: starting character device driver\n");
	// Device name must match what is inside driver-config.sh variable `device`
	int result = alloc_chrdev_region(&dev, 0, COUNT, "robindev");
	major_number = MAJOR(dev);
	if (result < 0) {
		printk(KERN_WARNING "robin: can't get major %d\n", major_number);
		return result;
	} else {
		printk(KERN_INFO "robin: got major %d\n", major_number);
	}

	return 0;
}

static void hello_exit(void) {
	unregister_chrdev_region(dev, COUNT);
	printk(KERN_WARNING "Good bye!!!\n");
}

module_init(hello_init);
module_exit(hello_exit);
