### start ###
.data
.equ SYS_EXIT, 93
.equ SUCCESS, 9
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
