#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "lab3.h"

int zero = 0;
int at = 1;
int v0 = 2;
int v1 = 3;
int a0 = 4;
int a1 = 5;
int a2 = 6;
int a3 = 7;
int t0 = 8;
int t1 = 9;
int t2 = 10;
int t3 = 11;
int t4 = 12;
int t5 = 13;
int t6 = 14;
int t7 = 15;
int t8 = 24;
int t9 = 25;
int s0 = 16;
int s1 = 17;
int s2 = 18;
int s3 = 19;
int s4 = 20;
int s5 = 21;
int s6 = 22;
int s7 = 23;
int k0 = 26;
int k1 = 27;
int gp = 28;
int sp = 29;
int fp = 30;
int ra = 31;

void itobin(char op[], char *binario, int sizeOp){
    int a;
    if (!strcmp(op, "$zero")) {
        a = zero;
    }
    else if (!strcmp(op, "$at")) {
        a = at;
    }
    else if (!strcmp(op, "$v0")) {
        a = v0;
    }
    else if (!strcmp(op, "$v1")) {
        a = v1;
    }
    else if (!strcmp(op, "$a0")) {
        a = a0;
    }
    else if (!strcmp(op, "$a1")) {
        a = a1;
    }
    else if (!strcmp(op, "$a2")) {
        a = a2;
    }
    else if (!strcmp(op, "$a3")) {
        a = a3;
    }
    else if (!strcmp(op, "$t0")) {
        a = t0;
    }
    else if (!strcmp(op, "$t1")) {
        a = t1;
    }
    else if (!strcmp(op, "$t2")) {
        a = t2;
    }
    else if (!strcmp(op, "$t3")) {
        a = t3;
    }
    else if (!strcmp(op, "$t4")) {
        a = t4;
    }
    else if (!strcmp(op, "$t5")) {
        a = t5;
    }
    else if (!strcmp(op, "$t6")) {
        a = t6;
    }
    else if (!strcmp(op, "$t7")) {
        a = t7;
    }
    else if (!strcmp(op, "$t8")) {
        a = t8;
    }
    else if (!strcmp(op, "$t9")) {
        a = t9;
    }
    else if (!strcmp(op, "$s0")) {
        a = s0;
    }
    else if (!strcmp(op, "$s1")) {
        a = s1;
    }
    else if (!strcmp(op, "$s2")) {
        a = s2;
    }
    else if (!strcmp(op, "$s3")) {
        a = s3;
    }
    else if (!strcmp(op, "$s4")) {
        a = s4;
    }
    else if (!strcmp(op, "$s5")) {
        a = s5;
    }
    else if (!strcmp(op, "$s6")) {
        a = s6;
    }
    else if (!strcmp(op, "$s7")) {
        a = s7;
    }
    else if (!strcmp(op, "$k0")) {
        a = k0;
    }
    else if (!strcmp(op, "$k1")) {
        a = k1;
    }
    else if (!strcmp(op, "$gp")) {
        a = gp;
    }
    else if (!strcmp(op, "$sp")) {
        a = sp;
    }
    else if (!strcmp(op, "$fp")) {
        a = fp;
    }
    else if (!strcmp(op, "$ra")) {
        a = ra;
    }
    else if (sizeOp == 16) {
        a = atoi(op);
        printf("%d", a);
    }
    char aux[sizeOp];
    int i;
    for(i=0;i<sizeOp;i++){
        if (a%2) {
            aux[i] = '1';
        } else {
            aux[i] = '0';
        }
        a = a/2;
    }
    aux[i] = '\0';
    for(i=strlen(aux);i>=0;i--){
        binario[strlen(aux)-i] = aux[i-1];
    }
    binario[strlen(aux)] = '\0';
    printf("%s\n", binario);
}


