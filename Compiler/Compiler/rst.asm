	.text
		ori	$fp	$sp	0
		sw	$fp	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		ori	$fp	$sp	0
		subi	$sp	$sp	4
		li	$t8	0x10010000			#save word
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		j	__main
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
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	0	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		j	gcd__main
gcd__main:
		li	$v0	1
		lw	$a0	24($fp)
		syscall
		li	$v0	1
		lw	$a0	20($fp)
		syscall
		li	$v0	1
		lw	$a0	16($fp)
		syscall
		li	$v0	3
		j	__FEND_LAB_gcd
__FEND_LAB_gcd:
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
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	10
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	6
		sw	$t0	($sp)
		subi	$sp	$sp	4
		move	$t9	$fp
		jal	gcd
		nop
		sw	$v0	-12($fp)
		lw	$t0	-12($fp)
		lw	$t1	-4($fp)
		add	$t0	$t0	$t1
		sw	$t0	-16($fp)
		lw	$t0	-16($fp)
		sw	$t0	-8($fp)
		li	$v0	10
		syscall
