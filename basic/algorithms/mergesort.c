#include "utest/utest.h"
#include "algo_analysis.h"

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int *n, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int L[n1], R[n2];

    algo_storage += n1+n2;

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = n[l + i];
    for (j = 0; j < n2; j++)
        R[j] = n[m + 1 + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        algo_steps++;

        if (L[i] <= R[j])
        {
            n[k++] = L[i++];
        }
        else
        {
            n[k++] = R[j++];
        }
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1)
    {
        algo_steps++;

        n[k++] = L[i++];
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2)
    {
        algo_steps++;

        n[k++] = R[j++];
    }
}

void mergesort(int *n, int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;

        // Sort first and second halves
        mergesort(n, l, m);
        mergesort(n, m + 1, r);

        merge(n, l, m, r);
    }
}

UTEST(math, mergesort_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    mergesort(n, 0, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, mergesort_bestcase_10) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    mergesort(n, 0, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, mergesort_worstcase) {
    int num_elements = 5;
    int n[5] = {5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    mergesort(n, 0, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, mergesort_worstcase_10) {
    int num_elements = 10;
    int n[10] = {10,9,8,7,6,5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    mergesort(n, 0, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, mergesort_averagecase) {
    int num_elements = 5;
    int n[5] = {3,4,1,5,2};

    algo_steps = 0;
    algo_storage = 0;

    mergesort(n, 0, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

UTEST(math, mergesort_averagecase_10) {
    int num_elements = 10;
    int n[10] = {3,4,1,5,2,8,10,9,7,6};

    algo_steps = 0;
    algo_storage = 0;

    mergesort(n, 0, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

//example run
/*
 */
