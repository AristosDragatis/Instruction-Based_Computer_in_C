#include "computer.h"
#include <stdio.h>
#include <stdlib.h>



void menu()
{
    printf("1)Boot\n2)Memory\n3)Load R[1 or 2\n4)Store R[1 or 2]\n5)Add/Sub R[1 or 2]\n6)Show R[1 or 2]\n");
}

void allCapitalCheck(char *x)
{
    int size = strlen(x);
    for(int i=0;i < size; i++)
    {
        if(x[i] >= 'a' && x[i] <= 'z')
        {
            x[i] -= 32;
        }
    }
}

void boot()
{



}

