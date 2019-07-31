#include <stdio.h>
#include "unidade_func.h"

//por convenção, as unidades funcionais 0 e 1 são de mult,
//a unidade funcional 2 é de div,
//a unidade funcional 3 é de add e
//a unidade funcional 4 é de int

unidade_func* init_unidade_func(){
    unidade_func unidades[TAM_UNIDADE_FUNC];
    for (int i = 0; i<TAM_UNIDADE_FUNC; i++){
        unidades[i].busy = FLAG_READY;
        unidades[i].operacao = i;
        unidades[i].dest_register = FLAG_VAZIO;
        for (int j = 0; j<2; j++){
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
    return unidades;
}

int issue(int op, int dst, int src1, int src2, int unidadefuncional, unidade_func* unidades){
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

void read_operands(int unidadefuncional, unidade_func* unidades){
    if(unidades[unidadefuncional].ready[0] == FLAG_READY && unidades[unidadefuncional].ready[1] == FLAG_READY){
        unidades[unidadefuncional].ready[0] = FLAG_BUSY;
        unidades[unidadefuncional].ready[1] = FLAG_BUSY;
    }
}

void execute(unidade_func* unidades, int unidadefuncional){
    switch (unidadefuncional){
        case 0:
            //MUL e MULT
            banco_registradores[unidades[0].dest_register].valor = ula_mult(unidades[0].source_register[0],unidades[0].source_register[1]);
        break;
        case 1:
            //MUL E MULT
            banco_registradores[unidades[1].dest_register].valor = ula_mult(unidades[1].source_register[0],unidades[1].source_register[1]);
        break;
        case 2:
            //DIV
            banco_registradores[unidades[2].dest_register].valor = ula_div(unidades[2].source_register[1],unidades[2].source_register[0]);
        break;
        case 3:
            //ADD, ADDI, MADD (verificar o instruction type)
            banco_registradores[unidades[3].dest_register].valor = ula_somador(unidades[3].source_register[0], unidades[3].source_register[1]);
        break;
        case 4:
            //B, J, BEQ, BEQL, BGEZ, BGTZ, BLEZ, BLTZ, BNE, SUB, MSUB, MFHI, MFLO, MOVN, MOVZ, MTHI, MTLO
            //(verificar o instruction type)
            
    }
}

void write_back(unidade_func* unidades){
    /* wait until (∀f {(Fj[f]≠Fi[FU] OR Rj[f]=No) AND (Fk[f]≠Fi[FU] OR Rk[f]=No)})
    foreach f do
        if Qj[f]=FU then Rj[f] ← Yes;
        if Qk[f]=FU then Rk[f] ← Yes;
    Result[Fi[FU]] ← 0; // 0 means no FU generates the register's result
    RegFile[Fi[FU]] ← computed value;
    Busy[FU] ← No; */
}