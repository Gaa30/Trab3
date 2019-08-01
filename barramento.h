#include <stdio.h>
#include <stdlib.h>
#include "definitions.h"
#include "unidade_func.h"

typedef struct{
    int type;
    void* instrucao;
    int valida;
}barramento;

barramento* init_barramento();

barramento* BUS;