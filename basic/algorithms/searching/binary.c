#include "utest/utest.h"
#include "algo_analysis.h"
#include <stdbool.h>

bool binary_search(int *n, int element, int start, int end)
{
    //check mid point against the element value. If its the same return true
    //if not check whether its less or greater than the element.
    //depending on the value either move left or right for continuing search.

    int mid;
    int loop_count = 0;

    for (int i=start; i<end;i++)
    {
        loop_count++;
        algo_steps++;

        mid=(start+end)/2;
        //l is from start to mid. r is from mid to end
        if(element == n[mid])
            return true;
        else if(element > n[mid])
            start=mid+1;//start looking right side
        else
            end=mid;//start looking on left
    }

    dbg("loop count %d", loop_count);

    return false;
}

bool binary_search_recursive(int *n, int element, int start, int end)
{
    //Same as above just use recursion.

    int mid;
    int loop_count = 0;

    loop_count++;
    algo_steps++;

    if(start>end)
        return false;

    mid=(start+end)/2;
    //l is from start to mid. r is from mid to end
    if(element == n[mid])
        return true;
    else if(element > n[mid])
        //start looking right side
        return binary_search_recursive(n, element, mid+1, end);
    else
        //start looking on left
        return binary_search_recursive(n, element, start, mid-1);

    dbg("loop count %d", loop_count);

    return false;
}

UTEST(search, binarysearch_found) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,9};
    int element = 4;
    bool result;

    algo_steps = 0;
    algo_storage = 0;

    result = binary_search(n, element, 0, num_elements);

    EXPECT_EQ(result, 1);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

UTEST(search, binarysearch_notfound) {
    int num_elements = 10;
    int n[10] = {1,2,3,3,5,6,7,8,9,9};
    int element = 4;
    bool result;

    algo_steps = 0;
    algo_storage = 0;

    result = binary_search(n, element, 0, num_elements);

    EXPECT_EQ(result, 0);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

UTEST(search, binarysearch_recursive_found) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,9};
    int element = 4;
    bool result;

    algo_steps = 0;
    algo_storage = 0;

    result = binary_search_recursive(n, element, 0, num_elements);

    EXPECT_EQ(result, 1);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

UTEST(search, binarysearch_recursive_notfound) {
    int num_elements = 10;
    int n[10] = {1,2,3,3,5,6,7,8,9,9};
    int element = 4;
    bool result;

    algo_steps = 0;
    algo_storage = 0;

    result = binary_search_recursive(n, element, 0, num_elements);

    EXPECT_EQ(result, 0);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

//example run
/*
 */
