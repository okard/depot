# Mini Assembler



## CPU

* Only 32 bit integer numbers
* 32 bit adresses
* each address contains a 32 bit value
* no 16, 64 bit modes for simplicity
* not optimized
* .data and stack lies in memory
* code seperated at the moment (so PC doesn't point to mem)

Register 

* PC - Program Counter
* ST - Stack Pointer

* FCT	- Function Register
* Frame pointer
* input register?
* INTERNAL

Safe register:

* REGA
* REGB
* REGC
* REGD
* REGF
* CMP	- Compare Result Register (-1, 0, +1)
* LC	- Loop Counter



## Instructions


### Basic Layout

* 32 Bit Size
* 6 Bit OpCode (64 instruktionen)
* 4 Bit Register (16 register max?)
* 16 Bit Constants signed Two's complement

Instruction types: 

* R/C -> Register / Constant
	6 + 4 +  22 Bit Constant (twos complement)

* R/R/C 
	6 + 4 + 4 + 18 Bit Constant  (twos complement)



Elements

* Register
* Memory
* Constant


### Op Codes

The opcode here also contains the register/constant specification
	value/address etc

Arithmetic

* MOV 		R(V), C
* MOV		R(V), R(V)

* ADD 		R(V), R(V)
* ADD 		R(V), C(V)

* SUB 		R(V), R(V)
* SUB 		R(V), C(V)

* MUL 		R(V), R(V)
* MUL 		R(V), C(V)

* DIV 		R(V), R(V)
* DIV 		R(V), C(V)

* SHIFT

* NOT
* NEG
* POS

Memory

* PUSH 		C(space)
* PUSHV 	C(V)
* POP
* POP 		R(*)
* LOAD		R(A)
* LOAD 		R(*), R(A), C
* STORE 	R(A), R(V)
* STORE 	R(*), R(A), C

Control

* CMP		R(*), R(*)
* JMP		C(A)	absolute?
* JMPEQ		C(A)
* JMPLT		C(A)
* JMPGT		C(A)
* JMPLE		C(A)
* JMPGE		C(A)


Special

* Syscalls (Virtual Calls)
	* PRINT
	* READ
* NOP

### Macros

Macros are syntax shortcuts for humans, 
hide many instructions behind one

Macros

* CALL
* RET

Syscall Macros:

* PRINTV R(*,V)
* PRINTA R(*,A)
* PRINTS R(A)

* READN R(V)


## Function/Stack Frames 

* Return address


* Bare Calls and Rets
	- Don't safe any stuff
* Calls, Rets
	- More comfortable

## Syntax

Regions
	.ident
	
Labels:
	@ident

Line Comments:
	# comment...

Addresses
	$ident 	- address of a data defintion
	
Register
	ident

Constants (32bit)

	%5
	%+3
	%-8
	%xEFEF
	%b101010101
	
Prefix Macro commands?
	~call
	
Special internal constants? (Print formats?)
	\num			= 0
	\num_hex		= 1
	\num_bin		= 2
	\address		= 3
	\str			= 4
	
Optional Shifts/Args
	[FC, %-2]

## Macro Commands

Templates for macro commands, macro commands only exist in source code representation to make life easier

## Conventions

