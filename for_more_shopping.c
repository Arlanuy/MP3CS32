#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define FALSE 0
#define TRUE 1

typedef struct Node Node;

struct Node
{
    int VRTX;
    char TYPE;
    Node *NEXT;
};

typedef struct {
    Node** node_list;
}LIST;

typedef struct{
    LIST list;
    int* pred;
    int* d;
    int* f;
}GRAPH; 



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
    char* menu_choice = malloc(sizeof(char) * menuchoice_size);
    assert(menu_choice != NULL);
    int more_dataset = TRUE, line_iter, start_line_iter, space_iter, row_iter = 0, line_bounds;
    int** cost_adj_mat = NULL;
    char** str_cost_adj_mat = NULL;
    int num_of_vertex;//, str_cost_alloc_iter, cost_alloc_iter;
    
    //for the graph
    GRAPH graph;
    LIST list;
    int vertex_create_iter, array_filler_iter;
    int start_vertex = 0, end_vertex = 0;
    
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
                    str_cost_adj_mat[row_iter] = realloc(str_cost_adj_mat[row_iter], (num_of_vertex * 5 * sizeof(char)) + 4); //5 for the amount of characters given a 3 digit number and a space, + 4 for extra characters like '\n' and carriage return
                    str_cost_adj_mat[row_iter] = line;
                    row_iter++;  
                }
                //constructing the graph
                 list.node_list = malloc(sizeof(Node*) * sizeof(num_of_vertex));
                 for (vertex_create_iter = 1; vertex_create_iter <= num_of_vertex; vertex_create_iter++) {
                    Node* node = malloc(sizeof(Node));
                    node->VRTX = vertex_create_iter;
                    node->NEXT = NULL;
                    printf("vertex %d created\t", node->VRTX);
                    list.node_list[vertex_create_iter - 1] = node;
                 }
                 

                 graph.list = list;
                 graph.pred = malloc(sizeof(int) * num_of_vertex);
                 graph.d = malloc(sizeof(int) * num_of_vertex);
                 graph.f = malloc(sizeof(int) * num_of_vertex);
                 
                 for(array_filler_iter = 0; array_filler_iter < num_of_vertex; array_filler_iter++) {
                    graph.pred[array_filler_iter] = 0;
                    printf("at %d init to 0\t", array_filler_iter);
                 }
                 
                 //DFS driver
                 
                
            case 1:
                printf("Enter a vertex pair (separate it by space): ");          
                fgets(str_vertex_pair, string_size, stdin);
                int str_vertex_pair_bounds = strlen(str_vertex_pair);
                printf("bounds is %d\n", str_vertex_pair_bounds);
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
                    printf("doing the DFS");       
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
     for (vertex_create_iter = 1; vertex_create_iter <= num_of_vertex; vertex_create_iter++) {
        free(list.node_list[vertex_create_iter - 1]);
     }
     free(list.node_list);
     free(graph.pred);
     free(graph.d);
     free(graph.f);
             
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