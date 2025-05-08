	.data
	.globl string_size
	.text
	# a0 - pointer to string
	# return
	# a0 - string size
string_size:
	addi sp, sp, -16
	sd ra, 8(sp)
	sd s0, 0(sp)

	mv t0, a0
	mv t2, a0
	li t1, 0
	
size_loop:
	lb t3, (t0)
	beq t3, t1, size_loop_end
	addi t0, t0, 1
	j size_loop

size_loop_end:
	sub a0, t0, t2
	j return

return:	
	ld ra, 8(sp)
	ld s0, 0(sp)
	addi sp, sp, 16
	ret


