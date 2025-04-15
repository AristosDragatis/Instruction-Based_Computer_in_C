#include "computer.h"
#include <stdio.h>


int main()
{
    char input[20];

    printf("Welcome, Please enter one of the following\nNote that you must use BOOT first!\n1)BOOT\n2)MEM\n3)LOAD R[1 or 2]\n4)STORE R[1 or 2]\n5)ADD/SUB R[1 or 2]\n6)SHOW R[1 or 2]\n");
    do
    {
        printf("Input here: ");
        gets(input);
        is_valid_input(input);

    } while (1);
    return 0;
}


