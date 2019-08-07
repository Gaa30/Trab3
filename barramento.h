#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "unidade_func.h"

typedef struct{
    int opcode;
    int type;
    int instrucao;
    int valida;
    int unidade_func;
    int rs,rt,rd;
}barramento;

barramento* init_barramento();

barramento* BUS;

void add_info_barramento(int opcode, int type, int instrucao, int valida, int unidade_func, int rs, int rt, int rd);
