#include "utest/utest.h"
#include "algo_analysis.h"

void insertionsort(int *n, int num_elements)
{
    //compare inserted elementand previous and check if they need to be
    //swapped. If yes then shift right and swap.

    int loop_count = 0;
    int swap_count = 0;
    int temp;

    //temp variable is the only storage required. In place swap of elements.
    algo_storage++;

    //Loop from 2nd element to num_elements.
    for(int i = 1; i<num_elements; i++)
    {
        //Loop from ith element to 0th element. Loop backwards.
        for (int j = i; j; j--)
        {
            loop_count++;
            algo_steps++;
            if(n[j] < n[j-1])
            {
                algo_steps +=3;
                swap_count++;
                //swap and shift
                temp = n[j];
                n[j]=n[j-1];
                n[j-1]=temp;
            }
            //else no need to swap
        }
    }
    dbg("loop count %d", loop_count);
    dbg("swap count %d", swap_count);
}

UTEST(math, inssort_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    insertionsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, inssort_bestcase_10) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    insertionsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, inssort_worstcase) {
    int num_elements = 5;
    int n[5] = {5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    insertionsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, inssort_worstcase_10) {
    int num_elements = 10;
    int n[10] = {10,9,8,7,6,5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    insertionsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, inssort_averagecase) {
    int num_elements = 5;
    int n[5] = {3,4,1,5,2};

    algo_steps = 0;
    algo_storage = 0;

    insertionsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, inssort_averagecase_10) {
    int num_elements = 10;
    int n[10] = {3,4,1,5,2,8,10,9,7,6};

    algo_steps = 0;
    algo_storage = 0;

    insertionsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

//example run
/*

best case: 1,2,3,4,5
Linear time

outer_loop 1:    //can be optimized out by starting loop from next element
    insert 1
    1:                  no swap
    1,2,3,4,5
outer_loop 2:
    insert 2
  inner_loop:1
    2<1:                no swap
    1,2,3,4,5
outer_loop 3:
    insert 3
  inner_loop:1
    3<1:                no swap
    1,2,3,4,5
  inner_loop 2:
    3<2:                no swap
    1,2,3,4,5
outer_loop 4:
    insert 4
  inner_loop 1:
    4<1:                no swap
    1,2,3,4,5
  inner_loop 2:
    4<2:                no swap
    1,2,3,4,5
  inner_loop 3:
    4<3:                no swap
    1,2,3,4,5
outer_loop 5:
    insert 4
  inner_loop 1:
    5<1:                no swap
    1,2,3,4,5
  inner_loop 2:
    5<2:                no swap
    1,2,3,4,5
  inner_loop 3:
    5<3:                no swap
    1,2,3,4,5
  inner_loop 4:
    5<4:                no swap
    1,2,3,4,5

total outer loops: 5. 4 i.e num elements -1 if first starting from 2nd element.
total inner loops: 10
total swap: 0

worst case: 5,4,3,2,1
Quadratic time

outer_loop 1:    //can be optimized out by starting loop from next element
    insert 5
    5:                  no swap
    5,4,3,2,1
outer_loop 2:
    insert 4
  inner_loop:1
    4<5:
    shift 5 by 1        shift 1
    4,5,3,2,1
outer_loop 3:
    insert 3
  inner_loop:1
    3<5:
    shift 5 by 1        shift 2
    4,3,5,2,1
  inner_loop 2:
    3<4:
    shift 4 by 1        shift 3
    3,4,5,2,1
outer_loop 4:
    insert 2
  inner_loop 1:
    2<5:
    shift 5 by 1        shift 4
    3,4,2,5,1
  inner_loop 2:
    2<4:
    shift 4 by 1        shift 5
    3,2,4,5,1
  inner_loop 3:
    2<3:
    shift 3 by 1        shift 6
    2,3,4,5,1
outer_loop 5:
    insert 1
  inner_loop 1:
    1<5:
    shift 5 by 1        shift 7
    2,3,4,1,5
  inner_loop 2:
    1<4:
    shift 4 by 1        shift 8
    2,3,1,4,5
  inner_loop 3:
    1<3:
    shift 3 by 1        shift 9
    2,1,3,4,5
  inner_loop 4:
    1<2:
    shift 2 by 1        shift 10
    1,2,3,4,5


total outer loops: 4 i.e num elements -1
total inner loops: 10
total swap: 10
*/

//Best case O(n) rather than O(n^2) ?
