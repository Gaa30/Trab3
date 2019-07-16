#include "processador.h"

void estagio_busca_pipeline(){
    IR.valor = read(PC.valor);    
    PC.valor += 4; //tem que fazer essa adição através da ULA, mas a ula nao ta pronta kkkj
}

//decodificacao do codigo da instrucao no IR, e coloca na fila
void decodificacao(){
    if(IR.valor == FLAG_VAZIO) return;
    int instr
}

void estagio_execucao_pipeline(){

}
