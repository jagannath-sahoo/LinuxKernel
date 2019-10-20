# Understanding Jiffies and HZ
HZ representsthe size of a jiffy. HZ depends on the hardware and on the kernel version, and also determines how frequently the clock interrupt fires.
What it means is that jiffies is incremented HZ times every second. If HZ = 1,000, then it
is incremented 1,000 times (that is, one tick every 1/1,000 seconds). Once defined, the programmable interrupt timer (PIT), which is a hardware component,

## Header file location
```
/linux-source-4.15.0/include/linux/timer.h
```

```
struct timer_list {
        /*
         * All fields that change during normal runtime grouped to the
         * same cacheline
         */
        struct hlist_node       entry;
        unsigned long           expires;
        void                    (*function)(struct timer_list *);
        u32                     flags;

#ifdef CONFIG_LOCKDEP
        struct lockdep_map      lockdep_map;
#endif
};
```

## Setup Timer
 timer_setup - prepare a timer for first use \
 @timer: the timer in question\
 @callback: the function to call when timer expires\ 
 @flags: any TIMER_* flags\
Regular timer initialization should use either DEFINE_TIMER() above,
or timer_setup()
```
timer_setup(timer, callback, flags)
```
## Some other methods to setup timer
extern void add_timer_on(struct timer_list *timer, int cpu);\
extern int del_timer(struct timer_list * timer);\
extern int mod_timer(struct timer_list *timer, unsigned long expires);\
extern int mod_timer_pending(struct timer_list *timer, unsigned long expires);\
extern int timer_reduce(struct timer_list *timer, unsigned long expires);\
