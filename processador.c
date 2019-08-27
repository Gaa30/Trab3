#include "processador.h"

int inicio = 0;

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

/*int predecode(int instr){
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
                    OPC.valor = PC.valor;
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
                    OPC.valor = PC.valor;
                    branch = 1;
                    type = REGIMM;
                    operation = BGEZ;
                    rd = rd &65535;
                    rs = rs >> 21 &31;
                    rt = FLAG_VAZIO;
                    PC.valor = rd;
                break;
                case BLTZ:
                    OPC.valor = PC.valor;
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
                    OPC.valor = PC.valor;
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
                    OPC.valor = PC.valor;
                    branch = 1;
                    type = DEFAULT;
                    operation = BEQL;
                    rd = rd &65535;
                    rt = rt >> 16 &31;
                    rs = rs >> 21 &31;
                    PC.valor = rd;
                break;
                case BGTZ:
                    OPC.valor = PC.valor;
                    branch = 1;
                    type = DEFAULT;
                    operation = BGTZ;
                    rd = rd &65535;
                    rs = rs >> 21 &31;
                    rt = FLAG_VAZIO;
                    PC.valor = rd;
                break;
                case BLEZ:
                    OPC.valor = PC.valor;
                    branch = 1;
                    type = DEFAULT;
                    operation = BLEZ;
                    rd = rd &65535;
                    rs = rs >> 21 &31;
                    rt = FLAG_VAZIO;
                    PC.valor = rd;
                break;
                case BNE:
                    OPC.valor = PC.valor;
                    branch = 1;
                    type = DEFAULT;
                    operation = BNE;
                    rd = rd &65535;
                    rt = rt >> 16 &31;
                    rs = rs >> 21 &31;
                    PC.valor = rd;
                break;
                case J:
                    OPC.valor = PC.valor;
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
}*/

