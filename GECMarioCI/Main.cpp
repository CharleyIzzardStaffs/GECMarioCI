#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "constants.h"
#include <iostream>
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
using namespace std;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Mix_Music* g_music = nullptr;
//functions initiated
bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(string path);
int main(int argc, char* args[])
{
	bool quit = false;
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		g_old_time = SDL_GetTicks(); //start time
		while (!quit)
		{
			Render();
			quit = Update();
			LoadMusic("Images/Mario.mp3");
			if (Mix_PlayingMusic() == 0)
			{
				Mix_PlayMusic(g_music, -1);
			}
		}
		
	}
	return 0;
}
bool InitSDL()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "mixxer could not init Error:" << Mix_GetError();
		return false;
	}
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 	//setup SDL
	{
		cout << "SDL did not initialise. ERROR: " << SDL_GetError();
		return false;
	}
	else
	{
		g_window = SDL_CreateWindow("Sad Mario", //create window if setup success
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if (g_window == nullptr)
		{
			cout << "window was not created. ERROR: " << SDL_GetError();
			return false;
		}
	}
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (g_renderer != nullptr)
	{
		//init png
		int imageFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imageFlags) & imageFlags))
		{
			cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}
	}
	else
	{
		cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}
	SDL_Texture* LoadTextureFromFile(string path);
}
void CloseSDL()
{
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	IMG_Quit();
	SDL_Quit();
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
	delete game_screen_manager; //destroy game screen manager
	game_screen_manager = nullptr;
	Mix_FreeMusic(g_music);//clear up music
	g_music = nullptr;

}
bool Update()
{
	Uint32 new_time = SDL_GetTicks();
	SDL_Event e;
	SDL_PollEvent(&e);
	switch (e.type)
	{
		//click x = quit
	case SDL_QUIT:
		return true;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_SPACE:
			return true;
		}
		//quit on q pressed
	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button)
		{
		case SDL_BUTTON_RIGHT:
			return true;
		}
	}
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
}
void Render()
{
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(g_renderer);
	//g_texture->Render(Vector2D(), SDL_FLIP_NONE);
	game_screen_manager->Render();
	SDL_RenderPresent(g_renderer);
}
void LoadMusic(string path) {
	g_music = Mix_LoadMUS(path.c_str());
	if (g_music == nullptr) //basic error check
	{
		cout << "Failed to load music. Error: " << Mix_GetError() << endl;
	}

}





