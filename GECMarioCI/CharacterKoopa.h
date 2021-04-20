#pragma once
#include "Character.h"
class CharacterKoopa : public Character
{
private:
	float m_single_sprite_h;
	float m_single_sprite_w;
	bool m_injured;
	float m_injured_time;
	float m_movement_speed;
	void FlipRightWayUp();
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagepath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);;
	~CharacterKoopa();
	void Jump();
	void TakeDamage();
	virtual void Render();
	virtual void Update(float deltatime, SDL_Event e);
	bool GetInjured() { return m_injured; }
};

