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
int flag = 0; 

void menu()
{
    printf("1)Boot\n2)Memory\n3)Load R[1 or 2]\n4)Store R[1 or 2]\n5)Add/Sub R[1 or 2]\n6)Show R[1 or 2]\n7)Quit (Q or q)\n8)Menu\n");
}


// validate user input 
int validateInput(char *name, char *arg, char *i_str) {
    if (name == NULL) {
        printf("Invalid Input!\n");
        return 0;
    }

    // Check for quit command
    if (strcmp(name, "q") == 0 || strcmp(name, "Q") == 0 || strcmp(name, "quit") == 0) {
        return 1; // allow quit, handler will exit
    }

    // Check for menu command
    if (strcmp(name, "menu") == 0) {
        return 1; // allow menu, handler will print menu
    }

    // load and store require 3 tokens
    if (strcmp(name, "load") == 0 || strcmp(name, "store") == 0) {
        if (arg == NULL || i_str == NULL) {
            printf("LOAD and STORE require 3 tokens eg.[load r1 1]\n");
            return 0;
        }
        return 1;
    }

    // add, sub, show require 2 tokens
    if (strcmp(name, "add") == 0 || strcmp(name, "sub") == 0 || strcmp(name, "show") == 0) {
        if (arg == NULL || i_str != NULL) {
            printf("ADD, SUB, SHOW require 2 tokens eg.[add r1]\n");
            return 0;
        }
        return 1;
    }

    // boot and mem require only the command
    if (strcmp(name, "boot") == 0 || strcmp(name, "mem") == 0) {
        if (arg != NULL || i_str != NULL) {
            printf("boot and mem do not require any other tokens\n");
            return 0;
        }
        return 1;
    }

    // If command is not recognized
    printf("Unknown command: %s\n", name);
    return 0;
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

    if(strcmp(name, "boot") == 0)
        inst->handler = handle_boot;
    else if(strcmp(name, "mem") == 0)
        inst->handler = handle_mem;
    else if(strcmp(name, "load") == 0)
        inst->handler = handle_load;
    else if(strcmp(name, "store") == 0)
        inst->handler = handle_store;
    else if(strcmp(name, "add") == 0)
        inst->handler = handle_add;
    else if(strcmp(name, "sub") == 0)
        inst->handler = handle_sub;
    else if(strcmp(name, "show") == 0)
        inst->handler = handle_show;
    else if(strcmp(name, "q") == 0 || strcmp(name, "Q") == 0)
        inst->handler = handle_quit;
    else if(strcmp(name, "menu") == 0)
        inst->handler = handle_menu;

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

// booting the "computer"
void boot()
{
    
    unsigned int seed = time(NULL);
    printf("Booting...\n");

    // Free previous memory if already allocated
    if(address){
        for(int i=0;i<10;i++)
        {
            free(address[i]);
        }
        free(address);
        address = NULL;
    }

    if(R1){
        free(R1);
        R1 = NULL;
    }
    if(R2){
        free(R2);
        R2 = NULL;
    }


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


int loadR1(int **address, int num) {
    // todo : implement logic for showing current memory 
    printf("Called loadR1 with num=%d\n", num);
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            R1[i] = address[num][i];
        }
    }
    return 0;
}

int loadR2(int **address, int num) {
    // TODO: implement logic
    printf("Called loadR2 with num=%d\n", num);
    return 0;
}

int storeR1(int **address, int num) {
    // TODO: implement logic
    printf("Called storeR1 with num=%d\n", num);
    return 0;
}

int storeR2(int **address, int num) {
    // TODO: implement logic
    printf("Called storeR2 with num=%d\n", num);
    return 0;
}

void addRegistersR1() {
    // TODO: implement logic
    printf("Called addRegistersR1\n");
}

void addRegistersR2() {
    // TODO: implement logic
    printf("Called addRegistersR2\n");
}

void subRegistersR1() {
    // TODO: implement logic
    printf("Called subRegistersR2\n");
}

void subRegistersR2() {
    // TODO: implement logic
    printf("Called subRegistersR2\n");
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

// handler function implementations
void handle_boot(char *arg, int i) { 
    if(flag != 1){
        flag = 1;
        boot(); 
    }else{
        printf("Already booted..\n");
    }
}
void handle_mem(char *arg, int i) { displayMemory(address); }

//load
void handle_load(char *arg, int i){
    if(arg && strcmp(arg, "r1") == 0)
        loadR1(address, i);
    else if(arg && strcmp(arg, "r2") == 0)
        loadR2(address, i);
    else
        printf("Unknown register for load: %s\n", arg);
}

//store 
void handle_store(char *arg, int i) {
    if(arg && strcmp(arg, "r1") == 0)
        storeR1(address, i);
    else if(arg && strcmp(arg, "r2") == 0)
        storeR2(address, i);
    else
        printf("Unknown register for store: %s\n", arg);
}

//add
void handle_add(char *arg, int i) {
    if(arg && strcmp(arg, "r1") == 0)
        addRegistersR1();
    else if(arg && strcmp(arg, "r2") == 0)
        addRegistersR2();
    else
        printf("Unknown register for add: %s\n", arg);
}

//sub
void handle_sub(char *arg, int i) {
    if(arg && strcmp(arg, "r2") == 0)
        subRegistersR2();
    else
        printf("Unknown register for sub: %s\n", arg);
}

//show
void handle_show(char *arg, int i) {
    if(arg && strcmp(arg, "r1") == 0)
        displayR1();
    else if(arg && strcmp(arg, "r2") == 0)
        displayR2();
    else
        printf("Unknown register for show: %s\n", arg);
}

// exiting
void handle_quit(char *arg, int i) {
    printf("Exiting...\n");
    flag = 0;
    exit(0);
}

//menu
void handle_menu(char *arg, int i) {
    menu();
}
