#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define FALSE 0
#define TRUE 1

//global variables for DFS
int time;
int edge_trav_iter;
char** color = NULL;

//structs

typedef struct {
    int VRTX;
    int discovered;
}VRTX_OBJ;

typedef struct Node Node;

struct Node
{
    VRTX_OBJ vrtx_obj;
    int VRTX;
    int TRAVEL_COST;
    char TYPE;
    Node *NEXT;
};

typedef struct {
    int start;
    int finish;
}Edge


typedef struct{
    int* pred;
    int* d;
    int* f;
    Node** node_list;
}GRAPH; 

//input helper

char* printMenuWithDataIter(char* menu_choice, int menuchoice_size) {
    printf("How would you like your input to be further processed?\n");
    printf("Enter 0 to process the next dataset\n");
    printf("Enter 1 to process another vertex pair\n");
    printf("Enter 2 to stop processing input on the file chosen\n");
    printf("Enter a number from the menu: ");
    fgets(menu_choice, menuchoice_size, stdin);
    menu_choice[strlen(menu_choice) - 1] = '\0';
    return menu_choice;
}

//cost matrix helper

int getNumOfVertex(char* cost_row) {
    int i, vertex_num = 1;
    for (i = 0; cost_row[i] != '\n'; i++) {
        if (cost_row[i] == ' ') {
            vertex_num++;
        }
    }
    //printf("vertex num is %d\n", vertex_num);
    return vertex_num;
}

void freeStrCostAdjMat(char** str_cost_adj_mat, int num_of_vertex) {
    int i;
    for (i = 0; i <  num_of_vertex; i++) {
        free(str_cost_adj_mat[i]);
    }
}

void freeCostAdjMat(int** cost_adj_mat, int num_of_vertex) {
    int i;
    for (i = 0; i <  num_of_vertex; i++) {
        free(cost_adj_mat[i]);
    }
    
}

printArrContent(int* arr, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");
}

printColorContent(int size){
    int i;
    for (i = 0; i < size; i++)
    printf("i:%d have color[i]: %s\n", i, color[i]);
}

int DFS(GRAPH* graph, Edge** edge_list, int i, int start_vertex, int end_vertex) {
    color[i - 1] = "gray";
    graph->d[i - 1] = time;
    time++;
    //printf("i is %d\n", i);
    Node* alpha = graph->node_list[i];
    int j = alpha->VRTX;
    Edge* edge = malloc(sizeof(edge));

    int already_discovered = FALSE;
    while (alpha != NULL) {
        if (already_discovered == FALSE) {
            j = alpha->VRTX;
            printf("WOW color at %d\n", j);
            printf(" is %s", color[j - 1]);
            
            if (strcmp(color[j - 1], "white") == 0) {
                alpha->TYPE = 'T';
                graph->pred[j - 1] = i;
                edge->start = i;
                edge->end = j;
                edge_list[edge_trav_iter - 1] = edge; 
                alpha->vrtx_obj->discovered = TRUE;
                DFS(graph, j, start_vertex, end_vertex);
            }
            
            else if (strcmp(color[j - 1], "gray") == 0) {
                if (graph->pred[i - 1] != j) {
                    alpha->TYPE = 'B';
                }
            }
                
            else if (strcmp(color[j - 1], "black") == 0) {
                if (graph->d[i - 1] < graph->d[j - 1]) {
                    alpha->TYPE = 'F';
                }
                else {
                    alpha->TYPE = 'X';
                }
            }
             //added implementation
             if (start_vertex != end_vertex && j == end_vertex) {
                color[i - 1] = "black";
                printf("vertex %d\n is now black\n", i);
                graph->f[i - 1] = time;
                time++;
                return TRUE;
             }
             //end
        }
        alpha = alpha->NEXT;
        already_discovered = alpha->vrtx_obj->discovered;
    }
    color[i - 1] = "black";
    alpha->vrtx_obj->discovered = FALSE;
    printf("vertex %d\n is now black\n", i);
    graph->f[i - 1] = time;
    time++;
    return TRUE;
}

