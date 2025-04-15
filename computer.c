#include "computer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <math.h>

int address[ROW][COL];
char R1[SIZE];
char R2[SIZE];


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
void boot()
{
    srand(time(NULL));
    int i, j, x;
    x = rand() % 16;
    if (x < 0)
    {
        x = -x;
    }
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

//reversing bits
void reverse(char x[])
{
    int i;
    for (i = 0; i < strlen(x) / 2; i++)
    {
        char c1 = x[i];
        char c2 = x[strlen(x) - i - 1];
        x[i] = c2;
        x[strlen(x) - i - 1] = c1;
    }
}

// decimal to binary 
void convert(char x[])
{
    int i = 0;
    int d = 4;
    while (d != 0)
    {
        int b = d % 2;
        d = d / 2;
        x[i++] = b + '0';
    }
    x[i] = 0;
    reverse(x);
}

// binary to decimal  
int bin2dec(char x[])
{
    int count = 0;
    int i;
    for (i = 0; i < strlen(x); i++)
    {
        if (x[i] == '1')
            count = 2 * count + 1;
        else
            count = 2 * count;
    }
    return count;
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

int storeR1(int address[][COL], int num)
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

int storeR2(int address[][COL], int num)
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
    int i;
    char sum[SIZE];
    char s[SIZE] = {1, 1, 1, 1};

    bin2dec(R1);
    bin2dec(R2);
    for (i = 0; i < SIZE; i++)
    {
        sum[i] = R1[i] + R2[i];
    }
    convert(R1);
    reverse(R1);
    convert(sum);
    reverse(sum);
    for (i = 0; i < SIZE; i++)
    {
        if (sum[i] <= s[i])
        {
            R1[i] = sum[i];
            printf("%d", R1[i]);
        }

        else
        {
            printf("Sum is over 15\n");
            printf("R1 = ");
            for (i = 0; i < SIZE; i++)
            {
                R1[i] = 0;
                printf("%4d", R1[i]);
            }
            printf("\n");
        }
    }
}
void addRegistersR2()
{
    int i;
    char sum[SIZE];
    char s[SIZE] = {1, 1, 1, 1};

    bin2dec(R1);
    bin2dec(R2);
    
    for (i = 0; i < SIZE; i++)
    {
        sum[i] = R1[i] + R2[i];
    }

    convert(R2);
    reverse(R2);
    convert(sum);
    reverse(sum);

    {
        for (i = 0; i < SIZE; i++)
        {
            if (sum[i] <= s[i])
            {
                R2[i] = sum[i];
                printf("%4d", R2[i]);
            }
            else
            {
                printf("Sum is over 15\n");
                printf("R2 = ");
                for (i = 0; i < SIZE; i++)
                {
                    R2[i] = 0;
                    printf("%4d", R2[i]);
                }
                printf("\n");
            }
        }
    }
}

void subRegistersR1()
{
    int i;
    char res[SIZE];
    char r[SIZE] = {0, 0, 0, 0};
    bin2dec(R1);
    bin2dec(R2);
    for (i = 0;i<SIZE;i++)
    {
        res[i] = R1[i] - R2[i];
    }
    convert(res);
    if (res[i] > 0)
    {
        for (i = SIZE; i >= 0; i--)
        {
            if (res[i] > r[i])
            {
                R1[i] = res[i];
            }
            else
            {
                printf("Result is less that 0\n");
                printf("R1 = ");
                for (i = SIZE; i > 0; i--)
                {
                    R1[i] = 1;
                    printf("%4d", R1[i]);
                }
            }
        }
        printf("\n");
    }
}

void subRegistersR2()
{
    int i;
    char res[SIZE];
    char r[SIZE] = {0};
    bin2dec(R1);
    bin2dec(R2);
    for(i=0;i<SIZE;i++)
    {
        res[i] = R2[i] - R1[i];
    }
    convert(res);
    {
        for (i = 0;i >= SIZE;i--)
        {
            if (res[i] > r[i])
            {
                R2[i] = res[i];
            }
            else
            {
                printf("Result is less than 0\n");
                printf("R2 = ");
                for (i = SIZE; i > 0; i--)
                {
                    R2[i] = 1;
                    printf("%4d", R2[i]);
                }
            }
        }
        printf("\n");
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
