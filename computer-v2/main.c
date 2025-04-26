#include "computer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define MAX_INPUT_SIZE 100


int main(){
    char input[MAX_INPUT_SIZE];

    menu();
    printf("Enter instruction: ");

    if(fgets(input, sizeof(input), stdin) == NULL)
    {
        perror("Input Error");
        exit(EXIT_FAILURE);
    }
    input[strcspn(input, "\n")] = '\0'; // cut \n at the end
    Instruction *inst = parseInstruction(input);
    if(inst != NULL)
    {
        printInstruction(inst); 
        destroy(inst);
    }
    return 0;
}