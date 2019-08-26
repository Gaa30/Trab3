#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "memoria.h"


Memoria m;

void inicia(int size){
    m.size = size;
    m.vet = malloc(sizeof(size*m.size));

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
        printf("%13d\n", read(i));

}

void alimenta_memoria(char* nomearquivoentrada){
    FILE *arq = fopen(nomearquivoentrada, "r");
    char aux[33];
    char* eptr;
    int a = 0;
    int aux2;
    memset(aux, '\0', 33);
    while(fgets(aux, 33, arq) != NULL) {
        aux[strcspn(aux, "\r\n")] = 0;
        printf("\n%s\n", aux);
        aux2 = (int)strtol(aux, &eptr, 2);
        write(aux2, a);
        a += 4;
        printf("%d\n", a);
    }
    fclose(arq);
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