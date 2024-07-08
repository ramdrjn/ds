#include "utest/utest.h"
#include "algo_analysis.h"
#include "pal.h"

bool debug_print_travelsal_vals = true;

typedef struct tree_node tree_node_t;

void avl_tree_pre_order_traversal_recursive(int *r, int *index,
                                            tree_node_t *root);

struct tree_node
{
    int value;
    int height;
    tree_node_t *left;
    tree_node_t *right;
};

// Avl tree is height balanced tree.
// Balance if the node balance factor is not -1,0 or 1
// Rotate to balance nodes.
// Rotate left if node is right heavy(-2)
/*
          x -2                                y 0
           \                                /  \
            y -1             ->          0  x    z 0
            \
             z 0
*/
// Rotate right if node is left heavy(2)
/*
          z 2                                y 0
         /                                  /  \
        y 1             ->              0  x    z 0
       /
      x 0
*/
// Rotate right left
/*
          x -2       x -2                      y 0
           \          \                      /  \
            z 1   ->   y -1       ->      0  x    z 0
           /            \
          y 0            z 0
*/
// Rotate left right
/*
          z 2          z 2                   y 0
         /            /                    /  \
        x -1   ->    y 1       ->      0  x    z 0
         \          /
          y 0      x 0
*/
//

tree_node_t* init_avl_tree(void)
{
    tree_node_t *t = NULL;

    algo_steps++;
    algo_storage++;

    t = MEM_ALLOC(1, sizeof(tree_node_t));

    t->left=NULL;
    t->right=NULL;
    t->value=0;

    return t;
}

void deinit_avl_tree(tree_node_t *root)
{
    MEM_FREE(root);
}

static void _init_node(int value, tree_node_t *node)
{
    node->left=NULL;
    node->right=NULL;
    node->value=value;
    node->height=1;
}

static int _maxof(int val1, int val2)
{
    if(val1 > val2)
        return val1;
    return val2;
}

static int _get_height(tree_node_t *node)
{
    if (!node)
        return 0;
    return node->height;
}

static void _adjust_height(tree_node_t *node)
{
    node->height = 1 + _maxof(_get_height(node->left),
                              _get_height(node->right));
}

static int _get_balance(tree_node_t *node)
{
    if (!node)
        return 0;
    return (_get_height(node->left) - _get_height(node->right));
}

static tree_node_t* _rotate_right(tree_node_t *node)
{
    dbg("rotate right on %d", node->value);
    tree_node_t *t = node->left;
    node->left = t->right;
    t->right = node;
    _adjust_height(node);
    _adjust_height(t);
    return t;
}

static tree_node_t* _rotate_left(tree_node_t *node)
{
    dbg("rotate left on %d", node->value);
    tree_node_t *t = node->right;
    node->right = t->left;
    t->left = node;
    _adjust_height(node);
    _adjust_height(t);
    return t;
}

static tree_node_t* _balance(tree_node_t *node)
{
    int bal = _get_balance(node);
    dbg("val %d, balance %d", node->value, bal);
    if (bal > 1)
    {
        int index=0;
        dbg("left heavy");
        dbg("before: ");
        avl_tree_pre_order_traversal_recursive(NULL, &index, node);
        int bal1 = _get_balance(node->left);
        dbg("left: val %d, balance %d", node->left->value, bal1);
        if (bal1 >= 0)
        {
            return _rotate_right(node);
        }
        else
        {
            node->left = _rotate_left(node->left);
            return _rotate_right(node);
        }
    }
    else if (bal < -1)
    {
        int index=0;
        dbg("right heavy");
        dbg("before: ");
        avl_tree_pre_order_traversal_recursive(NULL, &index, node);
        int bal1 = _get_balance(node->right);
        dbg("right: val %d, balance %d", node->right->value, bal1);
        if (bal1 <= 0)
        {
            return _rotate_left(node);
        }
        else
        {
            node->right = _rotate_right(node->right);
            return _rotate_left(node);
        }
    }

    return node;
}

tree_node_t* delete_avl_tree_node_recursive(tree_node_t* root, int value);

static void _in_order_successor(tree_node_t* root)
{
    tree_node_t* succParent = root;

    // Find successor
    tree_node_t* succ = root->right;
    while (succ->left != NULL)
    {
        succParent = succ;
        succ = succ->left;
    }

    // Copy Successor Data to root
    root->value = succ->value;

    // Delete Successor.
    root->right = delete_avl_tree_node_recursive(succParent, succ->value);
}

void insert_avl_tree_root(int value, tree_node_t *root)
{
    algo_steps++;
    _init_node(value, root);
}

tree_node_t *insert_avl_tree_node_recursive(int value, tree_node_t *node)
{
    tree_node_t *t = NULL;

    algo_steps++;
    algo_storage++;

    if (node == NULL)
    {
        t = MEM_ALLOC(1, sizeof(tree_node_t));
        _init_node(value, t);
        // dbg("insert node value %d", value);
        return t;
    }

    if (value < node->value)
    {
        node->left = insert_avl_tree_node_recursive(value, node->left);
    }
    else if (value > node->value)
    {
        node->right = insert_avl_tree_node_recursive(value, node->right);
    }
    else
    {
        err("same node value. duplicate node %d", value);
        return node;
    }

    _adjust_height(node);

    return _balance(node);
}

