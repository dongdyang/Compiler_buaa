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
		j	__main
__main:
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
		lw	$t0	-4($fp)
		sw	$t0	-24($fp)
		li	$v0	5
		syscall
		sw	$v0	-8($fp)
		li	$v0	5
		syscall
		sw	$v0	-12($fp)
		li	$t0	1
		sw	$t0	-16($fp)
		lw	$t0	-8($fp)
		sw	$t0	-20($fp)
		li	$t0	0
		li	$t1	10
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_1
		li	$t0	0
		sw	$t0	-28($fp)
_LABEL_0:
		lw	$t0	-28($fp)
		li	$t1	10
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_1
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	1
		lw	$a0	-28($fp)
		syscall
		lw	$t0	-28($fp)
		li	$t1	10
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_1
		lw	$t0	-28($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-32($fp)
		lw	$t0	-32($fp)
		sw	$t0	-28($fp)
		j	_LABEL_0
_LABEL_1:
		li	$t0	0
		li	$t1	10
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_3
		li	$t0	0
		sw	$t0	-28($fp)
_LABEL_2:
		lw	$t0	-28($fp)
		li	$t1	10
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_3
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	1
		lw	$a0	-28($fp)
		syscall
		lw	$t0	-28($fp)
		li	$t1	10
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_3
		lw	$t0	-28($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-36($fp)
		lw	$t0	-36($fp)
		sw	$t0	-28($fp)
		j	_LABEL_2
_LABEL_3:
_LABEL_4:
		lw	$t0	-20($fp)
		lw	$t1	-16($fp)
		sub	$t0	$t0	$t1
		sw	$t0	-40($fp)
		lw	$t0	-40($fp)
		sw	$t0	-20($fp)
		lw	$t0	-20($fp)
		lw	$t1	-12($fp)
		slt	$t0	$t1	$t0
		bne	$t0	1	_LABEL_6
		li	$v0	1
		lw	$a0	-20($fp)
		syscall
		j	_LABEL_7
_LABEL_6:
		li	$v0	11
		li	$a0	110
		syscall
		li	$v0	11
		li	$a0	111
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	104
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	110
		syscall
		li	$v0	11
		li	$a0	103
		syscall
		li	$v0	11
		li	$a0	33
		syscall
_LABEL_7:
		lw	$t0	-8($fp)
		li	$t1	5
		sub	$t0	$t0	$t1
		sw	$t0	-44($fp)
		lw	$t0	-20($fp)
		lw	$t1	-44($fp)
		slt	$t0	$t0	$t1
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_5
		j	_LABEL_4
_LABEL_5:
		li	$v0	10
		syscall
