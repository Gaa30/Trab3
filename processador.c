#include "processador.h"
#include "util.h"

void estagio_busca_pipeline(){
    IR.valor = read(PC.valor);    
    PC.valor += ula_somador(PC.valor, 4); //tem que fazer essa adição através da ULA, mas a ula nao ta pronta kkkj
}

//decodificacao do codigo da instrucao no IR, e coloca na fila
void decodificacao(){
    if(IR.valor == FLAG_VAZIO) return;
    int instr = IR.valor;
    int opcode = instr &111111;
    int special = getSPECIAL(instr);
    int type = getTipoInst(opcode);
}

void estagio_execucao_pipeline(){

}
