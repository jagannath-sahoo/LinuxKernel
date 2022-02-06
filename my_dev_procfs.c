#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>





/******************
 * Profs File operations
 *
    ssize_t	(*proc_read)(struct file *, char __user *, size_t, loff_t *);
	int	(*proc_open)(struct inode *, struct file *);
	ssize_t	(*proc_write)(struct file *, const char __user *, size_t, loff_t *);
    int	(*proc_release)(struct inode *, struct file *);
    */


#define KERN_BUFF_SIZE 4096

char kern_buff[KERN_BUFF_SIZE] = {0};
static int req_pid = 0;
static struct proc_dir_entry *parent;


static ssize_t mydev_proc_read(struct file *fptr, char __user *buff, size_t len, loff_t *f_pos)
{
    struct task_struct *task_list;

    pr_info("PROCFS read()\n");
    if( (*f_pos + len) > KERN_BUFF_SIZE)
    {
        len = KERN_BUFF_SIZE - *f_pos;
    }
    /*Reading Running Process on Kernel                     */
    
    
    for_each_process(task_list)/*This Macro intialize the task_list with "init_task" and print details*/
    {
        if (task_list->pid == req_pid)
        {
            sprintf(kern_buff,"Process %s, PID[%d]\n", task_list->comm, task_list->pid);
        }
    }
    /********************************************************/
    
    if(copy_to_user(buff, &kern_buff[*f_pos], len))
    {
        return -EFAULT;
    }
    *f_pos = *f_pos + len;

    pr_info("Number of bytes read %ld", len);
    pr_info("Updated file position %lld", *f_pos);
    return len;
}

static int	mydev_proc_open(struct inode *inode, struct file *fptr)
{
    pr_info("PROCFS Open()\n");
    return 0;
}

static int	mydev_proc_release(struct inode *inode, struct file *fptr)
{
    pr_info("PROCFS Close()\n");
    return 0;
}

static ssize_t mydev_proc_write(struct file *fptr, const char __user *buff, size_t len, loff_t *f_pos)
{
    pr_info("PROCFS write");
    if( (*f_pos + len) > KERN_BUFF_SIZE)
    {
        len = KERN_BUFF_SIZE - *f_pos;
    }
    if(!len)
    {
        pr_err("No Space left");
        return -ENOMEM;
    }

    if(copy_from_user(&kern_buff[*f_pos], buff, len))
    {
        return -EFAULT;
    }
    kstrtoint(&kern_buff[*f_pos], 10, &req_pid);
    pr_info("req_pid = %d", req_pid);
    
    *f_pos += len;

    pr_info("Number of bytes read %ld", len);
    pr_info("Updated file position %lld", *f_pos);

    return len;
}

static struct proc_ops proc_fops = {
    .proc_read = mydev_proc_read,
    .proc_write = mydev_proc_write,
    .proc_open = mydev_proc_open,
    .proc_release = mydev_proc_release
};

static __init int mydev_init(void)
{
    parent = proc_mkdir("mydev", NULL);
    if(parent == NULL)
    {
        pr_info("Error in creating proc entry\n");
        return -EFAULT;
    }
    proc_create("mydev_proc", 0666, parent, &proc_fops);
    pr_info("Device Driver Inserted... Done!");
    return 0;
}

static void __exit mydev_exit(void)
{
    proc_remove(parent);
    pr_info("Device Driver Remove... Done!");
}

module_init(mydev_init);
module_exit(mydev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jagannath");