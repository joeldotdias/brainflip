### start ###
.data
.equ SYS_EXIT, 93
.equ SUCCESS, 0
.equ SYS_WRITE, 64
.equ STDOUT, 1
.equ SYS_READ, 63
.equ STDIN, 0

.bss
.comm ARRAY, 30000

.text
.global _start
_start:
    la s2, ARRAY

	lb t0, 0(s2)
	addi t0, t0, 10
	sb t0, 0(s2)

	lb t0, 0(s2)
	beqz t0, LOOP_END_12

LOOP_START_1:

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 7
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 10
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 3
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, -4

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_1

LOOP_END_12:

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 2
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	lb t0, 0(s2)
	addi t0, t0, 7
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	lb t0, 0(s2)
	addi t0, t0, 3
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 2
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	addi s2, s2, -2

	lb t0, 0(s2)
	addi t0, t0, 15
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	addi s2, s2, 1

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	lb t0, 0(s2)
	addi t0, t0, 3
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	lb t0, 0(s2)
	addi t0, t0, -6
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	lb t0, 0(s2)
	addi t0, t0, -8
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	addi s2, s2, 1

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall
### end ###
    li a7, SYS_EXIT
    li a0, SUCCESS
    ecall
