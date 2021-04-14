#include <SDL.h>
#include "GameScreen.h"
#include <iostream>
using namespace std;
GameScreen::GameScreen(SDL_Renderer* renderer) //constructor
{
	m_renderer = renderer;
}
GameScreen::~GameScreen() //destructor
{
	m_renderer = nullptr;
}
void GameScreen::Render() 
{
	//testing
}
void GameScreen::Update(float deltaTime, SDL_Event e) 
{
}

