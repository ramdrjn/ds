#include "utest/utest.h"
#include "algo_analysis.h"

void selectionsortmax(int *n, int num_elements)
{
    //On every loop iteration move the largest values to the end

    int loop_count = 0;
    int swap_count = 0;
    int temp_index;
    int temp;
    int max_value_index;

    //temp variable is the only storage required. In place swap of elements.
    algo_storage++;

    //Loop from 1 to num_elements.
    for(int i = 0; i<num_elements-1; i++)
    {
        max_value_index = 0;
        temp_index=num_elements-i-1;
        //Loop from 1st element till num_elements - i -1
        for (int j = 1; j<=temp_index; j++)
        {
            loop_count++;
            algo_steps++;
            if(n[j] > n[max_value_index])
            {
                algo_steps++;
                max_value_index=j;
            }
            //else no need to update max_value_index
        }
        if(max_value_index < temp_index)
        {
            algo_steps +=3;
            swap_count++;
            //swap
            temp = n[temp_index];
            n[temp_index]=n[max_value_index];
            n[max_value_index]=temp;
        }
        /* else if (max_value_index > temp_index) */
        /* { */
        /*     err("invalid max_value_index %d vs temp_index %d", max_value_index, temp_index); */
        /* } */
        /* else */
        /* { */
        /*     dbg("same max_value_index %d vs temp_index %d", max_value_index, temp_index); */
        /* } */
    }
    dbg("loop count %d", loop_count);
    dbg("swap count %d", swap_count);
}

UTEST(sorting, ssort_max_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmax(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_max_bestcase_10) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmax(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_max_worstcase) {
    int num_elements = 5;
    int n[5] = {5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmax(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_max_worstcase_10) {
    int num_elements = 10;
    int n[10] = {10,9,8,7,6,5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmax(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_max_averagecase) {
    int num_elements = 5;
    int n[5] = {3,4,1,5,2};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmax(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_max_averagecase_10) {
    int num_elements = 10;
    int n[10] = {3,4,1,5,2,8,10,9,7,6};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmax(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_max_stablecase) {
    int num_elements = 10;
    int n[10] = {6,4,7,1,7,2,3,9,5,8};
    int r[10] = {1,2,3,4,5,6,7,7,8,9};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmax(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_max_randomcase) {
    int num_elements = 10;
    int n[10] = {583,31,6,244,4767,322,46,689,765,238};
    int r[10] = {6,31,46,238,244,322,583,689,765,4767};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmax(n, num_elements);

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
    max_value_index=0
  inner_loop 1:
  1>2:                 max_value_index=1
  inner_loop 2:
  2>3:                 max_value_index=2
  inner_loop 3:
  3>4:                 max_value_index=3
  inner_loop 4:
  4>5:                 max_value_index=4
  no swap since max_value_index == num_elements-i
  1,2,3,4,5
outer_loop 2:
    max_value_index=0
  inner_loop 1:
  1>2:                 max_value_index=1
  inner_loop 2:
  2>3:                 max_value_index=2
  inner_loop 3:
  3>4:                 max_value_index=3
  no swap since max_value_index == num_elements-i
  1,2,3,4,5
outer_loop 3:
    max_value_index=0
  inner_loop 1:
  1>2:                 max_value_index=1
  inner_loop 2:
  2>3:                 max_value_index=2
  no swap since max_value_index == num_elements-i
  1,2,3,4,5
outer_loop 4:
    max_value_index=0
  inner_loop 1:
  1>2:                 max_value_index=1
  no swap since max_value_index == num_elements-i
  1,2,3,4,5

total outer loops: 4 i.e num elements -1
total inner loops: 10
total swap: 0

worst case: 5,4,3,2,1
Quadratic time

outer_loop 1:
    max_value_index=0
  inner_loop 1:
  5>4:                 no index update
  inner_loop 2:
  5>3:                 no index update
  inner_loop 3:
  5>2:                 no index update
  inner_loop 4:
  5>1:                 no index update
  swap max_value_index and num_elements - i -1 //since index starts from 0
  1,4,3,2,5
outer_loop 2:
    max_value_index=0
  inner_loop 1:
  1>4:                 max_value_index=1
  inner_loop 2:
  4>3:                 no index update
  inner_loop 3:
  4>2:                 no index update
  swap max_value_index and num_elements - i -1 //since index starts from 0
  1,2,3,4,5
outer_loop 3:
    max_value_index=0
  inner_loop 1:
  1>2:                 max_value_index=1
  inner_loop 2:
  2>3:                 max_value_index=2
  no swap
  1,2,3,4,5
outer_loop 4:
    max_value_index=0
  inner_loop 1:
  1>2:                 max_value_index=1
  no swap
  1,2,3,4,5

total outer loops: 4 i.e num elements -1
total inner loops: 10
total swap: 2
*/

//Selection based on minimum value
void selectionsortmin(int *n, int num_elements)
{
    //On every loop iteration move the minimum value to the front

    int loop_count = 0;
    int swap_count = 0;
    int temp;
    int min_value_index;

    //temp variable is the only storage required. In place swap of elements.
    algo_storage++;

    //Loop from 0 to num_elements.
    for(int i = 0; i<num_elements-1; i++)
    {
        min_value_index = i;

        //loop from element next to the min to num_elements.
        for (int j = i+1; j<num_elements; j++)
        {
            loop_count++;
            algo_steps++;
            if(n[j] < n[min_value_index])
            {
                algo_steps++;
                min_value_index=j;
            }
            //else no need to update min_value_index
        }

        if (min_value_index > i)
        {
            algo_steps +=3;
            swap_count++;
            //swap
            temp = n[i];
            n[i]=n[min_value_index];
            n[min_value_index]=temp;
        }
    }
    dbg("loop count %d", loop_count);
    dbg("swap count %d", swap_count);
}

UTEST(sorting, ssort_min_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmin(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_min_bestcase_10) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmin(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_min_worstcase) {
    int num_elements = 5;
    int n[5] = {5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmin(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_min_worstcase_10) {
    int num_elements = 10;
    int n[10] = {10,9,8,7,6,5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmin(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_min_averagecase) {
    int num_elements = 5;
    int n[5] = {3,4,1,5,2};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmin(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_min_averagecase_10) {
    int num_elements = 10;
    int n[10] = {3,4,1,5,2,8,10,9,7,6};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmin(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_min_stablecase) {
    int num_elements = 10;
    int n[10] = {6,4,7,1,7,2,3,9,5,8};
    int r[10] = {1,2,3,4,5,6,7,7,8,9};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmin(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, ssort_min_randomcase) {
    int num_elements = 10;
    int n[10] = {583,31,6,244,4767,322,46,689,765,238};
    int r[10] = {6,31,46,238,244,322,583,689,765,4767};

    algo_steps = 0;
    algo_storage = 0;

    selectionsortmin(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}
