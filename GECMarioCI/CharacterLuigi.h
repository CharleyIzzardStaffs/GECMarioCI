#pragma once
#include "Character.h"
class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, string imagepath, Vector2D start_position);
	~CharacterLuigi();
	virtual void Update(float deltatime, SDL_Event e);
private:
	CharacterLuigi* Luigi;
};

