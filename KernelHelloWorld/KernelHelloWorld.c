#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>

/*
 *  Define function prototype for init() and exit() methods   
 */
static int __init hello_world_init(void);
static void __exit hello_world_exit(void);

static int __init hello_world_init(void)
{
    printk(KERN_INFO "Welcome to Kernel Module!");
    return 0;
}

static void __exit hello_world_exit(void)
{
    printk(KERN_INFO "Bye to Kernel Module!");
}

//Enter to kernel module
module_init(hello_world_init);
module_exit(hello_world_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jagannath <jagannath23sahoo@gmail.com>");
MODULE_DESCRIPTION("Hello World Kernel");
MODULE_VERSION("2:1.0");
