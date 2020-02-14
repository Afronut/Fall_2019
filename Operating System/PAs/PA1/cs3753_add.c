#include <linux/kernel.h>
#include <linux/linkage.h>
asmlinkage long sys_cs3753(int val1, int val2, int *addr)
{
    *addr = val1 + val2;
    printk(KERN_ALERT "%d + %d  is %d\n", val1, val2, *addr);
    return 0;
}