/* Given a avl search tree and a value, this function
   deletes the value and returns the new root */
tree_node_t* delete_avl_tree_node_recursive(tree_node_t* root, int value)
{
    if (root == NULL)
        return root;

    if (root->value > value)
    {
        root->left = delete_avl_tree_node_recursive(root->left, value);
    }
    else if (root->value < value)
    {
        root->right = delete_avl_tree_node_recursive(root->right, value);
    }
    else
    {
        // We reach here when root is the node
        // to be deleted.

        // If one of the children is empty
        if (root->left == NULL)
        {
            tree_node_t* t = root->right;
            MEM_FREE(root);
            return t;
        }
        else if (root->right == NULL)
        {
            tree_node_t* t = root->left;
            MEM_FREE(root);
            return t;
        }
        else // If both children exist
        {
            //Two ways of selecting the successor.
            //1. Inorder predecessor. Largest value from the left side.
            //2. inorder successor. Smallest value from the right side.

            //This is the in order successor implementation.
            _in_order_successor(root);
        }
    }
    return _balance(root);
}

/* Depth first search */
void avl_tree_pre_order_traversal_recursive(int *r, int *index,
                                               tree_node_t *root)
{
    if(root)
    {
        algo_steps++;
        if (r)
            r[*index]=root->value;
        *index=*index+1;
        if (debug_print_travelsal_vals)
            dbgval("%d[%d] ", root->value, root->height);
        avl_tree_pre_order_traversal_recursive(r, index, root->left);
        avl_tree_pre_order_traversal_recursive(r, index, root->right);
    }
}

void avl_tree_post_order_traversal_recursive(int *r, int *index,
                                                tree_node_t *root)
{
    if(root)
    {
        algo_steps++;
        avl_tree_post_order_traversal_recursive(r, index, root->left);
        avl_tree_post_order_traversal_recursive(r, index, root->right);
        r[*index]=root->value;
        *index=*index+1;
        if (debug_print_travelsal_vals)
            dbgval("%d", root->value);
    }
}

void avl_tree_in_order_traversal_recursive(int *r, int *index,
                                              tree_node_t *root)
{
    if(root)
    {
        algo_steps++;
        avl_tree_in_order_traversal_recursive(r, index, root->left);
        r[*index]=root->value;
        *index=*index+1;
        if (debug_print_travelsal_vals)
            dbgval("%d", root->value);
        avl_tree_in_order_traversal_recursive(r, index, root->right);
    }
}

int avl_search_tree_search(tree_node_t *root, int value)
{
    while(root)
    {
        algo_steps++;
        if(root->value == value)
        {
            return 1;
        }
        else if(root->value > value)
        {
            root=root->left;
        }
        else
        {
            root=root->right;
        }
    }
    return 0;
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

        tree_root = init_avl_tree();

        init_done=1;
    }
    utest_fixture->root=tree_root;

    //Check if the tree is initialized properly or not.
    ASSERT_NE(NULL, utest_fixture->root);
}

UTEST_F_TEARDOWN(ds)
{
    //deinit_avl_tree(utest_fixture->root);
}
/*
                   6
              /        \
             3         10
            /  \       /
           1    5     8
            \  /       \
             2 4        9

After left-right rotation (node 10):
                   6
              /        \
             3          9
            /  \       / \
           1    5     8  10
            \  /
             2 4

                   6
              /        \
             3          9
            /  \       / \
           1    5     8  10
            \  /     /
             2 4    7
 */
