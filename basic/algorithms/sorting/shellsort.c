#include "utest/utest.h"
#include "algo_analysis.h"

void shellsort(int *n, int num_elements)
{
    //Improves insertion sort by reducing number of shift and swaps.
    //Especially true if the smallest elements are placed at the end.
    //Their distance to the destination is large.
    //Shell sort is optimized for this case and improves over insertion sort.
    //Rather than comparing adjascent elements compare elements at a distant.
    //If element is less in value at the Gap interval, then swap them.
    //Number of comparisons increase but number of shift operations decrease.

    int loop_count = 0;
    int swap_count = 0;
    int temp, i;

    //temp variable is the only storage required. In place swap of elements.
    algo_storage++;

    //Loop until gap is valid.
    for(int gap = num_elements/2; gap; gap /= 2)
    {
        i = 0;
        for (int j = gap; j<num_elements; j++)
        {
            //i follows j with a distance of gap
            //i-=gap is important because this will check for reverse
            //element comparison
            for(i=j-gap; i>=0 && (n[i+gap] < n[i]); i-=gap)
            {
                loop_count++;
                algo_steps +=3;
                swap_count++;
                //swap
                temp = n[i+gap];
                n[i+gap]=n[i];
                n[i]=temp;
            }
            /* //dbg("  i %d j %d ", i,j); */
            /* loop_count++; */
            /* algo_steps++; */
            /* if(n[i] > n[j]) */
            /* { */
            /*     algo_steps +=3; */
            /*     swap_count++; */
            /*     //swap */
            /*     temp = n[j]; */
            /*     n[j]=n[i]; */
            /*     n[i]=temp; */
            /* } */
            /* //Check i-gap elements also and if so swap them */
            /* //Reverse check. Explicitly instead of part of loop. */
            /* if((n[i-gap] > n[i]) && (i-gap >= 0)) */
            /* { */
            /*     algo_steps +=3; */
            /*     swap_count++; */
            /*     //swap */
            /*     temp = n[i]; */
            /*     n[i]=n[i-gap]; */
            /*     n[i-gap]=temp; */
            /* } */
            /* i++; */
        }
        //dbg("gap %d, n:", gap);
        //for (int k = 0; k < num_elements; k++)
        //printf("%d", n[k]);
    }
    dbg("loop count %d", loop_count);
    dbg("swap count %d", swap_count);
}

UTEST(math, shsort_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    shellsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, shsort_bestcase_10) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    shellsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, shsort_worstcase) {
    int num_elements = 5;
    int n[5] = {5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    shellsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, shsort_worstcase_10) {
    int num_elements = 10;
    int n[10] = {10,9,8,7,6,5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    shellsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, shsort_averagecase) {
    int num_elements = 5;
    int n[5] = {3,4,1,5,2};

    algo_steps = 0;
    algo_storage = 0;

    shellsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, shsort_averagecase_10) {
    int num_elements = 10;
    int n[10] = {3,4,1,5,2,8,10,9,7,6};

    algo_steps = 0;
    algo_storage = 0;

    shellsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, shsort_stablecase) {
    int num_elements = 10;
    int n[10] = {6,4,7,1,7,2,3,9,5,8};
    int r[10] = {1,2,3,4,5,6,7,7,8,9};

    algo_steps = 0;
    algo_storage = 0;

    shellsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, shsort_randomcase) {
    int num_elements = 10;
    int n[10] = {583,31,6,244,4767,322,46,689,765,238};
    int r[10] = {6,31,46,238,244,322,583,689,765,4767};

    algo_steps = 0;
    algo_storage = 0;

    shellsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

//example run
/*
initial: 5,4,3,2,1

with old implementation i.e with explicit reverse comparison

|5|,4,|3|,2,1 -> |3|,4,|5|,2,1
DBG:   i 0 j 2
3,|4|,5,|2|,1 -> 3,|2|,5,|4|,1
DBG:   i 1 j 3
3,2,|5|,4,|1| -> 3,2,|1|,4,|5| && |3|,2,|1|,4,5 -> |1|,2,|3|,4,5
DBG:   i 2 j 4
DBG: gap 2, n:12345

|1|,|2|,3,4,5
DBG:   i 0 j 1
1,|2|,|3|,4,5
DBG:   i 1 j 2
1,2,|3|,|4|,5
DBG:   i 2 j 3
1,2,3,|4|,|5|
DBG:   i 3 j 4
DBG: gap 1, n:21345

*/
