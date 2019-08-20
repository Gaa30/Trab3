#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// ADD 4, ADDI 4, AND 4, ANDI 4, B 2, BEQ 4, BEQL 4, BGEZ 3, BGTZ 3, BLEZ 3, BLTZ 3, BNE 4, DIV 3, J 2, JR 2 , LUI 3, MADD 3, MFHI 2, MFLO 2, MOVN 4, MOVZ 4, MSUB 3, MTHI 2, MTLO 2, MUL 4, MULT 3, NOP 1, NOR 4 , OR 4, ORI 4, SUB 4, XOR 4, XORI 4
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

/*void //bintohex(char *bin, char *hex) {
    int i = 0, j = 0;
    char aux[4];
    for(i=0;i<32;i+=4){
        for(j=0;j<4;j++){
            aux[j] = bin[j+i];
        }
        if(!strcmp(aux, "0000")){
            strcat(hex, "0");
        }
        else if (!strcmp(aux, "0001")) {
            strcat(hex, "1");
        }
        else if (!strcmp(aux, "0010")) {
            strcat(hex, "2");
        }
        else if (!strcmp(aux, "0011")) {
            strcat(hex, "3");
        }
        else if (!strcmp(aux, "0100")) {
            strcat(hex, "4");
        }
        else if (!strcmp(aux, "0101")) {
            strcat(hex, "5");
        }
        else if (!strcmp(aux, "0110")) {
            strcat(hex, "6");
        }
        else if (!strcmp(aux, "0111")) {
            strcat(hex, "7");
        }
        else if (!strcmp(aux, "1000")) {
            strcat(hex, "8");
        }
        else if (!strcmp(aux, "1001")) {
            strcat(hex, "9");
        }
        else if (!strcmp(aux, "1010")) {
            strcat(hex, "A");
        }
        else if (!strcmp(aux, "1011")) {
            strcat(hex, "B");
        }
        else if (!strcmp(aux, "1100")) {
            strcat(hex, "C");
        }
        else if (!strcmp(aux, "1101")) {
            strcat(hex, "D");
        }
        else if (!strcmp(aux, "1110")) {
            strcat(hex, "E");
        }
        else if (!strcmp(aux, "1111")) {
            strcat(hex, "F");
        }
    }
}
*/

