#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "GameObjectManager.h"


class Game
{

public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;
	static void countIncriment();

private:
	static bool IsExiting();
	static void GameLoop();
	static void ShowSplashScreen();
	static void ShowMenu();
	//static void ShowCustomScreen();
	static void Init();
	static void reInit();
	static int getRandomNumber(int min, int max);
	static void levelInit();
	static std::vector<VisibleGameObject> levels;
	
	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting, Custom
	};

	//LAST need for itarate all enums, and LAST not apear in itaration, its ounly recicle element
	enum SelectedLevel {
		LEVEL_1,  CIRCLELvL, LAST 
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static GameObjectManager _gameObjectManager;
	//static int smashCount;
	static SelectedLevel _selectedLevel;
	static bool kinectControl;
};