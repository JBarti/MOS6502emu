# NES emulator

For the time being we will focus on emulating the NES CPU, since I have absolutely no idea what I'm doing.

In this README file I will be writing information I had trouble finding on the internet.

The reason why I'm even creating this emulator is because I've been programming since I was 14 and I have noooo idea how any of the components of the computer work. Also I wanted to put my C programming skills to the test and create an interesting opensource project I can talk about.



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
   

*The status flag descriptions were copied from http://www.obelisk.me.uk/6502/registers.html#C*

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



## Opcode interpreting tips

Every CPU instruction consists of 3 bytes at most. The first byte being the opcode and all of the other are memory addresses or values. That is why every opcode method inside the code has one `byte opcode` and one `byte vals[2]` array as arguments. If the opcode has a 16-bit memory address as an argument it will be listed in little endian (for e.g. the command `ADC $1234` will compile to `60 34 12`). 

When dealing with the `ADC` opcode we can use this formula to determine the status `Overflow flag` value:  `(first_sumator ^ sum) & (second_sumator ^ sum) & 0x80`.

Emulating the `SBC` opcode can be done by calling the function that emulates `ADC` but with the two's complement of the number you have to subtract from the accumulator. The twos complement can be calculated by usin the formula: `~val + 1`.

The 6502c chip doesn't have an arithmetical shift operation despite there being an operation called `ASL -> arithmetical shift left`. That operation is actually a logical shift because it doesn't preserve the sign bit.

The operation `TXS -> transfer stack pointer to X` has a very confusing name and definition. When called the operation sets the value of the X register to the address that the stack pointer is currently pointing.


Currently supported opcodes are:

`ADC` : add with carry


## Stack implementation

I should probably write something about this.


## Running code

I used an assembler called xa65 to assemble the assembly language examples, the binary files can then be loaded into the emulator.

When the program starts the code is loaded into a memory address specified by the first line of the .asm source code file or noted by the developer.

I have noticed that on multiple online assemblers the program is loaded into the address space starting at `$6000` if nothing else is specified.

The `PC` is then set to point to the address where the code is loaded.


# Installation

The current stage of the emulator uses ncurses for vizualisation and debugging.

To install ncurses on debian based systems run:
`sudo apt-get install libncurses5-dev libncursesw5-dev`

To compile the code run: `make`.

After the code is compiled run `./main`.

I will probably make a better makefile when I learn how to do it properly :)

# References

This is the list of literature is used to develop this emulator: 

- http://www.obelisk.me.uk/6502/reference.html#ADC
  - Great reference for learning what each opcode does, but does not have enough info on addressing modes and two hardest opcodes to emulate `ADC` and `SBC`.
- https://yizhang82.dev/nes-emu-overview
  - Introduces you to the hardware of the NES and describes a good starting plan, awesome if you want to emulate the whole NES and not just the CPU but teaches how the CPU works in a larger system.
- https://www.youtube.com/watch?v=fWqBmmPQP40
  - Video from a conference where the dude who helped reverse engineer the original 6502C processor talks how they did it, very fun, very interesting.
- https://www.youtube.com/watch?v=LnzuMJLZRdU
  - Ben Eater has a whole series in how to build your own computer using the 6502C.

- https://www.youtube.com/watch?v=8XmxKPJDGU0
  - This guy pretty much explains how to do the whole emulator in a video, doesn't implement all of the opcodes tho. If you want a coding challenge, I would recommend you watch the first 15 minutes where he explains how the CPU works without writing code.
- http://6502.org/tools/asm/
  - A list of development tools that can help you debug your emulator and write code for it. There are some great online assemblers listed that you can use to compile 6502C assembly code into bytecode.
- http://wiki.nesdev.com/w/index.php/CPU
  - The nesdev wiki is a great resource where you can learn how the CPU communicates with other elements and how to write 6502C code. It contains other information about the chips inside the NES. The page is very well written and is a great starting point for noobs (that's why I also started there).

