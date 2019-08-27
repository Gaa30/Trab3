addi $t0, $0, 9
addi $t1, $0, 2
addi $t2, $0, 9
addi $t3, $0, 0
loop
add $t1, $t1, $t0
addi $t3, $t3, 1
bne $t3, $t2, loop
add $ra, $0, $t1
