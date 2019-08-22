#include "processador.h"

void estagio_busca_pipeline(){
    IR.valor = read(PC.valor);    
    PC.valor += ula_somador(PC.valor, 4);
}

int getTipo(int instr){
    int isSpecial = instr >> 26 &0xB; 
    if (isSpecial = SPECIAL){
        return SPECIAL;
    }
    else if(isSpecial = SPECIAL2){
        return SPECIAL2;
    }
    else if(isSpecial = REGIMM){
        return REGIMM;
    }else{
        return DEFAULT;
    }
}

//decodificacao do codigo da instrucao no IR, e coloca na fila
void decodificacao(){
    if(IR.valor == FLAG_VAZIO) return;
    int instr = IR.valor;
    int rd, rs, rt = instr;
    int type = instr &111111;
    type = getTipo(type);
    int opcode = 0;
    instruction * instrucao = (instruction *)malloc(sizeof(instruction));
    switch(type){
        case SPECIAL:
            opcode = instr &111111;
            switch(opcode){
                case ADD:
                    instrucao->type = SPECIAL;
                    instrucao->operation = ADD;
                    instrucao->rd = rd >> 11 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt >> 16 &11111;
                break;
                case AND:
                    instrucao->type = SPECIAL;
                    instrucao->operation = AND;
                    instrucao->rd = rd >> 11 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt >> 16 &11111;
                break;
                case DIV:
                    instrucao->type = SPECIAL;
                    instrucao->operation = DIV;
                    instrucao->rd = REG_LO;
                    instrucao->rs = rs >> 16 &11111;
                    instrucao->rt = rt >> 21 &11111;
                break;
                case JR:
                    instrucao->type = SPECIAL;
                    instrucao->operation = JR;
                    instrucao->rd = FLAG_VAZIO;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case MFHI:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MFHI;
                    instrucao->rd = rd >> 11 &11111;
                    instrucao->rs = FLAG_VAZIO;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case MFLO:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MFLO;
                    instrucao->rd = rd >> 11 &11111;
                    instrucao->rs = FLAG_VAZIO;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case MOVN:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MOVN;
                    instrucao->rd = rd >> 11 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt >> 16 &11111;
                break;
                case MOVZ:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MOVZ;
                    instrucao->rd = rd >> 11 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt >> 16 &11111;
                break;
                case MTHI:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MTHI;
                    instrucao->rd = REG_HI;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case MTLO:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MTLO;
                    instrucao->rd = REG_LO;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt =FLAG_VAZIO ;
                break;
                case MULT:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MULT;
                    instrucao->rd = REG_LO;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt >> 16 &11111;
                break;
                case NOP:
                    instrucao->type = SPECIAL;
                    instrucao->operation = NOP;
                    instrucao->rd = 0;
                    instrucao->rs = 0;
                    instrucao->rt = 0;
                break;
                case NOR:
                    instrucao->type = SPECIAL;
                    instrucao->operation = NOR;
                    instrucao->rd = rd >> 11 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt >> 16 &11111;
                break;
                case OR:
                    instrucao->type = SPECIAL;
                    instrucao->operation = OR;
                    instrucao->rd = rd >> 11 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt >> 16 &11111;
                break;
                case SUB:
                    instrucao->type = SPECIAL;
                    instrucao->operation = SUB;
                    instrucao->rd = rd >> 11 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt >> 16 &11111;
                break;
                case XOR:
                    instrucao->type = SPECIAL;
                    instrucao->operation = XOR;
                    instrucao->rd = rd >> 11 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt >> 16 &11111;
                break;
            }
        break;
        case SPECIAL2:
            opcode = instr &111111;
            switch(opcode){
                case MADD:
                    instrucao->type = SPECIAL2;
                    instrucao->operation = MADD;
                    instrucao->rd = REG_LO;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt >> 16 &11111;
                break;
                case MSUB:
                    instrucao->type = SPECIAL2;
                    instrucao->operation = MSUB;
                    instrucao->rt = rt >> 16 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rd = REG_LO;
                break;
                case MUL:
                    instrucao->type = SPECIAL2;
                    instrucao->operation = MUL;
                    instrucao->rd = rd >> 11 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt >> 16 &11111;
                break;
            }
        break;
        case REGIMM:
            opcode = instr >> 16 &11111;
            switch(opcode){
                case BGEZ:
                    instrucao->type = REGIMM;
                    instrucao->operation = BGEZ;
                    instrucao->rd = rd &1111111111111111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case BLTZ:
                    instrucao->type = REGIMM;
                    instrucao->operation = BLTZ;
                    instrucao->rd = rd &1111111111111111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = FLAG_VAZIO;
                break;
            }
        break;
        case DEFAULT:
            opcode = instr >> 26 &111111;
            switch(opcode){
                case ADDI:
                    instrucao->type = DEFAULT;
                    instrucao->operation = ADDI;
                    instrucao->rd = rd >> 16 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt &1111111111111111;
                break;
                case ANDI:
                    instrucao->type = DEFAULT;
                    instrucao->operation = ANDI;
                    instrucao->rd = rd >> 16 &11111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = rt &1111111111111111;
                break;
                case B || BEQ:
                    instrucao->type = DEFAULT;
                    int checkB1, checkB2 = instr;
                    checkB1 = checkB1 >> 16 &11111;
                    checkB2 = checkB2 >> 21 &11111;
                    if(checkB1 == 00000 && checkB2 == 00000){
                        instrucao->operation = B;
                        instrucao->rd = rd &1111111111111111;
                        instrucao->rs = FLAG_VAZIO;
                        instrucao->rt = FLAG_VAZIO;
                    }else{
                        instrucao->operation = BEQ;
                        instrucao->rd = rd &1111111111111111;
                        instrucao->rt = rt >> 16 &11111;
                        instrucao->rs = rs >> 21 &11111;
                    }
                break;
                case BEQL:
                    instrucao->type = DEFAULT;
                    instrucao->operation = BEQL;
                    instrucao->rd = rd &1111111111111111;
                    instrucao->rt = rt >> 16 &11111;
                    instrucao->rs = rs >> 21 &11111;
                break;
                case BGTZ:
                    instrucao->type = DEFAULT;
                    instrucao->operation = BGTZ;
                    instrucao->rd = rd &1111111111111111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case BLEZ:
                    instrucao->type = DEFAULT;
                    instrucao->operation = BLEZ;
                    instrucao->rd = rd &1111111111111111;
                    instrucao->rs = rs >> 21 &11111;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case BNE:
                    instrucao->type = DEFAULT;
                    instrucao->operation = BNE;
                    instrucao->rd = rd &1111111111111111;
                    instrucao->rt = rt >> 16 &11111;
                    instrucao->rs = rs >> 21 &11111;
                break;
                case J:
                    instrucao->type = DEFAULT;
                    instrucao->operation = J;
                    instrucao->rd = rd &11111111111111111111111111;
                    instrucao->rt = FLAG_VAZIO;
                    instrucao->rs = FLAG_VAZIO;

                break;
                case LUI:
                    instrucao->type = DEFAULT;
                    instrucao->operation = LUI;
                    instrucao->rd = rd >> 16 &11111;
                    instrucao->rt = FLAG_VAZIO;
                    instrucao->rs = FLAG_VAZIO;
                break;
                case ORI:
                    instrucao->type = DEFAULT;
                    instrucao->operation = ORI;
                    instrucao->rd = rd &1111111111111111;
                    instrucao->rt = rt >> 16 &11111;
                    instrucao->rs = rs >> 21 &11111;
                break;
                case XORI:
                    instrucao->type = DEFAULT;
                    instrucao->operation = XORI;
                    instrucao->rd = rd &1111111111111111;
                    instrucao->rt = rt >> 16 &11111;
                    instrucao->rs = rs >> 21 &11111;
                break;
            }
        break;
        add_info_barramento(instrucao->operation, instrucao->type, instr, TRUE, FLAG_VAZIO, instrucao->rs, instrucao->rt, instrucao->rd);
    }
}

void processador(){
    
}


