	.data
	.globl rand_xorshift_32
	.globl rand_xorshift_64
	.text

# a0 - state
rand_xorshift_32:
	addi sp, sp, -16
	sd ra, 8(sp)
	sd s0, 0(sp)

	sllw t0, a0, 13
	xor a0, a0, t0

	srlw t0, a0, 17
	xor a0, a0, t0

	sllw t0, a0, 5
	xor a0, a0, t0

	ld s0, 0(sp)
	ld ra, 8(sp)
	addi sp, sp, 16
	ret
	

rand_xorshift_64:
	addi sp, sp, -16
	sd ra, 8(sp)
	sd s0, 0(sp)

	sll t0, a0, 13
	xor a0, a0, t0

	srl t0, a0, 17
	xor a0, a0, t0

	sll t0, a0, 5
	xor a0, a0, t0

	ld s0, 0(sp)
	ld ra, 8(sp)
	addi sp, sp, 16
	ret
# todo: xorshift128, xoshiro fam
