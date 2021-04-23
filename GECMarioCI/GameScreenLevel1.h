#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "LevelMap.h"
#include <vector>
//class Character;
class CharacterLuigi;
class CharactrerMario;
class Texture2D;
class PowBlock;
class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	CharacterMario* Mario;
	CharacterLuigi* Luigi;
	void SetLevelMap();
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	void DoScreenShake();
	void UpdateEnemies(float deltatime, SDL_Event e);
	CharacterKoopa* Koopa;
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	vector<CharacterKoopa*> m_enemies;
protected:
	bool m_alive;
};
#endif //_GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include <vector>