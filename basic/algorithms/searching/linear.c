#include "utest/utest.h"
#include "algo_analysis.h"

int linear_search(int *n, int num_elements, int element)
{
    //Iterate and find the element by comparing it with each element

    int i;
    int loop_count = 0;

    for (i=0; i< num_elements; i++)
    {
        loop_count++;
        algo_steps++;

        if(n[i] == element)
            break;
    }

    if(i == num_elements-1)
        i=-1;

    dbg("loop count %d", loop_count);

    return i;
}

UTEST(math, linearsearch_unsorted) {
    int num_elements = 10;
    int n[10] = {9,8,7,6,5,9,4,3,2,1};
    int element = 4;
    int result_index;

    algo_steps = 0;
    algo_storage = 0;

    result_index = linear_search(n, num_elements, element);

    EXPECT_NE(result_index, -1);
    EXPECT_EQ(element, n[result_index]);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

UTEST(math, linearsearch_sorted) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,9};
    int element = 4;
    int result_index;

    algo_steps = 0;
    algo_storage = 0;

    result_index = linear_search(n, num_elements, element);

    EXPECT_NE(result_index, -1);
    EXPECT_EQ(element, n[result_index]);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

//example run
/*
 */
