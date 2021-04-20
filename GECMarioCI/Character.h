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
	float GetCollisionRadius();
	Rect2D GetCollisionBox() {
		return Rect2D(m_position.x, m_position.y,
			m_texture->GetWidth(), m_texture->GetHeight()); }
	bool IsJumping() { return m_jumping; }
	void CancelJump() { m_jumping = false; }
	bool SetAlive(bool isAlive) { m_alive = isAlive; return m_alive; }
	bool GetAlive() { return m_alive; }
	float Lives = 3;
private:
	LevelMap* m_current_level_map;
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	FACING m_facing_direction;
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();
	bool m_jumping;
	bool m_can_jump;
	bool m_moving_right;
	bool m_moving_left;
	bool m_alive;
	float m_jump_force;
	float m_collision_radius;
};