//decodificacao do codigo da instrucao no IR, e coloca na fila
void decodificacao(){
    if(IR.valor == FLAG_VAZIO) return;
    int instr = IR.valor;
    int rt = instr;
    //printf("rt %d\n", rt);
    int rs = instr;
    //printf("rs %d\n", rs);
    int rd = instr;
    //printf("rt %d\n", rd);
    int type = instr;
    //type = type >> 26;
    type = getTipo(instr);
    //printf("\nTIPO %d\n", type);
    int opcode = 0;
    Instrucao.instr = IR.valor;
    switch(type){
        case SPECIAL:
            opcode = instr &63;
            switch(opcode){
                case ADD:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = ADD;
                    Instrucao.rd = rd >> 11 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt >> 16 &31;
                break;
                case AND:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = AND;
                    Instrucao.rd = rd >> 11 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt >> 16 &31;
                break;
                case DIV:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = DIV;
                    Instrucao.rd = REG_LO;
                    Instrucao.rs = rs >> 16 &31;
                    Instrucao.rt = rt >> 21 &31;
                break;
                case JR:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = JR;
                    Instrucao.rd = FLAG_VAZIO;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = FLAG_VAZIO;
                break;
                case MFHI:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = MFHI;
                    Instrucao.rd = rd >> 11 &31;
                    Instrucao.rs = FLAG_VAZIO;
                    Instrucao.rt = FLAG_VAZIO;
                break;
                case MFLO:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = MFLO;
                    Instrucao.rd = rd >> 11 &31;
                    Instrucao.rs = FLAG_VAZIO;
                    Instrucao.rt = FLAG_VAZIO;
                break;
                case MOVN:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = MOVN;
                    Instrucao.rd = rd >> 11 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt >> 16 &31;
                break;
                case MOVZ:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = MOVZ;
                    Instrucao.rd = rd >> 11 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt >> 16 &31;
                break;
                case MTHI:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = MTHI;
                    Instrucao.rd = REG_HI;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = FLAG_VAZIO;
                break;
                case MTLO:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = MTLO;
                    Instrucao.rd = REG_LO;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt =FLAG_VAZIO ;
                break;
                case MULT:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = MULT;
                    Instrucao.rd = REG_LO;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt >> 16 &31;
                break;
                case NOP:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = NOP;
                    Instrucao.rd = 0;
                    Instrucao.rs = 0;
                    Instrucao.rt = 0;
                break;
                case NOR:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = NOR;
                    Instrucao.rd = rd >> 11 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt >> 16 &31;
                break;
                case OR:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = OR;
                    Instrucao.rd = rd >> 11 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt >> 16 &31;
                break;
                case SUB:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = SUB;
                    Instrucao.rd = rd >> 11 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt >> 16 &31;
                break;
                case XOR:
                    Instrucao.type = SPECIAL;
                    Instrucao.operation = XOR;
                    Instrucao.rd = rd >> 11 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt >> 16 &31;
                break;
            }
        break;
        case SPECIAL2:
            opcode = instr &63;
            switch(opcode){
                case MADD:
                    Instrucao.type = SPECIAL2;
                    Instrucao.operation = MADD;
                    Instrucao.rd = REG_LO;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt >> 16 &31;
                break;
                case MSUB:
                    Instrucao.type = SPECIAL2;
                    Instrucao.operation = MSUB;
                    Instrucao.rt = rt >> 16 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rd = REG_LO;
                break;
                case MUL:
                    Instrucao.type = SPECIAL2;
                    Instrucao.operation = MUL;
                    Instrucao.rd = rd >> 11 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt >> 16 &31;
                break;
            }
        break;
        case REGIMM:
            opcode = instr >> 16 &31;
            switch(opcode){
                case BGEZ:
                    Instrucao.type = REGIMM;
                    Instrucao.operation = BGEZ;
                    Instrucao.rd = rd &65535;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = FLAG_VAZIO;
                break;
                case BLTZ:
                    Instrucao.type = REGIMM;
                    Instrucao.operation = BLTZ;
                    Instrucao.rd = rd &65535;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = FLAG_VAZIO;
                break;
            }
        break;
        case DEFAULT:
            opcode = instr >> 26 &63;
            switch(opcode){
                case ADDI:
                    Instrucao.type = DEFAULT;
                    Instrucao.operation = ADDI;
                    Instrucao.rd = rd >> 16 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt &65535;
                break;
                case ANDI:
                    Instrucao.type = DEFAULT;
                    Instrucao.operation = ANDI;
                    Instrucao.rd = rd >> 16 &31;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = rt &65535;
                break;
                case B || BEQ:
                    Instrucao.type = DEFAULT;
                    int checkB1, checkB2 = instr;
                    checkB1 = checkB1 >> 16 &31;
                    checkB2 = checkB2 >> 21 &31;
                    if(checkB1 == 00000 && checkB2 == 00000){
                        Instrucao.operation = B;
                        Instrucao.rd = rd &65535;
                        Instrucao.rs = FLAG_VAZIO;
                        Instrucao.rt = FLAG_VAZIO;
                    }else{
                        Instrucao.operation = BEQ;
                        Instrucao.rd = rd &65535;
                        Instrucao.rt = rt >> 16 &31;
                        Instrucao.rs = rs >> 21 &31;
                    }
                break;
                case BEQL:
                    Instrucao.type = DEFAULT;
                    Instrucao.operation = BEQL;
                    Instrucao.rd = rd &65535;
                    Instrucao.rt = rt >> 16 &31;
                    Instrucao.rs = rs >> 21 &31;
                break;
                case BGTZ:
                    Instrucao.type = DEFAULT;
                    Instrucao.operation = BGTZ;
                    Instrucao.rd = rd &65535;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = FLAG_VAZIO;
                break;
                case BLEZ:
                    Instrucao.type = DEFAULT;
                    Instrucao.operation = BLEZ;
                    Instrucao.rd = rd &65535;
                    Instrucao.rs = rs >> 21 &31;
                    Instrucao.rt = FLAG_VAZIO;
                break;
                case BNE:
                    Instrucao.type = DEFAULT;
                    Instrucao.operation = BNE;
                    Instrucao.rd = rd &65535;
                    Instrucao.rt = rt >> 16 &31;
                    Instrucao.rs = rs >> 21 &31;
                break;
                case J:
                    Instrucao.type = DEFAULT;
                    Instrucao.operation = J;
                    Instrucao.rd = rd &67108863;
                    Instrucao.rt = FLAG_VAZIO;
                    Instrucao.rs = FLAG_VAZIO;

                break;
                case LUI:
                    Instrucao.type = DEFAULT;
                    Instrucao.operation = LUI;
                    Instrucao.rd = rd >> 16 &31;
                    Instrucao.rt = rt &65535;
                    Instrucao.rs = FLAG_VAZIO;
                break;
                case ORI:
                    Instrucao.type = DEFAULT;
                    Instrucao.operation = ORI;
                    Instrucao.rd = rd &65535;
                    Instrucao.rt = rt >> 16 &31;
                    Instrucao.rs = rs >> 21 &31;
                break;
                case XORI:
                    Instrucao.type = DEFAULT;
                    Instrucao.operation = XORI;
                    Instrucao.rd = rd &65535;
                    Instrucao.rt = rt >> 16 &31;
                    Instrucao.rs = rs >> 21 &31;
                break;
            }
        break;
        //add_info_barramento(Instrucao.operation, Instrucao.type, Instrucao.instr, TRUE, FLAG_VAZIO, Instrucao.rs, Instrucao.rt, Instrucao.rd);

    }
}

