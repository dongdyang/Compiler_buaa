	.text
		ori	$fp	$sp	0
		sw	$fp	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		ori	$fp	$sp	0
		subi	$sp	$sp	4
		li	$t0	5	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	100	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		subi	$sp	$sp	40
		j	__main
gcd:
		#save register-----
		sw	$sp	($sp)
		subi	$sp	$sp	4
		sw	$ra	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		subi	$sp	$sp	4
		move	$t9	$fp
		add	$fp	$sp	$0
		sw	$t9	($fp)
		subi	$sp	$sp	4
		#save register ok---
		j	gcd__main
mod:
		#save register-----
		sw	$sp	($sp)
		subi	$sp	$sp	4
		sw	$ra	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		subi	$sp	$sp	4
		move	$t9	$fp
		add	$fp	$sp	$0
		sw	$t9	($fp)
		subi	$sp	$sp	4
		#save register ok---
		j	mod__main
mod__main:
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	20($fp)
		lw	$t1	16($fp)
		div	$t0	$t0	$t1
		sw	$t0	-4($fp)
		lw	$t0	-4($fp)
		lw	$t1	16($fp)
		mul	$t0	$t0	$t1
		sw	$t0	-8($fp)
		lw	$t0	20($fp)
		lw	$t1	-8($fp)
		sub	$t0	$t0	$t1
		sw	$t0	-12($fp)
		lw	$v0	-12($fp)
		j	__FEND_LAB_mod
__FEND_LAB_mod:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
gcd__main:
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	20($fp)
		lw	$t1	16($fp)
		mul	$t0	$t0	$t1
		sw	$t0	-16($fp)
		lw	$t0	-16($fp)
		li	$t1	0
		bne	$t0	$t1	__tLABEL0
		li	$t0	1
		j	__tLABEL1
__tLABEL0:
		li	$t0	0
__tLABEL1:
		bne	$t0	1	_LABEL_0
		lw	$t0	20($fp)
		lw	$t1	16($fp)
		add	$t0	$t0	$t1
		sw	$t0	-20($fp)
		lw	$v0	-20($fp)
		j	__FEND_LAB_gcd
		j	_LABEL_1
_LABEL_0:
		lw	$t0	20($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	16($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		jal	mod
		nop
		sw	$v0	-24($fp)
		lw	$t0	16($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	20($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		jal	mod
		nop
		sw	$v0	-28($fp)
		lw	$t0	-24($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	-28($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		jal	gcd
		nop
		sw	$v0	-32($fp)
		lw	$v0	-32($fp)
		j	__FEND_LAB_gcd
_LABEL_1:
__FEND_LAB_gcd:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
__main:
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$v0	11
		li	$a0	103
		syscall
		li	$v0	11
		li	$a0	99
		syscall
		li	$v0	11
		li	$a0	100
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	101
		syscall
		li	$v0	11
		li	$a0	115
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	98
		syscall
		li	$v0	11
		li	$a0	101
		syscall
		li	$v0	11
		li	$a0	103
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	110
		syscall
		li	$v0	11
		li	$a0	33
		syscall
		li	$v0	5
		syscall
		sw	$v0	-12($fp)
		li	$v0	5
		syscall
		sw	$v0	-16($fp)
		lw	$t0	-12($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	-16($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		jal	gcd
		nop
		sw	$v0	-60($fp)
		li	$v0	1
		lw	$a0	-60($fp)
		syscall
		li	$v0	10
		syscall
