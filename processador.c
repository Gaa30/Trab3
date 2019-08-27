#include "processador.h"

int getTipo(int instr){
    int isSpecial = instr >> 26;
    if (isSpecial == SPECIAL){
        //printf(" entrou no special");
        return SPECIAL;
    }
    else if(isSpecial == SPECIAL2){
         //printf(" entrou no special2");
        return SPECIAL2;
    }
    else if(isSpecial == REGIMM){
         //printf(" entrou no regimm");
        return REGIMM;
    }else{
         //printf(" entrou no defaul");
        return DEFAULT;
    }
}

int predecode(int instr){
    int branch = 0;
    int rt = instr;
    int rs = instr;
    int rd = instr;
    int type = instr;
    //type = type >> 26;
    type = getTipo(instr);
    int operation = 0;
    switch(type){
        case SPECIAL:
            operation = instr &63;
            switch(operation){
                case ADD:
                    branch = 0;
                    return branch;
                break;
                case AND:
                    branch = 0;
                    return branch;
                break;
                case DIV:
                    branch = 0;
                    return branch;
                break;
                case JR:
                    branch = 1;
                    type = SPECIAL;
                    operation = JR;
                    rd = FLAG_VAZIO;
                    rs = rs >> 21 &31;
                    rt = FLAG_VAZIO;
                    PC.valor = banco_registradores[rs].valor;
                break;
                case MFHI:
                    branch = 0;
                    return branch;
                break;
                case MFLO:
                    branch = 0;
                    return branch;
                break;
                case MOVN:
                    branch = 0;
                    return branch;
                break;
                case MOVZ:
                    branch = 0;
                    return branch;
                break;
                case MTHI:
                    branch = 0;
                    return branch;
                break;
                case MTLO:
                    branch = 0;
                    return branch;
                break;
                case MULT:
                    branch = 0;
                    return branch;
                break;
                case NOP:
                    branch = 0;
                    return branch;
                break;
                case NOR:
                    branch = 0;
                    return branch;
                break;
                case OR:
                    branch = 0;
                    return branch;
                break;
                case SUB:
                    branch = 0;
                    return branch;
                break;
                case XOR:
                    branch = 0;
                    return branch;
                break;
            }
        break;
        case SPECIAL2:
            operation = instr &63;
            switch(operation){
                case MADD:
                    branch = 0;
                    return branch;
                break;
                case MSUB:
                    branch = 0;
                    return branch;
                break;
                case MUL:
                    branch = 0;
                    return branch;
                break;
            }
        break;
        case REGIMM:
            operation = instr >> 16 &31;
            switch(operation){
                case BGEZ:
                    branch = 1;
                    type = REGIMM;
                    operation = BGEZ;
                    rd = rd &65535;
                    rs = rs >> 21 &31;
                    rt = FLAG_VAZIO;
                    PC.valor = rd;
                break;
                case BLTZ:
                    branch = 1;
                    type = REGIMM;
                    operation = BLTZ;
                    rd = rd &65535;
                    rs = rs >> 21 &31;
                    rt = FLAG_VAZIO;
                    PC.valor = rd;
                break;
            }
        break;
        case DEFAULT:
            operation = instr >> 26 &63;
            switch(operation){
                case ADDI:
                    branch = 0;
                    return branch;
                break;
                case ANDI:
                    branch = 0;
                    return branch;
                break;
                case B || BEQ:
                    branch = 1;
                    type = DEFAULT;
                    int checkB1, checkB2 = instr;
                    checkB1 = checkB1 >> 16 &31;
                    checkB2 = checkB2 >> 21 &31;
                    if(checkB1 == 00000 && checkB2 == 00000){
                        operation = B;
                        rd = rd &65535;
                        rs = FLAG_VAZIO;
                        rt = FLAG_VAZIO;
                    }else{
                        operation = BEQ;
                        rd = rd &65535;
                        rt = rt >> 16 &31;
                        rs = rs >> 21 &31;
                    }
                    PC.valor = rd;
                break;
                case BEQL:
                    branch = 1;
                    type = DEFAULT;
                    operation = BEQL;
                    rd = rd &65535;
                    rt = rt >> 16 &31;
                    rs = rs >> 21 &31;
                    PC.valor = rd;
                break;
                case BGTZ:
                    branch = 1;
                    type = DEFAULT;
                    operation = BGTZ;
                    rd = rd &65535;
                    rs = rs >> 21 &31;
                    rt = FLAG_VAZIO;
                    PC.valor = rd;
                break;
                case BLEZ:
                    branch = 1;
                    type = DEFAULT;
                    operation = BLEZ;
                    rd = rd &65535;
                    rs = rs >> 21 &31;
                    rt = FLAG_VAZIO;
                    PC.valor = rd;
                break;
                case BNE:
                    branch = 1;
                    type = DEFAULT;
                    operation = BNE;
                    rd = rd &65535;
                    rt = rt >> 16 &31;
                    rs = rs >> 21 &31;
                    PC.valor = rd;
                break;
                case J:
                    branch = 1;
                    type = DEFAULT;
                    operation = J;
                    rd = rd &67108863;
                    rt = FLAG_VAZIO;
                    rs = FLAG_VAZIO;
                    PC.valor = rd;
                break;
                case LUI:
                    branch = 0;
                    return branch;
                break;
                case ORI:
                    branch = 0;
                    return branch;
                break;
                case XORI:
                    branch = 0;
                    return branch;
                break;
            }
        break;
    }
}

