#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"

//class Character;
class CharacterLuigi;
class CharactrerMario;
class Texture2D;
class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	CharacterMario* Mario;
	CharacterLuigi* Luigi;
};
#endif //_GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"