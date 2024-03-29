#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "GameObjectManager.h"
#include "BodyBasics.h"


class Game
{

public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	static CBodyBasics & getKinectApplication();
	const static int SCREEN_WIDTH = 1900;
	const static int SCREEN_HEIGHT = 1200;
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
		LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, CIRCLELvL, LAST 
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;
	static GameObjectManager _gameObjectManager;
	//static int smashCount;
	static SelectedLevel _selectedLevel;
	static bool kinectControl;
	static CBodyBasics _kinectApplication;
};