void split_op(int numOp, char *palavra, int i, char *bin, int sizeOp3, int branchFlag) {
        char rs[20];
        char rt[20];
        char rd[20];
        memset(rs, '\0', 20);
        memset(rt, '\0', 20);
        memset(rd, '\0', 20);
        int k;
        int aux_count;
        char ch;
        if (numOp == 3) {
            ch = '0';
            int j = 0;
            char op1[10], op2[10], op3[10];
            for (i; palavra[i] != ','; i++) {
                ch = palavra[i];
                op1[j] = ch;
                j++;
            }
            op1[j] = '\0';
            itobin(op1, rd, 5);
            printf ("Op1: %s\n", op1);
            j = 0;
            for (i+=2; palavra[i] != ','; i++) {
                ch = palavra[i];
                op2[j] = ch;
                j++;
            }
            op2[j] = '\0';
            itobin(op2, rs, 5);
            printf ("Op2: %s\n", op2);
            j = 0;

            for (i+=2; palavra[i] != '\0'; i++) {
                ch = palavra[i];
                op3[j] = ch;
                j++;
            }
            op3[j] = '\0';
            if (branchFlag == 1) {
                strcat(rt, decimal_to_binary_16bits(get_data(op3)));
                printf("%s\n", rt);
                aux_count = strlen(rt);
                printf("%d", aux_count);
                if (sizeOp3 == 16) {
                    strcat(bin, rd);
                    strcat(bin, rs);
                    strcat(bin, rt);
                    printf("Op3: %s\n", op3);
                } else {
                    strcat(bin, rs);
                    strcat(bin, rd);
                    strcat(bin, rt);
                    printf ("Op3: %s\n", op3);
                }
            } 
            else {
                itobin(op3, rt, sizeOp3);
                if (sizeOp3 == 16) {
                    strcat(bin, rd);
                    strcat(bin, rs);
                    strcat(bin, rt);
                    printf("Op3: %s\n", op3);
                } else {
                    strcat(bin, rs);
                    strcat(bin, rt);
                    strcat(bin, rd);
                    printf ("Op3: %s\n", op3);
                }
            }
            
        }  else if (numOp == 2) {
            ch = '0';
            int j = 0;
            char op1[10], op2[10];
            for (i; palavra[i] != ','; i++) {
                ch = palavra[i];
                op1[j] = ch;
                j++;
            }
            op1[j] = '\0';
            itobin(op1, rs, 5);
            printf ("Op1: %s\n", op1);
            j = 0;
            
            for (i+=2; palavra[i] != '\0'; i++) {
                ch = palavra[i];
                op2[j] = ch;
                j++;
            }
            op2[j] = '\0';
            if (branchFlag == 1) {
                strcat(rt, decimal_to_binary_16bits(get_data(op2)));
                printf("%s\n", rt);
                strcat(bin, rs);
                strcat(bin, rt);
                printf("Op2: %s\n", op2);
            } else {
                itobin(op2, rt, sizeOp3);
                strcat(bin, rs);
                strcat(bin, rt);
                printf ("Op2: %s\n", op2);
                j = 0;
            }
        } else if (numOp == 1) {
            ch = '0';
            int j = 0;
            char op1[10];
            for (i; palavra[i] != '\0'; i++) {
                ch = palavra[i];
                op1[j] = ch;
                j++;
            }
            op1[j] = '\0';
            if (branchFlag == 1) {
                if (sizeOp3 == 26) {
                    strcat(rs, decimal_to_binary_26bits(get_data(op1)));
                    printf("%s\n", rs);
                    strcat(bin, rs);
                    printf("Op2: %s\n", op1);
                } else {
                    strcat(rs, decimal_to_binary_16bits(get_data(op1)));
                    printf("%s\n", rs);
                    strcat(bin, rs);
                    printf("Op2: %s\n", op1);
                }
            } else {
                op1[j] = '\0';
                itobin(op1, rs, sizeOp3);
                strcat(bin, rs);
                printf ("Op1: %s\n", op1);
            }
        }
}

int instrcounter = 0;

