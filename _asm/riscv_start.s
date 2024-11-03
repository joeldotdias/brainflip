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
