#include <stdio.h>
#include "unidade_func.h"

unidade_func* init_unidade_func(){
    unidade_func unidades[TAM_UNIDADE_FUNC];
    for (i = 0; i<TAM_UNIDADE_FUNC; i++){
        unidades[i].busy = FLAG_READY;
        unidades[i].operacao = FLAG_VAZIO;
        unidades[i].dest_register = FLAG_VAZIO;
        for (j = 0; j<2; j++){
            unidades[i].source_register[j] = FLAG_VAZIO;
            unidades[i].queue[j] = FLAG_VAZIO;
            unidades[i].ready[j] = FLAG_VAZIO;
        }
        unidades[i].instr_type = FLAG_VAZIO;
        unidades[i].instr_valida = FLAG_VAZIO;
        unidades[i].Res = FLAG_VAZIO;
        unidades[i].Res11 = FLAG_VAZIO;
        unidades[i].cycle_counter = FLAG_VAZIO;
    }
}

int issue(int op, int dst, int src1, int src2, int unidadefuncional){
    if(unidades[unidadefuncional].busy != FLAG_BUSY && unidades[unidadefuncional].Res == FLAG_VAZIO && unidades[unidadefuncional].Res11 == FLAG_VAZIO){
        unidades[unidadefuncional].busy = FLAG_BUSY;
        unidades[unidadefuncional].operacao = op;
        unidades[unidadefuncional].dest_register = dst;
        unidades[unidadefuncional].source_register[0] = src1;
        unidades[unidadefuncional].source_register[1] = src2;
        /*Qj[FU] ← Result[src1];
        Qk[FU] ← Result[src2];
        Rj[FU] ← Qj[FU] == 0;
        Rk[FU] ← Qk[FU] == 0;*/
    }
}

void read_operands(int unidadefuncional){
    if(unidades[unidadefuncional].ready[0] == FLAG_READY && unidades[unidadefuncional].ready[1] == FLAG_READY){
        unidades[unidadefuncional].ready[0] = FLAG_BUSY;
        unidades[unidadefuncional].ready[1] = FLAG_BUSY;
    }
}

void execute(){
    
}

void write_back(){

}
