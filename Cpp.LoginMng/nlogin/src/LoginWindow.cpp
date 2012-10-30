

#include "LoginWindow.hpp"


using namespace nlogin;

LoginWindow* LoginWindow::instance = nullptr;


LoginWindow::LoginWindow()
{
	if(instance != nullptr)
		throw "Error";
		
	instance = this;
	
	// start ncurses
	initscr();
	raw();		
	
	//username
	//password
	
	//session
	//button shutdown
	
	
	//FIELD *new_field(int height, int width, int toprow, int leftcol, int offscreen, int nbuffers);
			
}

LoginWindow::~LoginWindow()
{
	instance = nullptr;
	
	endwin();
}
