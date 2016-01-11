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
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		subi	$sp	$sp	40
		subi	$sp	$sp	28
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		j	__main
test:
		sw	$sp	($sp)		#save register begin-----
		subi	$sp	$sp	4
		sw	$ra	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		subi	$sp	$sp	4
		move	$fp	$sp
		sw	$t9	($fp)
		subi	$sp	$sp	4		#save register ok---
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
		lw	$t0	16($fp)
		li	$t1	1
		slt	$t0	$t1	$t0
		bne	$t0	1	_LABEL_0
		lw	$t0	16($fp)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-4($fp)
		lw	$t0	-4($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		lw	$t9	($t9)
		jal	test
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		sw	$v0	-8($fp)
		lw	$t0	16($fp)
		lw	$t1	-8($fp)
		mul	$t0	$t0	$t1
		sw	$t0	-12($fp)
		lw	$v0	-12($fp)
		j	__FEND_LAB_test
		j	_LABEL_1
_LABEL_0:
		lw	$v0	16($fp)
		j	__FEND_LAB_test
_LABEL_1:
__FEND_LAB_test:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
swap:
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
		j	swap__main
swap__main:
		lw	$s0	-4($fp)
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
swap2:
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
		j	swap2__main
swap2__main:
		lw	$s0	-4($fp)
		lw	$t0	20($fp)
		sw	$t0	-4($fp)
		lw	$t0	16($fp)
		sw	$t0	20($fp)
		lw	$t0	-4($fp)
		sw	$t0	16($fp)
__FEND_LAB_swap2:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
gcd:
		sw	$sp	($sp)		#save register begin-----
		subi	$sp	$sp	4
		sw	$ra	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		subi	$sp	$sp	4
		move	$fp	$sp
		sw	$t9	($fp)
		subi	$sp	$sp	4		#save register ok---
		j	gcd__main
mod:
		sw	$sp	($sp)		#save register begin-----
		subi	$sp	$sp	4
		sw	$ra	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		subi	$sp	$sp	4
		move	$fp	$sp
		sw	$t9	($fp)
		subi	$sp	$sp	4		#save register ok---
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
		lw	$s0	20($fp)
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
		lw	$s0	-16($fp)
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
		bne	$t0	1	_LABEL_2
		lw	$t0	20($fp)
		lw	$t1	16($fp)
		add	$t0	$t0	$t1
		sw	$t0	-20($fp)
		lw	$v0	-20($fp)
		j	__FEND_LAB_gcd
		j	_LABEL_3
_LABEL_2:
		lw	$t0	20($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	16($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	mod
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		sw	$v0	-24($fp)
		lw	$t0	16($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	20($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	mod
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		sw	$v0	-28($fp)
		lw	$t0	-24($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	-28($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		lw	$t9	($t9)
		jal	gcd
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		sw	$v0	-32($fp)
		lw	$v0	-32($fp)
		j	__FEND_LAB_gcd
_LABEL_3:
__FEND_LAB_gcd:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
sort:
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
		lw	$s0	-8($fp)
		lw	$s1	-12($fp)
		lw	$s2	-4($fp)
		move	$t9	$fp
		lw	$t9	($t9)
		lw	$t0	-8($t9)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-12($fp)
		lw	$t0	-12($fp)
		li	$t1	1
		slt	$t0	$t0	$t1
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_5
		lw	$t0	-12($fp)
		sw	$t0	-4($fp)
_LABEL_4:
		lw	$t0	-4($fp)
		li	$t1	1
		slt	$t0	$t0	$t1
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_5
		lw	$t0	-4($fp)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-16($fp)
		li	$t0	0
		lw	$t1	-16($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_7
		li	$t0	0
		sw	$t0	-8($fp)
_LABEL_6:
		lw	$t0	-8($fp)
		lw	$t1	-16($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_7
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-76
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
		addi	$t1	$t1	-76
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-28($fp)
		lw	$t0	-20($fp)
		lw	$t1	-28($fp)
		slt	$t0	$t1	$t0
		bne	$t0	1	_LABEL_8
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-76
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
		addi	$t1	$t1	-76
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
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		lw	$t9	($t9)
		jal	swap
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		lw	$t0	8($sp)
		sw	$t0	-32($fp)
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-76
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		sw	$t0	0($t1)
		lw	$t0	4($sp)
		sw	$t0	-40($fp)
		lw	$t1	-36($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-76
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		sw	$t0	0($t1)
		j	_LABEL_8
_LABEL_8:
		lw	$t0	-8($fp)
		lw	$t1	-16($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_7
		lw	$t0	-8($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-44($fp)
		lw	$t0	-44($fp)
		sw	$t0	-8($fp)
		j	_LABEL_6
_LABEL_7:
		lw	$t0	-4($fp)
		li	$t1	1
		slt	$t0	$t1	$t0
		bne	$t0	1	_LABEL_5
		lw	$t0	-4($fp)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-48($fp)
		lw	$t0	-48($fp)
		sw	$t0	-4($fp)
		j	_LABEL_4
_LABEL_5:
__FEND_LAB_sort:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
readList:
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
		j	readList__main
readList__main:
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$s0	-4($fp)
		lw	$s1	-8($fp)
		lw	$s2	-12($fp)
		move	$t9	$fp
		lw	$t9	($t9)
		lw	$t0	-8($t9)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-12($fp)
		li	$t0	0
		lw	$t1	-12($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_11
		li	$t0	0
		sw	$t0	-4($fp)
_LABEL_10:
		lw	$t0	-4($fp)
		lw	$t1	-12($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_11
		li	$v0	5
		syscall
		sw	$v0	-8($fp)
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-76
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t0	-8($fp)
		sw	$t0	0($t1)
		lw	$t0	-4($fp)
		lw	$t1	-12($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_11
		lw	$t0	-4($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-16($fp)
		lw	$t0	-16($fp)
		sw	$t0	-4($fp)
		j	_LABEL_10
_LABEL_11:
__FEND_LAB_readList:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
writeList:
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
		j	writeList__main
writeList__main:
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$s0	-4($fp)
		lw	$s1	-8($fp)
		lw	$s2	-12($fp)
		move	$t9	$fp
		lw	$t9	($t9)
		lw	$t0	-8($t9)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-8($fp)
		li	$t0	0
		lw	$t1	-8($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_13
		li	$t0	0
		sw	$t0	-4($fp)
_LABEL_12:
		lw	$t0	-4($fp)
		lw	$t1	-8($fp)
		slt	$t0	$t1	$t0
		li	$t1	1
		sub	$t0	$t1	$t0
		bne	$t0	1	_LABEL_13
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-76
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
		bne	$t0	1	_LABEL_13
		lw	$t0	-4($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-16($fp)
		lw	$t0	-16($fp)
		sw	$t0	-4($fp)
		j	_LABEL_12
_LABEL_13:
__FEND_LAB_writeList:
		lw	$sp	12($fp)
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		jr	$ra	
QuickSort:
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
		j	QuickSort__main
QuickSort__main:
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
		lw	$s0	20($fp)
		lw	$s1	-4($fp)
		lw	$s2	-16($fp)
		lw	$s3	16($fp)
		lw	$s4	-8($fp)
		lw	$s5	-12($fp)
		lw	$t0	20($fp)
		sw	$t0	-4($fp)
		lw	$t0	16($fp)
		sw	$t0	-8($fp)
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-104
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
		bne	$t0	1	_LABEL_14
_LABEL_16:
_LABEL_18:
		lw	$t0	-4($fp)
		lw	$t1	-8($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_20
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-104
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
		bne	$t0	1	_LABEL_22
		lw	$t0	-8($fp)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-28($fp)
		lw	$t0	-28($fp)
		sw	$t0	-8($fp)
		li	$t0	1
		sw	$t0	-16($fp)
		j	_LABEL_23
_LABEL_22:
		li	$t0	0
		sw	$t0	-16($fp)
_LABEL_23:
		j	_LABEL_21
_LABEL_20:
		li	$t0	0
		sw	$t0	-16($fp)
_LABEL_21:
		lw	$t0	-16($fp)
		li	$t1	1
		bne	$t0	$t1	__tLABEL2
		li	$t0	1
		j	__tLABEL3
__tLABEL2:
		li	$t0	0
__tLABEL3:
		bne	$t0	1	_LABEL_19
		j	_LABEL_18
_LABEL_19:
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-104
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-32($fp)
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-104
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t0	-32($fp)
		sw	$t0	0($t1)
_LABEL_24:
		lw	$t0	-4($fp)
		lw	$t1	-8($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_26
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-104
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
		bne	$t0	1	_LABEL_28
		lw	$t0	-4($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-40($fp)
		lw	$t0	-40($fp)
		sw	$t0	-4($fp)
		li	$t0	1
		sw	$t0	-16($fp)
		j	_LABEL_29
_LABEL_28:
		li	$t0	0
		sw	$t0	-16($fp)
_LABEL_29:
		j	_LABEL_27
_LABEL_26:
		li	$t0	0
		sw	$t0	-16($fp)
_LABEL_27:
		lw	$t0	-16($fp)
		li	$t1	1
		bne	$t0	$t1	__tLABEL4
		li	$t0	1
		j	__tLABEL5
__tLABEL4:
		li	$t0	0
__tLABEL5:
		bne	$t0	1	_LABEL_25
		j	_LABEL_24
_LABEL_25:
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-104
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t1	0($t1)
		sw	$t1	-44($fp)
		lw	$t1	-8($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-104
		move	$t9	$fp
		lw	$t9	($t9)
		add	$t1	$t1	$t9
		lw	$t0	-44($fp)
		sw	$t0	0($t1)
		lw	$t0	-4($fp)
		lw	$t1	-8($fp)
		slt	$t0	$t0	$t1
		bne	$t0	1	_LABEL_17
		j	_LABEL_16
_LABEL_17:
		lw	$t1	-4($fp)
		mul	$t1	$t1	4
		addi	$t1	$t1	-104
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
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		lw	$t9	($t9)
		jal	QuickSort
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
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
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		lw	$t9	($t9)
		jal	QuickSort
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		j	_LABEL_15
_LABEL_14:
_LABEL_15:
__FEND_LAB_QuickSort:
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
		lw	$s0	-116($fp)
		lw	$s1	-4($fp)
		lw	$s2	-16($fp)
		lw	$s3	-120($fp)
		lw	$s4	-8($fp)
		lw	$s5	-12($fp)
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
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
		li	$a0	32
		syscall
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
		li	$a0	112
		syscall
		li	$v0	11
		li	$a0	97
		syscall
		li	$v0	11
		li	$a0	114
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	58
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	5
		syscall
		sw	$v0	-16($fp)
		lw	$t0	-16($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	test
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		sw	$v0	-116($fp)
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	120
		syscall
		li	$v0	11
		li	$a0	33
		syscall
		li	$v0	11
		li	$a0	61
		syscall
		li	$v0	1
		lw	$a0	-116($fp)
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
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
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	115
		syscall
		li	$v0	11
		li	$a0	119
		syscall
		li	$v0	11
		li	$a0	97
		syscall
		li	$v0	11
		li	$a0	112
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	112
		syscall
		li	$v0	11
		li	$a0	97
		syscall
		li	$v0	11
		li	$a0	114
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	40
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	110
		syscall
		li	$v0	11
		li	$a0	112
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	119
		syscall
		li	$v0	11
		li	$a0	111
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	110
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	109
		syscall
		li	$v0	11
		li	$a0	98
		syscall
		li	$v0	11
		li	$a0	101
		syscall
		li	$v0	11
		li	$a0	114
		syscall
		li	$v0	11
		li	$a0	41
		syscall
		li	$v0	11
		li	$a0	58
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	5
		syscall
		sw	$v0	-20($fp)
		li	$v0	5
		syscall
		sw	$v0	-24($fp)
		lw	$t0	-20($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	-24($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	swap2
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	40
		syscall
		li	$v0	11
		li	$a0	119
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	104
		syscall
		li	$v0	11
		li	$a0	111
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	118
		syscall
		li	$v0	11
		li	$a0	97
		syscall
		li	$v0	11
		li	$a0	114
		syscall
		li	$v0	11
		li	$a0	41
		syscall
		li	$v0	11
		li	$a0	120
		syscall
		li	$v0	11
		li	$a0	49
		syscall
		li	$v0	11
		li	$a0	58
		syscall
		li	$v0	1
		lw	$a0	-20($fp)
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	120
		syscall
		li	$v0	11
		li	$a0	50
		syscall
		li	$v0	11
		li	$a0	58
		syscall
		li	$v0	1
		lw	$a0	-24($fp)
		syscall
		lw	$t0	-20($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	-24($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	swap
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		lw	$t0	8($sp)
		sw	$t0	-20($fp)
		lw	$t0	4($sp)
		sw	$t0	-24($fp)
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	40
		syscall
		li	$v0	11
		li	$a0	119
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	104
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	118
		syscall
		li	$v0	11
		li	$a0	97
		syscall
		li	$v0	11
		li	$a0	114
		syscall
		li	$v0	11
		li	$a0	41
		syscall
		li	$v0	11
		li	$a0	120
		syscall
		li	$v0	11
		li	$a0	49
		syscall
		li	$v0	11
		li	$a0	58
		syscall
		li	$v0	1
		lw	$a0	-20($fp)
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	120
		syscall
		li	$v0	11
		li	$a0	50
		syscall
		li	$v0	11
		li	$a0	58
		syscall
		li	$v0	1
		lw	$a0	-24($fp)
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
		syscall
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
		li	$a0	40
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	110
		syscall
		li	$v0	11
		li	$a0	112
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	119
		syscall
		li	$v0	11
		li	$a0	111
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	110
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	109
		syscall
		li	$v0	11
		li	$a0	98
		syscall
		li	$v0	11
		li	$a0	101
		syscall
		li	$v0	11
		li	$a0	114
		syscall
		li	$v0	11
		li	$a0	41
		syscall
		li	$v0	11
		li	$a0	58
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	5
		syscall
		sw	$v0	-20($fp)
		li	$v0	5
		syscall
		sw	$v0	-24($fp)
		lw	$t0	-20($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	-24($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	gcd
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		sw	$v0	-120($fp)
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	1
		lw	$a0	-120($fp)
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	98
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	98
		syscall
		li	$v0	11
		li	$a0	98
		syscall
		li	$v0	11
		li	$a0	108
		syscall
		li	$v0	11
		li	$a0	101
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	115
		syscall
		li	$v0	11
		li	$a0	111
		syscall
		li	$v0	11
		li	$a0	114
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
		li	$a0	40
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	110
		syscall
		li	$v0	11
		li	$a0	112
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	102
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	118
		syscall
		li	$v0	11
		li	$a0	101
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	110
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	109
		syscall
		li	$v0	11
		li	$a0	98
		syscall
		li	$v0	11
		li	$a0	101
		syscall
		li	$v0	11
		li	$a0	114
		syscall
		li	$v0	11
		li	$a0	41
		syscall
		li	$v0	11
		li	$a0	58
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	readList
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	sort
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	writeList
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	113
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	99
		syscall
		li	$v0	11
		li	$a0	107
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	115
		syscall
		li	$v0	11
		li	$a0	111
		syscall
		li	$v0	11
		li	$a0	114
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
		li	$a0	40
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	110
		syscall
		li	$v0	11
		li	$a0	112
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	116
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	102
		syscall
		li	$v0	11
		li	$a0	105
		syscall
		li	$v0	11
		li	$a0	118
		syscall
		li	$v0	11
		li	$a0	101
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		li	$v0	11
		li	$a0	110
		syscall
		li	$v0	11
		li	$a0	117
		syscall
		li	$v0	11
		li	$a0	109
		syscall
		li	$v0	11
		li	$a0	98
		syscall
		li	$v0	11
		li	$a0	101
		syscall
		li	$v0	11
		li	$a0	114
		syscall
		li	$v0	11
		li	$a0	41
		syscall
		li	$v0	11
		li	$a0	58
		syscall
		li	$v0	11
		li	$a0	32
		syscall
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	readList
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	sort
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		sw	$s0	0($gp)
		sw	$s1	4($gp)
		sw	$s2	8($gp)
		sw	$s3	12($gp)
		sw	$s4	16($gp)
		sw	$s5	20($gp)
		sw	$s6	24($gp)
		sw	$s7	28($gp)
		move	$t9	$fp
		jal	writeList
		nop
		lw	$s0	0($gp)
		lw	$s1	4($gp)
		lw	$s2	8($gp)
		lw	$s3	12($gp)
		lw	$s4	16($gp)
		lw	$s5	20($gp)
		lw	$s6	24($gp)
		lw	$s7	28($gp)
		li	$v0	10
		syscall
