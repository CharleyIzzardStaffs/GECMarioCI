#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "Collisions.h"
#include "Character.h"
#include "PowBlock.h"
using namespace std;
GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) //constructor
{
	m_renderer = renderer;
	m_level_map = nullptr;
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
	m_level_map = nullptr;
	m_pow_block = nullptr;
}
void GameScreenLevel1::Render() 
{
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE); //draw the background
	Mario->Render();
	Luigi->Render();
	m_pow_block->Render();
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake) {
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;
		if (m_shake_time <= 0.0f) {
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);
	if (Collisions::Instance()->Circle(Mario, Luigi)) {
		cout << "Circle hit!" << endl;
	}
	if (Collisions::Instance()->Box(Mario->GetCollisionBox(),Luigi->GetCollisionBox())) {
		cout << "Box hit!" << endl;
	}
	UpdatePOWBlock();
}
bool GameScreenLevel1::SetUpLevel() 
{
	SetLevelMap();
	Mario = new CharacterMario (m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	Luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(64, 360),m_level_map);
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("images/BackgroundMB.png")) 
	{
		cout << "Failed to load background texture" << endl;
		return false;
	}
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
}
void GameScreenLevel1::SetLevelMap() {
		int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										 { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										 { 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										 { 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										 { 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										 { 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										 { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										 { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
		if (m_level_map != nullptr)
		{
			delete m_level_map; //clear old map
		}
		m_level_map = new LevelMap(map); //load new map

}
void GameScreenLevel1::UpdatePOWBlock() {
	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), Mario->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (Mario->IsJumping()) //collided while jumping
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				Mario->CancelJump();
			}

		}
	}
	if (Collisions::Instance()->Box(m_pow_block->GetCollisionBox(), Luigi->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable())
		{
			if (Luigi->IsJumping()) //collided while jumping
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				Luigi->CancelJump();
			}
		}
	}
}
void GameScreenLevel1::DoScreenShake() {
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}

