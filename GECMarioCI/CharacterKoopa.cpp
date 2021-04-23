#include "CharacterKoopa.h"
CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, string imagepath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) : Character(renderer, imagepath, start_position, map) {
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;
	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}
CharacterKoopa::~CharacterKoopa() {

}
void CharacterKoopa::Update(float deltatime, SDL_Event e) {
	Character::Update(deltatime, e);
	if (!m_injured) { //if not injured move
		if (m_facing_direction == FACING_LEFT) {
			m_moving_left = true;
			m_moving_right = false;
		}
		if (m_facing_direction == FACING_RIGHT) {
			m_moving_left = false;
			m_moving_right = true;
		}
	}
	else {
		m_moving_left = false; // stop moving when hurt
		m_moving_right = false;
		m_injured_time -= deltatime; //stop moving for this long
		if (m_injured_time <= 0.0f)
			FlipRightWayUp();
	}

}
void CharacterKoopa::Jump() {
	if (!m_jumping) {
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}
}
void CharacterKoopa::TakeDamage() {
	m_injured = true;
	m_injured_time = KOOPA_DAMAGE_TIME;
	Jump();
}
void CharacterKoopa::FlipRightWayUp() {
	m_facing_direction = FACING_RIGHT;
	m_injured = false;
	Jump();
}
void CharacterKoopa::Render() {
	int left = 0.0f; //variable to hold the left position of the sprite we want to draw
	if (m_injured) //if injured move the left position to be the left position of the second image of the sprite sheet
		left = m_single_sprite_w;		   
	SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h }; //get the portion of the sprite sheet you want to draw {xPos, yPos, width of sprite, height of sprite}		
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h }; //determine where you want it drawn
	if (m_facing_direction == FACING_RIGHT) //then draw it facing the correct direction
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}
