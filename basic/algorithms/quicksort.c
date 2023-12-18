#include "utest/utest.h"
#include "algo_analysis.h"

void quicksort(int *n, int l, int r)
{
    int i = l;
    int j = r-1;
    int pivot = r;
    int temp;
    int loop_count = 0;
    int swap_count = 0;

    if (l >= r)
    {
        return;
    }

    //temp variable is the only storage required. In place swap of elements.
    algo_storage++;

    while (i < j)
    {
        loop_count++;
        algo_steps++;

        while(i < pivot && n[i]<=n[pivot])
        {
            loop_count++;
            algo_steps++;
            i++;
        }
        while(j > l && n[j]>=n[pivot])
        {
            loop_count++;
            algo_steps++;
            j--;
        }
        if(i<j)
        {
            algo_steps +=3;
            swap_count++;
            temp=n[j];
            n[j]=n[i];
            n[i]=temp;
        }
    }
    if (n[i] > n[pivot])
    {
        algo_steps +=3;
        swap_count++;
        temp=n[pivot];
        n[pivot]=n[i];
        n[i]=temp;
    }
    // Sort first and second halves
    quicksort(n, l, i - 1);
    quicksort(n, i + 1, r);

    //dbg("loop count %d", loop_count);
    //dbg("swap count %d", swap_count);
}

UTEST(math, quicksort_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    quicksort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, quicksort_bestcase_10) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    quicksort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, quicksort_worstcase) {
    int num_elements = 5;
    int n[5] = {5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    quicksort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, quicksort_worstcase_10) {
    int num_elements = 10;
    int n[10] = {10,9,8,7,6,5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    quicksort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, quicksort_averagecase) {
    int num_elements = 5;
    int n[5] = {3,4,1,5,2};

    algo_steps = 0;
    algo_storage = 0;

    quicksort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, quicksort_averagecase_10) {
    int num_elements = 10;
    int n[10] = {3,4,1,5,2,8,10,9,7,6};

    algo_steps = 0;
    algo_storage = 0;

    quicksort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

//example run
/*
initial: 5,2,4,1,3
*/
