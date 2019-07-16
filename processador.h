#ifndef PROCESSADOR_H
#define PROCESSADOR_H

//#include "util.h"
#include "memoria.h"
#include "banco_registradores.h"
//#include "estacoesReserva.h"
//#include "DQueue.h"

//Barramento CDB;

void start();
void next();
void print();

void estagio_busca_pipeline();
void estagio_execucao_pipeline();

#endif