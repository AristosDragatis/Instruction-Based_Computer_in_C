#ifndef COMPUTER
#define COMPUTER

extern int **address;
extern char *R1;
extern char *R2;

typedef struct {
    char *name;                            // π.χ. "LOAD"
    char *arg;                             // π.χ. "R1"
    int i;                                 // π.χ. 3
    void (*handler)(char *, int);         // δείκτης σε function
} Instruction;

Instruction *createInstruction(char *name, char *arg, int i);
Instruction *parseInstruction(char *input);
void printInstruction(Instruction *inst);
void destroy(Instruction *inst);
void boot();
void menu();
int loadR1(int **address, int num);
int loadR2(int **address, int num);
int storeR1(int **address, int num);
int storeR2(int **address, int num);
void addRegistersR1();
void addRegistersR2();
void subRegistersR2();
void subRegistersR2();
void displayR1();
void displayR2();
void displayMemory(int **address);
int is_valid_input(char *in);
void splitCommand(char *x);
void allLowerCheck(char *x);

#endif