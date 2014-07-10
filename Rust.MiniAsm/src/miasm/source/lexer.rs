
struct Codespan
{
	source_id: u32,
	line: u32,
	column: u32
}

pub enum Token
{
	EOF,
	Newline,
	
	Section, 		// .<ident>
	Label,			// @ident
	DataAddress,	// $ident
	Ident, 			// ident
	Macro,			// ~ident
	Constant,		// %+-bh num
	InternConst,	// \ident
	StringLiteral,	// "ident"
	
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



struct lex_context<'a>
{
	buf: & 'a str,
	start_pos: uint,
    pos: uint, 
    c: char, 
    toks: & 'a mut Vec<Token>,

}

pub fn read_ident(ctx: &mut lex_context, t: Token)
{
	//println!("read_ident");
	while ctx.pos < ctx.buf.len() && (ctx.c.is_alphanumeric() || ctx.c == '_') {
		next_char(ctx);
	}
	ctx.toks.push(t);
	println!("-> {}",ctx.buf.slice(ctx.start_pos, ctx.pos));
}

#[inline]
fn next_char(ctx: &mut lex_context)
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
	let mut ctx = lex_context {
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
			read_ident(&mut ctx, Section);
		} 
		
		'@' => {
			//skip @ 
			next_char(&mut ctx);
			ctx.start_pos += 1;
			read_ident(&mut ctx, Label);
		}
		
		'$' => {
			//skip $
			next_char(&mut ctx);
			ctx.start_pos += 1;
			read_ident(&mut ctx, DataAddress);
		}
		
		'~' => {
			//skip ~
			next_char(&mut ctx);
			ctx.start_pos += 1;
			read_ident(&mut ctx, Macro);
		}
		
		'%' => {
			//skip %
			next_char(&mut ctx);
			ctx.start_pos += 1;
			
			//followed by b/h/+/-
			//followed by 0-9, HEX
			read_ident(&mut ctx, Constant);
		}
		
		'\\' => {
			//skip \\
			next_char(&mut ctx);
			ctx.start_pos += 1;
			read_ident(&mut ctx, InternConst);
		}
		
		',' => {
			next_char(&mut ctx);
			ctx.start_pos += 1;
		}
		
		'[' => {
			next_char(&mut ctx);
			ctx.start_pos += 1;
		}
		
		']' => {
			next_char(&mut ctx);
			ctx.start_pos += 1;
		}
		
		'"' => {
			next_char(&mut ctx);
			ctx.start_pos += 1;
		}
		
		':' => {
			next_char(&mut ctx);
			ctx.start_pos += 1;
		}
		
		'-' => {
			next_char(&mut ctx);
			ctx.start_pos += 1;
		}
		
		_ => {}
	}
	
	//ident
	if ctx.c.is_alphanumeric() {
		while ctx.pos < ctx.buf.len() && (ctx.c.is_alphanumeric() || ctx.c == '_') 
		{
			next_char(&mut ctx);
		}
		ctx.toks.push(Ident);
		println!("Ident: {}",ctx.buf.slice(ctx.start_pos, ctx.pos))
	}
	

	//recursive
	if ctx.pos < ctx.buf.len() {
		lex_tok(ctx.buf.slice_from(ctx.pos), ctx.toks);
	}
	
}