UTEST_F(ds, avltree_insert)
{
    int num_elements = 10;
    int n[10] = {6,3,10,5,1,8,2,4,9,7};

    algo_steps = 0;
    algo_storage = 0;

    insert_avl_tree_root(n[0], utest_fixture->root);

    for(int i=1; i<num_elements; i++)
         utest_fixture->root = insert_avl_tree_node_recursive(n[i], utest_fixture->root);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

UTEST_F(ds, avltree_pre_order_traversal_recursive)
{
    int num_elements = 10;
    int r[10] = {0};
    int expected[10] = {6,3,1,2,5,4,9,8,7,10};
    int index=0;

    algo_steps = 0;
    algo_storage = 0;

    avl_tree_pre_order_traversal_recursive(r, &index, utest_fixture->root);
    for(int i=0; i<num_elements; i++)
        EXPECT_EQ(r[i], expected[i]);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

UTEST_F(ds, avltree_post_order_traversal_recursive)
{
    int num_elements = 10;
    int r[10] = {0};
    int expected[10] = {2,1,4,5,3,7,8,10,9,6};
    int index=0;

    algo_steps = 0;
    algo_storage = 0;

    avl_tree_post_order_traversal_recursive(r, &index, utest_fixture->root);
    for(int i=0; i<num_elements; i++)
        EXPECT_EQ(r[i], expected[i]);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

UTEST_F(ds, avltree_in_order_traversal_recursive)
{
    int num_elements = 10;
    int r[10] = {0};
    int expected[10] = {1,2,3,4,5,6,7,8,9,10};
    int index=0;

    algo_steps = 0;
    algo_storage = 0;

    avl_tree_in_order_traversal_recursive(r, &index, utest_fixture->root);
    for(int i=0; i<num_elements; i++)
        EXPECT_EQ(r[i], expected[i]);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

/*
                   6
              /        \
             3          9
            /  \       / \
           1    5     8  10
            \  /     /
             2 4    7<-
 */
UTEST_F(ds, avltree_delete_node_leaf)
{
    int num_elements=10;

    algo_steps = 0;
    algo_storage = 0;

    delete_avl_tree_node_recursive(utest_fixture->root, 7);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

/*
                   6
              /        \
             3          9
            /  \       / \
           1    5 <-  8  10
            \  /
             2 4
 */
UTEST_F(ds, avltree_delete_node_1_child)
{
    int num_elements=10;

    algo_steps = 0;
    algo_storage = 0;

    delete_avl_tree_node_recursive(utest_fixture->root, 5);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

/*
                   6
              /        \
             3          9
            /  \       / \
           1    4     8  10
            \             \
             2             11 <-
 */
UTEST_F(ds, avltree_insert_after_delete)
{
    int num_elements=10;

    algo_steps = 0;
    algo_storage = 0;

    insert_avl_tree_node_recursive(11, utest_fixture->root);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

UTEST_F(ds, avltree_pre_order_traversal_recursive_after_insert_after_deletes)
{
    int num_elements = 10;
    int r[10] = {0};
    int expected[10] = {6,3,1,2,4,9,8,10,11};
    int index=0;

    algo_steps = 0;
    algo_storage = 0;

    avl_tree_pre_order_traversal_recursive(r, &index, utest_fixture->root);
    for(int i=0; i<num_elements; i++)
        EXPECT_EQ(r[i], expected[i]);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

/*
                   6 <-
              /        \
             3          9
            /  \       / \
           1    4     8  10
            \             \
             2             11
After node deletion (node 6):
                   8
              /        \
             3          9
            /  \         \
           1    4        10
            \             \
             2             11
After left rotation (node 9):
                     8
                  /        \
                 3          10
                /  \       /  \
               1    4     9   11
                \
                 2
 */
UTEST_F(ds, avltree_delete_node_2_child)
{
    int num_elements=10;

    algo_steps = 0;
    algo_storage = 0;

    delete_avl_tree_node_recursive(utest_fixture->root, 6);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

/*
                      8
                  /        \
                 3          10
                /  \       /  \
               1    4     9   11
                \
                 2
 */
UTEST_F(ds, avltree_in_order_traversal_recursive_after_deletes_insert)
{
    int num_elements = 8;
    int r[8] = {0};
    int expected[8] = {1,2,3,4,8,9,10,11};
    int index=0;

    algo_steps = 0;
    algo_storage = 0;

    avl_tree_in_order_traversal_recursive(r, &index, utest_fixture->root);
    for(int i=0; i<num_elements; i++)
        EXPECT_EQ(r[i], expected[i]);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

UTEST_F(ds, avltree_pre_order_traversal_recursive_after_deletes_insert)
{
    int num_elements = 10;
    int r[10] = {0};
    int expected[10] = {8,3,1,2,4,10,9,11};
    int index=0;

    algo_steps = 0;
    algo_storage = 0;

    avl_tree_pre_order_traversal_recursive(r, &index, utest_fixture->root);
    for(int i=0; i<num_elements; i++)
        EXPECT_EQ(r[i], expected[i]);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

//BST - avl search tree
/*
                      8
                  /        \
                 3          10
                /  \       /  \
               1    4     9   11
                \
                 2
 */
UTEST_F(ds, avl_search_tree_search_found)
{
    int num_elements=8;
    int element = 10;
    int result;

    algo_steps = 0;
    algo_storage = 0;

    result = avl_search_tree_search(utest_fixture->root, element);

    EXPECT_EQ(result, 1);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

UTEST_F(ds, avl_search_tree_search_no_found)
{
    int num_elements=8;
    int element = 12;
    int result;

    algo_steps = 0;
    algo_storage = 0;

    result = avl_search_tree_search(utest_fixture->root, element);

    EXPECT_EQ(result, 0);

    algo_time_analysis(num_elements, "n");
    //algo_space_analysis(num_elements, "1");
}

//example run
/*

unbalanced runs:
insert sequence: 6,3,10,5,1,8,2,4,9,7
pre_order_traversal_recursive: 6,3,1,2,5,4,10,8,7,9
post_order_traversal_recursive: 2,1,4,5,3,7,9,8,10,6
in_order_traversal_recursive: 1,2,3,4,5,6,7,8,9,10


 */
