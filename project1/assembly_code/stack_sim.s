#stack simulation

.text
main:
	push C
	push B
	push A
	push X
	push X	

	mult		#top of stack is X^2, A, B, C
	mult		#top of stack is A*X^2, B, C
	pop A   	#A = A*X^2, top of stack is B, C
	push X  	#top of stack is X, B, C
	mult		#top of stack is X*B, C
	push A  	#top of stack is A*X^2, X*B, C
	add			#top of stack is A*X^2 + X*B, C
	add			#top of stack is A*X^2 + X*B + C
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
nl: 	.asciiz "\n"