#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

struct node* insert( struct node* root, int data ) {
		
	if(root == NULL) {
	
        struct node* node = (struct node*)malloc(sizeof(struct node));

        node->data = data;

        node->left = NULL;
        node->right = NULL;
        return node;
	  
	} else {
      
		struct node* cur;
		
		if(data <= root->data) {
            cur = insert(root->left, data);
            root->left = cur;
		} else {
            cur = insert(root->right, data);
            root->right = cur;
		}
	
		return root;
	}
}

/* you only have to complete the function given below.  
node is defined as  

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};
*/

struct node_tree_t
{
    int** lvl_matrix;
    int* lvl_index;
    int max_nodes;
};

static void get_next_node(struct node_tree_t* node_tree, struct node* node, int level);
static void print_node_level_order(struct node_tree_t* node_tree);
static struct node_tree_t* create_node_tree(int max_nodes);
static void destroy_node_tree(struct node_tree_t* node_tree);

void levelOrder(struct node *root) {
    struct node_tree_t* node_tree = create_node_tree(500);
    get_next_node(node_tree, root,0);
    print_node_level_order(node_tree);
    destroy_node_tree(node_tree);
}

static void print_node_level_order(struct node_tree_t* node_tree)
{
    for(int lvl = 0; lvl < node_tree->max_nodes; lvl++)
    {
        for (int node=0; node<node_tree->max_nodes; node++)
        {
            int matrix_lvl_node = node_tree->lvl_matrix[lvl][node];
            if (matrix_lvl_node == 0)
            {
                break;
            }
            printf("%d ", matrix_lvl_node);
        }
    }
}
static void get_next_node(struct node_tree_t* node_tree, struct node* node, int level)
{
    if (node == NULL)
    {
        //printf("(level %d) Node is Null\n", level);
        return;
    }
    
    int node_data = node->data;
    int level_index = node_tree->lvl_index[level];
    
    node_tree->lvl_matrix[level][level_index] = node_data;
    node_tree->lvl_index[level] = node_tree->lvl_index[level] + 1;
    
    //printf("(level %d, %d) Node data = %d\n", level, level_index, node_data);
    
    struct node *left = node->left;
    struct node *right = node->right; 
    
    get_next_node(node_tree, left, level + 1);
    get_next_node(node_tree, right, level + 1);
    
}

static struct node_tree_t* create_node_tree(int max_nodes)
{
    struct node_tree_t* node_tree = malloc(sizeof( struct node_tree_t));
    int **maxtrx = malloc(max_nodes * sizeof(int*));
    for (int i = 0; i < max_nodes; i++)
    {
        maxtrx[i] = (int*)malloc(max_nodes * sizeof(int));
    }
    
    int* lvl_index_array = malloc(max_nodes * sizeof(int));
    
    node_tree->lvl_matrix = maxtrx;
    node_tree->lvl_index = lvl_index_array;  
    node_tree->max_nodes = max_nodes;
    
    return node_tree; 
}

static void destroy_node_tree(struct node_tree_t* node_tree)
{
    if (node_tree->lvl_index != NULL)
    {
        free(node_tree->lvl_index);
    }
    
    for (int row = 0; row < node_tree->max_nodes; row++)
    {
        if (node_tree->lvl_matrix[row] != NULL)
        {
            free(node_tree->lvl_matrix[row]);
        }
    }
    
    if (node_tree->lvl_matrix != NULL)
    {
        free(node_tree->lvl_matrix);
    }
    
    free(node_tree);
}


