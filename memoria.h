#ifndef MEMORIA_H
#define MEMORIA_H 

#include <stdio.h>
#include <string.h>
#include "definitions.h"
#define TAM_PALAVRA 4
#include "hash.h"

typedef unsigned char Byte;
typedef unsigned int Palavra;

typedef struct{
    Byte *vet;
    int size;
}Memoria;

Palavra read(int endereco);
int write(Palavra p, int endereco);
void print();
void inicia(int size);
void alimenta_memoria(char* nomearquivoentrada);

#endif