void itobin(char op[], char *binario, int sizeOp){
    int a;
    if (!strcmp(op, "$zero")) {
        //printf("alo");
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
    //printf("%s ", binario);
}


void split_op(int numOp, char *palavra, int i, char *bin, int n, int sizeOp3) {
        char rs[20];
        char rt[20];
        char rd[20];
        int k;
        char ch;
        if (numOp == 3) {
            ch = 'a';
            int j = 0;
            char op1[10], op2[10], op3[10];
            for (i; palavra[i] != ','; i++) {
                ch = palavra[i];
                op1[j] = ch;
                j++;
            }
            op1[j] = '\0';
            itobin(op1, rd, 5);
            printf ("%s ", op1);
            j = 0;
            for (i+=2; palavra[i] != ','; i++) {
                ch = palavra[i];
                op2[j] = ch;
                j++;
            }
            op2[j] = '\0';
            itobin(op2, rs, 5);
            printf ("%s ", op2);
            j = 0;

            for (i+=2; palavra[i] != '\0'; i++) {
                ch = palavra[i];
                op3[j] = ch;
                j++;
            }

            op3[j] = '\0';
            itobin(op3, rt, sizeOp3);
            if (sizeOp3 == 16) {
                strcat(bin, rd);
                strcat(bin, rs);
                strcat(bin, rt);
                printf("%s\n", op3);
            } else {
                strcat(bin, rs);
                strcat(bin, rt);
                strcat(bin, rd);
                printf ("%s\n", op3);
            }
            
        }  else if (numOp == 2) {
            ch = 'a';
            int j = 0;
            char op1[10], op2[10];
            for (i; palavra[i] != ','; i++) {
                ch = palavra[i];
                op1[j] = ch;
                j++;
            }
            op1[j] = '\0';
            itobin(op1, rs, 5);
            printf ("%s ", op1);
            j = 0;
            
            for (i+=2; palavra[i] != '\0'; i++) {
                ch = palavra[i];
                op2[j] = ch;
                j++;
            }
            op2[j] = '\0';
            itobin(op2, rt, sizeOp3);
            strcat(bin, rs);
            strcat(bin, rt);
            printf ("%s\n", op2);
            j = 0;
        } else if (numOp == 1) {
            ch = 'a';
            int j = 0;
            char op1[10];
            for (i; palavra[i] != '\0'; i++) {
                ch = palavra[i];
                op1[j] = ch;
                j++;
            }
            op1[j] = '\0';
            itobin(op1, rs, sizeOp3);
            strcat(bin, rs);
            printf ("%s\n", op1);
            //j = 0;
        }
}

void tradutor(char *palavra, FILE *arq) {
    //FILE *arq;
    //arq = fopen("arquivo_saida", "w");
    char ch;
    char bin[32];
    int i = 0, a;
    char aux[strlen(palavra)];
    for (i; ch != ' '; i++) {
        ch = palavra[i];
        aux[i] = ch;
    }
    ch = 'a';
    aux[i-1] = '\0';
    printf ("%s ", aux);
    // ADD 4, ADDI 4, AND 4, ANDI 4, B 2, BEQ 4, BEQL 4, BGEZ 3, BGTZ 3, BLEZ 3, BLTZ 3, BNE 4, DIV 3, J 2, JR 2 ,
    //LUI 3, MADD 3, MFHI 2, MFLO 2, MOVN 4, MOVZ 4, MSUB 3, MTHI 2, MTLO 2, MUL 4, MULT 3, NOP 1, NOR 4 , OR 4, ORI 4, SUB 4, XOR 4, XORI 4
    if (!strcmp(aux, "ADD")) {
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 3;
        char hex[8], hex_aux[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "100000");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
    } 
    else if (!strcmp(aux, "ADDI")) {
        char instruBin[6] = "001000";
        int n = 6;
        int numOp = 3;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 16);
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
    }
    else if (!strcmp(aux, "AND")) {
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 3;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "100100");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "ANDI")) {
        char instruBin[6] = "001100";
        int n = 6;
        int numOp = 3;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 16);
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "B")) {
        // Arrumar, ainda não sei como implementar o offset.
        char instruBin[6] = "000100";
        int n = 6;
        int numOp = 1;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 16);
        strcat(bin, "00000");
        strcat(bin, "00000");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "BEQ")) {
        // Arrumar, ainda não sei como implementar o offset.
        char instruBin[6] = "000100";
        int n = 6;
        int numOp = 2;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        ////bintohex(bin, hex);
        ////printf("%s", hex);
        //fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "BEQL")) {
        // Arrumar, ainda não sei como implementar o offset.
        char instruBin[6] = "010100";
        int n = 6;
        int numOp = 2;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        ////bintohex(bin, hex);
        ////printf("%s", hex);
        //fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "BGEZ")) {
        // Arrumar, ainda não sei como implementar o offset.
        // Não está concatenando o registrador passado.
        char instruBin[6] = "000001";
        int n = 6;
        int numOp = 1;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00001");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        ////bintohex(bin, hex);
        ////printf("%s", hex);
        //fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "BGTZ")) {
        // Arrumar, ainda não sei como implementar o offset.
        // Não está concatenando o registrador passado.
        char instruBin[6] = "000111";
        int n = 6;
        int numOp = 1;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        ////bintohex(bin, hex);
        ////printf("%s", hex);
        //fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "BLEZ")) {
        // Arrumar, ainda não sei como implementar o offset.
        // Não está concatenando o registrador passado.
        char instruBin[6] = "000110";
        int n = 6;
        int numOp = 1;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        ////bintohex(bin, hex);
        ////printf("%s", hex);
        //fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "BLTZ")) {
        // Arrumar, ainda não sei como implementar o offset.
        // Não está concatenando o registrador passado.
        char instruBin[6] = "000001";
        int n = 6;
        int numOp = 1;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        ////bintohex(bin, hex);
        ////printf("%s", hex);
        //fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "BNE")) {
        // Arrumar, ainda não sei como implementar o offset.
        char instruBin[6] = "000101";
        int n = 6;
        int numOp = 2;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        ////bintohex(bin, hex);
        ////printf("%s", hex);
        //fprintf(arq, "%s\n", bin);        
        
    }
    else if (!strcmp(aux, "DIV")) {
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 2;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "0000000000");
        strcat(bin, "011010");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "J")) {
        // Ainda não sei o que é instr_index
        char instruBin[6] = "000010";
        int n = 6;
        int numOp = 1;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 26);
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "JR")) {
        // Ainda não sei o que é instr_index
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 1;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "00000");
        //Implementar o que é o hint.
        strcat(bin, "001001");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "LUI")) {
        char instruBin[6] = "001111";
        int n = 6;
        int numOp = 2;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        strcat(bin, "00000");
        split_op(numOp, palavra, i, bin, n, 16);
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "MADD")) {
        char instruBin[6] = "011100";
        int n = 6;
        int numOp = 2;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "00000");
        strcat(bin, "000000");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "MFHI")) {
        // Arrumar, provavelmente é o caso quando for só 1 operador.
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 1;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        strcat(bin, "000000");
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "010000");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "MFLO")) {
        // Arrumar, provavelmente é o caso quando for só 1 operador.
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 1;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        strcat(bin, "0000000000");
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "010010");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "MOVN")) {
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 3;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "001011");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        printf("%s", bin);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "MOVZ")) {
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 3;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "001010");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        printf("%s", bin);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "MSUB")) {
        char instruBin[6] = "011100";
        int n = 6;
        int numOp = 2;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "00000");
        strcat(bin, "000100");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        printf("%s", bin);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "MTHI")) {
        // Arrumar 1 op.
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 1;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "000000000000000");
        strcat(bin, "010001");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        printf("%s", bin);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "MTLO")) {
        // Arrumar 1 op.
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 1;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);

        strcat(bin, "000000000000000");
        strcat(bin, "010011");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        printf("%s", bin);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "MUL")) {
        char instruBin[6] = "011100";
        int n = 6;
        int numOp = 3;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "000010");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        printf("%s", bin);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "MULT")) {
        char instruBin[6] = "011100";
        int n = 6;
        int numOp = 2;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "0000000000");
        strcat(bin, "011000");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        printf("%s", bin);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "NOP")) {
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 0;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        strcat(bin, "00000");
        strcat(bin, "00000");
        strcat(bin, "00000");
        strcat(bin, "00000");
        strcat(bin, "000000");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        printf("%s", bin);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "NOR")) {
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 3;
        char hex[8];
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "100111");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "OR")) {
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 3;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "100101");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "ORI")) {
        char instruBin[6] = "001101";
        int n = 6;
        int numOp = 3;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 16);
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "SUB")) {
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 3;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "100010");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "XOR")) {
        char instruBin[6] = "000000";
        int n = 6;
        int numOp = 3;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 5);
        strcat(bin, "00000");
        strcat(bin, "100110");
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else if (!strcmp(aux, "XORI")) {
        char instruBin[6] = "001110";
        int n = 6;
        int numOp = 3;
        char hex[8];
        memset(hex, '\0', 8);
        strcpy(bin, instruBin);
        bin[6] = '\0';
        split_op(numOp, palavra, i, bin, n, 16);
        printf ("%s\n", bin);
        printf ("%li\n", strlen(bin));
        //bintohex(bin, hex);
        //printf("%s", hex);
        fprintf(arq, "%s\n", bin);
        
    }
    else {
        printf("Label");
    }
}

