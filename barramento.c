#include <stdio.h>
#include "barramento.h"

barramento* init_barramento(){
    BUS = (barramento*)malloc(sizeof(barramento)*QTD_BARRAMENTOS);
    for(int i =0; i<QTD_BARRAMENTOS; i++){
        BUS[i].opcode = FLAG_VAZIO;
        BUS[i].instrucao = FLAG_VAZIO;
        BUS[i].type = FLAG_VAZIO;
        BUS[i].valida = FLAG_READY;
        BUS[i].unidade_func = FLAG_VAZIO; 
        BUS[i].rs, BUS[i].rt, BUS[i].rd = FLAG_VAZIO;
    }
    return BUS;
}

void add_info_barramento(int opcode, int type, int instrucao, int valida, int unidade_func, int rs, int rt, int rd){
        BUS[0].opcode = opcode;
        BUS[0].instrucao = instrucao;
        BUS[0].type = type;
        BUS[0].valida = valida;
        BUS[0].unidade_func = FLAG_VAZIO;
        BUS[0].rs = rs;
        BUS[0].rt = rt;
        BUS[0].rd = rd; 
}