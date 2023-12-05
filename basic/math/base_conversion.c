#include "utest/utest.h"
#include "algo_analysis.h"

#define MAX_RESULT_BUF_SIZE 50
static char result_buf[MAX_RESULT_BUF_SIZE];
static int buf_index;

void convert(int n, int b)
{
    int reminder = n % b;
    char *remap="0123456789ABCDEF";

    algo_steps++;
    algo_storage++;

    if ((buf_index+1) == MAX_RESULT_BUF_SIZE)
    {
        err("conversion exceeds buffer size");
        return;
    }

    if (n /= b)
        convert(n, b);

    sprintf(&result_buf[buf_index++], "%c", remap[reminder]);
}

UTEST(math, base_conversion_2_256)
{
    int n = 256;

    algo_steps = 0;
    algo_storage = 0;

    buf_index=0;
    memset(result_buf, 0, sizeof(result_buf));

    convert(n, 2);
    EXPECT_STREQ(result_buf, "100000000");

    algo_time_analysis(n, "n");
    algo_space_analysis(n, "n");
}

UTEST(math, base_conversion_8_256)
{
    int n = 256;

    algo_steps = 0;
    algo_storage = 0;

    buf_index=0;
    memset(result_buf, 0, sizeof(result_buf));

    convert(n, 8);
    EXPECT_STREQ(result_buf, "400");

    algo_time_analysis(n, "n");
    algo_space_analysis(n, "n");
}

UTEST(math, base_conversion_16_256)
{
    int n = 256;

    algo_steps = 0;
    algo_storage = 0;

    buf_index=0;
    memset(result_buf, 0, sizeof(result_buf));

    convert(n, 16);
    EXPECT_STREQ(result_buf, "100");

    algo_time_analysis(n, "n");
    algo_space_analysis(n, "n");
}

UTEST(math, base_conversion_2_255)
{
    int n = 255;

    algo_steps = 0;
    algo_storage = 0;

    buf_index=0;
    memset(result_buf, 0, sizeof(result_buf));

    convert(n, 2);
    EXPECT_STREQ(result_buf, "11111111");

    algo_time_analysis(n, "n");
    algo_space_analysis(n, "n");
}

UTEST(math, base_conversion_8_255)
{
    int n = 255;

    algo_steps = 0;
    algo_storage = 0;

    buf_index=0;
    memset(result_buf, 0, sizeof(result_buf));

    convert(n, 8);
    EXPECT_STREQ(result_buf, "377");

    algo_time_analysis(n, "n");
    algo_space_analysis(n, "n");
}

UTEST(math, base_conversion_16_255)
{
    int n = 255;

    algo_steps = 0;
    algo_storage = 0;

    buf_index=0;
    memset(result_buf, 0, sizeof(result_buf));

    convert(n, 16);
    EXPECT_STREQ(result_buf, "FF");

    algo_time_analysis(n, "n");
    algo_space_analysis(n, "n");
}
