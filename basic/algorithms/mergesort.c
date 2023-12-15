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

    /* dbg("before n values l %d, m %d, r %d n1 %d n2 %d\n", l, m, r, n1, n2); */
    /* for (int i = 0; i < 5; i++) */
    /*     printf("%d", n[i]); */

    // Copy data to temp arrays L[] and R[]
//    dbg("L[i]=");
    for (i = 0; i < n1; i++)
    {
        L[i] = n[l + i];
//        printf("%d", L[i]);
    }
//    dbg("R[j]=");
    for (j = 0; j < n2; j++)
    {
        R[j] = n[m + 1 + j];
//        printf("%d", R[j]);
    }

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

    /* dbg("after n values "); */
    /* for (int i = 0; i < 5; i++) */
    /*     printf("%d", n[i]); */
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

    mergesort(n, 0, num_elements-1);

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

    mergesort(n, 0, num_elements-1);

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

    mergesort(n, 0, num_elements-1);

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

    mergesort(n, 0, num_elements-1);

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

    mergesort(n, 0, num_elements-1);

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

    mergesort(n, 0, num_elements-1);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n^2");
    algo_space_analysis(num_elements, "1");
}

//example run
/*
initial: 5,2,4,1,3
cond:i=0<n1 && j=0<n2

DBG: before n values l 0, m 0, r 1 n1 1 n2 1
52413   -> 5|2
0<1 && 0 <1
k=l=0
n[0]=2  i=1
------
n[1]=5  j=1
DBG: after n values 25413

DBG: before n values l 0, m 1, r 2 n1 2 n2 1
25413 -> 2,5|4
0<2 && 0<1
k=l=0
n[0]=2  i=1
k=1
n[1]=4  j=1
-------
n[2]=5  i=2
DBG: after n values 24513

DBG: before n values l 3, m 3, r 4 n1 1 n2 1
24513 -> 1|3
0<1 && 0<1
k=l=3
n[3]=1  i=1
------
n[4]=3 j=1
DBG: after n values 24513

DBG: before n values l 0, m 2, r 4 n1 3 n2 2
24513 -> 2,4,5|1,3
0<3 && 0<2
k=l=0
n[0]=1  j=1
k=1
n[1]=1 i=1
k=2
n[2]=3 j=2
------
n[3]=4
n[4]=5
DBG: after n values 12345
*/
