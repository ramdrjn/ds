#include "utest/utest.h"
#include "algo_analysis.h"
#include <stdbool.h>

//also called sequemtial search. Tell if the value is present in the
//list or not.
bool linear_search_unsorted(int *n, int num_elements, int element)
{
    //Iterate and find the element by comparing it with each element

    int loop_count = 0;

    for (int i=0; i< num_elements; i++)
    {
        loop_count++;
        algo_steps++;

        if(n[i] == element)
        {
            dbg("loop count %d", loop_count);
            return true;
        }
    }

    dbg("loop count %d", loop_count);

    return false;
}

bool linear_search_sorted(int *n, int num_elements, int element)
{
    //Same as unsorted but check if the next value is greater than the
    //element. If so then return false since the element is not present.

    int loop_count = 0;

    for (int i=0; i< num_elements; i++)
    {
        loop_count++;
        algo_steps++;

        if(n[i] == element)
        {
            dbg("loop count %d", loop_count);
            return true;
        }
        if (n[i] > element)
        {
            dbg("loop count %d", loop_count);
            return false;
        }
    }

    dbg("loop count %d", loop_count);

    return false;
}

UTEST(math, linearsearch_unsorted_unsorted_found) {
    int num_elements = 10;
    int n[10] = {9,8,7,6,5,9,4,3,2,1};
    int element = 4;
    bool result;

    algo_steps = 0;
    algo_storage = 0;

    result = linear_search_unsorted(n, num_elements, element);

    EXPECT_EQ(result, 1);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

UTEST(math, linearsearch_unsorted_sorted_found) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,9};
    int element = 4;
    bool result;

    algo_steps = 0;
    algo_storage = 0;

    result = linear_search_unsorted(n, num_elements, element);

    EXPECT_EQ(result, 1);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

UTEST(math, linearsearch_unsorted_unsorted_notfound) {
    int num_elements = 10;
    int n[10] = {9,8,7,6,5,9,2,3,2,1};
    int element = 4;
    bool result;

    algo_steps = 0;
    algo_storage = 0;

    result = linear_search_unsorted(n, num_elements, element);

    EXPECT_EQ(result, 0);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

UTEST(math, linearsearch_unsorted_sorted_notfound) {
    int num_elements = 10;
    int n[10] = {1,2,3,3,5,6,7,8,9,9};
    int element = 4;
    bool result;

    algo_steps = 0;
    algo_storage = 0;

    result = linear_search_unsorted(n, num_elements, element);

    EXPECT_EQ(result, 0);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

UTEST(math, linearsearch_sorted_sorted_found) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,9};
    int element = 4;
    bool result;

    algo_steps = 0;
    algo_storage = 0;

    result = linear_search_sorted(n, num_elements, element);

    EXPECT_EQ(result, 1);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

UTEST(math, linearsearch_sorted_sorted_notfound) {
    int num_elements = 10;
    int n[10] = {1,2,3,3,5,6,7,8,9,9};
    int element = 4;
    bool result;

    algo_steps = 0;
    algo_storage = 0;

    result = linear_search_sorted(n, num_elements, element);

    EXPECT_EQ(result, 0);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

//example run
/*
 */