int alimenta_hash(char* palavra, int count){
    //FILE *arq;
    //arq = fopen("arquivo_saida", "w");
    char ch;
    char bin[32];
    int i = 0, a;
    char aux[strlen(palavra)];
    for (i; ch != ' '; i++) {
        ch = palavra[i];
        aux[i] = ch;
    }
    ch = 'a';
    aux[i-1] = '\0';
    //printf ("%s ", aux);
    // ADD 4, ADDI 4, AND 4, ANDI 4, B 2, BEQ 4, BEQL 4, BGEZ 3, BGTZ 3, BLEZ 3, BLTZ 3, BNE 4, DIV 3, J 2, JR 2 ,
    //LUI 3, MADD 3, MFHI 2, MFLO 2, MOVN 4, MOVZ 4, MSUB 3, MTHI 2, MTLO 2, MUL 4, MULT 3, NOP 1, NOR 4 , OR 4, ORI 4, SUB 4, XOR 4, XORI 4
    if (!strcmp(aux, "ADD")) {
        char instruBin[6] = "000000";
        return 1;
    } 
    else if (!strcmp(aux, "ADDI")) {
        char instruBin[6] = "001000";
        return 1;
    }
    else if (!strcmp(aux, "AND")) {
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "ANDI")) {
        char instruBin[6] = "001100";
        return 1;
    }
    else if (!strcmp(aux, "B")) {
        // Arrumar, ainda não sei como implementar o offset.
        char instruBin[6] = "000100";
        return 1;
    }
    else if (!strcmp(aux, "BEQ")) {
        // Arrumar, ainda não sei como implementar o offset.
        char instruBin[6] = "000100";
        return 1;
    }
    else if (!strcmp(aux, "BEQL")) {
        // Arrumar, ainda não sei como implementar o offset.
        char instruBin[6] = "010100";
        return 1;
    }
    else if (!strcmp(aux, "BGEZ")) {
        // Arrumar, ainda não sei como implementar o offset.
        // Não está concatenando o registrador passado.
        char instruBin[6] = "000001";
        return 1;
    }
    else if (!strcmp(aux, "BGTZ")) {
        // Arrumar, ainda não sei como implementar o offset.
        // Não está concatenando o registrador passado.
        char instruBin[6] = "000111";
        return 1;
    }
    else if (!strcmp(aux, "BLEZ")) {
        // Arrumar, ainda não sei como implementar o offset.
        // Não está concatenando o registrador passado.
        char instruBin[6] = "000110";
        return 1;
    }
    else if (!strcmp(aux, "BLTZ")) {
        // Arrumar, ainda não sei como implementar o offset.
        // Não está concatenando o registrador passado.
        char instruBin[6] = "000001";
        return 1;
    }
    else if (!strcmp(aux, "BNE")) {
        // Arrumar, ainda não sei como implementar o offset.
        char instruBin[6] = "000101";     
        return 1;
    }
    else if (!strcmp(aux, "DIV")) {
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "J")) {
        // Ainda não sei o que é instr_index
        char instruBin[6] = "000010";
        return 1;
    }
    else if (!strcmp(aux, "JR")) {
        // Ainda não sei o que é instr_index
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "LUI")) {
        char instruBin[6] = "001111";
        return 1;
    }
    else if (!strcmp(aux, "MADD")) {
        char instruBin[6] = "011100";
        return 1;
    }
    else if (!strcmp(aux, "MFHI")) {
        // Arrumar, provavelmente é o caso quando for só 1 operador.
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "MFLO")) {
        // Arrumar, provavelmente é o caso quando for só 1 operador.
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "MOVN")) {
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "MOVZ")) {
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "MSUB")) {
        char instruBin[6] = "011100";
        return 1;
    }
    else if (!strcmp(aux, "MTHI")) {
        // Arrumar 1 op.
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "MTLO")) {
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "MUL")) {
        char instruBin[6] = "011100";
        return 1;
    }
    else if (!strcmp(aux, "MULT")) {
        char instruBin[6] = "011100";
        return 1;
    }
    else if (!strcmp(aux, "NOP")) {
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "NOR")) {
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "OR")) {
        char instruBin[6] = "000000";
        return 1;
        
    }
    else if (!strcmp(aux, "ORI")) {
        char instruBin[6] = "001101";
        return 1;
        
    }
    else if (!strcmp(aux, "SUB")) {
        char instruBin[6] = "000000";
        return 1;
        
    }
    else if (!strcmp(aux, "XOR")) {
        char instruBin[6] = "000000";
        return 1;
    }
    else if (!strcmp(aux, "XORI")) {
        char instruBin[6] = "001110";
        return 1;
    }
    else {
        printf("%s\n", aux);
        insert_label(aux, count*4);
        get_data(aux);
        return 2;
    }
}

