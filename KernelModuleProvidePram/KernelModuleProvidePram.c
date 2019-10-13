#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/sizes.h>

#define MAX_ARR_SIZE    5

int uVal = 0;
int uArr_Val[MAX_ARR_SIZE] = { 0 };
char *sName;
int uCBValue = 0;


module_param(uVal, int, S_IRUSR|S_IWUSR);
module_param(sName, charp, S_IRUSR | S_IWUSR);
module_param_array(uArr_Val, int, NULL, S_IRUSR|S_IWUSR);

static int notify_callback(const char *val, const struct kernel_param *kp);
static int __init KernelModuleProvidePram_init(void);
static void __exit KernelModuleProvidePram_exit(void);

// struct kernel_param_ops {
// 	/* How the ops should behave */
// 	unsigned int flags;
// 	/* Returns 0, or -errno.  arg is in kp->arg. */
// 	int (*set)(const char *val, const struct kernel_param *kp);
// 	/* Returns length written or -errno.  Buffer is 4k (ie. be short!) */
// 	int (*get)(char *buffer, const struct kernel_param *kp);
// 	/* Optional function to free kp->arg when module unloaded. */
// 	void (*free)(void *arg);
// };

static int notify_callback(const char *val, const struct kernel_param *kp)
{
    int res = param_set_int(val, kp);//Helper macro for write variable 
    if(res == 0)
    {
        printk(KERN_INFO "Callback method called...\n");
        printk(KERN_INFO "New Value of uCBValue = %d\n",uCBValue);
        return 0;
    }
    return -1;
}

const struct kernel_param_ops param_ops = {
    .set = &notify_callback, //Usr notify_callback

};

//Export uCBValue
module_param_cb(uCBValue, &param_ops, &uCBValue, S_IRUSR|S_IWUSR);

static int __init KernelModuleProvidePram_init(void)
{
    size_t i = 0;
    printk(KERN_INFO "uVal = %d\n", uVal);
    printk(KERN_INFO "uCBValue = %d\n", uCBValue);
    printk(KERN_INFO "sName = %s\n", sName);
    for (i = 0; i < MAX_ARR_SIZE; i++)
    {
         printk(KERN_INFO "uArr_Val[%ld] = %d\n", i, uArr_Val[i]);
    }
    printk(KERN_INFO "Kernel Module Inserted Succcessful...\n");
    return 0;
}

void __exit KernelModuleProvidePram_exit(void)
{
    printk(KERN_INFO "Kernel Module Removed Succcessful...\n");
}

module_init(KernelModuleProvidePram_init);
module_exit(KernelModuleProvidePram_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jagannath <jagannath23sahoo@gmail.com>");
MODULE_DESCRIPTION("Kernel Module to Provide Parameter from outside");
MODULE_VERSION("1.0");