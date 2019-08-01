#include <stdio.h>
#include "barramento.h"

barramento* init_barramento(){
    BUS = (barramento*)malloc(sizeof(barramento)*QTD_BARRAMENTOS);

    for(int i =0; i<QTD_BARRAMENTOS; i++){
        if (i==EXECUTE){
            BUS[i].instrucao = unidades_funcionais;
        }
        BUS[i].type = FLAG_VAZIO;
        BUS[i].valida = FLAG_READY;
    }
    return BUS;
}