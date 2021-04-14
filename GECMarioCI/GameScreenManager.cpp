#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startscreen) //constructor
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	ChangeScreen(startscreen);
}
GameScreenManager::~GameScreenManager() //destructor
{
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}
void GameScreenManager::Render() {
	m_current_screen->Render();
}
void GameScreenManager::Update(float deltatime, SDL_Event e) {
	m_current_screen->Update(deltatime, e);
}
void GameScreenManager::ChangeScreen(SCREENS new_screen) {
	if (m_current_screen != nullptr){
		delete m_current_screen;
	}
	GameScreenLevel1* tempScreen;
	switch (new_screen)
	{
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
	default:;
	}
}