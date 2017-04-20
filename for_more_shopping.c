#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define FALSE 0
#define TRUE 1

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

int main(void) {
     int filename_size = 50, line_size = 500, string_size = 70, menuchoice_size = 10;

    //for input
    char* input_name = NULL;
    input_name = malloc(sizeof(char) * filename_size);
    assert(input_name != NULL);
    FILE* input_file, *output_file;
    printf("Enter the name of the input file: ");
    fgets(input_name, filename_size, stdin);
    input_name[strlen(input_name) - 1] = '\0';
    input_file = fopen(input_name, "r");
    assert(input_file != NULL);
    
    //for output
    char* output_name = malloc(sizeof(char) * filename_size);
    assert(output_name != NULL);
    printf("Enter the name of the output file: ");
    fgets(output_name, filename_size, stdin);
    output_name[strlen(output_name) - 1] = '\0';
    output_file = fopen(output_name, "a");
    assert(output_file != NULL);
    
    //for menu choice
    int success_choice = FALSE, num_menu;
    char* line = malloc(sizeof(line_size)), *line2 = malloc(sizeof(line_size));
    char* menu_choice = malloc(sizeof(char) * menuchoice_size);
    assert(menu_choice != NULL);
    int more_dataset = TRUE, line_iter, start_line_iter, space_iter, row_iter, line_bounds;
    int** cost_adj_mat;
    while (more_dataset == TRUE) {
        row_iter = 0;
        while (fgets(line, line_size, input_file)) {
            space_iter = 0;
            start_line_iter = 0;
            line[strlen(line) - 1] = '\0';
            cost_adj_mat = realloc(cost_adj_mat, (row_iter + 1) * sizeof(int*));
            printf("string line is %s\n", line);
            line_bounds = strlen(line);
            for (line_iter = 0; line_iter < line_bounds; line_iter++) {
                if (line[line_iter] == ' ') {
                    line[line_iter] = '\0';
                    cost_adj_mat[row_iter] = realloc(cost_adj_mat[row_iter], (space_iter + 1) * sizeof(int));
                    cost_adj_mat[row_iter][space_iter] = atoi(&line[start_line_iter]);
                    printf("string is %s at i %d and j %d is %d\n", &line[start_line_iter], row_iter, space_iter, cost_adj_mat[row_iter][space_iter]);
                    space_iter++;
                    start_line_iter = line_iter + 1;
                }
            }
            
            row_iter++;  
        }
        //another choice of input mode

        success_choice = FALSE;
        while (success_choice == FALSE) {
            menu_choice = printMenuWithDataIter(menu_choice, menuchoice_size);
            printf("%s\n", menu_choice);
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
        if (num_menu != 0) {
            more_dataset = FALSE;
        }
     }
    
    printf("Enter the vertex pairs needed on the termal line (separate it by space)\n");
    printf("Enter 2 for processing through an input file\n");
}