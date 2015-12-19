	.text
		ori	$fp	$sp	0
		sw	$fp	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		ori	$fp	$sp	0
		subi	$sp	$sp	4
		li	$t0	10	
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
swap:
		#save register-----
		sw	$ra	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		subi	$sp	$sp	4
		move	$t9	$fp
		lw	$t9	($t9)
		add	$fp	$sp	$0
		sw	$t9	($fp)
		subi	$sp	$sp	4
		#save register ok---
		j	swap__main
swap__main:
		li	$t0	3
		move	$t9	$fp
		lw	$t9	($t9)
		sw	$t0	-8($t9)
		li	$v0	11
		li	$a0	51
		syscall
		li	$v0	1
		move	$t9	$fp
		lw	$t9	($t9)
		lw	$a0	-8($t9)
		syscall
__FEND_LAB_swap:
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		move	$sp	$fp
		jr	$ra	
__main:
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		jal	swap
		nop
		li	$v0	5
		syscall
		sw	$v0	-8($fp)
		li	$v0	5
		syscall
		sw	$v0	-16($fp)
		lw	$t0	-8($fp)
		lw	$t1	-16($fp)
		add	$t0	$t0	$t1
		sw	$t0	0($fp)
		lw	$t0	0($fp)
		sw	$t0	-16($fp)
		lw	$t0	-16($fp)
		li	$t1	15
		slt	$t0	$t1	$t0
		bne	$t0	1	_LABEL_0
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	104
		syscall
		li	$v0	11
		li	$a0	101
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	114
		syscall
		li	$v0	11
		li	$a0	101
		syscall
		li	$v0	11
		li	$a0	115
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	108
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	111
		syscall
		li	$v0	11
		li	$a0	102
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	99
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	115
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	58
		syscall
		li	$v0	1
		lw	$a0	-16($fp)
		syscall
		j	_LABEL_1
_LABEL_0:
_LABEL_1:
		li	$v0	10
		syscall
