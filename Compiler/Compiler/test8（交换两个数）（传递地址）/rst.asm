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
swap2:
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
		j	swap2__main
swap2__main:
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
__main:
		li	$t0	10
		sw	$t0	-12($fp)
		li	$t0	5
		sw	$t0	-16($fp)
		lw	$t0	-12($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	-16($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		jal	swap2
		nop
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
		lw	$a0	-12($fp)
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
		lw	$a0	-16($fp)
		syscall
		lw	$t0	-12($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		lw	$t0	-16($fp)
		sw	$t0	($sp)
		subi	$sp	$sp	4
		jal	swap
		nop
		lw	$t0	8($sp)
		sw	$t0	-12($fp)
		lw	$t0	4($sp)
		sw	$t0	-16($fp)
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
		lw	$a0	-12($fp)
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
		lw	$a0	-16($fp)
		syscall
		li	$v0	10
		syscall
