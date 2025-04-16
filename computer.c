#include "computer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

int address[ROW][COL];
char R1[5];
char R2[5];


void allCapitalCheck(char x[])
{
    int i;
    for (i = 0; i < strlen(x); i++)
    {
        if (x[i] >= 'a' && x[i] <= 'z')
        {
            x[i] -= 32;
        }
    }
}

int is_valid_input(char in[20])
{
    char temp[20];
    strcpy(temp, in);
    int length = strlen(temp);

    allCapitalCheck(temp);
    switch (length)
    {
    case 3:
        if (strncmp(temp, "MEM", 3) == 0)
        {
            splitCommand(temp);
            displayMemory(address);
        }
        break;
    case 4:
    {
        if (strncmp(temp, "BOOT", 4) == 0)
        {
            splitCommand(temp);
            printf("Booting system...\n");
            boot();
            printf("Booting was successful...\n");
        }
        else if(strncmp(temp, "BOOT", 4) != 0)
        {
            printf("Invalid Input\n");
        }
    }
    break;
    case 6:
        if(strcmp(temp, "ADD R1") == 0)
        {
            splitCommand(temp);
            addRegistersR1();
        }
        if(strcmp(temp, "ADD R2") == 0)
        {
            splitCommand(temp);
            addRegistersR2();
        }
        if (strcmp(temp, "SUB R1") == 0)
        {
            splitCommand(temp);
            subRegistersR1();
        }
        if(strcmp(temp, "SUB R2") == 0)
        {
            splitCommand(temp);
            subRegistersR2();
        }
    break;
    case 7:
    {
        if (strcmp(temp, "SHOW R1") == 0)
        {
            splitCommand(temp);
            displayR1();
        }
        else if(strcmp(temp, "SHOW R2") == 0)
        {
            splitCommand(temp);
            displayR2();
        }
        else 
        {
            printf("Invalid Input\n");
        }
    }
    break;
    case 9:
    {
        int i = 0;
        if (strncmp(temp, "LOAD R1", 7) == 0 && temp[7] == ' ')
        {
            i = temp[8] - '0';  // convert char to int  
            splitCommand(temp);
            loadR1(address, i);
        }
        else if (strncmp(temp, "LOAD R2", 7) == 0 && temp[7] == ' ')
        {
            i = temp[8] - '0';
            splitCommand(temp);
            loadR2(address, i);
        }
        else
        {
            printf("Invalid Input\n");
        }
    }
    break;
    case 10:
    {
        int n;
        if (strncmp(temp, "STORE R1", 8) == 0 && temp[8] == ' ')
        {
            n = temp[9] - '0';
            splitCommand(temp);
            storeR1(address, n);
        }
        else if(strncmp(temp, "STORE R2", 8) == 0 && temp[8] == ' ')
        {
            n = temp[9] - '0';
            splitCommand(temp);
            storeR2(address, n);
        }
        else
        {
            printf("Invalid Input\n");
        }
    }
    break;
    default:
    {
        if (strlen(temp) > 11)
        {
            printf("Size must not be over 11 letters!!\n");
        }
    }
    }
}

// booting the pc and giving it random values [0 or 1]
// random values to address and R1, R2 registers 
void boot()
{
    srand(time(NULL));
    int i, j;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            address[i][j] = rand() % 2;
        }
    }
    for (i = 0; i < SIZE; i++)
    {
        R1[i] = rand() % 2; 
        R2[i] = rand() % 2;
    }
}


// printing Memory 2D-array 
void displayMemory(int address[][COL])
{
    int i, j;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            printf("%d\t", address[i][j]);
        }
        printf("\n");
    }
}

// check if command or definition 
void splitCommand(char x[])
{
    int i, icount = 0;
    char entoli[50];
    char orisma[50];
    int flag = 0;
    for (i = 0; i < strlen(x); i++)
    {
        if (x[i] != ' ')
        {
            if (flag == 0)
                entoli[icount++] = x[i];
            else
                orisma[icount++] = x[i];
        }
        else
        {
            if (flag == 0)
            {
                entoli[icount] = '\0';
                flag = 1;
                printf("Command given: %s \n", entoli);
            }
            else
            {
                orisma[icount] = '\0';
                printf("Definition given: %s \n", orisma);
            }
            icount = 0;
        }
    }
    if (x[strlen(x) - 1] != ' ')
    {
        if (flag == 0)
        {
            entoli[icount] = '\0';
            printf("Command Given: %s \n", entoli);
        }
        else
        {
            orisma[icount] = '\0';
            printf("Definition given: %s \n", orisma);
        }
    }
}


int loadR1(int address[ROW][COL], int num)
{
    int j;
    if(num < 0 || num >= ROW) 
    {
        printf("Invalid memory location [0 - 9]\n");
        return 0;
    }
    else{
        for (j = 0; j < COL; j++)
        {
            R1[j] = address[num][j];
        }
        return 1;
    }
}

