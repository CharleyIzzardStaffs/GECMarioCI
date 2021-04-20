#include "GameScreenLevel1.h"
#include <iostream>
#include <string>
#include <sstream>
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
	m_enemies.clear();
}
void GameScreenLevel1::Render() 
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}
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
	UpdateEnemies(deltaTime, e);
	if (Mario->SetAlive(false)) {
		Mario->SetPositon(Vector2D(64, 330));
		Mario->SetAlive(true);
		cout << "Mario's Lives: " << Mario->Lives << endl;
	}
	if (Mario->Lives == 0) {
		cout << "Mario is out of lives!" << endl;
		SDL_Quit();
	}
	if (Luigi->SetAlive(false)) {
		Luigi->SetPositon(Vector2D(64, 330));
		Luigi->SetAlive(true);
		cout << "Luigi's Lives: " << Luigi->Lives << endl;
	}
	if (Luigi->Lives == 0) {
		cout << "Luigi is out of lives!" << endl;
		SDL_Quit();
	}
}
bool GameScreenLevel1::SetUpLevel() 
{
	SetLevelMap();
	Mario = new CharacterMario (m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	Luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(448, 330),m_level_map);
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("images/BackgroundMB.png")) 
	{
		cout << "Failed to load background texture" << endl;
		return false;
	}
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
	cout << "Mario's Lives: " << Mario->Lives << endl << "Luigi's Lives: " << Luigi->Lives << endl;

	
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
	for ( int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}
void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e) {
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[
					i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
					m_enemies[i]->SetAlive(false);
			}
			//now do the update
			m_enemies[i]->Update(deltaTime, e);
			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->
				GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], Mario))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//kill mario
						Mario->SetAlive(false);
					}
				}
				if (Collisions::Instance()->Circle(m_enemies[i], Luigi))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//kill mario
						Luigi->SetAlive(false);
					}
				}
			}
			if (!m_enemies[i]->GetAlive()) //if the enemy is no longer alive then schedule it for deletion
			{
				enemyIndexToDelete = i;
			}
		}
		if (enemyIndexToDelete != -1) //remove dead enemies -1 each update
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}
void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed) {

}