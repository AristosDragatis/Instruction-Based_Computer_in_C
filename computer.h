/* Header file */
#ifndef COMPUTER
#define COMPUTER

#define ROW 10
#define COL 4
#define SIZE 4

// declarations
extern int address[ROW][COL];
extern char R1[SIZE];
extern char R2[SIZE];

void boot();
int loadR1(int address[ROW][COL], int num);
int loadR2(int address[ROW][COL], int num);
int storeR1(int address[ROW][COL], int num);
int storeR2(int address[ROW][COL], int num);
void addRegistersR1();
void addRegistersR2();
void subRegistersR1();
void subRegistersR2();
void displayR1();
void displayR2();
void displayMemory();
int is_valid_input(char in[20]);
void splitCommand(char x[]);
void allCapitalCheck(char x[]);
int bin2dec(char x[]);
void convert(char x[]);
void reverse(char x[]);

#endif


