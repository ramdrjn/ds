#include "utest/utest.h"
#include "algo_analysis.h"

int loop_count = 0;
int swap_count = 0;

void countingsort(int *n, int num_elements, int pos)
{
    int index;
    int counter[10] = {0};
    int temp[num_elements];

    //counter storage depends on the range
    algo_storage += 10;
    //storage for the temp array
    algo_storage += num_elements;

    //Count
    for(int i=0; i < num_elements; i++)
    {
        loop_count++;
        algo_steps++;

        index = (n[i] / pos) % 10;
        counter[index]++;
    }

    //Cummulative count
    for(int i=1; i < 10; i++)
    {
        loop_count++;
        algo_steps++;

        counter[i] += counter[i-1];
    }

    //Create sorted array
    for(int i = num_elements - 1; i >= 0; i--)
    {
        loop_count++;
        algo_steps++;

        index = (n[i] / pos) % 10;
        counter[index]--;
        temp[counter[index]] = n[i];
    }

    //Copy back to n array
    for(int i=0; i < num_elements; i++)
    {
        loop_count++;
        algo_steps++;

        n[i] = temp[i];
    }
}

//Time complexity is d*(n+k) where d is the number of digits in the max value.
//n is the number of elements and k is the range where in this case its 10.
void radixsort(int *n, int num_elements)
{
    int max=0;
    //find max number of digits of the maximum value in the array.
    for(int i=0; i < num_elements; i++)
    {
        loop_count++;
        algo_steps++;

        if(n[i] > max)
            max = n[i];
    }
    //get the current radix value and pass to counting sort
    for(int pos=1; max/pos > 0; pos *= 10)
    {
        loop_count++;
        algo_steps++;

        countingsort(n, num_elements, pos);
    }

    dbg("loop count %d", loop_count);
    dbg("swap count %d", swap_count);
}

UTEST(math, radixsort_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    radixsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "d*(n+k)");
    algo_space_analysis(num_elements, "n+k");
}

UTEST(math, radixsort_bestcase_10) {
    int num_elements = 10;
    int n[10] = {0,1,2,3,4,5,6,7,8,9};

    algo_steps = 0;
    algo_storage = 0;

    radixsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i);

    algo_time_analysis(num_elements, "d*(n+k)");
    algo_space_analysis(num_elements, "n+k");
}

UTEST(math, radixsort_worstcase) {
    int num_elements = 5;
    int n[10] = {515,424,333,242,151};
    int r[10] = {151,242,333,424,515};

    algo_steps = 0;
    algo_storage = 0;

    radixsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "d*(n+k)");
    algo_space_analysis(num_elements, "n+k");
}

UTEST(math, radixsort_worstcase_10) {
    int num_elements = 10;
    int n[10] = {909,818,727,636,545,454,363,272,181,90};
    int r[10] = {90,181,272,363,454,545,636,727,818,909};

    algo_steps = 0;
    algo_storage = 0;

    radixsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "d*(n+k)");
    algo_space_analysis(num_elements, "n+k");
}

UTEST(math, radixsort_worstcase_4) {
    int num_elements = 5;
    int n[10] = {515,442,4333,42,151};
    int r[10] = {42,151,442,515,4333};

    algo_steps = 0;
    algo_storage = 0;

    radixsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "d*(n+k)");
    algo_space_analysis(num_elements, "n+k");
}

UTEST(math, radixsort_averagecase) {
    int num_elements = 10;
    int n[10] = {356,6789,437,571,2437,752,683,29,85,358};
    int r[10] = {29,85,356,358,437,571,683,752,2437,6789};

    algo_steps = 0;
    algo_storage = 0;

    radixsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "d*(n+k)");
    algo_space_analysis(num_elements, "n+k");
}

//example run
/*
*/