void tradutor(char *palavra) {
    FILE *arq2;
    char ch;
    char bin[32];
    int i = 0, j;
    char aux[strlen(palavra)];
    for (i; ch != ' '; i++) {
        ch = palavra[i];
        aux[i] = ch;
    }
    ch = '0';
    aux[i-1] = '\0';
    printf ("%s\n", aux);
    char* buffer;
    if (!strcmp(aux, "ADD")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "100000");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    } 
    else if (!strcmp(aux, "ADDI")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "001000";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 16, 0);
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "AND")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "100100");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "ANDI")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "001100";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 16, 0);
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "B")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000100";
        int numOp = 1;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        strcat(bin, "00000");
        strcat(bin, "00000");
        split_op(numOp, palavra, i, bin, 16, 1);
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "BEQ")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000100";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 1);
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "BEQL")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "010100";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 1);
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "BGEZ")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000001";
        char auxCase[5] = "00001";
        char bin_aux[32];
        int numOp = 2, cont, cont2;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        auxCase[5] = '\0';
        split_op(numOp, palavra, i, bin, 5, 1);
        for (cont = 0; cont < 11; cont++) {
            bin_aux[cont] = bin[cont];
        }
        strcat(bin_aux, auxCase);
        for (cont2 = 16; cont2 <= 32; cont2++) {
            bin_aux[cont2] = bin[cont2-5];
        }
        printf ("Binário: %s\n", bin_aux);
        printf ("Tamanho: %li\n\n", strlen(bin_aux));
        fprintf(arq2, "%s\n", bin_aux);
        fclose(arq2);
    }
    else if (!strcmp(aux, "BGTZ")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000111";
        char auxCase[5] = "00000";
        char bin_aux[32];
        int numOp = 2, cont, cont2;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        auxCase[5] = '\0';
        split_op(numOp, palavra, i, bin, 5, 1);
        for (cont = 0; cont < 11; cont++) {
            bin_aux[cont] = bin[cont];
        }
        strcat(bin_aux, auxCase);
        for (cont2 = 16; cont2 <= 32; cont2++) {
            bin_aux[cont2] = bin[cont2-5];
        }
        printf ("Binário: %s\n", bin_aux);
        printf ("Tamanho: %li\n\n", strlen(bin_aux));
        fprintf(arq2, "%s\n", bin_aux);
        fclose(arq2);
    }
    else if (!strcmp(aux, "BLEZ")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000110";
        char auxCase[5] = "00000";
        char bin_aux[32];
        int numOp = 2, cont, cont2;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        auxCase[5] = '\0';
        split_op(numOp, palavra, i, bin, 5, 1);
        for (cont = 0; cont < 11; cont++) {
            bin_aux[cont] = bin[cont];
        }
        strcat(bin_aux, auxCase);
        for (cont2 = 16; cont2 <= 32; cont2++) {
            bin_aux[cont2] = bin[cont2-5];
        }
        printf ("Binário: %s\n", bin_aux);
        printf ("Tamanho: %li\n\n", strlen(bin_aux));
        fprintf(arq2, "%s\n", bin_aux);
        fclose(arq2);
    }
    else if (!strcmp(aux, "BLTZ")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000001";
        char auxCase[5] = "00000";
        char bin_aux[32];
        int numOp = 2, cont, cont2;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        auxCase[5] = '\0';
        split_op(numOp, palavra, i, bin, 5, 1);
        for (cont = 0; cont < 11; cont++) {
            bin_aux[cont] = bin[cont];
        }
        strcat(bin_aux, auxCase);
        for (cont2 = 16; cont2 <= 32; cont2++) {
            bin_aux[cont2] = bin[cont2-5];
        }        
        printf ("Binário: %s\n", bin_aux);
        printf ("Tamanho: %li\n\n", strlen(bin_aux));
        fprintf(arq2, "%s\n", bin_aux);
        fclose(arq2);
    }
    else if (!strcmp(aux, "BNE")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000101";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 1);
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "DIV")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 2;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "0000000000");
        strcat(bin, "011010");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "J")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000010";
        int numOp = 1;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 26, 1);
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "JR")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 1;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "00000");
        strcat(bin, "00100"); //hint 4, pag 332
        //Implementar o que é o hint.
        strcat(bin, "001001");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "LUI")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "001111";
        int numOp = 2;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        strcat(bin, "00000");
        split_op(numOp, palavra, i, bin, 16, 0);
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "MADD")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "011100";
        int numOp = 2;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "00000");
        strcat(bin, "000000");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "MFHI")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 1;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        strcat(bin, "0000000000");
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "010000");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "MFLO")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 1;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "0000000000");
        strcat(bin, "00000");
        strcat(bin, "010010");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "MOVN")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "001011");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "MOVZ")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "001010");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "MSUB")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "011100";
        int numOp = 2;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "00000");
        strcat(bin, "000100");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "MTHI")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 1;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "000000000000000");
        strcat(bin, "010001");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "MTLO")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 1;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "000000000000000");
        strcat(bin, "010011");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "MUL")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "011100";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "000010");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "MULT")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 2;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "0000000000");
        strcat(bin, "011000");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "NOP")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 0;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        strcat(bin, "00000");
        strcat(bin, "00000");
        strcat(bin, "00000");
        strcat(bin, "00000");
        strcat(bin, "000000");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "NOR")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "100111");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "OR")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "100101");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "ORI")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "001101";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 16, 0);
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "SUB")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "100010");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "XOR")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "000000";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 5, 0);
        strcat(bin, "00000");
        strcat(bin, "100110");
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else if (!strcmp(aux, "XORI")) {
        arq2 = fopen("arquivo_saida", "a");
        char instruBin[6] = "001110";
        int numOp = 3;
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, 16, 0);
        printf ("Binário: %s\n", bin);
        printf ("Tamanho: %li\n\n", strlen(bin));
        fprintf(arq2, "%s\n", bin);
        fclose(arq2);
    }
    else {
        printf("Instrução não implementada.");
    }
    instrcounter++;
}

