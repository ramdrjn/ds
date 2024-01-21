#include "utest/utest.h"
#include "algo_analysis.h"

#define NUM_BUCKETS 3

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
        algo_steps+=3;

        bucket_index = (n[i] / 10)*NUM_BUCKETS;
        bucket_index += (n[i] % 10) - 1;
        buckets[bucket_index] = n[i];
    }

    //sort buckets. Right now not needed since the bucket distribution
    //takes care of sorting.
    //sort(buckets, bucketsize);

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

UTEST(sorting, bucketsort) {
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
