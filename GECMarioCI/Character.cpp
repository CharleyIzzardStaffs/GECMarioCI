#include "Character.h"
#include "Texture2D.h"

Character::Character(SDL_Renderer* renderer, string impagePath, Vector2D start_position) { //constructor
	m_renderer = renderer;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(impagePath))
		cout << "Failed to Load Image" << endl;
	/*m_facing_direction = FACING_RIGHT;*/
	m_moving_left = false;
	m_moving_right = false;
	m_collision_radius = 15.0f;
}
Character::~Character() {
	m_renderer = nullptr;
}
void Character::Render() {
	m_texture->Render(m_position, SDL_FLIP_NONE);
	if (m_facing_direction == FACING_RIGHT)
		m_texture->Render(m_position, SDL_FLIP_NONE);
	if (m_facing_direction == FACING_LEFT)
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
}
void Character::Update(float deltaTime, SDL_Event e) {
	if (m_jumping){ //jumping first
		m_position.y -= m_jump_force * deltaTime;
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;
		if (m_jump_force <= 0.0f)
			m_jumping = false;
	}
	if (m_moving_left) {
		MoveLeft(deltaTime);
	}
	if (m_moving_right) {
		MoveRight(deltaTime);
	}
	AddGravity(deltaTime);
}
void Character::SetPositon(Vector2D new_position) {
	m_position = new_position;
}
Vector2D Character::GetPosition() {
	return m_position;
}
void Character::MoveRight(float deltatime){
	m_position.x += deltatime * MOVEMENTSPEED;
	m_facing_direction = FACING_RIGHT;
}
void Character::MoveLeft(float deltatime){
	m_position.x -= deltatime * MOVEMENTSPEED;
	m_facing_direction = FACING_LEFT;
}
void Character::AddGravity(float deltaTime) {
	if (m_position.y + MARIO_HEIGHT <= SCREEN_HEIGHT){
		m_position.y += GRAVITY * deltaTime;
	}
	else{
		m_can_jump = true;
	}
}
void Character::Jump() {
	if (!m_jumping) {
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}
float Character::GetCollisionRadius() {
	return m_collision_radius;
}