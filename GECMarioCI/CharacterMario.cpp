#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map) {
	m_renderer = renderer;
}
CharacterMario::~CharacterMario() {
	m_renderer = nullptr;
}
void CharacterMario::Update(float deltatime, SDL_Event e) {
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		case SDLK_w:
			Jump();
		} break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		} break;
	}
	Character::Update(deltatime, e);
}