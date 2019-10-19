# GFP_KERNEL
The prototype of kmalloc is:

void *kmalloc(size_t size,int flags);

The first argument to the kmalloc is the size of the block to be allocated.The second argument is allocation flag.

The most commonly used allocation flag is GFP_KERNEL means that allocation is performed on behalf of a process running in the kernel space.This means that the calling function is executing a system call on behalf of a process.**_Using GFP_KERNEL means that kmalloc can put the current process to sleep waiting for a page when called in low-memory situations._**

A function that allocates memory using GFP_KERNEL must, therefore, be reentrant and cannot be running in atomic context. While the current process sleeps, the kernel takes proper action to **_locate some free memory,_** either by **_flushing buffers to disk or by swapping out memory_** from a user process.