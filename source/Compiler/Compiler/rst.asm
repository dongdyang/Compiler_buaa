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
		li	$t0	10
		sw	$t0	-8($fp)
		li	$t0	10
		sw	$t0	-32($fp)
		lw	$t0	-8($fp)
		sw	$t0	-4($fp)
		lw	$t0	-32($fp)
		lw	$t1	-12($fp)
		mul	$t0	$t0	$t1
		sw	$t0	-36($fp)
		lw	$t0	-36($fp)
		sw	$t0	-16($fp)
		li	$t0	0 
		lw	$t1	-8($fp)
		sub	$t0	$t0	$t1
		sw	$t0	-40($fp)
		lw	$t0	-40($fp)
		sw	$t0	-20($fp)
		lw	$t0	-32($fp)
		lw	$t1	-20($fp)
		mul	$t0	$t0	$t1
		sw	$t0	-44($fp)
		lw	$t0	-44($fp)
		sw	$t0	-8($fp)
		lw	$t0	-16($fp)
		lw	$t1	-8($fp)
		add	$t0	$t0	$t1
		sw	$t0	-48($fp)
		lw	$t0	-48($fp)
		sw	$t0	-24($fp)
		lw	$t0	-24($fp)
		sw	$t0	-28($fp)
		li	$v0	10
		syscall
