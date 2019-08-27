#ifndef UNIDADE_FUNC_H
#define UNIDADE_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include "barramento.h"
#include "ula.h"
#include "banco_registradores.h"
#include "definitions.h"
#include "utils.h"

typedef struct unidade_func{
    int busy;
    int operacao;
    int dest_register;
    int source_register[2];
    int q[2];
    int ready[2];
    int instr_type;
    int instr;
    int instr_valida;
    int Res;
    int Res11;
    int cycle_counter;
    int cycles_needed;
    int unidade_func_type;
}unidade_func;

void next();

unidade_func* unidades_funcionais;

unidade_func* init_unidade_func();
int issue();
int read_operands();
void execute();
void write_back();
void verifica_all_uf();

#endif 