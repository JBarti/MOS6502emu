# NES emulator

For the time being we will focus on emulating the NES CPU, since I have absolutely no idea what I'm doing.

## BUS

All of the devices that the processor communicates with are connected to a bus and are given a certain address space. The processor can send a read or a write command to a certain address which corresponds to a device on the bus.

For the time being the only thing connected to our bus will be the RAM chip occupying the whole address space.


**RAM**: 0x0000 - 0xffff (64 kB)


## CPU

The NES uses a modified version of the 6502C 8-bit processor used in the Commodore and Apple II computers. The most notable modification is that the processor doesn't use the decimal mode.

The CPU contains 3 8-bit registers used for storing an 8-bit number:
 - A: accumulator
 - X: register
 - Y: register

In addition we have:
 - SP: stack pointer
 - PC: program counter
 - status register

The status register contains flags that allow us to inspect the state of the CPU:
 - C: Carry flag
 - Z: Zero flag
 - I: Interrupt disable
 - D: Decimal mode flag
 - B: Break command
 - V: Overflow flag
 - N: Negative flag


**Carry Flag**

The carry flag is set if the last operation caused an overflow from bit 7 of the result or an underflow from bit 0. This condition is set during arithmetic, comparison and during logical shifts. It can be explicitly set using the 'Set Carry Flag' (SEC) instruction and cleared with 'Clear Carry Flag' (CLC).

**Zero Flag**

The zero flag is set if the result of the last operation as was zero.

**Interrupt Disable**

The interrupt disable flag is set if the program has executed a 'Set Interrupt Disable' (SEI) instruction. While this flag is set the processor will not respond to interrupts from devices until it is cleared by a 'Clear Interrupt Disable' (CLI) instruction.

**Decimal Mode (unused)**

While the decimal mode flag is set the processor will obey the rules of Binary Coded Decimal (BCD) arithmetic during addition and subtraction. The flag can be explicitly set using 'Set Decimal Flag' (SED) and cleared with 'Clear Decimal Flag' (CLD).

**Break Command**

The break command bit is set when a BRK instruction has been executed and an interrupt has been generated to process it.

**Overflow Flag**

The overflow flag is set during arithmetic operations if the result has yielded an invalid 2's complement result (e.g. adding to positive numbers and ending up with a negative result: 64 + 64 => -128). It is determined by looking at the carry between bits 6 and 7 and between bit 7 and the carry flag.

**Negative Flag**

The negative flag is set if the result of the last operation had bit 7 set to a one.



## Running code

When the program starts the code is loaded into a memory address specified by the first line of the .asm source code file or noted in a way by the developer.

The PC is then set to point to the address where the code is loaded.


# Installation

The current stage of the emulator uses ncurses for visualisation and debuging.

To install ncurses on debian based systems run:
`sudo apt-get install libncurses5-dev libncursesw5-dev`

To compile the code run: `make`.

After the code is compiled run `./main`.
