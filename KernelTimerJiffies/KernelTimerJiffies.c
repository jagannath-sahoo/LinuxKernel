#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/time.h>

#define TIMER_TIMEOUT   1000

void my_timer_callback(struct timer_list *timer_handle)
{
    int retval;
    printk(KERN_INFO" %s called (%ld) %d HZ\n",__FUNCTION__, jiffies, HZ);
    /*Setup Again*/
    retval = mod_timer(timer_handle, jiffies + msecs_to_jiffies(TIMER_TIMEOUT));
    if(retval){/*Error Handling*/
        printk(KERN_INFO"Timer Failed");
    }
}

static int __init my_init(void);
static void __exit my_exit(void);

static struct timer_list my_timer = {
    .function = &my_timer_callback
};

static int __init my_init(void)
{
    int retval;
    printk("Timer module loaded into kernel.\n");
    /*step 1. Setup timer*/
    timer_setup(&my_timer,my_timer_callback,0);
    printk(KERN_INFO"Setup timer to fore in every %d ms (%ld)\n", TIMER_TIMEOUT,jiffies);
    /*step 2. Setup timer to expiry*/
    retval = mod_timer(&my_timer, jiffies + msecs_to_jiffies(TIMER_TIMEOUT));
    if(retval){/*Error Handling*/
        printk(KERN_INFO"Timer Failed");
    }
    return 0;
}

static void __exit my_exit(void)
{
    int retval;
    /*step 3. Delete timer*/
    retval = del_timer(&my_timer);
    if(retval){/*Error Handling*/
         printk(KERN_INFO"Timer Deletion Failed! Still in use\n");
    }
    printk("Timer module unloaded from kernel.\n");
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("Jagannath Sahoo");
MODULE_DESCRIPTION("Timer demo");
MODULE_LICENSE("GPL");