#pragma once
#include "level.h"
#include "Game.h"

class Level_1 : public Level
{
public:
	Level_1();
	~Level_1();
	void Draw(sf::RenderWindow & renderWindow);
	void Update(sf::Event& event);
	void reInit();

private:
	void Load(std::string filename);		//use in Init() function 

	Line line1;

	Button startButton;
	Button winButton;

	std::vector<Line> lines;
	std::vector<Button> buttons;


	bool _isLoaded;

};