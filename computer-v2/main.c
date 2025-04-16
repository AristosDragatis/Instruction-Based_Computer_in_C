#include "computer.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    char *input = (char *)malloc(15 * sizeof(char));

    menu();
    if(input == NULL)
    {
        printf("Allocation failed\n");
        exit(0);
    }else{
        printf("Enter input here: ");
        fgets(input, sizeof(input), stdin);
        // is_valid_input(input);
    }
    free(input);
    return 0;
}