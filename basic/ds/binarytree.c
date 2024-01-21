#include "utest/utest.h"
#include "algo_analysis.h"
#include "pal.h"

static int result_index=0;

typedef struct tree_node tree_node_t;

struct tree_node
{
    int value;
    tree_node_t *left;
    tree_node_t *right;
};

tree_node_t* init_binary_tree(void)
{
    //Binary tree is not height balanced.
    //left and right placement of node values can be custom.
    //In this example smaller values are placed to left and larger values
    //on right
    //root value will be the first element in array.

    tree_node_t *t = NULL;

    algo_steps++;
    algo_storage++;

    t = MEM_ALLOC(1, sizeof(tree_node_t));

    t->left=NULL;
    t->right=NULL;
    t->value=0;

    return t;
}

void deinit_binary_tree(tree_node_t *root)
{
    MEM_FREE(root);
}

void insert_binary_tree_root(int value, tree_node_t *root)
{
    algo_steps++;

    root->left=NULL;
    root->right=NULL;
    root->value=value;
}

void insert_binary_tree(int value, tree_node_t *root)
{
    tree_node_t *t = NULL;
    tree_node_t *curr_node = root;

    algo_steps++;
    algo_storage++;

    t = MEM_ALLOC(1, sizeof(tree_node_t));

    t->left=NULL;
    t->right=NULL;
    t->value=value;

    //dbg("insert node value %d", value);

    while(curr_node)
    {
        algo_steps++;
        if(t->value > curr_node->value) //move right
        {
            if(curr_node->right)
            {
                //dbg("  <mv-right>current node value %d", curr_node->value);
                curr_node=curr_node->right;
            }
            else
            {
                //dbg(" <ins-right>current node value %d", curr_node->value);
                curr_node->right = t;
                break;
            }
        }
        else //if same or t value less than curr node value. Move left
        {
            if(curr_node->left)
            {
                //dbg("  <mv-left>current node value %d", curr_node->value);
                curr_node=curr_node->left;
            }
            else
            {
                //dbg(" <ins-left>current node value %d", curr_node->value);
                curr_node->left = t;
                break;
            }
        }
    }
}

void delete_binart_tree(int value, tree_node_t *root)
{
    tree_node_t *t = NULL;
    MEM_FREE(t);
}

void binary_tree_pre_order_traversal(int *r, tree_node_t *root)
{
    if(root)
    {
        algo_steps++;
        r[result_index++]=root->value;
        //printf("%d", root->value);
        binary_tree_pre_order_traversal(r, root->left);
        binary_tree_pre_order_traversal(r, root->right);
    }
}

void binary_tree_post_order_traversal(int *r, tree_node_t *root)
{
    if(root)
    {
        algo_steps++;
        binary_tree_post_order_traversal(r, root->left);
        binary_tree_post_order_traversal(r, root->right);
        r[result_index++]=root->value;
        //printf("%d", root->value);
    }
}

void binary_tree_in_order_traversal(int *r, tree_node_t *root)
{
    if(root)
    {
        algo_steps++;
        binary_tree_in_order_traversal(r, root->left);
        r[result_index++]=root->value;
        //printf("%d", root->value);
        binary_tree_in_order_traversal(r, root->right);
    }
}

static int init_done=0;
static tree_node_t *tree_root=NULL;

struct ds
{
    tree_node_t *root;
};

UTEST_F_SETUP(ds)
{
    if(init_done == 0)
    {
        tree_root = NULL;

        tree_root = init_binary_tree();

        init_done=1;
    }
    utest_fixture->root=tree_root;

    //Check if the tree is initialized properly or not.
    ASSERT_NE(NULL, utest_fixture->root);
}

UTEST_F_TEARDOWN(ds)
{
    //deinit_binary_tree(utest_fixture->root);
}

UTEST_F(ds, binarytree_insert)
{
    int num_elements = 10;
    int n[10] = {6,3,10,5,1,8,2,4,9,7};

    algo_steps = 0;
    algo_storage = 0;

    insert_binary_tree_root(n[0], utest_fixture->root);

    for(int i=1; i<num_elements; i++)
        insert_binary_tree(n[i], utest_fixture->root);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

UTEST_F(ds, binarytree_pre_order_traversal)
{
    int num_elements = 10;
    int r[10] = {0};
    int expected[10] = {6,3,1,2,5,4,10,8,7,9};

    algo_steps = 0;
    algo_storage = 0;

    result_index=0;
    binary_tree_pre_order_traversal(r, utest_fixture->root);
    for(int i=0; i<num_elements; i++)
        EXPECT_EQ(r[i], expected[i]);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

UTEST_F(ds, binarytree_post_order_traversal)
{
    int num_elements = 10;
    int r[10] = {0};
    int expected[10] = {2,1,4,5,3,7,9,8,10,6};

    algo_steps = 0;
    algo_storage = 0;

    result_index=0;
    binary_tree_post_order_traversal(r, utest_fixture->root);
    for(int i=0; i<num_elements; i++)
        EXPECT_EQ(r[i], expected[i]);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

UTEST_F(ds, binarytree_in_order_traversal)
{
    int num_elements = 10;
    int r[10] = {0};
    int expected[10] = {1,2,3,4,5,6,7,8,9,10};

    algo_steps = 0;
    algo_storage = 0;

    result_index=0;
    binary_tree_in_order_traversal(r, utest_fixture->root);
    for(int i=0; i<num_elements; i++)
        EXPECT_EQ(r[i], expected[i]);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

//example run
/*
 */
