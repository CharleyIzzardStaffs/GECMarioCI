#pragma once
#include "Character.h"
class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, string imagepath, Vector2D start_position);
	~CharacterMario();
	virtual void Update(float deltatime, SDL_Event e);
private:
	CharacterMario* Mario;
};

