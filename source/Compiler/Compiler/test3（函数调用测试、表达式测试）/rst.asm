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
		j	__main
p:
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
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		j	p__main
q:
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
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		j	q__main
q__main:
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
		li	$t0	2
		sw	$t0	-4($fp)
		li	$v0	1
		lw	$a0	-4($fp)
		syscall
		li	$t0	2
		li	$t1	3
		add	$t0	$t0	$t1
		sw	$t0	-8($fp)
		lw	$t0	-8($fp)
		li	$t1	4
		add	$t0	$t0	$t1
		sw	$t0	-12($fp)
		lw	$t0	-12($fp)
		li	$t1	1
		sub	$t0	$t0	$t1
		sw	$t0	-16($fp)
		li	$t0	5
		li	$t1	6
		mul	$t0	$t0	$t1
		sw	$t0	-20($fp)
		lw	$t0	-20($fp)
		li	$t1	1
		mul	$t0	$t0	$t1
		sw	$t0	-24($fp)
		lw	$t0	-16($fp)
		lw	$t1	-24($fp)
		add	$t0	$t0	$t1
		sw	$t0	-28($fp)
		li	$t0	3
		li	$t1	2
		div	$t0	$t0	$t1
		sw	$t0	-32($fp)
		lw	$t0	-32($fp)
		li	$t1	3
		div	$t0	$t0	$t1
		sw	$t0	-36($fp)
		lw	$t0	-28($fp)
		lw	$t1	-36($fp)
		add	$t0	$t0	$t1
		sw	$t0	-40($fp)
		lw	$t0	-40($fp)
		li	$t1	1
		add	$t0	$t0	$t1
		sw	$t0	-44($fp)
		lw	$t0	-44($fp)
		move	$t9	$fp
		lw	$t9	($t9)
		sw	$t0	-4($t9)
__FEND_LAB_q:
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		move	$sp	$fp
		jr	$ra	
p__main:
		jal	q
		nop
		li	$v0	1
		lw	$a0	-4($fp)
		syscall
		li	$v0	5
		syscall
		move	$t9	$fp
		lw	$t9	($t9)
		sw	$v0	-4($t9)
__FEND_LAB_p:
		lw	$ra	8($fp)
		lw	$fp	4($fp)
		move	$sp	$fp
		jr	$ra	
__main:
		jal	p
		nop
		li	$v0	1
		lw	$a0	-4($fp)
		syscall
		li	$v0	10
		syscall
