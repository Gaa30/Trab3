addi $t0, $zero, 1
addi $t4, $zero, 10
add $t5, $zero, $t4 
addi $t1, $zero, 0
addi $t2, $zero, 1
addi $t3, $zero, 2
add $t4, $zero, $t1 
beq $t0, $t1, end
add $t4, $zero, $t5 
beq $t0, $t2, end
add $t4, $zero, $t2 
beq $t0, $t3, end
add $t4, $zero, $t3 
end
