	.text
		ori	$fp	$sp	0
		sw	$fp	($sp)
		subi	$sp	$sp	4
		sw	$fp	($sp)
		ori	$fp	$sp	0
		subi	$sp	$sp	4
		li	$t0	100	
		sw	$t0	($sp)
		subi	$sp	$sp	4
		li	$t0	101	
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
		sw	$t0	-56($fp)
		
		lw	$t0	-4($fp)
		sw	$t0	-52($fp)
		
		lw	$t0	-56($fp)
		sw	$t0	-60($fp)
		lw	$t0	-52($fp)
		sw	$t0	-64($fp)
		lw	$t0	-60($fp)
		lw	$t1	-64($fp)
		add	$t0	$t0	$t1
		sw	$t0	-68($fp)
		lw	$t0	-68($fp)
		sw	$t0	-12($fp)
		lw	$t0	-52($fp)
		sw	$t0	-72($fp)
		lw	$t0	-56($fp)
		sw	$t0	-76($fp)
		lw	$t0	-72($fp)
		lw	$t1	-76($fp)
		div	$t0	$t0	$t1
		sw	$t0	-80($fp)
		lw	$t0	-80($fp)
		sw	$t0	-16($fp)
		li	$v0	11
		li	$a0	49
		syscall
		li	$v0	11
		li	$a0	48
		syscall
		li	$v0	11
		li	$a0	48
		syscall
		li	$v0	1
		lw	$a0	-12($fp)
		syscall
		li	$v0	1
		lw	$a0	-16($fp)
		syscall
		lw	$t0	-56($fp)
		sw	$t0	-84($fp)
		li	$v0	1
		lw	$a0	-84($fp)
		syscall
		lw	$t0	-52($fp)
		sw	$t0	-88($fp)
		li	$v0	1
		lw	$a0	-88($fp)
		syscall
		li	$v0	1
		lw	$a0	-4($fp)
		syscall
		li	$v0	11
		lw	$a0	-8($fp)
		syscall
		li	$v0	10
		syscall
