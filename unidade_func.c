#include <stdio.h>
#include "unidade_func.h"

//por convenção, as unidades funcionais 0 e 1 são de mult,
//a unidade funcional 2 é de div,
//a unidade funcional 3 é de add e
//a unidade funcional 4 é de int

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
    switch(BUS[0].type){
        case DEFAULT:
            switch(BUS[0].opcode){
                case ADDI:
                    int unidade_funcional_code = UF_ADD_CODE;
                    int i = INIT_POS_ADD;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_INT){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_ADD_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case ANDI:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case B || BEQ:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    int checkB1, checkB2 = BUS[0].instrucao;
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
                        }
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case BEQL:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case BGTZ:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                            unidades_funcionais[i].operacao = BUS[0].opcode;
                            unidades_funcionais[i].instr = BUS[0].instrucao;
                            unidades_funcionais[i].instr_type = BUS[0].type;
                            unidades_funcionais[i].dest_register = BUS[0].rd;
                            unidades_funcionais[i].source_register[1] = BUS[0].rs;
                            unidades_funcionais[i].q[0] = FLAG_READY;
                            unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                            unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                            unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                            unidades_funcionais[i].cycles_needed = 2;
                            BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case BLEZ:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                        unidades_funcionais[i].operacao = BUS[0].opcode;
                        unidades_funcionais[i].instr = BUS[0].instrucao;
                        unidades_funcionais[i].instr_type = BUS[0].type;
                        unidades_funcionais[i].dest_register = BUS[0].rd;
                        unidades_funcionais[i].source_register[1] = BUS[0].rs;
                        unidades_funcionais[i].q[0] = FLAG_READY;
                        unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                        unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                        unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                        unidades_funcionais[i].cycles_needed = 2;
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case BNE:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case J:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                        unidades_funcionais[i].operacao = BUS[0].opcode;
                        unidades_funcionais[i].instr = BUS[0].instrucao;
                        unidades_funcionais[i].instr_type = BUS[0].type;
                        unidades_funcionais[i].dest_register = BUS[0].rd;
                        unidades_funcionais[i].q[0] = FLAG_READY;
                        unidades_funcionais[i].q[1] = FLAG_READY;
                        unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                        unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                        unidades_funcionais[i].cycles_needed = 1;
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case LUI:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                        unidades_funcionais[i].operacao = BUS[0].opcode;
                        unidades_funcionais[i].instr = BUS[0].instrucao;
                        unidades_funcionais[i].instr_type = BUS[0].type;
                        unidades_funcionais[i].dest_register = BUS[0].rd;
                        unidades_funcionais[i].q[0] = FLAG_READY;
                        unidades_funcionais[i].q[1] = FLAG_READY;
                        unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                        unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                        unidades_funcionais[i].cycles_needed = 2;
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case ORI:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case XORI:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
            }
        break;
        case SPECIAL:
            switch(BUS[0].opcode){
                case ADD:
                    int unidade_funcional_code = UF_ADD_CODE;
                    int i = INIT_POS_ADD;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_INT){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_ADD_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case AND:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case DIV:
                    int unidade_funcional_code = UF_DIV_CODE;
                    int i = INIT_POS_DIV;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_ADD){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_DIV_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case JR://como assim não tem rd???
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                        unidades_funcionais[i].operacao = BUS[0].opcode;
                        unidades_funcionais[i].instr = BUS[0].instrucao;
                        unidades_funcionais[i].instr_type = BUS[0].type;
                        unidades_funcionais[i].dest_register = BUS[0].rd;
                        unidades_funcionais[i].source_register[1] = BUS[0].rs;
                        unidades_funcionais[i].q[0] = FLAG_READY;
                        unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                        unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                        unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                        unidades_funcionais[i].cycles_needed = 1;
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case MFHI:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                        unidades_funcionais[i].operacao = BUS[0].opcode;
                        unidades_funcionais[i].instr = BUS[0].instrucao;
                        unidades_funcionais[i].instr_type = BUS[0].type;
                        unidades_funcionais[i].dest_register = BUS[0].rd;
                        unidades_funcionais[i].q[0] = FLAG_READY;
                        unidades_funcionais[i].q[1] = FLAG_READY;
                        unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                        unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                        unidades_funcionais[i].cycles_needed = 2;
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case MFLO:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                        unidades_funcionais[i].operacao = BUS[0].opcode;
                        unidades_funcionais[i].instr = BUS[0].instrucao;
                        unidades_funcionais[i].instr_type = BUS[0].type;
                        unidades_funcionais[i].dest_register = BUS[0].rd;
                        unidades_funcionais[i].q[0] = FLAG_READY;
                        unidades_funcionais[i].q[1] = FLAG_READY;
                        unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                        unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                        unidades_funcionais[i].cycles_needed = 2;
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case MOVN:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case MOVZ:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case MTHI:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case MTLO:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case MULT:
                    int unidade_funcional_code = UF_MUL_CODE;
                    int i = INIT_POS;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_DIV){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_MUL_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case NOP:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                        unidades_funcionais[i].operacao = BUS[0].opcode;
                        unidades_funcionais[i].instr = BUS[0].instrucao;
                        unidades_funcionais[i].instr_type = BUS[0].type;
                        unidades_funcionais[i].q[0] = FLAG_READY;
                        unidades_funcionais[i].q[1] = FLAG_READY;
                        unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                        unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                        unidades_funcionais[i].cycles_needed = 1;
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case NOR:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case OR:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case SUB:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case XOR:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
            }
        break;
        case SPECIAL2:
            switch(BUS[0].opcode){
                case MADD:
                    int unidade_funcional_code = UF_ADD_CODE;
                    int i = INIT_POS_ADD;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_INT){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_ADD_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case MSUB:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case MUL:
                    int unidade_funcional_code = UF_MUL_CODE;
                    int i = INIT_POS;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < INIT_POS_DIV){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_MUL_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
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
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
            }
        break;
        case REGIMM:
            switch(BUS[0].opcode){
                case BGEZ:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                        unidades_funcionais[i].operacao = BUS[0].opcode;
                        unidades_funcionais[i].instr = BUS[0].instrucao;
                        unidades_funcionais[i].instr_type = BUS[0].type;
                        unidades_funcionais[i].dest_register = BUS[0].rd;
                        unidades_funcionais[i].source_register[1] = BUS[0].rs;
                        unidades_funcionais[i].q[0] = FLAG_READY;
                        unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                        unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                        unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                        unidades_funcionais[i].cycles_needed = 2;
                        BUS[0].unidade_func = i;
                        }
                    }else{
                        return 0;
                    }
                break;
                case BLTZ:
                    int unidade_funcional_code = UF_INT_CODE;
                    int i = INIT_POS_INT;
                    while(unidades_funcionais[i].busy != FLAG_READY && i < TAM_UNIDADE_FUNC){
                        i++;
                    }
                    if(unidades_funcionais[i].unidade_func_type == UF_INT_CODE){
                        unidades_funcionais[i].busy = FLAG_BUSY;
                        if(unidades_funcionais[i].Res == FLAG_VAZIO && unidades_funcionais[i].Res11 == FLAG_VAZIO){
                        unidades_funcionais[i].operacao = BUS[0].opcode;
                        unidades_funcionais[i].instr = BUS[0].instrucao;
                        unidades_funcionais[i].instr_type = BUS[0].type;
                        unidades_funcionais[i].dest_register = BUS[0].rd;
                        unidades_funcionais[i].source_register[1] = BUS[0].rs;
                        unidades_funcionais[i].q[0] = FLAG_READY;
                        unidades_funcionais[i].q[1] = reg_get_status(unidades_funcionais[i].source_register[1]);
                        unidades_funcionais[i].ready[0] = unidades_funcionais[i].q[0];
                        unidades_funcionais[i].ready[1] = unidades_funcionais[i].q[1];
                        unidades_funcionais[i].cycles_needed = 2;
                        BUS[0].unidade_func = i;                        
                        }
                    }else{
                        return 0;
                    }
                break;
            }
        break;
    }
    next(1);
    return 1;
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
    for(int i = INIT_POS; i < TAM_UNIDADE_FUNC; i++){
        if(unidades_funcionais[i].cycle_counter < unidades_funcionais[i].cycles_needed){
            if(unidades_funcionais[i].cycle_counter == 0){
                switch (unidades_funcionais[i].unidade_func_type){
                    case UF_MUL_CODE:
                        //MUL E MULT
                        if(unidades_funcionais[i].instr == MUL){
                            banco_registradores[unidades_funcionais[i].dest_register].valor = ula_mult(unidades_funcionais[i].source_register[0],unidades_funcionais[i].source_register[1]);
                        }else{//falta checar overflow
                            int resultado;
                            resultado = ula_mult(unidades_funcionais[i].source_register[0],unidades_funcionais[i].source_register[1]);
                            banco_registradores[unidades_funcionais[i].dest_register].valor = ula_and(resultado, 0000000000000000000000000000000011111111111111111111111111111111);
                            banco_registradores[REG_HI].valor = resultado >> 32;        
                        }
                    break;
                    case UF_DIV_CODE:
                        //DIV
                        banco_registradores[unidades_funcionais[i].dest_register].valor = ula_div(unidades_funcionais[i].source_register[1],unidades_funcionais[i].source_register[0]);
                        banco_registradores[REG_HI].valor = ula_mod(unidades_funcionais[i].source_register[1],unidades_funcionais[i].source_register[0]);
                    break;
                    case UF_ADD_CODE:
                        //ADD, ADDI, MADD (verificar o instruction type)
                        if(unidades_funcionais[i].instr == ADD){
                            banco_registradores[unidades_funcionais[i].dest_register].valor = ula_somador(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                        }else if (unidades_funcionais[i].instr == ADDI){
                            banco_registradores[unidades_funcionais[i].dest_register].valor = ula_somador(unidades_funcionais[i].source_register[0], banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                        }else{
                            int resultado;
                            resultado = ula_mult(unidades_funcionais[i].source_register[0],unidades_funcionais[i].source_register[1]);
                            banco_registradores[unidades_funcionais[i].dest_register].valor = ula_and(resultado, 0000000000000000000000000000000011111111111111111111111111111111);
                            banco_registradores[REG_HI].valor = resultado >> 32;     
                        }
                    break;
                    case UF_INT_CODE:
                        switch(unidades_funcionais[i].instr_type){
                            case REGIMM:
                                switch(unidades_funcionais[i].instr){
                                    case BGEZ:
                                        if(banco_registradores[unidades_funcionais[i].source_register[1]].valor >= 0){
                                            //faz a parte do pulo;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                        }
                                    break;
                                    case BLTZ:
                                        if(banco_registradores[unidades_funcionais[i].source_register[1]].valor < 0){
                                            //faz a parte do pulo;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                        }
                                    break;
                                }
                            break;
                            case SPECIAL:
                                switch(unidades_funcionais[i].instr){
                                    case AND:
                                        banco_registradores[unidades_funcionais[i].dest_register].valor = ula_and(unidades_funcionais[i].source_register[0], unidades_funcionais[i].source_register[1]);
                                    break;
                                    case JR:
                                    //
                                    case MFHI:
                                        banco_registradores[unidades_funcionais[i].dest_register].valor = banco_registradores[REG_HI].valor;
                                    break;
                                    case MFLO:
                                        banco_registradores[unidades_funcionais[i].dest_register].valor = banco_registradores[REG_LO].valor;
                                    break;
                                    case MOVN:
                                        if(banco_registradores[unidades_funcionais[i].source_register[0]].valor != 0){
                                            banco_registradores[unidades_funcionais[i].dest_register].valor = banco_registradores[unidades_funcionais[i].source_register[1]].valor;
                                        } else{
                                            return 0;
                                        }
                                    break;
                                    case MOVZ:
                                        if(banco_registradores[unidades_funcionais[i].source_register[0]].valor == 0){
                                            banco_registradores[unidades_funcionais[i].dest_register].valor = banco_registradores[unidades_funcionais[i].source_register[1]].valor;
                                        }
                                    break;
                                    case MTHI:
                                        banco_registradores[REG_HI].valor = banco_registradores[unidades_funcionais[i].source_register[1]].valor; 
                                    break;
                                    case MTLO:
                                        banco_registradores[REG_LO].valor = banco_registradores[unidades_funcionais[i].source_register[1]].valor;
                                    break;
                                    case NOP:
                                        
                                    case NOR:
                                        banco_registradores[unidades_funcionais[i].dest_register].valor = ula_nor(unidades_funcionais[i].source_register[0], unidades_funcionais[i].source_register[1]);
                                    break;
                                    case OR:
                                        banco_registradores[unidades_funcionais[i].dest_register].valor = ula_or(unidades_funcionais[i].source_register[1], unidades_funcionais[i].source_register[0]);
                                    break;
                                    case SUB:
                                        banco_registradores[unidades_funcionais[i].dest_register].valor = ula_sub(unidades_funcionais[i].source_register[1], unidades_funcionais[i].source_register[0]);
                                    break;
                                    case XOR:
                                        banco_registradores[unidades_funcionais[i].dest_register].valor = ula_xor(unidades_funcionais[i].source_register[i], unidades_funcionais[i].source_register[0]);
                                    break;
                                } 
                            break;                   
                            case SPECIAL2:
                                switch(unidades_funcionais[i].instr){
                                    case MSUB:
                                        ula_subtrator(ula_or(banco_registradores[REG_HI], banco_registradores[REG_LO]), ula_mult(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor));
                                    break;
                                } 
                            break;               
                            case DEFAULT:
                                switch(unidades_funcionais[i].instr){
                                    case ANDI:
                                        banco_registradores[unidades_funcionais[i].dest_register].valor = ula_and(unidades_funcionais[i].source_register[0], unidades_funcionais[i].source_register[1]);
                                    break;
                                    case B || BEQ:
                                        if (unidades_funcionais[i].instr == BEQ){
                                            int verifica = ula_div(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                                            if(verifica == 1){
                                                //faz a parte do pulo;
                                            }else{
                                                unidades_funcionais[i].instr_valida = FALSE;
                                            }
                                        }else{
                                            unidades_funcionais[i].instr_valida = TRUE;
                                        }
                                    break;
                                    case BEQL:
                                        int verifica = ula_div(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                                        if(verifica == 1){
                                            //faz a parte do pulo;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                        }
                                    break;
                                    case BGTZ:
                                        if(banco_registradores[unidades_funcionais[i].source_register[1]].valor > 0){
                                            //faz a parte do pulo;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                        }
                                    break;
                                    case BLEZ:
                                        if(banco_registradores[unidades_funcionais[i].source_register[1]].valor <= 0){
                                            //faz a parte do pulo;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                        }
                                    break;
                                    case BNE:
                                        int verifica = ula_div(banco_registradores[unidades_funcionais[i].source_register[0]].valor, banco_registradores[unidades_funcionais[i].source_register[1]].valor);
                                        if(verifica != 1){
                                            //faz a parte do pulo;
                                        }else{
                                            unidades_funcionais[i].instr_valida = FALSE;
                                        }
                                    break;
                                    case J:
                                        //PC  PCGPRLEN-1..28 || instr_index || 02
                                    break;
                                    case LUI:
                                        int low_order_zero = 00000000000000000000000000000000;
                                        banco_registradores[unidades_funcionais[i].dest_register].valor = low_order_zero;
                                    break;
                                    case ORI:
                                        banco_registradores[unidades_funcionais[i].source_register[0]].valor = ula_or(banco_registradores[unidades_funcionais[i].source_register[1]].valor, unidades_funcionais[i].dest_register);
                                    break;
                                    case XORI:
                                        banco_registradores[unidades_funcionais[i].source_register[0]].valor = ula_xor(banco_registradores[unidades_funcionais[i].source_register[1]].valor, unidades_funcionais[i].dest_register);
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
            next(3);
        }
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