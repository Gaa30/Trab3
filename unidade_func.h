#ifndef UNIDADE_FUNC_H
#define UNIDADE_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include "definitions.h" 
#include "banco_registradores.h"
#include "barramento.h"

typedef struct unidade_func{
    int busy;
    int operacao;
    int dest_register;
    int source_register[2];
    int queue[2];
    int ready[2];
    int instr_type;
    void* instr;
    int instr_valida;
    int Res;
    int Res11;
    int cycle_counter;
}unidade_func;

void next();

unidade_func* unidades_funcionais;

unidade_func* init_unidade_func();
int issue();
void read_operands();
void execute();
void write_back();

#endif 