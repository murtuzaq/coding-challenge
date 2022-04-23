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
int max_height = 0;
static void get_next_node_level(struct node* node, int level);

int getHeight(struct node* root) {
    // Write your code here
    get_next_node_level(root, 0);
    //printf("Node Height = %d\n", max_height);
    return max_height;
}

static void get_next_node_level(struct node* node, int level)
{
    //printf("==== level %d====\n", level);
    if (node == NULL)
    {
        //printf("(level %d)node is NULL\n", level);
        return;
    }
    //printf("(level %d)node->data = %d\n", level, node->data);
    struct node* next_node_left = node->left;
    struct node* next_node_right = node->right;
     
    if (next_node_left == NULL && next_node_right == NULL)
    {
        //printf("(level %d)found the bottom of the tree\n", level);
        if (level > max_height)
        {
           max_height = level; 
        }
        return;
    }

    get_next_node_level(next_node_left, level + 1);
    get_next_node_level(next_node_right, level + 1); 
    return ;
     
}


int main() {
  
    struct node* root = NULL;
    
    int t;
    int data;

    scanf("%d", &t);

    while(t-- > 0) {
        scanf("%d", &data);
        root = insert(root, data);
    }
  
	printf("%d",getHeight(root));
    return 0;
}
