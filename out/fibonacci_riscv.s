### start ###
.data
.equ SYS_EXIT, 93    # RISC-V exit syscall number
.equ SUCCESS, 9
.equ SYS_WRITE, 64   # RISC-V write syscall number
.equ STDOUT, 1
.equ SYS_READ, 63    # RISC-V read syscall number
.equ STDIN, 0

.bss
.comm ARRAY, 30000   # RISC-V uses .comm instead of .lcomm

.text
.global _start
_start:
    la s2, ARRAY     # s2 will be our pointer register (equivalent to r12)

	lb t0, 0(s2)
	beqz t0, LOOP_END_8

LOOP_START_0:

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
	addi t0, t0, -1
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	li a7, SYS_READ
	li a0, STDIN
	mv a1, s2
	li a2, 1
	ecall

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	li a7, SYS_READ
	li a0, STDIN
	mv a1, s2
	li a2, 1
	ecall

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
	bnez t0, LOOP_START_0

LOOP_END_8:

	lb t0, 0(s2)
	addi t0, t0, 11
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 4

	lb t0, 0(s2)
	addi t0, t0, 44
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 32
	sb t0, 0(s2)

	addi s2, s2, -6

	lb t0, 0(s2)
	beqz t0, LOOP_END_200

LOOP_START_17:

	addi s2, s2, 1

	lb t0, 0(s2)
	beqz t0, LOOP_END_26

LOOP_START_19:

	addi s2, s2, 6

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, -7

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_19

LOOP_END_26:

	addi s2, s2, 7

	lb t0, 0(s2)
	beqz t0, LOOP_END_33

LOOP_START_28:

	addi s2, s2, -7

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 7

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_28

LOOP_END_33:

	addi s2, s2, -1

	lb t0, 0(s2)
	beqz t0, LOOP_END_119

LOOP_START_35:

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 10
	sb t0, 0(s2)

	lb t0, 0(s2)
	beqz t0, LOOP_END_82

LOOP_START_38:

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	addi s2, s2, -1

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	beqz t0, LOOP_END_49

LOOP_START_42:

	addi s2, s2, 2

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, -3

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_42

LOOP_END_49:

	addi s2, s2, 3

	lb t0, 0(s2)
	beqz t0, LOOP_END_56

LOOP_START_51:

	addi s2, s2, -3

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 3

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_51

LOOP_END_56:

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, -1

	lb t0, 0(s2)
	beqz t0, LOOP_END_67

LOOP_START_59:

	addi s2, s2, 1

	lb t0, 0(s2)
	beqz t0, LOOP_END_63

LOOP_START_61:

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_61

LOOP_END_63:

	addi s2, s2, -1

	lb t0, 0(s2)
	beqz t0, LOOP_END_67

LOOP_START_65:

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_65

LOOP_END_67:

	addi s2, s2, 1

	lb t0, 0(s2)
	beqz t0, LOOP_END_80

LOOP_START_69:

	addi s2, s2, -2

	lb t0, 0(s2)
	beqz t0, LOOP_END_76

LOOP_START_71:

	addi s2, s2, 3

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, -3

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_71

LOOP_END_76:

	addi s2, s2, 2

	lb t0, 0(s2)
	beqz t0, LOOP_END_80

LOOP_START_78:

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_78

LOOP_END_80:

	addi s2, s2, -2

	lb t0, 0(s2)
	bnez t0, LOOP_START_38

LOOP_END_82:

	addi s2, s2, 3

	lb t0, 0(s2)
	beqz t0, LOOP_END_91

LOOP_START_84:

	addi s2, s2, 2

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, -3

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_84

LOOP_END_91:

	addi s2, s2, 3

	lb t0, 0(s2)
	beqz t0, LOOP_END_98

LOOP_START_93:

	addi s2, s2, -3

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 3

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_93

LOOP_END_98:

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, -1

	lb t0, 0(s2)
	beqz t0, LOOP_END_109

