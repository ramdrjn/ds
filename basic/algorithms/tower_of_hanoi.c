#include "utest/utest.h"
#include "algo_analysis.h"

void tower_of_hanoi(int n)
{
    //

    algo_steps++;
    algo_storage++;

    if (n==1)
        return 1;

    return n * gcd(n-1);
}

UTEST(math, gcd_4) {
    int n = 4;

    algo_steps = 0;
    algo_storage = 0;

    tower_of_hanoi(n);
    //EXPECT_EQ(, 24);

    algo_time_analysis(n, "n");
    algo_space_analysis(n, "n");
}