/*int fila_vazia (){
    for(int i =0; i < 4; i++){
        if(fila[i].operation == FLAG_VAZIO){
            continue;
        }else{
            return FALSE;
        }
    }
    return TRUE;
}*/

/*int retira_fila(){
    int verificacao = verifica_barramento(0);
    if(verificacao == TRUE){
        printf("\n\n entrou \n\n");
        add_info_barramento(Instrucao.operation, Instrucao.type, Instrucao.instr, TRUE, FLAG_VAZIO, Instrucao.rs, Instrucao.rt, Instrucao.rd);
        /*printf("\n\nFILA\n\n ");
        printf("OPeration : %d\n", Instrucao.operation);
        printf("type : %d\n", Instrucao.type);
        printf("instr : %d\n", Instrucao.instr);
        printf("rs : %d\n", Instrucao.rs);
        printf("rd : %d\n", Instrucao.rd);
        printf("rt : %d\n", Instrucao.rt);
        printf("\n\n adicionou \n\n");
        Instrucao.operation = FLAG_VAZIO;
        Instrucao.rd = FLAG_VAZIO;
        Instrucao.rs = FLAG_VAZIO;
        Instrucao.rt = FLAG_VAZIO;
        Instrucao.type = FLAG_VAZIO;
        Instrucao.instr = FLAG_VAZIO;
        inicio++;
        if(inicio == 4){
            printf("\n alo inicio = %d \n", inicio);
            inicio = 0;
        }
    }
}
*/
void estagio_busca_pipeline(int PCMAX){
    printf("\n PC = %ld\n", PC.valor);
    /*int verifica_fila = fila_vazia();
    int buscas_realizadas = 0;
    if(verifica_fila == TRUE){
        while(buscas_realizadas < 4 && PC.valor < PCMAX){*/
    IR.valor = read(PC.valor);
    int buscas_realizadas = 1;
    printf("\n Busca %i IR = %ld e PC %ld\n", buscas_realizadas, IR.valor, PC.valor);
    decodificacao();
    add_info_barramento(Instrucao.operation, Instrucao.type, Instrucao.instr, TRUE, FLAG_VAZIO, Instrucao.rs, Instrucao.rt, Instrucao.rd);
    printf("\n%d\n", Instrucao.operation);
            switch(Instrucao.type){
                case DEFAULT:
                    switch(Instrucao.operation){
                        case BEQ || B:
                        case BEQL:
                        case BGTZ:
                        case BLEZ:
                        case BNE:
                            OPC.valor = PC.valor;
                            PC.valor = Instrucao.rd;
                        break;
                        case J:
                            PC.valor = Instrucao.rd;
                        default:
                            PC.valor = ula_somador(PC.valor, 4);
                        break;
                    }
                break;
                case REGIMM:
                    switch(Instrucao.operation){
                        case BGEZ:
                        case BLTZ:
                            OPC.valor = PC.valor;
                            PC.valor = Instrucao.rd;
                        break;
                        default:
                            PC.valor = ula_somador(PC.valor, 4);
                        break;
                    }
                default:
                    PC.valor = ula_somador(PC.valor, 4);
                break;
            }
            buscas_realizadas++;
}

void processador(int instrcounter){
    int PCMAX = instrcounter *4;
    int inicio =0;
    int fim = 1;
    write_back();
    execute();
    read_operands();
    issue();
    estagio_busca_pipeline(PCMAX);
    //while(verifica_all_barramentos()==FALSE && verifica_all_uf()==FALSE){
    for(int i = 0; i <100 ; i++){
        write_back();
        execute();
        read_operands();
        issue();
        estagio_busca_pipeline(PCMAX);
    }
    printf("/n/n BANCO_REGISTRADORES /n/n");
    reg_banco_print();
}


