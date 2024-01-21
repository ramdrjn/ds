#include "utest/utest.h"
#include "algo_analysis.h"

//Drawbacks: Cannot be used on negative number and floats.
//Range has to be feasible and should have denser values in the list.
void countingsort(int *n, int range_lower, int range_upper, int num_elements)
{
    //Count the occurances of the values and update that in their
    //corresponding index in the counting array.
    //Once all the element's count values are updated, recreate the list
    //based on the count values.
    //not a comparison sort

    int loop_count = 0;
    int swap_count = 0;

    int counter[range_upper-range_lower+1];
    int index_adjust=range_lower;
    int index=0;
    int temp[num_elements];

    //counter storage depends on the range
    algo_storage += sizeof(counter)/sizeof(int);
    //storage for the temp array
    algo_storage += num_elements;

    memset(counter, 0, sizeof(counter));

    //Loop from 1 to num_elements.
    for(int i = 0; i<num_elements; i++)
    {
        loop_count++;
        algo_steps++;

        index=n[i]-index_adjust;
        counter[index] += 1;
    }
    //for (int i = 0; i < range_upper-range_lower+1; i++)
    //    printf("%d ",counter[i]);

    //Update counter. Cummulative count.
    //This will reflect the position of the elements in the recreated
    //list
    for(int i=1; i <= range_upper-range_lower+1; i++)
    {
        loop_count++;
        algo_steps++;

        counter[i] += counter[i-1];
    }

    //Recreate list. Build this on a temporary array.
    //Note. Start from reverse inorder to preserve the values in index
    //incase of duplicate elements. Maintains stability.
    for(int i = num_elements-1; i >= 0; i--)
    {
        loop_count++;
        algo_steps++;

        //counter[n[i]-index_adjust]--;
        //temp[counter[n[i]-index_adjust]] = n[i];

        index = n[i]-index_adjust;
        counter[index]--;
        temp[counter[index]] = n[i];
    }

    //Copy from temp array to final array
    for(int i = 0; i < num_elements; i++)
    {
        loop_count++;
        algo_steps++;

        n[i] = temp[i];
    }

    dbg("loop count %d", loop_count);
    dbg("swap count %d", swap_count);
}

UTEST(sorting, csort_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 5, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_bestcase_10) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 10, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_worstcase) {
    int num_elements = 5;
    int n[5] = {5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 5, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_worstcase_10) {
    int num_elements = 10;
    int n[10] = {10,9,8,7,6,5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 10, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_averagecase) {
    int num_elements = 5;
    int n[5] = {3,4,1,5,2};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 5, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_averagecase_10) {
    int num_elements = 10;
    int n[10] = {3,4,1,5,2,8,10,9,7,6};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 10, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_stablecase) {
    int num_elements = 10;
    int n[10] = {6,4,7,1,7,2,3,9,5,8};
    int r[10] = {1,2,3,4,5,6,7,7,8,9};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 9, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_dupelementscase) {
    int num_elements = 10;
    int n[10] = {9,4,7,1,7,9,3,9,5,8};
    int r[10] = {1,3,4,5,7,7,8,9,9,9};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 1, 9, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_rangecase) {
    int num_elements = 10;
    int n[10] = {26,24,27,21,27,22,23,29,25,28};
    int r[10] = {21,22,23,24,25,26,27,27,28,29};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 21, 29, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_randomcase) {
    int num_elements = 10;
    int n[10] = {583,31,6,244,4767,322,46,689,765,238};
    int r[10] = {6,31,46,238,244,322,583,689,765,4767};

    algo_steps = 0;
    algo_storage = 0;

    countingsort(n, 6, 4767, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

//example run
/*
*/

void countingsort_range(int *n, int range_lower, int range_upper,
                        int num_elements)
{
    //Count the occurances of the values and update that in their
    //corresponding index in the counting array.
    //Once all the element's count values are updated, recreate the list
    //based on the count values.
    //not a comparison sort

    int loop_count = 0;
    int swap_count = 0;

    int counter[range_upper-range_lower+1];
    int index_adjust=range_lower;
    int index=0;

    //counter storage depends on the range
    algo_storage += sizeof(counter)/sizeof(int);

    memset(counter, 0, sizeof(counter));

    //Loop from 1 to num_elements.
    for(int i = 0; i<num_elements; i++)
    {
        loop_count++;
        algo_steps++;

        index=n[i]-index_adjust;
        counter[index] += 1;
    }
    //for (int i = 0; i < range_upper-range_lower+1; i++)
    //    printf("%d ",counter[i]);

    //Recreate array but with sorted elements
    //For loop assumes that the elements can be re-created based on the index
    //This is good if the range of elements are small and element values are
    //close.
    for(int i = 0, index=0; index<num_elements;i++)
    {
        loop_count++;
        algo_steps++;

        for(; counter[i]>0; counter[i]--)
        {
            loop_count++;
            algo_steps++;

            n[index]=i+index_adjust;
            index++;
        }
    }

    dbg("loop count %d", loop_count);
    dbg("swap count %d", swap_count);
}

UTEST(sorting, csort_range_bestcase) {
    int num_elements = 5;
    int n[5] = {1,2,3,4,5};

    algo_steps = 0;
    algo_storage = 0;

    countingsort_range(n, 1, 5, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_range_bestcase_10) {
    int num_elements = 10;
    int n[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    countingsort_range(n, 1, 10, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_range_worstcase) {
    int num_elements = 5;
    int n[5] = {5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    countingsort_range(n, 1, 5, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_range_worstcase_10) {
    int num_elements = 10;
    int n[10] = {10,9,8,7,6,5,4,3,2,1};

    algo_steps = 0;
    algo_storage = 0;

    countingsort_range(n, 1, 10, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_range_averagecase) {
    int num_elements = 5;
    int n[5] = {3,4,1,5,2};

    algo_steps = 0;
    algo_storage = 0;

    countingsort_range(n, 1, 5, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_range_averagecase_10) {
    int num_elements = 10;
    int n[10] = {3,4,1,5,2,8,10,9,7,6};

    algo_steps = 0;
    algo_storage = 0;

    countingsort_range(n, 1, 10, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], i+1);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_range_stablecase) {
    int num_elements = 10;
    int n[10] = {6,4,7,1,7,2,3,9,5,8};
    int r[10] = {1,2,3,4,5,6,7,7,8,9};

    algo_steps = 0;
    algo_storage = 0;

    countingsort_range(n, 1, 9, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_range_dupelementscase) {
    int num_elements = 10;
    int n[10] = {9,4,7,1,7,9,3,9,5,8};
    int r[10] = {1,3,4,5,7,7,8,9,9,9};

    algo_steps = 0;
    algo_storage = 0;

    countingsort_range(n, 1, 9, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_range_rangecase) {
    int num_elements = 10;
    int n[10] = {26,24,27,21,27,22,23,29,25,28};
    int r[10] = {21,22,23,24,25,26,27,27,28,29};

    algo_steps = 0;
    algo_storage = 0;

    countingsort_range(n, 21, 29, num_elements);

    for (int i = 0; i < num_elements; i++)
        EXPECT_EQ(n[i], r[i]);

    algo_time_analysis(num_elements, "n+range");
    algo_space_analysis(num_elements, "range");
}

UTEST(sorting, csort_range_randomcase) {
    UTEST_SKIP("Range too large");
}

//example run
/*
*/
