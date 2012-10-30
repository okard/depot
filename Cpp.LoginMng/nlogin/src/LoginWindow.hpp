

#pragma once
#ifndef __NLOGIN_LOGINWINDOW_HPP__
#define __NLOGIN_LOGINWINDOW_HPP__


#include <ncurses.h>

namespace nlogin
{

/**
* Ncurses Login Window
*/
class LoginWindow
{
private:
	WINDOW *main_window;
	
	static LoginWindow* instance;
	
public:
	LoginWindow();
	~LoginWindow();
	
	
	//initscr();			/* Start curses mode 		*/
	//raw();				/* Line buffering disabled	*/
	//my_win = create_newwin(height, width, starty, startx);
	/*
	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);	
	wrefresh(local_win);		
	return local_win;
	*/
	
};
	 
	 
} // end namespace nlogin


#endif // __NLOGIN_LOGINWINDOW_HPP__
