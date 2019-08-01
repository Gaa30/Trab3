#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "memoria.h"
#define TAM_PALAVRA 4

Memoria m;

void inicia(int size){
    m.vet = malloc(sizeof(size*TAM_PALAVRA));
    m.size = size;

    for(int i=0; i<size; i = i+TAM_PALAVRA)
        m.vet[i] = -1;
}

int write(Palavra p, int endereco){
    char * ptr = (char *) &p;
    int aux, i = 0;
    for(aux = endereco; aux<endereco+TAM_PALAVRA; aux++)
        m.vet[aux] = ptr[i++];
    return endereco+TAM_PALAVRA;

}


Palavra read(int endereco){
    Palavra * ptr = malloc(sizeof(Palavra));
    ptr = (Palavra *) (m.vet + endereco);
    return *ptr;
}

void print(){
    int i= 0;
    for(i=0; i<m.size; i = i+TAM_PALAVRA)
        printf("%13d", read(i));

}

/* int main(int argc, char *argv[]){
    FILE *arq;
    char *rola = "1A2";
    char *pau = "aaa";
    inicia(12);
    //write(*rola,0);
    //write(*pau,4);
    read(0);
    print();
    return 0;


}   */
