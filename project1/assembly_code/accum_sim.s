#accumulator simulation

.text
main:
	load X  	#reg = X
	mult X		#reg = X^2
	mult A		#reg = A*X^2
	stor A   	#A = A*X^2
	load X 		#reg = X
	mult B		#reg = X*B
	stor B 		#B = X*B
	add	A		#reg = A*X^2 + X*B
	add	C		#reg = A*X^2 + X*B + C
	stor A 		#A = A*X^2 + X*B + C   
	load ans	#reg = "Answer = "
	prnt		#print "Answer = "
	load A 		#reg = A*X^2 + X*B + C
	prnt 		#print "82"
	load nl 	#reg = "\n"
	prnt 		#print new line
	end

.data
X:		.word 3
A:		.word 7
B:		.word 5
C:		.word 4
ans: 	.asciiz "Answer = "
nl: 	.asciiz "\n"