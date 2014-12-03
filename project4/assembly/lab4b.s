
.text

main:
li $5, 7
li $32, 0
li $33, 10
li $34, 100
li $35, 1000
loop:
subi $5, $5, 1
fadd $32, $32, $33
fadd $32, $32, $34
fadd $32, $32, $35
bge $5, $0, loop
nop
nop
li $29, 10
nop
syscall