void find_label(char arquivo_binario[]) {
    FILE *arq;
    int i = 0;
    int TAM_AUX;
    char aux[24];
    memset(aux, '\0', 24);
    arq = fopen(arquivo_binario, "r");
    if (arq != NULL) {
        while(fgets(aux, 24, arq) != NULL) {
            aux[strcspn(aux, "\r\n")] = 0;
            TAM_AUX = strlen(aux);
            if (aux[TAM_AUX-1] == ':') {
                insert_label(aux, i*4);
                printf("%s -> %d\n\n", aux, get_data(aux));
            } else {
                i++;
            }
        }
    } else {
        perror("Falha ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    fclose(arq);
}

void init_search(char arquivo_binario[]) {
    FILE *arq;
    //FILE *arq2;
    char aux[24];
    int TAM_AUX;
    memset(aux, '\0', 24);
    arq = fopen(arquivo_binario, "r");
    //arq2 = fopen("arquivo_saida", "w+");
    if (arq != NULL) {
        fseek(arq, 0, SEEK_SET);
        while(fgets(aux, 24, arq) != NULL) {
            aux[strcspn(aux, "\r\n")] = 0;
            TAM_AUX = strlen(aux);
            if (aux[TAM_AUX-1] == ':') {
                continue;
            } else {
                printf("Instrução: %s\n", aux);
                tradutor(aux);
            }
        }
        fclose(arq);
        //fclose(arq2);
    } 
    else {
        perror("Falha ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
}



int main () {
    inicializar_registradores();
    init_barramento();
    init_hash();
    inicia(42);
    init_unidade_func();
    //char arquivo_binario[24] = "ADDI $t1, $t1, 3";
    //tradutor(arquivo_binario);
    //printf("%s", arquivo_binario);
    //tradutor(arquivo_binario);
    //find_label("aritm_1");
    find_label("final_1");
    // Teste 1) Tradução de todas as operações sem ser os branchs.
    //init_search("aritm_1");
    // Teste 2) Tradução de todas as operações de branch.
    init_search("final_1");
    // Teste 3) Tradução de todas operações.
    //init_search("all_1");
    alimenta_memoria("arquivo_saida");
    print();
    processador(instrcounter);
    return 0;
}