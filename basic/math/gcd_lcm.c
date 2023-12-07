#include "utest/utest.h"
#include "algo_analysis.h"

int gcd(int n, int m)
{
    //Euclidean algorithm
    //gcd(n,m) = gcd(n, r) where n=mq+r and provided n>m and m!= 0
    //gcd(any_num, 0) is any_num
    //therefore when r becomes 0 then gcd value equals value of n at that time.

    algo_steps++;
    algo_storage++;

    if (m==0)
        return n;

    dbg("value of n %d mod m %d is %d", n, m, n%m);

    //Single line but adds another recursion.
    /*
      For gcd(4,16)
      DBG: value of n 4 mod m 16 is 4
      DBG: value of n 16 mod m 4 is 0

      for gcd(16,4)
      DBG: value of n 16 mod m 4 is 0
     */
    //return gcd(m, n%m);

    //Checking condition avoids recursion
    /*
      For gcd(4,16)
      DBG: value of n 4 mod m 16 is 4

      for gcd(16,4)
      DBG: value of n 16 mod m 4 is 0
     */
    if (n>m)
        return gcd(m, n%m);
    else
        return gcd(n, m%n);
}

int lcm(int n, int m)
{
    //Using principle lcm(n,m) = n*m / gcd(n,m)
    return (n*m/gcd(n,m));
}

UTEST(math, gcd_16_4) {
    int n = 16;
    int m = 4;

    algo_steps = 0;
    algo_storage = 0;

    EXPECT_EQ(gcd(n, m), 4);

    algo_time_analysis(n, "log(min(n, m))");
    algo_space_analysis(n, "log(min(n,m))");
}

UTEST(math, gcd_4_16) {
    int n = 4;
    int m = 16;

    algo_steps = 0;
    algo_storage = 0;

    EXPECT_EQ(gcd(n, m), 4);

    algo_time_analysis(n, "log(min(n, m))");
    algo_space_analysis(n, "log(min(n,m))");
}

UTEST(math, lcm_4_16) {
    int n = 4;
    int m = 16;

    algo_steps = 0;
    algo_storage = 0;

    EXPECT_EQ(lcm(n, m), 16);

    algo_time_analysis(n, "log(min(n, m))");
    algo_space_analysis(n, "log(min(n,m))");
}
