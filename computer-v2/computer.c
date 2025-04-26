#include "computer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


void menu()
{
    printf("1)Boot\n2)Memory\n3)Load R[1 or 2]\n4)Store R[1 or 2]\n5)Add/Sub R[1 or 2]\n6)Show R[1 or 2]\n");
}


int validateInput(char *name,char *arg,char *i_str){
    //allLowerCheck(name);
    //allLowerCheck(arg);

    if(name == NULL)
    {
        printf("Invalid Input!\n");
        return 0;
    }

    if(strcmp(name, "load") == 0 || strcmp(name, "store") == 0)
    {
        if(arg == NULL || i_str == NULL)
        {
            printf("LOAD and STORE require 3 tokens eg.[load r1 1]\n");
            return 0;
        }
    }

    if(strcmp(name, "add") == 0 || strcmp(name, "sub") == 0 || strcmp(name, "show") == 0)
    {
        if(arg == NULL || i_str != NULL)
        {
            printf("ADD, SUB, SHOW require 2 tokens eg.[add r1]");
            return 0;
        }
    }

    if(strcmp(name, "boot") == 0 || strcmp(name, "mem") == 0)
    {
        if(arg != NULL || i_str != NULL)
        {
            printf("boot and mem do not require any other tokens\n");
            return 0;
        }
    }
    return 1;

}


Instruction *parseInstruction(char *input){
    char *name = strtok(input, " \n");
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
    inst->arg = strdup(arg);
    inst->i = i;
    inst->handler = NULL;

    return inst;
}



void printInstruction(Instruction *inst){
    printf("User entered: ");
    printf("%s %s %d\n", inst->name, inst->arg, inst->i);
}

void destroy(Instruction *inst){
    assert(inst != NULL);

    free(inst->name);
    free(inst->arg);
    free(inst);
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


