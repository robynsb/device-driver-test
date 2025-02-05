#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("Dual BSD/GPL");

dev_t dev;
unsigned int COUNT = 4;
int major_number;
struct cdev cdev;
struct file_operations fops;

int rbn_open(struct inode *inode, struct file *filp) {
	printk(KERN_INFO "robin: opened\n");
	return 0;
}

int rbn_release(struct inode *inode, struct file *filp) {
	printk(KERN_INFO "robin: released\n");
	return 0;
}

static int hello_init(void) {
	printk(KERN_INFO "robin: starting character device driver\n");
	// Device name must match what is inside driver-config.sh variable `device`
	int result = alloc_chrdev_region(&dev, 0, COUNT, "robindev");
	major_number = MAJOR(dev);
	if (result < 0) {
		printk(KERN_WARNING "robin: ERROR: can't get major %d\n", major_number);
		return result;
	} else {
		printk(KERN_INFO "robin: got major %d\n", major_number);
	}
	// TODO: initialise fops
	fops.open = &rbn_open;
	fops.release = &rbn_release;

	cdev_init(&cdev, &fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &fops;
	result = cdev_add(&cdev, dev, COUNT); // last param is usually 1. shift dev with MKDEV.
	if (result < 0) {
		printk(KERN_WARNING "robin: ERROR: could not add device");
		return result;
	} else {
		printk(KERN_INFO "robin: added device\n");
	}

	return 0;
}

static void hello_exit(void) {
	cdev_del(&cdev);
	unregister_chrdev_region(dev, COUNT);
	printk(KERN_WARNING "Good bye!!!\n");
}

module_init(hello_init);
module_exit(hello_exit);
