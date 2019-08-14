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
}

unidade_func* init_unidade_func(){
    unidades_funcionais = (unidade_func*)malloc(sizeof(unidade_func)*TAM_UNIDADE_FUNC);
    for (int i = 0; i<TAM_UNIDADE_FUNC; i++){
        unidades_funcionais[i].busy = FLAG_READY;
        unidades_funcionais[i].operacao = i;
        unidades_funcionais[i].dest_register = FLAG_VAZIO;
        if (i < 2){
            unidades_funcionais[i].cycles_needed = 5;
        }else if(i == 2){
            unidades_funcionais[i].cycles_needed = 5;
        }else if(i == 3){
            unidades_funcionais[i].cycles_needed = 2;
        }else{
            unidades_funcionais[i].cycles_needed = 2;
        }
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
    return unidades_funcionais;
}

int getUF(int opcode){
    if (opcode == ADD || opcode == ADDI || opcode == SUB)
        return 3;
    else if (opcode == MUL || opcode == MULT) //tem mais ainda
        return 1;
    else if (opcode == DIV)
        return 2;
    else
    {
        return 4;
    }
}

int issue(){
    int unidadefuncional = getUF(BUS[0].opcode);
    BUS[0].unidade_func = unidadefuncional;
    if(unidadefuncional == 1){
        if(unidades_funcionais[0].busy == FLAG_BUSY && unidades_funcionais[1].busy == FLAG_READY)
            unidadefuncional == 1;
        else if(unidades_funcionais[1].busy == FLAG_BUSY && unidades_funcionais[0].busy == FLAG_READY)
            unidadefuncional == 0;
        else if(unidades_funcionais[0].busy == FLAG_READY && unidades_funcionais[1].busy == FLAG_READY)
            unidadefuncional == 0;
        else{
            unidadefuncional == 1;
        }
    }
    if(unidades_funcionais[unidadefuncional].busy != FLAG_BUSY && unidades_funcionais[unidadefuncional].Res == FLAG_VAZIO && unidades_funcionais[unidadefuncional].Res11 == FLAG_VAZIO){
        unidades_funcionais[unidadefuncional].busy = FLAG_BUSY;
        unidades_funcionais[unidadefuncional].operacao = BUS[0].opcode;
        int dst,src1,src2 = BUS[0].instrucao;
        unidades_funcionais[unidadefuncional].instr = BUS[0].instrucao;
        unidades_funcionais[unidadefuncional].instr_type = BUS[0].type;
        unidades_funcionais[unidadefuncional].dest_register = BUS[0].rd;
        unidades_funcionais[unidadefuncional].source_register[0] = BUS[0].rt;
        unidades_funcionais[unidadefuncional].source_register[1] = BUS[0].rs;
        unidades_funcionais[unidadefuncional].q[0] = reg_get_status(unidades_funcionais[unidadefuncional].source_register[0]);
        unidades_funcionais[unidadefuncional].q[1] = reg_get_status(unidades_funcionais[unidadefuncional].source_register[1]);                unidades_funcionais[unidadefuncional].q[1] = reg_get_status(unidades_funcionais[unidadefuncional].source_register[1]);
        unidades_funcionais[unidadefuncional].ready[0] = unidades_funcionais[unidadefuncional].q[0];
        unidades_funcionais[unidadefuncional].ready[1] = unidades_funcionais[unidadefuncional].q[1];
    }
    next(1);
}

void read_operands(){
    int unidadefuncional = BUS[1].unidade_func;
    if(unidades_funcionais[unidadefuncional].ready[0] == FLAG_READY && unidades_funcionais[unidadefuncional].ready[1] == FLAG_READY){
        unidades_funcionais[unidadefuncional].ready[0] = FLAG_BUSY;
        unidades_funcionais[unidadefuncional].ready[1] = FLAG_BUSY;
    }
    next(2);
}

void execute(){
    switch (BUS[2].unidade_func){
        case 0:
            //MUL E MULT
            if(unidades_funcionais[0].instr == MUL){
                banco_registradores[unidades_funcionais[0].dest_register].valor = ula_mult(unidades_funcionais[0].source_register[0],unidades_funcionais[0].source_register[1]);
            }else{//falta checar overflow
                int resultado;
                resultado = ula_mult(unidades_funcionais[0].source_register[0],unidades_funcionais[0].source_register[1]);
                banco_registradores[unidades_funcionais[0].dest_register].valor = ula_and(resultado, 0000000000000000000000000000000011111111111111111111111111111111);
                banco_registradores[REG_HI].valor = resultado >> 32;        
            }
        break;
        case 1:
            //MUL E MULT
            if(unidades_funcionais[1].instr == MUL){
                banco_registradores[unidades_funcionais[1].dest_register].valor = ula_mult(unidades_funcionais[1].source_register[0],unidades_funcionais[1].source_register[1]);
            }else{//falta checar overflow
                int resultado;
                resultado = ula_mult(unidades_funcionais[1].source_register[0],unidades_funcionais[1].source_register[1]);
                banco_registradores[unidades_funcionais[1].dest_register].valor = ula_and(resultado, 0000000000000000000000000000000011111111111111111111111111111111);
                banco_registradores[REG_HI].valor = resultado >> 32;  
            }
        break;
        case 2:
            //DIV
            banco_registradores[unidades_funcionais[2].dest_register].valor = ula_div(unidades_funcionais[2].source_register[1],unidades_funcionais[2].source_register[0]);
            banco_registradores[REG_HI].valor = ula_mod(unidades_funcionais[2].source_register[1],unidades_funcionais[2].source_register[0]);
        break;
        case 3:
            //ADD, ADDI, MADD (verificar o instruction type)
            if(unidades_funcionais[3].instr == ADD){
                banco_registradores[unidades_funcionais[3].dest_register].valor = ula_somador(unidades_funcionais[3].source_register[0], unidades_funcionais[3].source_register[1]);
            }else if (unidades_funcionais[3].instr == ADDI){
                banco_registradores[unidades_funcionais[3].dest_register].valor = ula_somador(unidades_funcionais[3].source_register[0], unidades_funcionais[3].source_register[1]);
            }else{
                int resultado;
                resultado = ula_mult(unidades_funcionais[3].source_register[0],unidades_funcionais[3].source_register[1]);
                banco_registradores[unidades_funcionais[3].dest_register].valor = ula_and(resultado, 0000000000000000000000000000000011111111111111111111111111111111);
                banco_registradores[REG_HI].valor = resultado >> 32;     
            }
        break;
        case 4:
            switch(unidades_funcionais[4].instr_type){
                case REGIMM:
                    switch(unidades_funcionais[4].instr){
                        case BGEZ:
                            if(banco_registradores[unidades_funcionais[4].source_register[1]].valor >= 0){
                                //faz a parte do pulo;
                            }else{
                                unidades_funcionais[4].instr_valida = FALSE;
                            }
                        break;
                        case BLTZ:
                            if(banco_registradores[unidades_funcionais[4].source_register[1]].valor < 0){
                                //faz a parte do pulo;
                            }else{
                                unidades_funcionais[4].instr_valida = FALSE;
                            }
                        break;
                    }
                break;
                case SPECIAL:
                    switch(unidades_funcionais[4].instr){
                        case AND:
                            banco_registradores[unidades_funcionais[4].dest_register].valor = ula_and(unidades_funcionais[4].source_register[0], unidades_funcionais[4].source_register[1]);
                        break;
                        case JR:
                           //
                        case MFHI:
                            banco_registradores[unidades_funcionais[4].dest_register].valor = banco_registradores[REG_HI].valor;
                        break;
                        case MFLO:
                            banco_registradores[unidades_funcionais[4].dest_register].valor = banco_registradores[REG_LO].valor;
                        break;
                        case MOVN:
                            if(banco_registradores[unidades_funcionais[4].source_register[0]].valor != 0){
                                banco_registradores[unidades_funcionais[4].dest_register].valor = banco_registradores[unidades_funcionais[4].source_register[1]].valor;
                            } else{
                                return 0;
                            }
                        break;
                        case MOVZ:
                            if(banco_registradores[unidades_funcionais[4].source_register[0]].valor == 0){
                                banco_registradores[unidades_funcionais[4].dest_register].valor = banco_registradores[unidades_funcionais[4].source_register[1]].valor;
                            }
                        break;
                        case MTHI:
                            banco_registradores[REG_HI].valor = banco_registradores[unidades_funcionais[4].source_register[1]].valor; 
                        break;
                        case MTLO:
                            banco_registradores[REG_LO].valor = banco_registradores[unidades_funcionais[4].source_register[1]].valor;
                        break;
                        case NOP:
                            
                        case NOR:
                            banco_registradores[unidades_funcionais[4].dest_register].valor = ula_nor(unidades_funcionais[4].source_register[0], unidades_funcionais[4].source_register[1]);
                        break;
                        case OR:
                            banco_registradores[unidades_funcionais[4].dest_register].valor = ula_or(unidades_funcionais[4].source_register[1], unidades_funcionais[4].source_register[0]);
                        break;
                        case SUB:
                            banco_registradores[unidades_funcionais[4].dest_register].valor = ula_sub(unidades_funcionais[4].source_register[1], unidades_funcionais[4].source_register[0]);
                        break;
                        case XOR:
                            banco_registradores[unidades_funcionais[4].dest_register].valor = ula_xor(unidades_funcionais[4].source_register[1], unidades_funcionais[4].source_register[0]);
                        break;
                    } 
                break;                   
                case SPECIAL2:
                    switch(unidades_funcionais[4].instr){
                        case MSUB:
                            ula_subtrator(ula_or(banco_registradores[REG_HI], banco_registradores[REG_LO]), ula_mult(banco_registradores[unidades_funcionais[4].source_register[0]].valor, banco_registradores[unidades_funcionais[4].source_register[1]].valor));
                        break;
                    } 
                break;               
                case DEFAULT:
                    switch(unidades_funcionais[4].instr){
                        case ANDI:
                            banco_registradores[unidades_funcionais[4].dest_register].valor = ula_and(unidades_funcionais[4].source_register[0], unidades_funcionais[4].source_register[1]);
                        break;
                        case B || BEQ:
                            if (unidades_funcionais[4].instr == BEQ){
                                int verifica = ula_div(banco_registradores[unidades_funcionais[4].source_register[0]].valor, banco_registradores[unidades_funcionais[4].source_register[1]].valor);
                                if(verifica == 1){
                                    //faz a parte do pulo;
                                }else{
                                    unidades_funcionais[4].instr_valida = FALSE;
                                }
                            }else{
                                unidades_funcionais[4].instr_valida = TRUE;
                            }
                        break;
                        case BEQL:
                            int verifica = ula_div(banco_registradores[unidades_funcionais[4].source_register[0]].valor, banco_registradores[unidades_funcionais[4].source_register[1]].valor);
                            if(verifica == 1){
                                //faz a parte do pulo;
                            }else{
                                unidades_funcionais[4].instr_valida = FALSE;
                            }
                        break;
                        case BGTZ:
                            if(banco_registradores[unidades_funcionais[4].source_register[1]].valor > 0){
                                //faz a parte do pulo;
                            }else{
                                unidades_funcionais[4].instr_valida = FALSE;
                            }
                        break;
                        case BLEZ:
                            if(banco_registradores[unidades_funcionais[4].source_register[1]].valor <= 0){
                                //faz a parte do pulo;
                            }else{
                                unidades_funcionais[4].instr_valida = FALSE;
                            }
                        break;
                        case BNE:
                            int verifica = ula_div(banco_registradores[unidades_funcionais[4].source_register[0]].valor, banco_registradores[unidades_funcionais[4].source_register[1]].valor);
                            if(verifica != 1){
                                //faz a parte do pulo;
                            }else{
                                unidades_funcionais[4].instr_valida = FALSE;
                            }
                        break;
                        case J:
                            //PC  PCGPRLEN-1..28 || instr_index || 02
                        break;
                        case LUI:
                            int low_order_zero = 00000000000000000000000000000000;
                            banco_registradores[unidades_funcionais[4].dest_register].valor = low_order_zero;
                        break;
                        case ORI:
                            banco_registradores[unidades_funcionais[4].source_register[0]].valor = ula_or(banco_registradores[unidades_funcionais[4].source_register[1]].valor, unidades_funcionais[4].dest_register);
                        break;
                        case XORI:
                            banco_registradores[unidades_funcionais[4].source_register[0]].valor = ula_xor(banco_registradores[unidades_funcionais[4].source_register[1]].valor, unidades_funcionais[4].dest_register);
                        break;
                    } 
                break;               
            }
        break;
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