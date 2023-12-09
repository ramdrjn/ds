#include "utest/utest.h"
#include "algo_analysis.h"
#include <stdbool.h>

void bubblesort(int *n, int num_elements)
{
    //compare two adjascent elements and check if they need to be
    //swapped.

    //optimization 1. Break from outer loop if no swapping has occurred.
    //Optimizes the best case performance.

    int loop_count = 0;
    int swap_count = 0;
    int temp;
    bool swap_done = false;

    //temp variable is the only storage required. In place swap of elements.
    algo_storage++;

    //Loop from 1 to num_elements.
    for(int i = 0; i<num_elements-1; i++)
    {
        //Loop from 1 to num_elements-j.
        for (int j = 0; j<num_elements-1-i; j++)
        {
            swap_done=false;
            loop_count++;
            algo_steps++;
            if(n[j] > n[j+1])
            {
                swap_done=true;
                algo_steps +=3;
                swap_count++;
                //swap
                temp = n[j];
                n[j]=n[j+1];
                n[j+1]=temp;
            }
            //else no need to swap
        }
        if (!swap_done)
            break;
    }
    dbg("loop count %d", loop_count);
    dbg("swap count %d", swap_count);
}

UTEST(math, bbsort_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    bubblesort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n"); //with optimization 1
    algo_space_analysis(num_elements, "1");
}

UTEST(math, bbsort_bestcase_10) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    bubblesort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n"); //with optimization 1
    algo_space_analysis(num_elements, "1");
}

UTEST(math, bbsort_worstcase) {
    int num_elements = 5;
    int n[5] = {5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    bubblesort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, bbsort_worstcase_10) {
    int num_elements = 10;
    int n[10] = {10,9,8,7,6,5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    bubblesort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, bbsort_averagecase) {
    int num_elements = 5;
    int n[5] = {3,4,1,5,2};

    algo_steps = 0;
    algo_storage = 0;

    bubblesort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, bbsort_averagecase_10) {
    int num_elements = 10;
    int n[10] = {3,4,1,5,2,8,10,9,7,6};

    algo_steps = 0;
    algo_storage = 0;

    bubblesort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, bbsort_stablecase) {
    int num_elements = 10;
    int n[10] = {6,4,7,1,7,2,3,9,5,8};
    int r[10] = {1,2,3,4,5,6,7,7,8,9};

    algo_steps = 0;
    algo_storage = 0;

    bubblesort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

//example run
/*

best case: 1,2,3,4,5
Linear time

outer_loop 1:
  inner_loop 1:
    1<2:                no swap
    1,2,3,4,5
  inner_loop 2:
    2<3:                no swap
    1,2,3,4,5
  inner_loop 3:
    3<4:                no swap
    1,2,3,4,5
  inner_loop 4:
    4<5:                no swap
    1,2,3,4,5
                      << with optimization 1 the loop breaks out >>
outer_loop 2:
  inner_loop 1:
    1<2:                no swap
    1,2,3,4,5
  inner_loop 2:
    2<3:                no swap
    1,2,3,4,5
  inner_loop 3:
    3<4:                no swap
    1,2,3,4,5
outer_loop 3:
  inner_loop 1:
    1<2:                no swap
    1,2,3,4,5
  inner_loop 2:
    2<3:                no swap
    1,2,3,4,5
outer_loop 4:
  inner_loop 1:
    1<2:                no swap
    1,2,3,4,5

total outer loops: 4 i.e num elements -1
total inner loops: 10
total swap: 0

worst case: 5,4,3,2,1
Quadratic time

outer_loop 1:
  inner_loop 1:
    5<4:                swap 1
    4,5,3,2,1
  inner_loop 2:
    5<3:                swap 2
    4,3,5,2,1
  inner_loop 3:
    5<2:                swap 3
    4,3,2,5,1
  inner_loop 4:
    5<1:                swap 4
    4,3,2,1,5
outer_loop 2:
  inner_loop 1:
    4<3:                swap 5
    3,4,2,1,5
  inner_loop 2:
    4<2:                swap 6
    3,2,4,1,5
  inner_loop 3:
    4<1:                swap 7
    3,2,1,4,5
outer_loop 3:
  inner_loop 1:
    3<2:                swap 8
    2,3,1,4,5
  inner_loop 2:
    3<1:                swap 9
    2,1,3,4,5
outer_loop 4:
  inner_loop 1:
    2<1:                swap 10
    1,2,3,4,5

total outer loops: 4 i.e num elements -1
total inner loops: 10
total swap: 10
*/
