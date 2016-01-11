	.text
		ori	$fp	$sp	0
		sw	$fp	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		ori	$fp	$sp	0
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		j	__main
test:
		#save register-----
		sw	$ra	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		subi	$sp	$sp	4
		move	$t9	$fp
		add	$fp	$sp	$0
		sw	$t9	($fp)
		subi	$sp	$sp	4
		#save register ok---
		j	test__main
test__main:
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	12($fp)
		li	$t1	1
		slt	$t0	$t1	$t0
		bne	$t0	1	_LABEL_0
		lw	$t0	12($fp)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-4($fp)
		lw	$t0	-4($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		jal	test
		nop
		sw	$v0	-8($fp)
		lw	$t0	12($fp)
		lw	$t1	-8($fp)
		mul	$t0	$t0	$t1
		sw	$t0	-12($fp)
		lw	$v0	-12($fp)
		j	__FEND_LAB_test
		j	_LABEL_1
_LABEL_0:
		lw	$v0	12($fp)
		j	__FEND_LAB_test
_LABEL_1:
__FEND_LAB_test:
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		move	$sp	$fp
		jr	$ra	
__main:
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$v0	5
		syscall
		sw	$v0	-8($fp)
		lw	$t0	-8($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		jal	test
		nop
		sw	$v0	-20($fp)
		li	$v0	11
		li	$a0	120
		syscall
		li	$v0	11
		li	$a0	33
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	61
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	1
		lw	$a0	-20($fp)
		syscall
		li	$v0	10
		syscall
