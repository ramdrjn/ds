#include "utest/utest.h"
#include "algo_analysis.h"

void quicksort(int *n, int l, int r)
{
    //select a pivot element (last element in this case) and move
    //elements in list to left side if the elements are less than the pivot
    //and to right side if the values are greater than the pivot.
    //Split the list at ith position and then recursively call quick sort
    //on the two halves.
    //Equal values can be either side and hence is not stable
    //also called as partition exchange swap algorithm
    int i = l;
    int j = r-1; //-1 makes sense here since we do not want to compare the pivot element
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
        while(j > l && n[j]>n[pivot]) //is > only or is >= ?
        {
            loop_count++;
            algo_steps++;
            j--;
        }
        //found elements that are less than and greater than pivot. swap.
        if(i<j)
        {
            algo_steps +=3;
            swap_count++;
            temp=n[j];
            n[j]=n[i];
            n[i]=temp;
            //i and j have not to be incremented here.
            //Continue in next iteration from same values of i and j
        }
        //continue after swap here until i is still less than j
    }
    //i is not less than j i.e either i is equal to j or i is greater than j
    //determine if the swap is required and then swap.
    //swap i and pivot element.
    if (n[i] > n[pivot])
    {
        algo_steps +=3;
        swap_count++;
        temp=n[pivot];
        n[pivot]=n[i];
        n[i]=temp;
    }
    // Sort first and second halves. Division based on ith index value.
    //ith position contains the pivot element.
    quicksort(n, l, i - 1);
    quicksort(n, i + 1, r);

    //dbg("loop count %d", loop_count);
    //dbg("swap count %d", swap_count);
}

UTEST(sorting, quicksort_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    quicksort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "nlog(n)");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, quicksort_bestcase_10) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    quicksort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "nlog(n)");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, quicksort_worstcase) {
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

UTEST(sorting, quicksort_worstcase_10) {
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

UTEST(sorting, quicksort_averagecase) {
    int num_elements = 5;
    int n[5] = {3,4,1,5,2};

    algo_steps = 0;
    algo_storage = 0;

    quicksort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "nlog(n)");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, quicksort_averagecase_10) {
    int num_elements = 10;
    int n[10] = {3,4,1,5,2,8,10,9,7,6};

    algo_steps = 0;
    algo_storage = 0;

    quicksort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "nlog(n)");
    algo_space_analysis(num_elements, "1");
}

UTEST(sorting, quicksort_stablecase) {
    UTEST_SKIP("Quicksort is not a stable sort");
}

UTEST(sorting, quicksort_randomcase) {
    int num_elements = 10;
    int n[10] = {583,31,6,244,4767,322,46,689,765,238};
    int r[10] = {6,31,46,238,244,322,583,689,765,4767};

    algo_steps = 0;
    algo_storage = 0;

    quicksort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "nlog(n)");
    algo_space_analysis(num_elements, "1");
}

//example run
/*
initial: 5,2,4,1,3
*/
