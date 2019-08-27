#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include<stdlib.h>
#include<string.h>


#define TAM_PALAVRA 4
#define START_ADDRESS_DATA 0x4000000

#define UF_MUL_CODE 9990
#define UF_DIV_CODE 9991
#define UF_INT_CODE 9992
#define UF_ADD_CODE 9993


//#define DATA_AMOUNT 400

//#define FLAG_EXIT  17
#define FLAG_VAZIO -1
#define FLAG_READY -3
#define FLAG_BUSY  -2
#define DISPONIVEL -4

#define REG_PG 28 /*GP*/
#define REG_PS 29 /*SP*/
#define REG_RA 31
#define REG_HI 32
#define REG_LO 33

#define SPECIAL 0
#define SPECIAL2 28
#define REGIMM 1
#define DEFAULT 63

#define QTD_BARRAMENTOS 4
#define TRUE 1000
#define FALSE 1010

#define ISSUE 0
#define READ 1
#define EXECUTE 2
#define WRITEBACK 3

#define TYPE_R -6
#define TYPE_I -7
#define TYPE_J -8

#define ADD 32
#define ADDI 8
#define AND 36
#define ANDI 12
#define B 4
#define BEQ 4
#define BEQL 20
#define BGEZ 1
#define BGTZ 7
#define BLEZ 6
#define BLTZ 0 //00000
#define BNE 5
#define DIV 26
#define J 2
#define JR 8
#define LUI 15
#define MADD 0
#define MFHI 16
#define MFLO 18
#define MOVN 11
#define MOVZ 10
#define MSUB 4
#define MTHI 17
#define MTLO 19
#define MUL 2
#define MULT 24
#define NOP 0
#define NOR 39
#define OR 37
#define ORI 13
#define SUB 34
#define XOR 38
#define XORI 14

typedef struct instruction{
    int instr;
    int rs;
    int rt;
    int rd;
    int type;
    int operation;
}instruction;

instruction Instrucao;

#endif