
#ifndef SLD_window_H
#define SLD_window_H

#include <SDL.h>
#include "./fun_aux/Filme.hpp"
#include "./fun_aux/escena.hpp"
//include "./fun_aux/camera.hpp"

class SLD_window
{
	public:
		SLD_window();
		
		int OnExecute();
		bool OnInit();
		void OnEvent(SDL_Event *event);
		void OnExit();
		
	private:
		
	private:
		Filme filme_w;
		
		//qbRT::Scene m_scene;
		
		// SDL objetos
		bool isRunning;
		SDL_Window *sdl_win;
		SDL_Renderer *sdl_ren;
		
};

#endif