LOOP_START_101:

	addi s2, s2, 1

	lb t0, 0(s2)
	beqz t0, LOOP_END_105

LOOP_START_103:

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_103

LOOP_END_105:

	addi s2, s2, -1

	lb t0, 0(s2)
	beqz t0, LOOP_END_109

LOOP_START_107:

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_107

LOOP_END_109:

	addi s2, s2, 1

	lb t0, 0(s2)
	beqz t0, LOOP_END_117

LOOP_START_111:

	addi s2, s2, -2

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 2

	lb t0, 0(s2)
	beqz t0, LOOP_END_117

LOOP_START_115:

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_115

LOOP_END_117:

	addi s2, s2, -7

	lb t0, 0(s2)
	bnez t0, LOOP_START_35

LOOP_END_119:

	addi s2, s2, 5

	lb t0, 0(s2)
	beqz t0, LOOP_END_126

LOOP_START_121:

	lb t0, 0(s2)
	addi t0, t0, 48
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	lb t0, 0(s2)
	beqz t0, LOOP_END_126

LOOP_START_124:

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_124

LOOP_END_126:

	lb t0, 0(s2)
	addi t0, t0, 10
	sb t0, 0(s2)

	addi s2, s2, -1

	lb t0, 0(s2)
	beqz t0, LOOP_END_134

LOOP_START_129:

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	addi s2, s2, -1

	lb t0, 0(s2)
	bnez t0, LOOP_START_129

LOOP_END_134:

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 48
	sb t0, 0(s2)

	li a7, SYS_WRITE
	li a0, STDOUT
	mv a1, s2
	li a2, 1
	ecall

	lb t0, 0(s2)
	beqz t0, LOOP_END_140

LOOP_START_138:

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_138

LOOP_END_140:

	addi s2, s2, -12

	lb t0, 0(s2)
	beqz t0, LOOP_END_149

LOOP_START_142:

	addi s2, s2, 3

	lb t0, 0(s2)
	addi t0, t0, 1
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
	bnez t0, LOOP_START_142

LOOP_END_149:

	addi s2, s2, 4

	lb t0, 0(s2)
	beqz t0, LOOP_END_156

LOOP_START_151:

	addi s2, s2, -4

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 4

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_151

LOOP_END_156:

	addi s2, s2, -1

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	beqz t0, LOOP_END_167

LOOP_START_159:

	addi s2, s2, 2

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

	addi s2, s2, -3

	lb t0, 0(s2)
	beqz t0, LOOP_END_167

LOOP_START_165:

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_165

LOOP_END_167:

	addi s2, s2, -2

	lb t0, 0(s2)
	beqz t0, LOOP_END_176

LOOP_START_169:

	addi s2, s2, 2

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, -3

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_169

LOOP_END_176:

	addi s2, s2, 3

	lb t0, 0(s2)
	beqz t0, LOOP_END_183

LOOP_START_178:

	addi s2, s2, -3

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 3

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_178

LOOP_END_183:

	addi s2, s2, -2

	lb t0, 0(s2)
	beqz t0, LOOP_END_190

LOOP_START_185:

	addi s2, s2, -1

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_185

LOOP_END_190:

	addi s2, s2, 1

	lb t0, 0(s2)
	beqz t0, LOOP_END_197

LOOP_START_192:

	addi s2, s2, -1

	lb t0, 0(s2)
	addi t0, t0, 1
	sb t0, 0(s2)

	addi s2, s2, 1

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_192

LOOP_END_197:

	addi s2, s2, -3

	lb t0, 0(s2)
	addi t0, t0, -1
	sb t0, 0(s2)

	lb t0, 0(s2)
	bnez t0, LOOP_START_17

LOOP_END_200:
### end ###
    li a7, SYS_EXIT      # Exit syscall number
    li a0, SUCCESS       # Exit code
    ecall               # Make the syscall
