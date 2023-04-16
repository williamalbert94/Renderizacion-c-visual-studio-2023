#include "source.h"

const int heigth = 100;
const int weigth = 100;

/* ***********************************************************

Aqui llamaremos el resultado de la renderizacion con el modelo phong.
como la idea es usar una ventana y/o cavnas, primero llamaremos este
lo inicializamos, creamos un plano o filme, hacemos el render,
y por ultimo actualizamos


Este código es parte de una clase llamada SLD_window que se encarga de inicializar una ventana de SDL y 
controlar su ciclo de vida.

En el constructor de la clase, se inicializan tres variables miembro: isRunning, sdl_win y sdl_ren. 
La variable isRunning se usa para indicar si la ventana está en ejecución o no. Las variables sdl_win y 
sdl_ren son punteros a la ventana y el renderizador de SDL, respectivamente, y se inicializan con un valor nulo.

La función OnInit() se llama al iniciar la ventana y se encarga de inicializar SDL y crear la ventana 
y el renderizador. Si se produce algún error durante la inicialización, la función devuelve false.

La función OnExecute() es el bucle principal del programa y se ejecuta hasta que isRunning se
establece en false. Dentro del bucle, se utiliza la función SDL_PollEvent() para detectar eventos y 
se llama a la función OnEvent() para manejarlos.

La función OnEvent() se llama cuando se detecta un evento. En este caso, la función verifica 
si el evento es del tipo SDL_QUIT (que se produce cuando el usuario cierra la ventana) y, 
si es así, establece isRunning en false.

Por último, la función OnExit() se llama cuando se cierra 
la ventana y se encarga de liberar la memoria de los recursos de SDL
que se utilizaron en la ventana (el renderizador y la ventana) y llama a 
la función SDL_Quit() para cerrar SDL.

***********************************************************/
SLD_window::SLD_window()
{
	isRunning = true;
	sdl_win = NULL;
	sdl_ren = NULL;
}

bool SLD_window::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}
	
	sdl_win = SDL_CreateWindow("test1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, heigth, weigth, SDL_WINDOW_SHOWN);
	
	if (sdl_win != NULL)
	{
		sdl_ren = SDL_CreateRenderer(sdl_win, -1, 0);
		
		// inicio el sdl abriendo un cavnas
		filme_w.Initialize(heigth, weigth, sdl_ren);
		
		// pantalla blanca
		SDL_SetRenderDrawColor(sdl_ren, 255, 255, 255, 255);
		SDL_RenderClear(sdl_ren);
		

		filme_w.Display();
		

		SDL_RenderPresent(sdl_ren);
		
	}
	else
	{
		return false;
	}
	
	return true;
}

int SLD_window::OnExecute()
{
	SDL_Event event;
	
	if (OnInit() == false)
	{
		return -1;
	}
	
	while (isRunning)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			OnEvent(&event);
		}
	}
	
	OnExit();
	return 0;
}

void SLD_window::OnEvent(SDL_Event *event)
{
	if (event->type == SDL_QUIT)
	{
		isRunning = false;
	}
}

void SLD_window::OnExit()
{
	SDL_DestroyRenderer(sdl_ren);
	SDL_DestroyWindow(sdl_win);
	sdl_win = NULL;
	SDL_Quit();
}




























