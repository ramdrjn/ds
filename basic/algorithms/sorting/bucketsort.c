#include "utest/utest.h"
#include "algo_analysis.h"

#define NUM_BUCKETS 3

void simple_sort(int *b, int size)
{
    int temp;
    for(int i = 0; i<size; i+=NUM_BUCKETS)
    {
        if(b[i] > b[i+1])
        {
            temp=b[i];
            b[i]=b[i+1];
            b[i+1]=temp;
        }
    }
}

int compute_hash(int value)
{
    int base = (value / 10)*NUM_BUCKETS;
    base += (value % 10) - 1;
    return base;
}

void bucketsort(int *n, int num_elements)
{
    //compute hash for the elements and distribute it into buckets
    //sort the elements in bucket and then re-fill the array
    //from the buckets

    int loop_count = 0;
    int swap_count = 0;
    int i, bucket_index = 0;
    int bucketsize = num_elements*NUM_BUCKETS;

    int buckets[bucketsize];

    memset(buckets, 0, sizeof(buckets));

    //buckets are the temporary storage.
    algo_storage += sizeof(buckets)/sizeof(int);

    //distribute elements into buckets
    for(i = 0; i<num_elements; i++)
    {
        loop_count++;
        algo_steps++;
        bucket_index = compute_hash(n[i]);
        buckets[bucket_index] = n[i];
    }

    //sort buckets
    simple_sort(buckets, bucketsize);

    //refill buffers with sorted values
    i=0;
    for (bucket_index = 0; bucket_index<bucketsize; bucket_index++)
    {
        loop_count++;
        algo_steps++;
        if(buckets[bucket_index] != 0)
        {
            n[i]=buckets[bucket_index];
            i++;
        }
    }
    dbg("loop count %d", loop_count);
    dbg("swap count %d", swap_count);
}

UTEST(math, bucketsort) {
    int num_elements = 10;
    int n[10] = {21,20,10,41,22,51,11,42,31,32};
    int r[10] = {10,11,20,21,22,31,32,41,42,51};

    algo_steps = 0;
    algo_storage = 0;

    bucketsort(n, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "1");
}

//example run
/*
 */
