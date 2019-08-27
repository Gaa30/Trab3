#include <stdio.h>
#include "barramento.h"

int TAM_UF = QUANT_UF_ADD + QUANT_UF_DIV + QUANT_UF_INT + QUANT_UF_MUL;

barramento* init_barramento(){
    BUS = (barramento*)malloc(sizeof(barramento)*QTD_BARRAMENTOS);
    for(int i =0; i<QTD_BARRAMENTOS; i++){
        BUS[i].opcode = FLAG_VAZIO;
        BUS[i].instrucao = FLAG_VAZIO;
        BUS[i].type = FLAG_VAZIO;
        BUS[i].valida = FLAG_READY;
        BUS[i].unidade_func = FLAG_VAZIO; 
        BUS[i].rs, BUS[i].rt, BUS[i].rd = FLAG_VAZIO;
        if (i == 3){
            for(int j = 0; j < TAM_UF; j++){
                BUS[i].lista_UF_prontas[j] = FLAG_VAZIO;
            }
        }
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

int verifica_barramento(int pos){
    if(BUS[pos].instrucao == FLAG_VAZIO){
        return TRUE;
    }else{
        return FALSE;
    }
}

void remove_barramento(int pos){
   // BUS[pos].opcode = FLAG_VAZIO;
    BUS[pos].instrucao = FLAG_VAZIO;
   // BUS[pos].type = FLAG_VAZIO;
   // BUS[pos].valida = FLAG_VAZIO;
   // BUS[pos].unidade_func = FLAG_VAZIO;
   // BUS[pos].rs = FLAG_VAZIO;
   // BUS[pos].rt = FLAG_VAZIO;
   // BUS[pos].rd = FLAG_VAZIO;
}

int verifica_all_barramentos(){
    for(int i = 0; i<4; i++){
        if(verifica_barramento(i)==TRUE){
            continue;
        }else{
            return FALSE;
        }
    }
    return TRUE;
}