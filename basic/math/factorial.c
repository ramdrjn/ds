#include "log.h"

int factorial(int n)
{
    //n! = n * (n-1) * (n-2) .. * 2

    if (n==1)
        return 1;

    return n * factorial(n-1);
}

void main()
{
    int n;
    info("enter n value:");
    scanf("%d", &n);
    info("factorial value of %d is %d \n", n, factorial(n));
}
