use cpu::register::{Register};

#[allow(non_camel_case_types)]
#[deriving(FromPrimitive)]
pub enum OpCode
{
	NOP = 0,
	MOV_R_C = 1,
	MOV_R_R = 2,
	ADD_R_R,
	
	LOAD_R_RA_C,
	
	CMP_R_R,
	CMP_R_C,
}

//helper methods


pub type Instr = u32;


pub fn set_instr(instr: &mut Instr, op: OpCode, r1: Register, r2: Register)
{
	//layout: 
	//check layout? bit size of enum values
	
	*instr = 0;
	*instr |= op as Instr << 26; // 26 bit shift op code at 'front'
	*instr |= r1 as Instr << 22; // 4 bit register
	*instr |= r2 as Instr << 18; // 4 bit register
}

pub fn set_instr_r_c(instr: &mut Instr, op: OpCode, r1: Register, c: u32)
{
	//layout: 
	//check layout? bit size of enum values
	
	*instr = 0;
	*instr |= op as Instr << 26; // 26 bit shift op code at 'front'
	*instr |= r1 as Instr << 22; // 4 bit register
	*instr |= c as Instr << 4;   // 16 bit constant
}

pub fn get_op(instr: Instr) -> OpCode
{
	FromPrimitive::from_u32((instr & 0xFC000000) >> 26).unwrap()
}

pub fn get_reg1(instr: Instr) -> Register
{
	FromPrimitive::from_u32((instr & 0x03C00000) >> 22).unwrap()
}

pub fn get_reg2(instr: Instr) -> Register
{
	FromPrimitive::from_u32((instr & 0x003C0000) >> 18).unwrap()
}

pub fn get_c1(instr: Instr) -> u32
{
	0
}

