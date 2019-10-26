#pragma once
#include "level.h"
#include "Game.h"

class Level_4 : public Level
{
public:
	Level_4();
	~Level_4();
	void Draw(sf::RenderWindow & renderWindow);
	void Update(sf::Event& event);
	//void reInit();

private:
	void Load(std::string filename);		//use in Init() function 
	int animationNumber;
	Line blinkLine;
	Line line2;
	Line line3;
	Line line4;
	Line line5;

	std::vector<Line> lines;

	sf::Clock animationClock;
	float animationTime;

	sf::Clock clockForBlinkLine;
	float blinkLineTime;

	bool _isLoaded;


	CBodyBasics kinectApplication;
	int _trashHold;


};