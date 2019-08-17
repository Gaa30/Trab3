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
    int lista_UF_prontas[QUANT_UF_ADD + QUANT_UF_DIV + QUANT_UF_INT + QUANT_UF_MUL];
}barramento;

barramento* init_barramento();

barramento* BUS;

void add_info_barramento(int opcode, int type, int instrucao, int valida, int unidade_func, int rs, int rt, int rd);
