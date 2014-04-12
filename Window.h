#ifndef WINDOW_H_INCLUED
#define WINDOW_H_INCLUED

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <string>
#include <vector>
#include "Error.h"
struct SingleWindow
{
	std::string		    title;
	SDL_Window		    *pWindow;
	unsigned	int	    width;
	unsigned	int 	height;
};

class Window
{
	public:
		Window(const std::string &title, unsigned int width, unsigned int height, bool fullscreen);
		virtual SDL_GLContext   CreateContext(unsigned int numWindow);
		virtual void            SwapWindow(unsigned int numWindow);
		virtual ~Window();

	protected:
		std::vector < SingleWindow >	m_vsWindow;
};

#endif