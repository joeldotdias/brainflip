# Brainflip

Currently targets x86_64 and RISC-V 64-bit.

All emitted assembly files are in the `out` directory.

## Usage
Change the compiler in the Makefile if needed and run `make` to build the binary.

### For x86_64
- Requires `clang`
```
brainflip <file>
# then, compile the emitted assembly file
# if "hello_x86.s" was produced
clang -nostdlib -no-pie -fno-integrated-as -Wa,-msyntax=intel,-mnaked-reg -s out/hello_x86.s -o hello.out
# run the binary
./hello.out
```

### For RISC-V
- Requires `riscv64-linux-gnu-gcc`, `qemu-user-static`
```
brainflip <file> riscv
# if "hello_riscv.s" was produced
riscv64-linux-gnu-as hello_riscv.s -o hello.o
riscv64-linux-gnu-ld hello.o -o hello
# run the binary with qemu
qemu-riscv64-static ./hello
```
