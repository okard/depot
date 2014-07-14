
use reg = cpu::register;


struct Codespan
{
	source_id: u32,
	line: u32,
	column: u32
}

#[deriving(Show, PartialEq)]
pub enum Token
{
	EOF,
	Newline,
	
	Section(Box<String>), 		// .<ident>
	Label(Box<String>),			// @ident
	DataAddress(Box<String>),	// $ident
	Ident(Box<String>), 		// ident
	Macro(Box<String>),			// ~ident
	Constant(Box<String>),		// %+-bh num
	InternConst(Box<String>),	// \ident
	StringLiteral(Box<String>),	// "ident"
	RegIdent(reg::Register),
	
	SBOpen,			// [
	SBClose,		// ]
	Comma,			// ,
	Colon,			// :
}

pub fn lex(line: &str) -> Vec<Token>
{
	let mut toks = Vec::new();
	lex_tok(line, &mut toks);	
	toks
}



struct LexContext<'a>
{
	buf: & 'a str,
	start_pos: uint,
    pos: uint, 
    c: char, 
    toks: & 'a mut Vec<Token>,

}

fn read_ident(ctx: &mut LexContext) -> String
{
	//println!("read_ident");
	while ctx.pos < ctx.buf.len() && (ctx.c.is_alphanumeric() || ctx.c == '_') {
		next_char(ctx);
	}
	String::from_str(ctx.buf.slice(ctx.start_pos, ctx.pos))
}


fn read_string(ctx: &mut LexContext)
{
	while ctx.pos < ctx.buf.len() 
	&& ctx.c != '"' {
		next_char(ctx);
	}
	let name = box String::from_str(ctx.buf.slice(ctx.start_pos, ctx.pos));
	ctx.toks.push(StringLiteral(name));
	
	//skip trailing "
	assert!(ctx.c == '"');
	next_char(ctx);
}



#[inline]
fn next_char(ctx: &mut LexContext)
{
	//println!("next_char");
	ctx.pos += ctx.c.len_utf8_bytes();
	if ctx.pos >= ctx.buf.len() {
		return;
	}
	ctx.c = ctx.buf.char_at(ctx.pos);
}

fn lex_tok(buf: &str, toks: &mut Vec<Token>)
{
	let mut ctx = LexContext {
		buf : buf,
		start_pos : 0,
		pos : 0 ,
		c : '\0' ,
		toks : toks
	};
	
	ctx.c = ctx.buf.char_at(ctx.pos);
	
	//println!("line: {}", buf);
	
	// ignore whitespace
	if ctx.pos < ctx.buf.len() && ctx.c.is_whitespace() {
		next_char(&mut ctx);
	}
	ctx.start_pos = ctx.pos;
	
	// 
	match ctx.c
	{
		//ignore comments
		'#' => {
			while ctx.pos < ctx.buf.len() && ctx.c != '\n' {
				next_char(&mut ctx);
			}
			return;
		}
		
		//Section
		'.' => {
			//skip . 
			next_char(&mut ctx);
			ctx.start_pos += 1;
			let sec_name = box read_ident(&mut ctx);
			ctx.toks.push(Section(sec_name));
		} 
		
		'@' => {
			//skip @ 
			next_char(&mut ctx);
			ctx.start_pos += 1;
			let label_name = box read_ident(&mut ctx);
			ctx.toks.push(Label(label_name));
		}
		
		'$' => {
			//skip $
			next_char(&mut ctx);
			ctx.start_pos += 1;
			let name = box read_ident(&mut ctx);
			ctx.toks.push(DataAddress(name));
		}
		
		'~' => {
			//skip ~
			next_char(&mut ctx);
			ctx.start_pos += 1;
			let name = box read_ident(&mut ctx);
			ctx.toks.push(Macro(name));
		}
		
		'%' => {
			//skip %
			next_char(&mut ctx);
			ctx.start_pos += 1;
			
			match ctx.c
			{
				'+' => { next_char(&mut ctx);}
				'-' => { next_char(&mut ctx);}
				'b' => {next_char(&mut ctx);ctx.start_pos += 1; }
				'h' => {next_char(&mut ctx);ctx.start_pos += 1;}
				'0'..'9' => {}
				_ => { println!("%Literal Invalid char {}", ctx.c); }
			}
			
			//followed by b/h/+/-
			//followed by 0-9, HEX
			let name = box read_ident(&mut ctx);
			ctx.toks.push(Constant(name));
			
		}
		
		'\\' => {
			//skip \\
			next_char(&mut ctx);
			ctx.start_pos += 1;
			let name = box read_ident(&mut ctx);
			ctx.toks.push(InternConst(name));
		}
		
		',' => {
			next_char(&mut ctx);
			ctx.start_pos += 1;
			ctx.toks.push(Comma);
		}
		
		'[' => {
			next_char(&mut ctx);
			ctx.start_pos += 1;
			ctx.toks.push(SBOpen);
		}
		
		']' => {
			next_char(&mut ctx);
			ctx.start_pos += 1;
			ctx.toks.push(SBClose);
		}
		
		'"' => {
			//skip "
			next_char(&mut ctx);
			ctx.start_pos += 1;
			read_string(&mut ctx);
		}
		
		':' => {
			next_char(&mut ctx);
			ctx.start_pos += 1;
			ctx.toks.push(Colon);
		}
		
		_ => {}
	}
	
	//ident
	if ctx.c.is_alphanumeric() {
		while ctx.pos < ctx.buf.len() && (ctx.c.is_alphanumeric() || ctx.c == '_') 
		{
			next_char(&mut ctx);
		}
		
		let name = box String::from_str(ctx.buf.slice(ctx.start_pos, ctx.pos));
		let reg = get_register(&name);
		
		if reg.is_some() {
			ctx.toks.push(RegIdent(reg.unwrap()));
		}
		else {
			ctx.toks.push(Ident(name));
		}
	}
	

	//recursive
	if ctx.pos < ctx.buf.len() {
		lex_tok(ctx.buf.slice_from(ctx.pos), ctx.toks);
	}
	
}

fn get_register(s: &Box<String>) -> Option<reg::Register>
{
	match s.as_slice()
	{
		"reg_a" => Some(reg::REG_A),
		"reg_b" => Some(reg::REG_B),
		"reg_c" => Some(reg::REG_C),
		"reg_d" => Some(reg::REG_D),
		"loop" => Some(reg::LOOP),
		"cmp" => Some(reg::CMP),
		"PC" => Some(reg::PC),
		"ST" => Some(reg::ST),
		"FP" => Some(reg::FP),
		_ => None
	}
}


