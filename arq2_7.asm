ADDI $t0, $0, 0
ADDI $t1, $0, 1
ADDI $t2, $0, 2
ADDI $t3, $0, 3
ADDI $t4, $0, 4
ADDI $t5, $0, 5
ADDI $t6, $0, 6
ADDI $t7, $0, 7
ADDI $t8, $0, 8
ADDI $t9, $0, 9

ADD $s0, $0, $t0
SUB $s1, $s0, $t1
BGTZ $s1, pulat1
ADD $s0, $0, $t1
pulat1:
sub $s1, $s0, $t2
BGTZ $s1, pulat2
ADD $s0, $0, $t3
pulat2:
sub $s1, $s0, $t3
BGTZ $s1, pulat3
ADD $s0, $0, $t4
pulat3:
sub $s1, $s0, $t4
BGTZ $s1, pulat4
ADD $s0, $0, $t4
pulat4:
sub $s1, $s0, $t5
BGTZ $s1, pulat5
ADD $s0, $0, $t5
pulat5:
sub $s1, $s0, $t6
BGTZ $s1, pulat6
ADD $s0, $0, $t6
pulat6:
sub $s1, $s0, $t7
BGTZ $s1, pulat7
ADD $s0, $0, $t7
pulat7:
sub $s1, $s0, $t8
BGTZ $s1, pulat8
ADD $s0, $0, $t8
pulat8:
sub $s1, $s0, $t9
BGTZ $s1, pulat9
ADD $s0, $0, $t9
pulat9:
ADD $ra, $0, $s0 

