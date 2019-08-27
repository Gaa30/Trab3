addi $t0, $zero, 6
addi $t1, $zero, 0
add $a0, $zero, $zero
add $a1, $zero, $zero
addi $a2, $zero, 1
beq $t0, $zero, end
loop
addi $t1, $t1, 1
add $a0, $a1, $a2
addi $a1, $a2, 0
addi $a2, $a0, 0
bne $t0, $t1, loop
end
