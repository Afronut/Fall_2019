#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main()
{

    syscall(548);
    int pointer;
    int val1 = 10;
    int val2 = 34;
    int result = syscall(549, val1, val2, &pointer);
    printf("The result of %d + %d is %d \n", val1, val2, pointer);
    return 0;
}