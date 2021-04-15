#pragma once
#include <SDL.h>
#include <iostream>
#include "Constants.h"
#include "Commons.h"
#include "Character.h"
#include "Texture2D.h"
#include "LevelMap.h"
using namespace std;
class Texture2D;
class Character
{
public:
	Character(SDL_Renderer* renderer, string impagePath, Vector2D start_position, LevelMap* map);
	~Character();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPositon(Vector2D new_position);
	Vector2D GetPosition();
	virtual void AddGravity(float deltaTime);
	float GetCollisionRadius();
	Rect2D GetCollisionBox() {
		return Rect2D(m_position.x, m_position.y,
			m_texture->GetWidth(), m_texture->GetHeight());
	}
private:
	LevelMap* m_current_level_map;
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
	float m_collision_radius;
	FACING m_facing_direction;
};