int loadR2(int address[ROW][COL], int num)
{
    int j;
    if (num < 0 || num >= ROW) 
    {
        printf("Invalid memory location [0 - 9]\n");
        return 0;
    }
    else{
        for(j=0;j<COL;j++)
        {
            R2[j] = address[num][j];
        }
        return 1;
    }
}

int storeR1(int address[ROW][COL], int num)
{
    int j;
    if(num < 0 || num >= ROW){
        printf("Invalid memory location [0-9]\n");
        return 0;
    }
    for(j=0;j<COL;j++)
    {
        address[num][j] = R1[j];
    }
    return 1;
}

int storeR2(int address[ROW][COL], int num)
{
    int j;
    if(num < 0 || num >= ROW)
    {
        printf("Invalid memory location [0-9]\n");
        return 0;
    }

    for(j=0;j<COL;j++)
    {
        address[num][j] = R2[j];
    }
    return 1;
}

void addRegistersR1()
{
    int i, val1=0, val2=0;
    int sum;
    
    // convert to int
    for(i=0;i<SIZE;i++){
        val1 = val1 * 2 + R1[i];
        val2 = val2 * 2 + R2[i];
    }

    for (i = 0; i < SIZE; i++)
    {
        sum = val1 + val2;  // sum registers
    }


    for(i=0;i<SIZE;i++)
    {
        if(sum > 15){
            printf("Sum is over 15\n");
            printf("R1 = ");
            for(i=0;i<SIZE;i++){
                R1[i] = 0;
                printf("%4d", R1[i]);
            }
            printf("\n");
        }else{
            for(i=SIZE-1; i>= 0;i--){
                R1[i] = sum % 2;
                sum = sum/2;
            }
            printf("R1= ");
            for (i = 0; i < SIZE; i++)
            {
                printf("%4d",R1[i]);
            }
        }
    }
}

void addRegistersR2()
{
    int i, val1=0, val2=0;
    int sum;
    
    // convert to int
    for(i=0;i<SIZE;i++){
        val1 = val1 * 2 + R1[i];
        val2 = val2 * 2 + R2[i];
    }

    for (i = 0; i < SIZE; i++)
    {
        sum = val2 + val1;  // sum registers
    }


    for(i=0;i<SIZE;i++)
    {
        if(sum > 15){
            printf("Sum is over 15\n");
            printf("R2 = ");
            for(i=0;i<SIZE;i++){
                R2[i] = 0;
                printf("%4d", R2[i]);
            }
            printf("\n");
        }else{
            for(i=SIZE-1; i>= 0;i--){
                R2[i] = sum % 2;
                sum = sum/2;
            }
            printf("R2 = ");
            for (i = 0; i < SIZE; i++)
            {
                printf("%4d",R2[i]);
            }
        }
    } 
}


void subRegistersR1()
{
    int i, val1=0, val2=0;
    int res;
    
    // convert from char to int (left-shift)
    for(i=0;i<SIZE;i++){
        val1 = val1 * 2 + R1[i];
        val2 = val2 * 2 + R2[i];
    }

    for (i = 0; i < SIZE; i++)
    {
        res = val1 - val2;  // subtract registers
    }


    for(i=0;i<SIZE;i++)
    {
        if(res < 0){
            printf("Subtraction is less than 0\n");
            printf("R1 = ");
            for(i=0;i<SIZE;i++){
                R1[i] = 0;
                printf("%4d", R1[i]);
            }
            printf("\n");
        }else{
            for(i=SIZE-1; i>= 0;i--){
                R1[i] = res % 2;
                res = res/2;
            }
            printf("R1 = ");
            for (i = 0; i < SIZE; i++)
            {
                printf("%4d",R1[i]);
            }
        }
    } 
}

void subRegistersR2()
{

    int i, val1=0, val2=0;
    int res;
    
    // convert from char to int (left-shift)
    for(i=0;i<SIZE;i++){
        val1 = val1 * 2 + R1[i];
        val2 = val2 * 2 + R2[i];
    }

    for (i = 0; i < SIZE; i++)
    {
        res = val2 - val1;  // subtract registers
    }


    for(i=0;i<SIZE;i++)
    {
        if(res < 0){
            printf("Subtraction is less than 0\n");
            printf("R2 = ");
            for(i=0;i<SIZE;i++){
                R2[i] = 0;
                printf("%4d", R2[i]);
            }
            printf("\n");
        }else{
            for(i=SIZE-1; i>= 0;i--){
                R2[i] = res % 2;
                res = res/2;
            }
            printf("R2 = ");
            for (i = 0; i < SIZE; i++)
            {
                printf("%4d",R2[i]);
            }
        }
    } 
}

void displayR1()
{
    int i;

    for (i = 0; i < SIZE; i++)
    {
        printf("%4d", R1[i]);
    }
    printf("\n");
}

void displayR2()
{
    int i;

    for (i = 0; i < SIZE; i++)
    {
        printf("%4d", R2[i]);
    }
    printf("\n");
}