void estagio_busca_pipeline(){
    printf("\n PC = %ld\n", PC.valor);
    IR.valor = read(PC.valor);
    printf("\n IR = %ld\n", IR.valor);    
    int is_branch = predecode(IR.valor);
    if(!is_branch){
        PC.valor = ula_somador(PC.valor, 4);
    }
}

//decodificacao do codigo da instrucao no IR, e coloca na fila
void decodificacao(){
    if(IR.valor == FLAG_VAZIO) return;
    int instr = IR.valor;
    int rt = instr;
    int rs = instr;
    int rd = instr;
    int type = instr;
    //type = type >> 26;
    type = getTipo(instr);
    printf("\nTIPO %d\n", type);
    int opcode = 0;
    instruction * instrucao = (instruction *)malloc(sizeof(instruction));
    switch(type){
        case SPECIAL:
            opcode = instr &63;
            switch(opcode){
                case ADD:
                    instrucao->type = SPECIAL;
                    instrucao->operation = ADD;
                    instrucao->rd = rd >> 11 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt >> 16 &31;
                break;
                case AND:
                    instrucao->type = SPECIAL;
                    instrucao->operation = AND;
                    instrucao->rd = rd >> 11 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt >> 16 &31;
                break;
                case DIV:
                    instrucao->type = SPECIAL;
                    instrucao->operation = DIV;
                    instrucao->rd = REG_LO;
                    instrucao->rs = rs >> 16 &31;
                    instrucao->rt = rt >> 21 &31;
                break;
                case JR:
                    instrucao->type = SPECIAL;
                    instrucao->operation = JR;
                    instrucao->rd = FLAG_VAZIO;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case MFHI:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MFHI;
                    instrucao->rd = rd >> 11 &31;
                    instrucao->rs = FLAG_VAZIO;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case MFLO:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MFLO;
                    instrucao->rd = rd >> 11 &31;
                    instrucao->rs = FLAG_VAZIO;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case MOVN:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MOVN;
                    instrucao->rd = rd >> 11 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt >> 16 &31;
                break;
                case MOVZ:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MOVZ;
                    instrucao->rd = rd >> 11 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt >> 16 &31;
                break;
                case MTHI:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MTHI;
                    instrucao->rd = REG_HI;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case MTLO:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MTLO;
                    instrucao->rd = REG_LO;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt =FLAG_VAZIO ;
                break;
                case MULT:
                    instrucao->type = SPECIAL;
                    instrucao->operation = MULT;
                    instrucao->rd = REG_LO;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt >> 16 &31;
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
                    instrucao->rd = rd >> 11 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt >> 16 &31;
                break;
                case OR:
                    instrucao->type = SPECIAL;
                    instrucao->operation = OR;
                    instrucao->rd = rd >> 11 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt >> 16 &31;
                break;
                case SUB:
                    instrucao->type = SPECIAL;
                    instrucao->operation = SUB;
                    instrucao->rd = rd >> 11 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt >> 16 &31;
                break;
                case XOR:
                    instrucao->type = SPECIAL;
                    instrucao->operation = XOR;
                    instrucao->rd = rd >> 11 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt >> 16 &31;
                break;
            }
        break;
        case SPECIAL2:
            opcode = instr &63;
            switch(opcode){
                case MADD:
                    instrucao->type = SPECIAL2;
                    instrucao->operation = MADD;
                    instrucao->rd = REG_LO;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt >> 16 &31;
                break;
                case MSUB:
                    instrucao->type = SPECIAL2;
                    instrucao->operation = MSUB;
                    instrucao->rt = rt >> 16 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rd = REG_LO;
                break;
                case MUL:
                    instrucao->type = SPECIAL2;
                    instrucao->operation = MUL;
                    instrucao->rd = rd >> 11 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt >> 16 &31;
                break;
            }
        break;
        case REGIMM:
            opcode = instr >> 16 &31;
            switch(opcode){
                case BGEZ:
                    instrucao->type = REGIMM;
                    instrucao->operation = BGEZ;
                    instrucao->rd = rd &65535;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case BLTZ:
                    instrucao->type = REGIMM;
                    instrucao->operation = BLTZ;
                    instrucao->rd = rd &65535;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = FLAG_VAZIO;
                break;
            }
        break;
        case DEFAULT:
            opcode = instr >> 26 &63;
            switch(opcode){
                case ADDI:
                    instrucao->type = DEFAULT;
                    instrucao->operation = ADDI;
                    instrucao->rd = rd >> 16 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt &65535;
                break;
                case ANDI:
                    instrucao->type = DEFAULT;
                    instrucao->operation = ANDI;
                    instrucao->rd = rd >> 16 &31;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = rt &65535;
                break;
                case B || BEQ:
                    instrucao->type = DEFAULT;
                    int checkB1, checkB2 = instr;
                    checkB1 = checkB1 >> 16 &31;
                    checkB2 = checkB2 >> 21 &31;
                    if(checkB1 == 00000 && checkB2 == 00000){
                        instrucao->operation = B;
                        instrucao->rd = rd &65535;
                        instrucao->rs = FLAG_VAZIO;
                        instrucao->rt = FLAG_VAZIO;
                    }else{
                        instrucao->operation = BEQ;
                        instrucao->rd = rd &65535;
                        instrucao->rt = rt >> 16 &31;
                        instrucao->rs = rs >> 21 &31;
                    }
                break;
                case BEQL:
                    instrucao->type = DEFAULT;
                    instrucao->operation = BEQL;
                    instrucao->rd = rd &65535;
                    instrucao->rt = rt >> 16 &31;
                    instrucao->rs = rs >> 21 &31;
                break;
                case BGTZ:
                    instrucao->type = DEFAULT;
                    instrucao->operation = BGTZ;
                    instrucao->rd = rd &65535;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case BLEZ:
                    instrucao->type = DEFAULT;
                    instrucao->operation = BLEZ;
                    instrucao->rd = rd &65535;
                    instrucao->rs = rs >> 21 &31;
                    instrucao->rt = FLAG_VAZIO;
                break;
                case BNE:
                    instrucao->type = DEFAULT;
                    instrucao->operation = BNE;
                    instrucao->rd = rd &65535;
                    instrucao->rt = rt >> 16 &31;
                    instrucao->rs = rs >> 21 &31;
                break;
                case J:
                    instrucao->type = DEFAULT;
                    instrucao->operation = J;
                    instrucao->rd = rd &67108863;
                    instrucao->rt = FLAG_VAZIO;
                    instrucao->rs = FLAG_VAZIO;

                break;
                case LUI:
                    instrucao->type = DEFAULT;
                    instrucao->operation = LUI;
                    instrucao->rd = rd >> 16 &31;
                    instrucao->rt = rt &65535;
                    instrucao->rs = FLAG_VAZIO;
                break;
                case ORI:
                    instrucao->type = DEFAULT;
                    instrucao->operation = ORI;
                    instrucao->rd = rd &65535;
                    instrucao->rt = rt >> 16 &31;
                    instrucao->rs = rs >> 21 &31;
                break;
                case XORI:
                    instrucao->type = DEFAULT;
                    instrucao->operation = XORI;
                    instrucao->rd = rd &65535;
                    instrucao->rt = rt >> 16 &31;
                    instrucao->rs = rs >> 21 &31;
                break;
            }
        break;
        add_info_barramento(instrucao->operation, instrucao->type, instr, TRUE, FLAG_VAZIO, instrucao->rs, instrucao->rt, instrucao->rd);
    }
}

void processador(int instrcounter){
    int PCMAX = instrcounter *4;
    int fila[4];
    for(int i = 0; i<42; i++){
        write_back();
        execute();
        read_operands();
        issue();
        decodificacao();
        estagio_busca_pipeline();
    }
}


