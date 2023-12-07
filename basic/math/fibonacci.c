#include "utest/utest.h"
#include "algo_analysis.h"

int fibonacci_number(int n)
{
    //Xn = Xn-1 + Xn-2
    //Fibonacci number is computed by sum of previous two
    //fibonacci number from the series.

    algo_steps++;
    algo_storage++;

    if (n <= 1)
        return n;

    return fibonacci_number(n-1) + fibonacci_number(n-2);
}

UTEST(math, fibonacci_10) {
    int n = 10;

    algo_steps = 0;
    algo_storage = 0;

    EXPECT_EQ(fibonacci_number(n), 55);

    algo_time_analysis(n, "2^n");
    algo_space_analysis(n, "2^n");
}

UTEST(math, fibonacci_11) {
    int n = 11;

    algo_steps = 0;
    algo_storage = 0;

    EXPECT_EQ(fibonacci_number(n), 89);

    algo_time_analysis(n, "2^n");
    algo_space_analysis(n, "2^n");
}

UTEST(math, fibonacci_12) {
    int n = 12;

    algo_steps = 0;
    algo_storage = 0;

    EXPECT_EQ(fibonacci_number(n), 144);

    algo_time_analysis(n, "2^n");
    algo_space_analysis(n, "2^n");
}

//The growth of function is exponantial
