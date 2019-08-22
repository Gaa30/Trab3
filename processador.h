#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include <stdio.h>
#include <stdlib.h>
#include "ula.h"
#include "barramento.h"
#include "unidade_func.h"
#include "definitions.h"
#include "memoria.h"

//Barramento CDB;

void start();
void next();
void print();

int getTipoInst(int opcode);
void estagio_busca_pipeline();
void processador();

#endif