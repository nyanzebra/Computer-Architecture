#stack simulation

.text
main:
	push X
	push X
	push A
	push B
	push C

	mul			#top of stack is X^2, A, B, C
	mul			#top of stack is A*X^2, B, C
	pop	A   	#A = A*X^2, top of stack is B, C
	push X  	#top of stack is X, B, C
	mul			#top of stack is X*B, C
	push A  	#top of stack is A*X^2, X*B, C
	add			#top of stack is A*X^2 + X*B, C
	add			#top of stack is A*X^2 + X*B + C
	pop A   	#A now holds the answer
	push ans    
	prnt		#print Answer =
	prnt		#print answer
	push nl
	prnt
	end

.data
X:		.word 3
A:		.word 7
B:		.word 5
C:		.word 4
ans: 	.asciiz "Answer = "
nl 		.asciiz "\n"