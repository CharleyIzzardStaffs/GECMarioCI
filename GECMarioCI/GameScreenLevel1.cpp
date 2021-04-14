#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "Character.h"
using namespace std;
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) //constructor
{
	m_renderer = renderer;
	SetUpLevel();
}
GameScreenLevel1::~GameScreenLevel1() //destructor
{
	m_renderer = nullptr;
	delete m_background_texture;
	m_background_texture = nullptr;
	delete Mario;
	Mario = nullptr;
	delete Luigi;
	Luigi = nullptr;
}
void GameScreenLevel1::Render() 
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE); //draw the background
	Mario->Render();
	Luigi->Render();
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);
	if (Collisions::Instance()->Circle(Mario, Luigi)) {
		cout << "Circle hit!" << endl;
	}
	if (Collisions::Instance()->Box(Mario->GetCollisionBox(),Luigi->GetCollisionBox())) {
		cout << "Box hit!" << endl;
	}
}
bool GameScreenLevel1::SetUpLevel() 
{
	Mario = new CharacterMario (m_renderer, "Images/Mario.png", Vector2D(64, 330));
	Luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 360));
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("images/test.bmp")) 
	{
		cout << "Failed to load background texture" << endl;
		return false;
	}
}

