#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "circleLvL.h"
//#include "Target.h"
#include "Timer.h"
//#include "CustomScreen.h"
#include "SmashCounter.h"
//#include <random>
#include "winButton.h"
#include "startButton.h"
#include "level_1.h"



void Game::Start(void)	//������������� ��������
{
	if (_gameState != Uninitialized) return;

	_mainWindow.create(sf::VideoMode(1900, 1000), "Pang!");
	bool kinectControl = false;

	Game::Init(targetCount, kinectControl);

	_gameState = Game::ShowingSplash;		//�������� � ��������

	while (!IsExiting())
	{
		GameLoop();
	}

	Game::_mainWindow.close();
}

bool Game::IsExiting()//��� ��������� GameLoop()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

sf::RenderWindow& Game::GetWindow()
{
	return Game::_mainWindow;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	
	switch (_gameState)
	{
		
		case Game::ShowingMenu:
		{
			ShowMenu();		
			break;
		}
		case Game::ShowingSplash:
		{
		
			ShowSplashScreen();
			break;
		}
		case Game::Custom:
		{

			//ShowCustomScreen();
			break;
		}
		case Game::Playing:
		{
		
			
			_mainWindow.clear(sf::Color(0, 0, 0));
			
			_gameObjectManager.setAllPlased();
			
			_gameObjectManager.UpdateAll(currentEvent);		//��������� ��� �������
			_gameObjectManager.DrawAll(_mainWindow);		//������ ��� �������

			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;

			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape)		//����� �� ����� ���� � ���� �� ������� ESC
				{
					_gameState = Game::ShowingMenu;
				}
			}
			break;
		}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);					//������ ����������� ���� ����������� �� ������� ����� �������
													
	_gameState = Game::ShowingMenu;
}

////void Game::ShowCustomScreen()
////{
////	CustomScreen customScreen;
////	customScreen.Show(_mainWindow, _gameObjectManager);					//������ ����������� ���� ����������� �� ������� ����� �������
////
////	_gameState = Game::ShowingMenu;
////}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);   //���������� �������� ������� "������", �.�. ��� ������ ������: ������ ��� ����� �� ����
																//������ ����������� ���� ����������� �� ������� ����� �� "������" ��� �������� ����
																	

	switch (result)
	{
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			Game::reInit(targetCount);
			break;
	}
}

void Game::Init(int targ_count, bool kinectControl) {

	Timer *time1 = new Timer();
	time1->Load("font/11583.ttf");
	_gameObjectManager.Add("timer1", time1);


	CircleLvL *circleLvL = new CircleLvL();
	circleLvL->setKinectControl(kinectControl);
	//_gameObjectManager.Add("circleLvL", circleLvL);

	WinButton *winButton = new WinButton();
	winButton->setKinectControl(kinectControl);
	_gameObjectManager.Add("winButton", winButton);

	StartButton *startButton = new StartButton();
	startButton->setKinectControl(kinectControl);
	_gameObjectManager.Add("startButton", startButton);

	Level_1 *level_1 = new Level_1();
	level_1->setKinectControl(kinectControl);
	_gameObjectManager.Add("level_1", level_1);

}

void Game::reInit(int targ_count)
{
	_gameObjectManager.Get("timer1")->reInit();
	//_gameObjectManager.Get("circleLvL")->reInit();
	_gameObjectManager.Get("winButton")->reInit();
	_gameObjectManager.Get("startButton")->reInit();
}


void Game::countIncriment() {

}

int Game::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	// ���������� ������������ ��������� ����� � ����� ���������
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

GameObjectManager Game::_gameObjectManager;
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
int Game::targetCount = 5;				//if >5 need to change Init()





