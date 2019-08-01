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
    }
    return BUS;
}