int main(void) {
     int filename_size = 50, line_size = 500, string_size = 70, menuchoice_size = 10;

    //for input
    char* input_name = NULL;
    input_name = malloc(sizeof(char) * filename_size);
    assert(input_name != NULL);
    FILE* input_file, *output_file;
    /**
    printf("Enter the name of the input file: ");
    fgets(input_name, filename_size, stdin);
    input_name[strlen(input_name) - 1] = '\0';
    input_file = fopen(input_name, "r");
    assert(input_file != NULL); */
    input_file = fopen("input.txt", "r");
    
    //for output
    /**
    char* output_name = malloc(sizeof(char) * filename_size);
    assert(output_name != NULL);
    printf("Enter the name of the output file: ");
    fgets(output_name, filename_size, stdin);
    output_name[strlen(output_name) - 1] = '\0';
    output_file = fopen(output_name, "a");
    assert(output_file != NULL); */
    
    output_file = fopen("output.txt", "a");
    
    //for menu choice
    int success_choice = FALSE, num_menu;
    char* line = malloc(sizeof(line_size)), *str_vertex_pair = malloc(sizeof(line_size));
    assert(line != NULL);
    assert(str_vertex_pair != NULL);
    char* menu_choice = malloc(sizeof(char) * menuchoice_size);
    assert(menu_choice != NULL);
    int more_dataset = TRUE, line_iter, start_line_iter, space_iter, row_iter = 0, line_bounds;
    int** cost_adj_mat = NULL;
    char** str_cost_adj_mat = NULL;
    int num_of_vertex;//, str_cost_alloc_iter, cost_alloc_iter;
    
    //for the graph
    GRAPH* graph = malloc(sizeof(GRAPH));
    int vertex_create_iter, array_filler_iter;
    int start_vertex = 0, end_vertex = 0;
    graph->node_list = NULL;
    graph->pred = NULL;
    graph->d = NULL;
    graph->f = NULL;
    Node* node;
    VRTX*_OBJ vrtx_obj;
    //for str_cost_adj_mat helpers
    int str_max_of_chars_for_num = 5, end_of_line_chars = 4;
    
    //for menu
    menu_choice = printMenuWithDataIter(menu_choice, menuchoice_size);
    while (more_dataset == TRUE) {
        switch(menu_choice[0] - '0') {
            case 0:
                row_iter = 0;
                while (fgets(line, line_size, input_file) && strcmp(line, "end\n") != 0) {
                    if (row_iter == 0) {
                        num_of_vertex = getNumOfVertex(line);
                        str_cost_adj_mat = realloc(str_cost_adj_mat, num_of_vertex * sizeof(char*));
                        cost_adj_mat = realloc(cost_adj_mat, num_of_vertex * sizeof(int*));
                        
                    }

                    space_iter = 0;
                    start_line_iter = 0;
                    //cost_adj_mat = realloc(cost_adj_mat, (row_iter + 1) * sizeof(int*));
                    //printf("string line is %s\n", line);
                    line_bounds = strlen(line);
                    str_cost_adj_mat[row_iter] = realloc(str_cost_adj_mat[row_iter], (num_of_vertex * str_max_of_chars_for_num * sizeof(char)) + end_of_line_chars); 
                    strncpy(str_cost_adj_mat[row_iter], line, line_bounds);
                    printf("copy_of_input: %s\n", str_cost_adj_mat[row_iter]);
                    for (line_iter = 0; line_iter < line_bounds; line_iter++) {
                        if (line[line_iter] == ' ' || line[line_iter] == '\n') {
                            line[line_iter] = '\0';
                            cost_adj_mat[row_iter] = realloc(cost_adj_mat[row_iter], (space_iter + 1) * sizeof(int));
                            cost_adj_mat[row_iter][space_iter] = atoi(&line[start_line_iter]);
                            //printf("string is %s at i %d and j %d is %d\n", &line[start_line_iter], row_iter, space_iter, cost_adj_mat[row_iter][space_iter]);
                            space_iter++;
                            start_line_iter = line_iter + 1;
                        }
                    }
                    line[line_bounds - 1] = '\0';
                    row_iter++;  
                }
                
                //constructing the graph
                /**
                 node = malloc(sizeof(Node));
                 graph->node_list = malloc(sizeof(Node*) * (sizeof(num_of_vertex) + 1));
                 graph->node_list[0] = node;*/
                 graph->node_list = malloc(sizeof(Node*) * (sizeof(num_of_vertex) + 1));
                 for (vertex_create_iter = 0; vertex_create_iter <= num_of_vertex; vertex_create_iter++) {
                    node = malloc(sizeof(Node));
                    vrtx_obj = malloc(sizeof(VRTX_OBJ));
                    vrtx_obj->VRTX = vertex_create_iter;
                    vrtx_obj->discovered = FALSE;
                    node->VRTX = vertex_create_iter;
                    node->vrtx_obj = vrtx_obj;
                    node->NEXT = NULL;
                    //printf("vertex %d created\t", node->VRTX);
                    graph->node_list[vertex_create_iter] = node;
                    //printf("vti: %d\tnode vrtx is %d\n with pointer %p\n", vertex_create_iter, graph->node_list[vertex_create_iter]->VRTX, graph->node_list[vertex_create_iter]);
                 }
                 printf("1.5 node vrtx is %d with pointer %p\n", graph->node_list[1]->VRTX, graph->node_list[1]);

                 
                 graph->pred = malloc(sizeof(int) * num_of_vertex);
                 graph->d = malloc(sizeof(int) * num_of_vertex);
                 graph->f = malloc(sizeof(int) * num_of_vertex);
                 
                 for(array_filler_iter = 0; array_filler_iter < num_of_vertex; array_filler_iter++) {
                    graph->pred[array_filler_iter] = 0;
                    //printf("at %d init to 0\t", array_filler_iter);
                 }
                 
                 //assigning cost to the graph edges
                 
                 
             case 1:
                printf("Enter a vertex pair (separate it by space): ");          
                fgets(str_vertex_pair, string_size, stdin);
                int str_vertex_pair_bounds = strlen(str_vertex_pair);
                //printf("bounds is %d\n", str_vertex_pair_bounds);
                str_vertex_pair[str_vertex_pair_bounds - 1] = '\0'; 
                int svp_iter;
 
                for (svp_iter = 0; svp_iter < str_vertex_pair_bounds; svp_iter++) {
                    if (str_vertex_pair[svp_iter] == ' ') {
                        str_vertex_pair[svp_iter] = '\0';
                        start_vertex = atoi(&str_vertex_pair[0]);
                        //printf("sv %d\n", start_vertex);
                        end_vertex = atoi(&str_vertex_pair[svp_iter + 1]);
                        //printf("ev %d\n", end_vertex);
                        break;
                    }
                }
                

                
                if ((start_vertex != 0 && (start_vertex <= num_of_vertex) && (start_vertex >= 1)) &&
                    (end_vertex != 0 && (end_vertex <= num_of_vertex) && (end_vertex >= 1))) {
                                            
                    int pred = 0, vertex_trav_iter, vertex_trav_iter2, color_iter;
                    
                    //using the cost adjacency matrix to build up every element of node_list by appending adjacent vertex
                    Node* rover;
                    for (vertex_trav_iter = 1; vertex_trav_iter <= num_of_vertex; vertex_trav_iter++) {
                        rover = graph->node_list[vertex_trav_iter];
                       for (vertex_trav_iter2 = 1; vertex_trav_iter2 <= num_of_vertex; vertex_trav_iter2++) {
                            if (cost_adj_mat[vertex_trav_iter - 1][vertex_trav_iter2 - 1] != 1000) {
                                node = malloc(sizeof(Node));
                                node->VRTX = vertex_trav_iter2;
                                node->TRAVEL_COST = cost_adj_mat[vertex_trav_iter - 1][vertex_trav_iter2 - 1];
                                rover->NEXT = node;
                                rover = node;
                                printf("start vertex: %d current_vertex: %d travel cost: %d\n", graph->node_list[vertex_trav_iter]->VRTX, node->VRTX, node->TRAVEL_COST);
                            }
                        } 
                    }
                    
                    //DFS driver
                    if (color != NULL) {
                        free(color);
                    }
                    
                    color = malloc(sizeof(char*) * num_of_vertex);
                    time = 1;
                                   
                    for (color_iter = 0; color_iter < num_of_vertex; color_iter++) {
                        color[color_iter] = "white";
                    }
                    edge_trav_iter = 1;
                    Edge** edge_list = malloc(2 * sizeof(Edge*));
                    int found_one = FALSE;
                    found_one = DFS(graph, edge_list, start_vertex, start_vertex, end_vertex);
                    
                    if (found_one == TRUE) {
                        printf("There is a longest path and it is");
                        int edge_iter;
                        for (edge_iter = 0; edge_iter < edge_trav_iter; edge_iter++) {
                            printf("start: %d - end: %d\n", edge_list[edge_iter]->start, edge_list[edge_iter]->end);
                        }
                        
                    }
                    
                    else {
                        printf("There is no longest path");
                    }
                            
                    printf("pred content\n");
                    printArrContent(graph->pred, num_of_vertex);
                    printf("d content\n");
                    printArrContent(graph->d, num_of_vertex);
                    printf("f content\n");
                    printArrContent(graph->f, num_of_vertex);
                }
                else {
                    printf("Vertex pair invalid input\nPlease follow the format: d d where d is an integer within bounds\n");
                }
                break;
        }
        
        //another choice of input mode
            
        success_choice = FALSE;
        while (success_choice == FALSE) {
            menu_choice = printMenuWithDataIter(menu_choice, menuchoice_size);
            printf("mc %s\n", menu_choice);
            if (strlen(menu_choice) == 1) {
                num_menu = menu_choice[0] - '0';
                if ((num_menu >= 0) && (num_menu <= 2)) {
                    success_choice = TRUE;
                }

                else {
                    printf("Enter a number menu from 0 to 1 only");
                }
            }

            else {
                printf("Enter a choice of length 1 only");
            }
        }
        if (num_menu == 2) {
            more_dataset = FALSE;
        }
    }
    
    //freeing all the pointers used in constructing the graph
     for (vertex_create_iter = 0; vertex_create_iter <= num_of_vertex; vertex_create_iter++) {
        Node* alpha = graph->node_list[vertex_create_iter]->NEXT;
        while (alpha != NULL) {
            Node* beta = alpha->NEXT;
            free(alpha);
            alpha = beta;
        }
        free(graph->node_list[vertex_create_iter]);
     }
     free(graph->node_list);
     free(graph->pred);
     free(graph->d);
     free(graph->f);
     free(edge_list);         
     //freeing all the other used pointers
     freeStrCostAdjMat(str_cost_adj_mat, num_of_vertex);
     free(str_cost_adj_mat);
     freeCostAdjMat(cost_adj_mat, num_of_vertex);
     free(cost_adj_mat);
     free(input_name);
     free(line);
     free(str_vertex_pair);
     free(menu_choice);
}
            

