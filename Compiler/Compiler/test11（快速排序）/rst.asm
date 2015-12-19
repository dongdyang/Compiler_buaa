	.text
		ori	$fp	$sp	0
		sw	$fp	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		ori	$fp	$sp	0
		subi	$sp	$sp	4
		subi	$sp	$sp	28
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		j	__main
quicksort:
		sw	$sp	($sp)		#save register begin-----
		subi	$sp	$sp	4
		sw	$ra	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		subi	$sp	$sp	4
		move	$fp	$sp
		sw	$t9	($fp)
		subi	$sp	$sp	4		#save register ok---
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
		j	quicksort__main
quicksort__main:
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
		lw	$t0	20($fp)
		sw	$t0	-4($fp)
		lw	$t0	16($fp)
		sw	$t0	-8($fp)
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-28
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-20($fp)
		lw	$t0	-20($fp)
		sw	$t0	-12($fp)
		lw	$t0	-4($fp)
		lw	$t1	-8($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_0
_LABEL_2:
_LABEL_4:
		lw	$t0	-4($fp)
		lw	$t1	-8($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_6
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-28
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-24($fp)
		lw	$t0	-24($fp)
		lw	$t1	-12($fp)
		slt	$t0	$t0	$t1
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_8
		lw	$t0	-8($fp)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-28($fp)
		lw	$t0	-28($fp)
		sw	$t0	-8($fp)
		li	$t0	1
		sw	$t0	-16($fp)
		j	_LABEL_9
_LABEL_8:
		li	$t0	0
		sw	$t0	-16($fp)
_LABEL_9:
		j	_LABEL_7
_LABEL_6:
		li	$t0	0
		sw	$t0	-16($fp)
_LABEL_7:
		lw	$t0	-16($fp)
		li	$t1	1
		bne	$t0	$t1	__tLABEL0
		li	$t0	1
		j	__tLABEL1
__tLABEL0:
		li	$t0	0
__tLABEL1:
		bne	$t0	1	_LABEL_5
		j	_LABEL_4
_LABEL_5:
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-28
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-32($fp)
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-28
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t0	-32($fp)
		sw	$t0	0($t1)
_LABEL_10:
		lw	$t0	-4($fp)
		lw	$t1	-8($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_12
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-28
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-36($fp)
		lw	$t0	-36($fp)
		lw	$t1	-12($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_14
		lw	$t0	-4($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-40($fp)
		lw	$t0	-40($fp)
		sw	$t0	-4($fp)
		li	$t0	1
		sw	$t0	-16($fp)
		j	_LABEL_15
_LABEL_14:
		li	$t0	0
		sw	$t0	-16($fp)
_LABEL_15:
		j	_LABEL_13
_LABEL_12:
		li	$t0	0
		sw	$t0	-16($fp)
_LABEL_13:
		lw	$t0	-16($fp)
		li	$t1	1
		bne	$t0	$t1	__tLABEL2
		li	$t0	1
		j	__tLABEL3
__tLABEL2:
		li	$t0	0
__tLABEL3:
		bne	$t0	1	_LABEL_11
		j	_LABEL_10
_LABEL_11:
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-28
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-44($fp)
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-28
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t0	-44($fp)
		sw	$t0	0($t1)
		lw	$t0	-4($fp)
		lw	$t1	-8($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_3
		j	_LABEL_2
_LABEL_3:
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-28
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t0	-12($fp)
		sw	$t0	0($t1)
		lw	$t0	-4($fp)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-48($fp)
		lw	$t0	20($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	-48($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		move	$t9	$fp
		lw	$t9	($t9)
		jal	quicksort
		nop
		lw	$t0	-4($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-52($fp)
		lw	$t0	-52($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	16($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		move	$t9	$fp
		lw	$t9	($t9)
		jal	quicksort
		nop
		j	_LABEL_1
_LABEL_0:
_LABEL_1:
__FEND_LAB_quicksort:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
__main:
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	5
		sw	$t0	-32($fp)
		li	$t0	4
		sw	$t0	-28($fp)
		li	$t0	8
		sw	$t0	-24($fp)
		li	$t0	1
		sw	$t0	-20($fp)
		li	$t0	3
		sw	$t0	-16($fp)
		li	$t0	5
		sw	$t0	-12($fp)
		li	$t0	0
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	4
		sw	$t0	($sp)
		subi	$sp	$sp	4
		move	$t9	$fp
		jal	quicksort
		nop
		li	$t0	0
		li	$t1	4
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_17
		li	$t0	0
		sw	$t0	-36($fp)
_LABEL_16:
		lw	$t0	-36($fp)
		li	$t1	4
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_17
		lw	$t1	-36($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-28
		add	$t1	$t1	$fp
		lw	$t1	0($t1)
		sw	$t1	-72($fp)
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	1
		lw	$a0	-72($fp)
		syscall
		lw	$t0	-36($fp)
		li	$t1	4
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_17
		lw	$t0	-36($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-76($fp)
		lw	$t0	-76($fp)
		sw	$t0	-36($fp)
		j	_LABEL_16
_LABEL_17:
		li	$v0	10
		syscall