void busca_label2(char arquivo_binario[]) {
    FILE *arq;
    arq = fopen(arquivo_binario, "r");
    int i = 0;
    char aux[24];
    while(fgets(aux, 24, arq) != NULL) {
        aux[strcspn(aux, "\r\n")] = 0;
        if (alimenta_hash(aux, i) == 2){
            i = i;
        }else{
            i++;
        }
    }
}

void busca(char arquivo_binario[]) {
    FILE *arq;
    FILE *arq2;
    arq2 = fopen("arquivo_saida", "w");
    char aux[24];
    memset(aux, '\0', 24);
    int a;
    arq = fopen(arquivo_binario, "r");
    fseek(arq, 0, SEEK_SET);
    while(fgets(aux, 24, arq) != NULL) {
        aux[strcspn(aux, "\r\n")] = 0;
        printf("\n%s\n", aux);
        tradutor(aux, arq2);
    }
    fclose(arq);
    fclose(arq2);
}



int main () {
    init_hash();
    int a;
    //char arquivo_binario[24] = "ADDI $t1, $t1, 3";
    //tradutor(arquivo_binario);
    //printf("%s", arquivo_binario);
    //tradutor(arquivo_binario);
    //busca("arquivo_assembly");
    busca_label2("arquivo_assembly");

    return 0;
}
