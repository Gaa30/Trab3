#include <stdio.h>
#include "util.h"

int getTipo(int instr){
    int isSpecial = instr >> 26 &0xB; 
    if (isSpecial = SPECIAL){
        return SPECIAL;
    }
    else if(isSpecial = SPECIAL2){
        return SPECIAL2;
    }
    else if(isSpecial = REGIMM){
        return REGIMM;
    }else{
        return DEFAULT;
    }
}