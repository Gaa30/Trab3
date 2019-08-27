ADDI $t0, $zero, 6
ADDI $t1, $zero, 0
ADD $a0, $zero, $zero
ADD $a1, $zero, $zero
ADDI $a2, $zero, 1
BEQ $t0, $zero, END
LOOP:
ADDI $t1, $t1, 1
ADD $a0, $a1, $a2
ADDI $a1, $a2, 0
ADDI $a2, $a0, 0
BNE $t0, $t1, LOOP
END:
