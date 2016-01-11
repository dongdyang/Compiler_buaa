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
		subi	$sp	$sp	40
		j	__main
swap:
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
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		j	swap__main
swap__main:
		lw	$t0	20($fp)
		sw	$t0	-4($fp)
		lw	$t0	16($fp)
		sw	$t0	20($fp)
		lw	$t0	-4($fp)
		sw	$t0	16($fp)
__FEND_LAB_swap:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
sort:
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
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		j	sort__main
sort__main:
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
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		move	$t9	$fp
		lw	$t9	($t9)
		lw	$t0	-4($t9)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-12($fp)
		lw	$t0	-12($fp)
		li	$t1	1
		slt	$t0	$t0	$t1
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_1
		lw	$t0	-12($fp)
		sw	$t0	-4($fp)
_LABEL_0:
		lw	$t0	-4($fp)
		li	$t1	1
		slt	$t0	$t0	$t1
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_1
		lw	$t0	-4($fp)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-16($fp)
		li	$t0	0
		lw	$t1	-16($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_3
		li	$t0	0
		sw	$t0	-8($fp)
_LABEL_2:
		lw	$t0	-8($fp)
		lw	$t1	-16($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_3
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-44
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-20($fp)
		lw	$t0	-8($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-24($fp)
		lw	$t1	-24($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-44
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-28($fp)
		lw	$t0	-20($fp)
		lw	$t1	-28($fp)
		slt	$t0	$t1	$t0
		bne	$t0	1	_LABEL_4
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-44
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-32($fp)
		lw	$t0	-8($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-36($fp)
		lw	$t1	-36($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-44
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-40($fp)
		lw	$t0	-32($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	-40($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		jal	swap
		nop
		lw	$t0	8($sp)
		sw	$t0	-32($fp)
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-44
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		sw	$t0	0($t1)
		lw	$t0	4($sp)
		sw	$t0	-40($fp)
		lw	$t1	-36($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-44
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		sw	$t0	0($t1)
		j	_LABEL_5
_LABEL_4:
_LABEL_5:
		lw	$t0	-8($fp)
		lw	$t1	-16($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_3
		lw	$t0	-8($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-44($fp)
		lw	$t0	-44($fp)
		sw	$t0	-8($fp)
		j	_LABEL_2
_LABEL_3:
		lw	$t0	-4($fp)
		li	$t1	1
		slt	$t0	$t1	$t0
		bne	$t0	1	_LABEL_1
		lw	$t0	-4($fp)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-48($fp)
		lw	$t0	-48($fp)
		sw	$t0	-4($fp)
		j	_LABEL_0
_LABEL_1:
__FEND_LAB_sort:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
readlist:
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
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		j	readlist__main
readlist__main:
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		move	$t9	$fp
		lw	$t9	($t9)
		lw	$t0	-4($t9)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-12($fp)
		li	$t0	0
		lw	$t1	-12($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_7
		li	$t0	0
		sw	$t0	-4($fp)
_LABEL_6:
		lw	$t0	-4($fp)
		lw	$t1	-12($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_7
		li	$v0	5
		syscall
		sw	$v0	-8($fp)
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-44
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t0	-8($fp)
		sw	$t0	0($t1)
		lw	$t0	-4($fp)
		lw	$t1	-12($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_7
		lw	$t0	-4($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-16($fp)
		lw	$t0	-16($fp)
		sw	$t0	-4($fp)
		j	_LABEL_6
_LABEL_7:
__FEND_LAB_readlist:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
writelist:
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
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		j	writelist__main
writelist__main:
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		move	$t9	$fp
		lw	$t9	($t9)
		lw	$t0	-4($t9)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-8($fp)
		li	$t0	0
		lw	$t1	-8($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_9
		li	$t0	0
		sw	$t0	-4($fp)
_LABEL_8:
		lw	$t0	-4($fp)
		lw	$t1	-8($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_9
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-44
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-12($fp)
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	1
		lw	$a0	-12($fp)
		syscall
		lw	$t0	-4($fp)
		lw	$t1	-8($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_9
		lw	$t0	-4($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-16($fp)
		lw	$t0	-16($fp)
		sw	$t0	-4($fp)
		j	_LABEL_8
_LABEL_9:
__FEND_LAB_writelist:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
__main:
		jal	readlist
		nop
		jal	sort
		nop
		jal	writelist
		nop
		li	$v0	10
		syscall
