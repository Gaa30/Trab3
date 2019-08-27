#include <stdio.h>
#include "unidade_func.h"

//por convenção, as unidades funcionais 0 e 1 são de mult,
//a unidade funcional 2 é de div,
//a unidade funcional 3 é de add e
//a unidade funcional 4 é de int

int EMITIDA = TRUE;
int INIT_POS = 0;
int INIT_POS_DIV = QUANT_UF_MUL;
int INIT_POS_ADD = QUANT_UF_MUL + QUANT_UF_DIV;
int INIT_POS_INT = QUANT_UF_MUL + QUANT_UF_DIV + QUANT_UF_ADD;
int TAM_UNIDADE_FUNC = QUANT_UF_ADD + QUANT_UF_DIV + QUANT_UF_INT + QUANT_UF_MUL;

void next(int pos){
    BUS[pos].type = BUS[pos - 1].type;
    BUS[pos].instrucao = BUS[pos - 1].instrucao;
    BUS[pos].valida = BUS[pos - 1].valida;
    BUS[pos].opcode = BUS[pos - 1].opcode;
    BUS[pos].unidade_func = BUS[pos - 1].unidade_func;
    BUS[pos].rd = BUS[pos -1].rd;
    BUS[pos].rt = BUS[pos -1].rt;
    BUS[pos].rs = BUS[pos -1].rs;
}

void next_writeback(int pos, int uf){
    for(int i = 0; i< TAM_UNIDADE_FUNC; i++){
        if(BUS[pos].lista_UF_prontas[i] == FLAG_VAZIO){
            BUS[pos].lista_UF_prontas[i] = uf;
        }
    }
}

unidade_func* init_unidade_func(){
    unidades_funcionais = (unidade_func*)malloc(sizeof(unidade_func)*TAM_UNIDADE_FUNC);
    for (int i = 0; i<TAM_UNIDADE_FUNC; i++){
        unidades_funcionais[i].busy = FLAG_READY;
        unidades_funcionais[i].operacao = i;
        unidades_funcionais[i].dest_register = FLAG_VAZIO;
        for (int j = 0; j<2; j++){
            unidades_funcionais[i].source_register[j] = FLAG_VAZIO;
            unidades_funcionais[i].q[j] = FLAG_VAZIO;
            unidades_funcionais[i].ready[j] = FLAG_VAZIO;
        }
        unidades_funcionais[i].instr_type = FLAG_VAZIO;
        unidades_funcionais[i].instr_valida = FLAG_VAZIO;
        unidades_funcionais[i].Res = FLAG_VAZIO;
        unidades_funcionais[i].Res11 = FLAG_VAZIO;
        unidades_funcionais[i].cycle_counter = FLAG_VAZIO;
    }
    for (int i = 0; i<QUANT_UF_MUL; i++){
        unidades_funcionais[i].unidade_func_type = UF_MUL_CODE;
    }
    for (int i = INIT_POS_DIV; i< INIT_POS_ADD; i++){
        unidades_funcionais[i].unidade_func_type = UF_DIV_CODE;
    }
    for (int i = INIT_POS_ADD; i < INIT_POS_INT; i++){
        unidades_funcionais[i].unidade_func_type = UF_ADD_CODE;
    }
    for (int i = INIT_POS_INT; i< TAM_UNIDADE_FUNC; i++){
        unidades_funcionais[i].unidade_func_type = UF_INT_CODE;
    }
    return unidades_funcionais;
}

