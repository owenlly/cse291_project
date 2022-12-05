	.file	"test1.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"i = %d\n"
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	li	a5,1
	sw	a5,-24(s0)
	li	a5,2
	sw	a5,-28(s0)
	li	a5,3
	sw	a5,-32(s0)
	lw	a5,-24(s0)
	mulw	a5,a5,a5
	sext.w	a5,a5
	lw	a4,-24(s0)
	mulw	a5,a4,a5
	sext.w	a4,a5
	lw	a5,-28(s0)
	mulw	a5,a5,a5
	sext.w	a5,a5
	lw	a3,-28(s0)
	mulw	a5,a3,a5
	sext.w	a5,a5
	addw	a5,a4,a5
	sext.w	a4,a5
	lw	a5,-32(s0)
	mulw	a5,a5,a5
	sext.w	a5,a5
	lw	a3,-32(s0)
	mulw	a5,a3,a5
	sext.w	a5,a5
	addw	a5,a4,a5
	sext.w	a4,a5
	lw	a5,-24(s0)
	mv	a3,a5
	lw	a5,-28(s0)
	mulw	a5,a3,a5
	sext.w	a5,a5
	lw	a3,-32(s0)
	mulw	a5,a3,a5
	sext.w	a5,a5
	addw	a5,a4,a5
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	sext.w	a5,a5
	bge	a5,zero,.L2
	lw	a5,-20(s0)
	addiw	a5,a5,1
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	mulw	a5,a5,a5
	sw	a5,-20(s0)
	j	.L3
.L2:
	lw	a5,-20(s0)
	mulw	a5,a5,a5
	sw	a5,-20(s0)
.L3:
	lw	a5,-20(s0)
	mv	a1,a5
	lui	a5,%hi(.LC0)
	addi	a0,a5,%lo(.LC0)
	call	printf
	li	a5,0
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (g2ee5e430018) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
