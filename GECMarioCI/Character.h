#pragma once
#include <SDL.h>
#include <iostream>
#include "Constants.h"
#include "Commons.h"
using namespace std;
class Texture2D;
class Character
{
public:
	Character(SDL_Renderer* renderer, string impagePath, Vector2D start_position);
	~Character();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPositon(Vector2D new_position);
	Vector2D GetPosition();
	virtual void AddGravity(float deltaTime);
private:
	FACING m_facing_direction;
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	bool m_moving_right;
	bool m_moving_left;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
	virtual void Jump();
};