//ISSUE TA PRONTA
int issue(){
    int unidade_funcional_code;
    int i;
    int checkB1, checkB2;
    switch(BUS[0].type){
        case DEFAULT:
            switch(BUS[0].opcode){
                case ADDI:
                    unidade_funcional_code = UF_ADD_CODE;
                    i = INIT_POS_ADD;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_INT){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_ADD_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;

                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case ANDI:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 1;
                            reg_change_status(unidades_funcionais[i].dest_register, i);       
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);                                                 
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case B || BEQ:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    checkB1, checkB2 = BUS[0].instrucao;
                    checkB1 = checkB1 >> 16 &11111;
                    checkB2 = checkB2 >> 21 &11111;
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        if(checkB1 == 00000 && checkB2 == 00000){
                            unidades_funcionais[i].cycles_needed = 1;           
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = FLAG_READY;                                                      
                        }else{
                            unidades_funcionais[i].cycles_needed = 2;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                        }
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            OPC.valor = PC.valor;
                            PC.valor = unidades_funcionais[i].dest_register;
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case BEQL:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            OPC.valor = PC.valor;
                            PC.valor = unidades_funcionais[i].dest_register;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);   
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case BGTZ:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            OPC.valor = PC.valor;
                            PC.valor = unidades_funcionais[i].dest_register;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case BLEZ:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            OPC.valor = PC.valor;
                            PC.valor = unidades_funcionais[i].dest_register;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case BNE:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            OPC.valor = PC.valor;
                            PC.valor = unidades_funcionais[i].dest_register;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case J:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            OPC.valor = PC.valor;
                            PC.valor = unidades_funcionais[i].dest_register;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = FLAG_READY;
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 1;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case LUI:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt; 
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = FLAG_READY;
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case ORI:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 1;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case XORI:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 1;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
            }
        break;
        case SPECIAL:
            switch(BUS[0].opcode){
                case ADD:
                    unidade_funcional_code = UF_ADD_CODE;
                    i = INIT_POS_ADD;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_INT){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_ADD_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case AND:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 1;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case DIV:
                    unidade_funcional_code = UF_DIV_CODE;
                    i = INIT_POS_DIV;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_ADD){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_DIV_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 5;
                            reg_change_status(unidades_funcionais[i].dest_register, i);   
                            reg_change_status(REG_HI, i); 
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case JR://como assim não tem rd??? //verificar
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            OPC.valor = PC.valor;
                            PC.valor = banco_registradores[unidades_funcionais[i].source_register[1]].valor;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 1;
                            reg_change_status(unidades_funcionais[i].dest_register, i); 
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case MFHI:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = FLAG_READY;
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case MFLO:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = FLAG_READY;
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case MOVN:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case MOVZ:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case MTHI:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case MTLO:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case MULT:
                    unidade_funcional_code = UF_MUL_CODE;
                    i = INIT_POS;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_DIV){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_MUL_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 5;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            reg_change_status(REG_HI, i);
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case NOP:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = FLAG_READY;
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 1;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case NOR:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 1;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case OR:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 1;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case SUB:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case XOR:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 1;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
            }
        break;
        case SPECIAL2:
            switch(BUS[0].opcode){
                case MADD:
                    unidade_funcional_code = UF_ADD_CODE;
                    i = INIT_POS_ADD;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_INT){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_ADD_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            reg_change_status(REG_HI, i);
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case MSUB:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);  
                            reg_change_status(REG_HI, i);  
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case MUL:
                    unidade_funcional_code = UF_MUL_CODE;
                    i = INIT_POS;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_DIV){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_MUL_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[0] = BUS[0].rt;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = reg_get_status(unidades_funcionais[i].source_register[0]);
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 5;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[0]].Qi);
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
            }
        break;
        case REGIMM:
            switch(BUS[0].opcode){
                case BGEZ:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            OPC.valor = PC.valor;
                            PC.valor = unidades_funcionais[i].dest_register;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
                case BLTZ:
                    unidade_funcional_code = UF_INT_CODE;
                    i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            EMITIDA = TRUE;
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            OPC.valor = PC.valor;
                            PC.valor = unidades_funcionais[i].dest_register;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            reg_change_status(unidades_funcionais[i].dest_register, i);    
                            unidades_funcionais[i].Res11 = reg_get_UF(banco_registradores[unidades_funcionais[i].source_register[1]].Qi);
                            BUS[0].unidade_func = i;                        
                        }
                    }else{
                        EMITIDA = FALSE;
                    }
                break;
            }
        break;
    }
    if(EMITIDA == TRUE){
        next(1);
    }
}

