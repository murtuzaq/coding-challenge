#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

struct edge_desc_t
{
    int node_u;
    int node_v;
    int length;
};

struct bfs_graph_t
{
    int total_nodes;
    int total_edges;
    int source_node;
    struct edge_desc_t* p_edges;
    int* distance_from_source;
    int* node_evaluated;
};

static void print_shortest_reach_solution(struct bfs_graph_t* bfs_graph);
static void solve_for_the_shortest_reach(struct bfs_graph_t* bfs_graph );
static void update_distance_from_active_node(struct bfs_graph_t* bfs_graph, int active_node);
static int select_next_active_node(struct bfs_graph_t* bfs_graph);
static void destroy_bfs_graph(struct bfs_graph_t* bfs_graph);
static struct bfs_graph_t* create_bfs_graph_from_user_input(void);
static int get_integer_input_from_user(void);

int main() 
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int queries;
    struct bfs_graph_t* bfs_graph;
    
    queries = get_integer_input_from_user();
    //printf("queries = %d \n",queries);
    
    for (int i = 0; i < queries; i++ )
    {
        bfs_graph = create_bfs_graph_from_user_input();
        solve_for_the_shortest_reach(bfs_graph);
        print_shortest_reach_solution(bfs_graph);
        destroy_bfs_graph(bfs_graph);
    }
    
    return 0;
}
static void print_shortest_reach_solution(struct bfs_graph_t* bfs_graph)
{
    for(int i = 0; i < bfs_graph->total_nodes; i++)
    {
        int node = i + 1;
        if (node == bfs_graph->source_node)
        {
            continue;
        }
        
        printf("%d ", bfs_graph->distance_from_source[i] );
    }
    printf("\n");
    return;
}
static void solve_for_the_shortest_reach(struct bfs_graph_t* bfs_graph )
{
    int active_node = bfs_graph->source_node;
    bfs_graph->distance_from_source[active_node - 1] = 0;
    
    for (int i = 0; i < bfs_graph->total_nodes;i++ )
    {
        update_distance_from_active_node(bfs_graph, active_node);
        active_node = select_next_active_node(bfs_graph);
    }

    return;
}

static void update_distance_from_active_node(struct bfs_graph_t* bfs_graph, int active_node)
{
    for (int i = 0; i < bfs_graph->total_edges; i++)
    {
        int node_u = bfs_graph->p_edges[i].node_u;
        int node_v = bfs_graph->p_edges[i].node_v;
        if (node_u == active_node)
        {
            int new_node_v_dist = bfs_graph->distance_from_source[active_node - 1] + bfs_graph->p_edges->length;
            
            int node_v_dist = bfs_graph->distance_from_source[node_v - 1];
            //printf("node %d is currently %d\n", node_v, node_v_dist);
            if (node_v_dist == -1 || new_node_v_dist < node_v_dist)
            {
                bfs_graph->distance_from_source[node_v - 1] = new_node_v_dist;
                //printf("node %d updated to %d\n", node_v, new_node_v_dist);
            }
            
        }
        else if (node_v == active_node)
        {
            int new_node_u_dist = bfs_graph->distance_from_source[active_node - 1] + bfs_graph->p_edges->length;
            
            int node_u_dist = bfs_graph->distance_from_source[node_u - 1];
            //printf("node %d is currently %d\n", node_v, node_v_dist);
            if (node_u_dist == -1 || new_node_u_dist < node_u_dist)
            {
                bfs_graph->distance_from_source[node_u - 1] = new_node_u_dist;
                //printf("node %d updated to %d\n", node_v, new_node_v_dist);
            }
        }
    }
    
    bfs_graph->node_evaluated[active_node - 1] = true;
    //printf("active_node = %d done evaluated\n",active_node );
    
    return;
}

static int select_next_active_node(struct bfs_graph_t* bfs_graph)
{
    for(int i = 0; i < bfs_graph->total_nodes;i++)
    {
        if (bfs_graph->node_evaluated[i] == 0)
        {
            int next_active_node = i + 1;
            //printf("next active node = %d\n", next_active_node);
            return next_active_node;
        }
    }
    return 0;
}
static void destroy_bfs_graph(struct bfs_graph_t* bfs_graph)
{
    if (bfs_graph == NULL)
    {
        return;
    }
    
    if(bfs_graph->p_edges != NULL)
    {
        free(bfs_graph->p_edges);
    }
    
    if (bfs_graph->distance_from_source != NULL)
    {
        free(bfs_graph->distance_from_source);
    }
    
    if (bfs_graph->node_evaluated  != NULL)
    {
        free(bfs_graph->node_evaluated);
    }
    
    free(bfs_graph);
}

static struct bfs_graph_t* create_bfs_graph_from_user_input(void)
{
    struct bfs_graph_t* bfs_graph = malloc(sizeof(struct bfs_graph_t));
    int total_nodes = get_integer_input_from_user();
    int total_edges = get_integer_input_from_user();
 
    int size_of_edges_struct = total_edges * sizeof(struct edge_desc_t);
    struct edge_desc_t* p_edges = malloc(size_of_edges_struct);
    int size_of_node_array = total_nodes * sizeof(int);
    int* distance_from_source = malloc(size_of_node_array);
    int* node_evaluated = malloc(size_of_node_array);
    
    for (int i = 0; i < total_nodes; i++ )
    {
        distance_from_source[i] = -1;
        node_evaluated[i] = false;
    }
    
    for (int i = 0; i < total_edges; i++)
    {
        p_edges[i].node_u = get_integer_input_from_user();
        p_edges[i].node_v = get_integer_input_from_user();
        p_edges[i].length = 6;
        
        //printf("u=%d, v=%d\n",p_edges[i].node_u, p_edges[i].node_v);
    }
    
    int source_node = get_integer_input_from_user();
    
    bfs_graph->source_node = source_node;
    bfs_graph->p_edges = p_edges; 
    bfs_graph->total_edges = total_edges;
    bfs_graph->total_nodes = total_nodes;
    bfs_graph->distance_from_source = distance_from_source;
    bfs_graph->node_evaluated = node_evaluated;
    
    
 /**********   
    printf("total_nodes = %d \n",bfs_graph->total_nodes);
    printf("total_edges = %d \n",bfs_graph->total_edges);
    printf("source node = %d \n",bfs_graph->source_node);
    printf("edges ptr = %d,size = %d \n",(int)bfs_graph->p_edges, size_of_edges_struct);
    printf("distance ptr = %d,size = %d \n",(int)bfs_graph->distance_from_source, size_of_node_array);
    printf("evaluated ptr = %d,size = %d \n",(int)bfs_graph->node_evaluated, size_of_node_array);
    printf("=========================\n");
    ***************/
    return bfs_graph;
}

static int get_integer_input_from_user(void)
{
    int int_number = -1;
    int int2 = -1;
    scanf("%d", &int_number);
    
    return int_number;
}
