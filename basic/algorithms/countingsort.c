#include "utest/utest.h"
#include "algo_analysis.h"

void countingsort(int *n, int range_lower, int range_upper, int num_elements)
{
    //Count the occurances of the values and update that in their
    //corresponding index in the counting array.
    //Once all the element's count values are updated, recreate the list
    //based on the count values.

    int loop_count = 0;
    int swap_count = 0;

    int counter[range_upper-range_lower+1];
    int index_adjust=range_lower;
    int index=0;

    //counter storage depends on the range
    algo_storage += sizeof(counter)/sizeof(int);

    memset(counter, 0, sizeof(counter));

    //Loop from 1 to num_elements.
    for(int i = 0; i<num_elements; i++)
    {
        loop_count++;
        algo_steps++;

        index=n[i]-index_adjust;
        counter[index] += 1;
    }
    //for (int i = 0; i < range_upper-range_lower+1; i++)
    //    printf("%d ",counter[i]);

    //Recreate array but with sorted elements
    for(int i = 0, index=0; index<num_elements;i++)
    {
        loop_count++;
        algo_steps++;

        for(int j=0; j<counter[i]; j++)
        {
            loop_count++;
            algo_steps++;

            n[index]=i+index_adjust;
            index++;
        }
    }

    dbg("loop count %d", loop_count);
    dbg("swap count %d", swap_count);
}

UTEST(math, csort_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 5, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, csort_bestcase_10) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 10, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, csort_worstcase) {
    int num_elements = 5;
    int n[5] = {5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 5, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, csort_worstcase_10) {
    int num_elements = 10;
    int n[10] = {10,9,8,7,6,5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 10, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, csort_averagecase) {
    int num_elements = 5;
    int n[5] = {3,4,1,5,2};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 5, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, csort_averagecase_10) {
    int num_elements = 10;
    int n[10] = {3,4,1,5,2,8,10,9,7,6};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 10, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, csort_stablecase) {
    int num_elements = 10;
    int n[10] = {6,4,7,1,7,2,3,9,5,8};
    int r[10] = {1,2,3,4,5,6,7,7,8,9};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 9, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, csort_dupelementscase) {
    int num_elements = 10;
    int n[10] = {9,4,7,1,7,9,3,9,5,8};
    int r[10] = {1,3,4,5,7,7,8,9,9,9};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 9, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, csort_rangecase) {
    int num_elements = 10;
    int n[10] = {26,24,27,21,27,22,23,29,25,28};
    int r[10] = {21,22,23,24,25,26,27,27,28,29};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 21, 29, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

//example run
/*
*/