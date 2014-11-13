	

.text

main: 
 li $1, 0
 li $29, 32

loop:
 subi $29, $29, 1
 nop
 nop
 nop
 nop
 nop
 bge $29, $1, loop
 nop

 li $29, 10
 syscall