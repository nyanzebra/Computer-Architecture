## Daniel J. Ellard -- 02/21/94
## palindrome.asm -- read a line of text and test if it is a palindrome.
##
## A palindrome is a string that is exactly the same when read backwards
## as when it is read forward (e.g. anna).
##
## Whitespace is considered significant in this version, so "ahahaha"
## is a palindrome while "aha haha" is not.
##
## Register usage:
## $1 - A - initially, the address of the first character in the string S.
## $2 - B - initially, the address of the the last character in S.
## $3 - the character at address A.
## $4 - the character at address B.
## $29 - syscall parameter / return values.
## $30 - syscall parameters.
## $31 - syscall parameters.

	.text
main:
	
## read the string S:
	la $30, string_space
	li $31, 1024
	li $29, 8		# load "read_string" code into $v0.
	syscall

	la $1, string_space	# A = S.
	la $2, string_space	# we need to move B to the end

length_loop:			# length of the string
	lb $3, $2, 0		# load the byte at addr B into $t3.
	beqz $3, end_length_loop # if $t3 == 0, branch out of loop.

	addi $2, $2, 1	# otherwise, increment B,
	b length_loop		# and repeat the loop.

end_length_loop:
	subi $2, $2, 1	# subtract 1 to move B back past

# the '\0' and '\n'.

test_loop:
	bge $1, $2, is_palin	# if A >= B, it's a palindrome.

	lb $3, $1, 0		# load the byte at addr A into $t3,
	lb $4, $2, 0		# load the byte at addr B into $t4.
	bne $3, $4, not_palin # if $t3 != $t4, not a palindrome.

# Otherwise,

	addi $1, $1, 1	# increment A,
	subi $2, $2, 1	# decrement B,
	b test_loop		# and repeat the loop.

is_palin:			# print the is_palin_msg, and exit.

	la $30, is_palin_msg
	li $29, 4
	syscall
	b exit

not_palin:
	la $30, not_palin_msg	## print the not_palin_msg, and exit.
	li $29, 4
	syscall
	b exit

exit:				# exit the program
	li $29, 10		# load "exit" code into $v0.
	syscall			# make the system call.


	.data
is_palin_msg: .asciiz "The string is a palindrome.\n"
not_palin_msg: .asciiz "The string is not a palindrome.\n"
string_space: .space 1024	# reserve 1024 bytes for the string.
