
#include <memory>
#include <iostream>

#include <shellng/Source.hpp>
#include <shellng/Lexer.hpp>

using namespace sng;

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cerr << "Invalid arguments" << std::endl;
		return 1;
	}
	
	std::shared_ptr<Source> source;
   
	source.reset(new SourceFile());
	static_cast<SourceFile*>(source.get())->open(argv[1]);
   
	Lexer lex;
	Token tok;
	lex.open(source);
   
	while(lex.next(tok, true) != TokenID::TEOF)
	{
	   Lexer::print(tok);
	}
}
