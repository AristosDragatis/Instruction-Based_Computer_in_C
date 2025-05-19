#ifndef COMPUTER
#define COMPUTER

extern int **address;
extern char *R1;
extern char *R2;

typedef struct {
    char *name;                            // "LOAD"
    char *arg;                             // "R1"
    int i;                                 // 3
    void (*handler)(char *, int);         // pointer function
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
void subRegistersR1();
void subRegistersR2();
void displayR1();
void displayR2();
void displayMemory(int **address);
void allLowerCheck(char *x);


// handler function declarations
void handle_boot(char *arg, int i);
void handle_mem(char *arg, int i);
void handle_load(char *arg, int i);
void handle_store(char *arg, int i);
void handle_add(char *arg, int i);
void handle_sub(char *arg, int i);
void handle_show(char *arg, int i);
void handle_quit(char *arg, int i);
void handle_menu(char *arg, int i);

#endif