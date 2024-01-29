#include "utest/utest.h"
#include "algo_analysis.h"
#include "pal.h"

typedef struct tree_node tree_node_t;

struct tree_node
{
    int value;
    int height;
    tree_node_t *left;
    tree_node_t *right;
};

tree_node_t* init_avl_tree(void)
{
    //Avl tree is height balanced tree.
    //root value will be the first element in array.

    tree_node_t *t = NULL;

    algo_steps++;
    algo_storage++;

    t = MEM_ALLOC(1, sizeof(tree_node_t));

    t->left=NULL;
    t->right=NULL;
    t->value=0;
    t->height=0;

    return t;
}

void deinit_avl_tree(tree_node_t *root)
{
    MEM_FREE(root);
}

void insert_avl_tree_root(int value, tree_node_t *root)
{
    algo_steps++;

    root->left=NULL;
    root->right=NULL;
    root->value=value;
    root->height=0;
}

void insert_avl_tree_node(int value, tree_node_t *root)
{
    tree_node_t *t = NULL;
    tree_node_t *curr_node = root;

    algo_steps++;
    algo_storage++;

    t = MEM_ALLOC(1, sizeof(tree_node_t));

    t->left=NULL;
    t->right=NULL;
    t->value=value;
    t->height=0;

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

/* Given a avl search tree and a value, this function
   deletes the value and returns the new root */
tree_node_t* delete_avl_tree_node(tree_node_t* root, int value)
{
    if (root == NULL)
        return root;

    if (root->value > value)
    {
        root->left = delete_avl_tree_node(root->left, value);
        return root;
    }
    else if (root->value < value)
    {
        root->right = delete_avl_tree_node(root->right, value);
        return root;
    }

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
        tree_node_t* succParent = root;

        // Find successor
        tree_node_t* succ = root->right;
        while (succ->left != NULL)
        {
            succParent = succ;
            succ = succ->left;
        }

        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        // If there is no succ, then assign
        // succ->right to succParent->right
        if (succParent != root)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        // Copy Successor Data to root
        root->value = succ->value;

        // Delete Successor and return root
        MEM_FREE(succ);
        return root;
    }
}

