#include "computer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_INPUT_SIZE 100

int **address = NULL;
char *R1 = NULL;
char *R2 = NULL;

void menu()
{
    printf("1)Boot\n2)Memory\n3)Load R[1 or 2]\n4)Store R[1 or 2]\n5)Add/Sub R[1 or 2]\n6)Show R[1 or 2]\n7)Quit (Q or q)\n8)Menu\n");
}


// validate user input 
int validateInput(char *name,char *arg,char *i_str){
    //allLowerCheck(name);
    //allLowerCheck(arg);

    // if no user input print invalid input
    if(name == NULL)
    {
        printf("Invalid Input!\n");
        return 0;
    }

    // show menu
    if(strcmp(name, "menu") == 0)
    {
        menu();
    }

    // exiting program functionality
    if(strcmp(name, "q") == 0 || strcmp(name, "Q") == 0 || strcmp(name, "quit") == 0)
    {
        printf("Exiting...\n");
        exit(-1);
    }

    // load and store 
    if(strcmp(name, "load") == 0 || strcmp(name, "store") == 0)
    {
        if(arg == NULL || i_str == NULL)
        {
            printf("LOAD and STORE require 3 tokens eg.[load r1 1]\n");
            return 0;
        }
    }

    // add, sub and show
    if(strcmp(name, "add") == 0 || strcmp(name, "sub") == 0 || strcmp(name, "show") == 0)
    {
        if(arg == NULL || i_str != NULL)
        {
            printf("ADD, SUB, SHOW require 2 tokens eg.[add r1]");
            return 0;
        }
        if(strcmp(name, "add") == 0)
        {
            if(strcmp(arg, "r1") == 0){
                //addRegistersR1();
            }
            else if(strcmp(arg, "r2") == 0){
                //addRegistersR2();
            }
        }
        if(strcmp(name, "sub") == 0)
        {
            if(strcmp(arg, "r1") == 0){
                //subRegistersR1();
            }
            else if(strcmp(arg, "r2") == 0){
                //subRegistersR2();
            }
        }
        //functionality for show R1 and R2
        if(strcmp(name, "show") == 0)
        {
            if(strcmp(arg, "r1") == 0)
            {
                displayR1();
            }
            else if(strcmp(arg, "r2") == 0)
            {
                displayR2();
            }
        }
    }

    // boot and mem
    if(strcmp(name, "boot") == 0 || strcmp(name, "mem") == 0)
    {
        if(arg != NULL || i_str != NULL)
        {
            printf("boot and mem do not require any other tokens\n");
            return 0;
        }else
        {
            if(strcmp(name, "boot") == 0)
            {
                boot();
            }
            else if(strcmp(name, "mem") == 0)
            {
                displayMemory(address);
            }
        }
    }
    return 1;

}

Instruction *parseInstruction(char *input){

    char tempInput[MAX_INPUT_SIZE];
    strncpy(tempInput, input, MAX_INPUT_SIZE);
    tempInput[MAX_INPUT_SIZE-1] = '\0'; // always null-terminate

    char *name = strtok(tempInput, " \n");
    char *arg = strtok(NULL, "  \n");
    char *i_str = strtok(NULL, " \n");
    

    if(!validateInput(name, arg, i_str))
    {
        return NULL;
    }
    
    int i=0;
    if(i_str != NULL)
    {
        i = atoi(i_str);
    }
    return createInstruction(name, arg, i);
}


Instruction *createInstruction(char *name, char *arg, int i)
{
    Instruction *inst= malloc(sizeof(Instruction));
    assert(inst != NULL);

    inst->name = strdup(name);
    inst->arg = arg ? strdup(arg): NULL; // Only strdup if arg is not NULL
    inst->i = i;
    inst->handler = NULL;

    return inst;
}



void printInstruction(Instruction *inst){
    if(inst->arg)
        printf("%s %s %d\n", inst->name, inst->arg, inst->i);
    else
        printf("%s\n", inst->name);
}

// Function to destroy the instruction object
void destroy(Instruction *inst){
    assert(inst != NULL);

    free(inst->name);
    free(inst->arg);
    free(inst);
}

void boot()
{
    unsigned int seed = time(NULL);
    printf("Booting...\n");
    // allocating memory space for address 
    address = malloc(10 * sizeof(int*));
    for(int i=0;i<10;i++)
    {
        address[i] = malloc(10 * sizeof(int));
        for(int j=0;j<10;j++)
        {
            // fill address with random 0 and 1 numbers 
            address[i][j] = rand_r(&seed) % 2;
        }
    }
    R1 = malloc(10 * sizeof(char));
    R2 = malloc(10 * sizeof(char));
    for(int i=0;i<10;i++)
    {
        seed = time(NULL) + i;
        R1[i] = rand_r(&seed) % 2;
        R2[i] = rand_r(&seed) % 2;
    }
    printf("Boot complete.\n");
}

void displayMemory(int **address)
{
    printf("Memory:\n");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            printf("%d ", address[i][j]);
        }
        printf("\n");
    }
}


// functions to display registers R1 and R2
void displayR1()
{
    printf("R1= ");
    for(int i=0;i<10;i++)
    {
        printf("%2d", R1[i]);
    }
    printf(" \n");
}

void displayR2()
{
    printf("R2= ");
    for(int i=0;i<10;i++)
    {
        printf("%2d", R2[i]);
    }
    printf(" \n");
}


void allLowerCheck(char *x)
{
    int size = strlen(x);
    for(int i=0;i < size; i++)
    {
        if(x[i] >= 'A' && x[i] <= 'Z')
        {
            x[i] += 32;
        }
    }
}
