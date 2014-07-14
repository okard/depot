
#[allow(non_camel_case_types)]
#[deriving(Show, PartialEq)]
#[deriving(FromPrimitive)]
pub enum Register
{
	REG_A 	= 0,
	REG_B 	= 1,
	REG_C 	= 2,
	REG_D 	= 3,
	LOOP 	= 4,
	CMP 	= 5,
	
	
	PC 		= 6, // Program Counter
	ST 		= 7, // Stack Pointer
	FP		= 8, // Frame Pointer
}