/* Depth first search */
void avl_tree_pre_order_traversal_recursive(int *r, int *index,
                                            tree_node_t *root)
{
    if(root)
    {
        algo_steps++;
        r[*index]=root->value;
        *index=*index+1;
        //printf("%d", root->value);
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
        //printf("%d", root->value);
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
        //printf("%d", root->value);
        avl_tree_in_order_traversal_recursive(r, index, root->right);
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
  \  /    /   \
  2 4   7     9
*/
UTEST_F(ds, avltree_insert)
{
    int num_elements = 10;
    int n[10] = {6,3,10,5,1,8,2,4,9,7};

    algo_steps = 0;
    algo_storage = 0;

    insert_avl_tree_root(n[0], utest_fixture->root);

    for(int i=1; i<num_elements; i++)
        insert_avl_tree_node(n[i], utest_fixture->root);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

UTEST_F(ds, avltree_pre_order_traversal_recursive)
{
    int num_elements = 10;
    int r[10] = {0};
    int expected[10] = {6,3,1,2,5,4,10,8,7,9};
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
    int expected[10] = {2,1,4,5,3,7,9,8,10,6};
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
  3         10
  /  \       /
  1    5     8
  \  /    /   \
  2 4   7     9 <-
*/
UTEST_F(ds, avltree_delete_node_leaf)
{
    int num_elements=10;

    algo_steps = 0;
    algo_storage = 0;

    delete_avl_tree_node(utest_fixture->root, 9);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

/*
  6
  /        \
  3         10
  /  \       /
  1    5 <-  8
  \  /    /
  2 4   7
*/
UTEST_F(ds, avltree_delete_node_1_child)
{
    int num_elements=10;

    algo_steps = 0;
    algo_storage = 0;

    delete_avl_tree_node(utest_fixture->root, 5);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

/*
  6
  /        \
  3         10
  /  \       / \
  1    4     8  11 <-
  \        /
  2      7
*/
UTEST_F(ds, avltree_insert_after_delete)
{
    int num_elements=10;

    algo_steps = 0;
    algo_storage = 0;

    insert_avl_tree_node(11, utest_fixture->root);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

/*
  6 <-
  /        \
  3         10
  /  \       / \
  1    4     8  11
  \        /
  2      7
*/
UTEST_F(ds, avltree_delete_node_2_child)
{
    int num_elements=10;

    algo_steps = 0;
    algo_storage = 0;

    delete_avl_tree_node(utest_fixture->root, 6);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

/*
  7
  /        \
  3         10
  /  \       / \
  1    4     8  11
  \
  2
*/
UTEST_F(ds, avltree_in_order_traversal_recursive_after_delete_insert)
{
    int num_elements = 8;
    int r[8] = {0};
    int expected[8] = {1,2,3,4,7,8,10,11};
    int index=0;

    algo_steps = 0;
    algo_storage = 0;

    avl_tree_in_order_traversal_recursive(r, &index, utest_fixture->root);
    for(int i=0; i<num_elements; i++)
        EXPECT_EQ(r[i], expected[i]);

    algo_time_analysis(num_elements, "n");
    algo_space_analysis(num_elements, "n");
}

//example run
/*
 */

#if 0
int max(int a, int b);

// Calculate height
int height(tree_node_t *N) {
  if (N == NULL)
    return 0;
  return N->height;
}

int max(int a, int b) {
  return (a > b) ? a : b;
}

// Right rotate
tree_node_t *rightRotate(tree_node_t *y) {
  tree_node_t *x = y->left;
  tree_node_t *T2 = x->right;

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

// Left rotate
tree_node_t *leftRotate(tree_node_t *x) {
  tree_node_t *y = x->right;
  tree_node_t *T2 = y->left;

  y->left = x;
  x->right = T2;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;

  return y;
}

// Get the balance factor
int getBalance(tree_node_t *N) {
  if (N == NULL)
    return 0;
  return height(N->left) - height(N->right);
}

// Insert node
tree_node_t *insertNode(tree_node_t *node, int value) {
  // Find the correct position to insertNode the node and insertNode it
  if (node == NULL)
    return (newNode(value));

  if (value < node->value)
    node->left = insertNode(node->left, value);
  else if (value > node->value)
    node->right = insertNode(node->right, value);
  else
    return node;

  // Update the balance factor of each node and
  // Balance the tree
  node->height = 1 + max(height(node->left),
               height(node->right));

  int balance = getBalance(node);
  if (balance > 1 && value < node->left->value)
    return rightRotate(node);

  if (balance < -1 && value > node->right->value)
    return leftRotate(node);

  if (balance > 1 && value > node->left->value) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
  }

  if (balance < -1 && value < node->right->value) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
  }

  return node;
}

tree_node_t *minValueNode(tree_node_t *node) {
  tree_node_t *current = node;

  while (current->left != NULL)
    current = current->left;

  return current;
}

// Delete a nodes
tree_node_t *deleteNode(tree_node_t *root, int value) {
  // Find the node and delete it
  if (root == NULL)
    return root;

  if (value < root->value)
    root->left = deleteNode(root->left, value);

  else if (value > root->value)
    root->right = deleteNode(root->right, value);

  else {
    if ((root->left == NULL) || (root->right == NULL)) {
      tree_node_t *temp = root->left ? root->left : root->right;

      if (temp == NULL) {
        temp = root;
        root = NULL;
      } else
        *root = *temp;
      free(temp);
    } else {
      tree_node_t *temp = minValueNode(root->right);

      root->value = temp->value;

      root->right = deleteNode(root->right, temp->value);
    }
  }

  if (root == NULL)
    return root;

  // Update the balance factor of each node and
  // balance the tree
  root->height = 1 + max(height(root->left),
               height(root->right));

  int balance = getBalance(root);
  if (balance > 1 && getBalance(root->left) >= 0)
    return rightRotate(root);

  if (balance > 1 && getBalance(root->left) < 0) {
    root->left = leftRotate(root->left);
    return rightRotate(root);
  }

  if (balance < -1 && getBalance(root->right) <= 0)
    return leftRotate(root);

  if (balance < -1 && getBalance(root->right) > 0) {
    root->right = rightRotate(root->right);
    return leftRotate(root);
  }

  return root;
}
#endif
