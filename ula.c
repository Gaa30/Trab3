#include "ula.h"

size_t ula_somador(size_t operando1, size_t operando2){
    return operando1 + operando2;
}

size_t ula_subtrator(size_t operando1, size_t operando2){
    return operando1 - operando2;
}

size_t ula_and(size_t operando1, size_t operando2){
    return operando1 & operando2;
}

size_t ula_or(size_t operando1, size_t operando2){
    return operando1 | operando2;
}

size_t ula_xor(size_t operando1, size_t operando2){
    return operando1 ^ operando2;
}

size_t ula_nor(size_t operando1, size_t operando2){
    return ~(operando1 | operando2);
}

size_t ula_mult(size_t operando1, size_t operando2){
    return operando1 * operando2;
}

size_t ula_div(size_t divisor, size_t dividiendo){
    if(divisor !=0){
        return dividiendo/divisor;
    }
    else{
        return ;
    }
}

size_t ula_mod(size_t operando1, size_t operando2){
    return operando1 % operando2;
}

size_t ula_shiftleft(size_t operando1, size_t operando2){
    return operando1 << operando2;
}