int read_operands(){
    int unidadefuncional = BUS[1].unidade_func;
    if(unidades_funcionais[unidadefuncional].dest_register == unidades_funcionais[unidadefuncional].source_register[0]){
        unidades_funcionais[unidadefuncional].ready[0] = FLAG_READY;
    }else if(unidades_funcionais[unidadefuncional].dest_register == unidades_funcionais[unidadefuncional].source_register[1]){
        unidades_funcionais[unidadefuncional].ready[1] = FLAG_READY;
    }
    if(unidades_funcionais[unidadefuncional].ready[0] == FLAG_READY && unidades_funcionais[unidadefuncional].ready[1] == FLAG_READY){
        unidades_funcionais[unidadefuncional].ready[0] = FLAG_BUSY;
        unidades_funcionais[unidadefuncional].ready[1] = FLAG_BUSY;
        next(2);
    }else{
        return 0;
    }
    return 1;
}

void execute(){
    int verifica;
    int i;
    int lui;
    for(i = INIT_POS; i < TAM_UNIDADE_FUNC; i++){
        if(unidades_funcionais[i].cycle_counter < unidades_funcionais[i].cycles_needed){
            if(unidades_funcionais[i].cycle_counter == 0){
                switch (unidades_funcionais[i].unidade_func_type){
                    case UF_MUL_CODE:
                        //MUL E MULT
                        if(unidades_funcionais[i].instr == MUL){
                            buffer[unidades_funcionais[i].dest_register].valor = ula_mult(banco_registradores[unidades_funcionais[i].source_register[0]].valor,banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                        }else{//falta checar overflow
                            size_t resultado;
                            resultado = ula_mult(banco_registradores[unidades_funcionais[i].source_register[0]].valor,banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                            buffer[unidades_funcionais[i].dest_register].valor = ula_and(resultado, 0000000000000000000000000000000011111111111111111111111111111111);
                            buffer[REG_HI].valor = resultado >> 32;        
                        }
                    break;
                    case UF_DIV_CODE:
                        //DIV
                        buffer[unidades_funcionais[i].dest_register].valor = ula_div(banco_registradores[unidades_funcionais[i].source_register[1]].valor,banco_registradores[unidades_funcionais[i].source_register[0]].valor);
                        buffer[REG_HI].valor = ula_mod(banco_registradores[unidades_funcionais[i].source_register[1]].valor,banco_registradores[unidades_funcionais[i].source_register[0]].valor);
                    break;
                    case UF_ADD_CODE:
                        //ADD, ADDI, MADD (verificar o instruction type)
                        if(unidades_funcionais[i].instr == ADD){
                            buffer[unidades_funcionais[i].dest_register].valor = ula_somador(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                        }else if (unidades_funcionais[i].instr == ADDI){
                            buffer[unidades_funcionais[i].dest_register].valor = ula_somador(unidades_funcionais[i].source_register[0], banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                        }else{
                            size_t resultado;
                            resultado = ula_mult(unidades_funcionais[i].source_register[0],unidades_funcionais[i].source_register[1]);
                            buffer[unidades_funcionais[i].dest_register].valor = ula_and(resultado, 0000000000000000000000000000000011111111111111111111111111111111);
                            buffer[REG_HI].valor = resultado >> 32;     
                        }
                    break;
                    case UF_INT_CODE:
                        switch(unidades_funcionais[i].instr_type){
                            case REGIMM:
                                switch(unidades_funcionais[i].instr){
                                    case BGEZ:
                                        if(buffer[unidades_funcionais[i].source_register[1]].valor >= 0){
                                            unidades_funcionais[i].instr_valida = TRUE;
                                            PC.valor = PC.valor;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                            PC.valor = OPC.valor;
                                        }
                                    break;
                                    case BLTZ:
                                        if(buffer[unidades_funcionais[i].source_register[1]].valor < 0){
                                            unidades_funcionais[i].instr_valida = TRUE;
                                            PC.valor = PC.valor;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                            PC.valor = OPC.valor;
                                        }
                                    break;
                                }
                            break;
                            case SPECIAL:
                                switch(unidades_funcionais[i].instr){
                                    case AND:
                                        buffer[unidades_funcionais[i].dest_register].valor = ula_and(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                                    break;
                                    case JR:
                                        unidades_funcionais[i].instr_valida = TRUE;
                                        PC.valor = PC.valor;
                                    case MFHI:
                                        buffer[unidades_funcionais[i].dest_register].valor = banco_registradores[REG_HI].valor;
                                    break;
                                    case MFLO:
                                        buffer[unidades_funcionais[i].dest_register].valor = banco_registradores[REG_LO].valor;
                                    break;
                                    case MOVN:
                                        if(buffer[unidades_funcionais[i].source_register[0]].valor != 0){
                                            buffer[unidades_funcionais[i].dest_register].valor = banco_registradores[unidades_funcionais[i].source_register[1]].valor;
                                        } else{
                                            printf("Nao foi possivel mover\n");//verificar
                                        }
                                    break;
                                    case MOVZ:
                                        if(buffer[unidades_funcionais[i].source_register[0]].valor == 0){
                                            buffer[unidades_funcionais[i].dest_register].valor = banco_registradores[unidades_funcionais[i].source_register[1]].valor;
                                        }
                                    break;
                                    case MTHI:
                                        buffer[REG_HI].valor = banco_registradores[unidades_funcionais[i].source_register[1]].valor; 
                                    break;
                                    case MTLO:
                                        buffer[REG_LO].valor = banco_registradores[unidades_funcionais[i].source_register[1]].valor;
                                    break;
                                    case NOP:
                                        buffer[unidades_funcionais[i].dest_register].valor = 0;
                                    case NOR:
                                        buffer[unidades_funcionais[i].dest_register].valor = ula_nor(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                                    break;
                                    case OR:
                                        buffer[unidades_funcionais[i].dest_register].valor = ula_or(banco_registradores[unidades_funcionais[i].source_register[1]].valor, banco_registradores[unidades_funcionais[i].source_register[0]].valor);
                                    break;
                                    case SUB:
                                        buffer[unidades_funcionais[i].dest_register].valor = ula_subtrator(banco_registradores[unidades_funcionais[i].source_register[1]].valor, banco_registradores[unidades_funcionais[i].source_register[0]].valor);
                                    break;
                                    case XOR:
                                        buffer[unidades_funcionais[i].dest_register].valor = ula_xor(banco_registradores[unidades_funcionais[i].source_register[i]].valor, banco_registradores[unidades_funcionais[i].source_register[0]].valor);
                                    break;
                                } 
                            break;                   
                            case SPECIAL2:
                                switch(unidades_funcionais[i].instr){
                                    case MSUB:
                                        buffer[unidades_funcionais[i].dest_register].valor = ula_subtrator(ula_or(banco_registradores[REG_HI].valor, banco_registradores[REG_LO].valor), ula_mult(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor));
                                        buffer[REG_HI].valor = ula_subtrator(ula_or(banco_registradores[REG_HI].valor, banco_registradores[REG_LO].valor), ula_mult(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor)) >> 32;
                                    break;
                                } 
                            break;               
                            case DEFAULT:
                                switch(unidades_funcionais[i].instr){
                                    case ANDI:
                                        buffer[unidades_funcionais[i].dest_register].valor = ula_and(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                                    break;
                                    case B || BEQ:
                                        if (unidades_funcionais[i].instr == BEQ){
                                            verifica = ula_div(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                                            if(verifica == 1){
                                                unidades_funcionais[i].instr_valida = TRUE;
                                                PC.valor = PC.valor;
                                            }else{
                                                unidades_funcionais[i].instr_valida = FALSE;
                                                PC.valor = OPC.valor;
                                            }
                                        }else{
                                            unidades_funcionais[i].instr_valida = TRUE;
                                        }
                                    break;
                                    case BEQL:
                                        verifica = ula_div(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                                        if(verifica == 1){
                                            unidades_funcionais[i].instr_valida = TRUE;
                                            PC.valor = PC.valor;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                            PC.valor = OPC.valor;
                                        }
                                    break;
                                    case BGTZ:
                                        if(banco_registradores[unidades_funcionais[i].source_register[1]].valor > 0){
                                            unidades_funcionais[i].instr_valida = TRUE;
                                            PC.valor = PC.valor;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                            PC.valor = OPC.valor;
                                        }
                                    break;
                                    case BLEZ:
                                        if(banco_registradores[unidades_funcionais[i].source_register[1]].valor <= 0){
                                            unidades_funcionais[i].instr_valida = TRUE;
                                            PC.valor = PC.valor;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                            PC.valor = OPC.valor;
                                        }
                                    break;
                                    case BNE:
                                        verifica = ula_div(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                                        if(verifica != 1){
                                            unidades_funcionais[i].instr_valida = TRUE;
                                            PC.valor = PC.valor;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                            PC.valor = OPC.valor;
                                        }
                                    break;
                                    case J:
                                        unidades_funcionais[i].instr_valida = TRUE;
                                        PC.valor = PC.valor;
                                    break;
                                    case LUI:
                                        lui = ula_shiftleft(unidades_funcionais[i].source_register[0], 16);
                                        buffer[unidades_funcionais[i].dest_register].valor = lui;
                                    break;
                                    case ORI:
                                        buffer[unidades_funcionais[i].source_register[0]].valor = ula_or(banco_registradores[unidades_funcionais[i].source_register[1]].valor, unidades_funcionais[i].dest_register);
                                    break;
                                    case XORI:
                                        buffer[unidades_funcionais[i].source_register[0]].valor = ula_xor(banco_registradores[unidades_funcionais[i].source_register[1]].valor, unidades_funcionais[i].dest_register);
                                    break;
                                } 
                            break;               
                        }
                    break;
                }
                unidades_funcionais[i].cycle_counter++;
            }else{
                unidades_funcionais[i].cycle_counter++;
            }
        }else{
            next_writeback(3, i);
        }
    }
}

void write_back(unidade_func* unidades){
    for(int i = 0; i < TAM_UNIDADE_FUNC; i++){
        if(BUS[3].lista_UF_prontas[i] != FLAG_VAZIO){
            banco_registradores[unidades_funcionais[BUS[3].lista_UF_prontas[i]].dest_register].valor = buffer[unidades_funcionais[BUS[3].lista_UF_prontas[i]].dest_register].valor;
            banco_registradores[unidades_funcionais[BUS[3].lista_UF_prontas[i]].dest_register].Qi = FLAG_VAZIO;
            switch(unidades_funcionais[BUS[3].lista_UF_prontas[i]].operacao){
                case MULT:
                case DIV:
                case MADD:
                case MSUB:
                    banco_registradores[REG_HI].valor = buffer[REG_HI].valor;
                    banco_registradores[REG_HI].Qi = FLAG_VAZIO;
            }
            unidades_funcionais[BUS[3].lista_UF_prontas[i]].busy = FLAG_READY;
            unidades_funcionais[BUS[3].lista_UF_prontas[i]].operacao = i;
            unidades_funcionais[BUS[3].lista_UF_prontas[i]].dest_register = FLAG_VAZIO;
            for (int j = 0; j<2; j++){
                unidades_funcionais[BUS[3].lista_UF_prontas[i]].source_register[j] = FLAG_VAZIO;
                unidades_funcionais[BUS[3].lista_UF_prontas[i]].q[j] = FLAG_VAZIO;
                unidades_funcionais[BUS[3].lista_UF_prontas[i]].ready[j] = FLAG_VAZIO;
            }
            unidades_funcionais[BUS[3].lista_UF_prontas[i]].instr_type = FLAG_VAZIO;
            unidades_funcionais[BUS[3].lista_UF_prontas[i]].instr_valida = FLAG_VAZIO;
            unidades_funcionais[BUS[3].lista_UF_prontas[i]].Res = FLAG_VAZIO;
            unidades_funcionais[BUS[3].lista_UF_prontas[i]].Res11 = FLAG_VAZIO;
            unidades_funcionais[BUS[3].lista_UF_prontas[i]].cycle_counter = FLAG_VAZIO;
            BUS[3].lista_UF_prontas[i] = FLAG_VAZIO;
        }
    }

    /* wait until (∀f {(Fj[f]≠Fi[FU] OR Rj[f]=No) AND (Fk[f]≠Fi[FU] OR Rk[f]=No)})
    foreach f do
        if Qj[f]=FU then Rj[f] ← Yes;
        if Qk[f]=FU then Rk[f] ← Yes;
    Result[Fi[FU]] ← 0; // 0 means no FU generates the register's result
    RegFile[Fi[FU]] ← computed value;
    Busy[FU] ← No; */
}