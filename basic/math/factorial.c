#include "utest/utest.h"
#include "algo_analysis.h"

int factorial(int n)
{
    //n! = n * (n-1) * (n-2) .. * 2

    algo_steps++;
    algo_storage++;

    if (n==1)
        return 1;

    return n * factorial(n-1);
}

UTEST(math, factorial_4) {
    int n = 4;

    algo_steps = 0;
    algo_storage = 0;

    EXPECT_EQ(factorial(n), 24);

    algo_time_analysis(n, "n");
    algo_space_analysis(n, "n");
}
