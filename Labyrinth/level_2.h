#pragma once

#pragma once
#include "level.h"
#include "Game.h"

class Level_2 : public Level
{
public:
	Level_2();
	~Level_2();
	void Draw(sf::RenderWindow & renderWindow);
	void Update(sf::Event& event);
	void reInit();

private:
	void Load(std::string filename);		//use in Init() function 
	sf::RectangleShape _line1;				//use for boundering resulutions
	sf::Vector2f _line1_Pos;
	float lineAngl;
	sf::Clock animationClock;
	float animationTime;
	sf::Sprite  _sprite;					//sprite of each one animation partical tesla
	sf::Texture _texture;					//same for texture
	sf::Image _image;						//--------------------

	std::vector< sf::Texture> animationTextureArr_tesla;			//vector of tetures that used in teslaCircle
	void loadTextureArr(std::string filename, int animationCount);		//load textures and init animationTextureArr_tesla vector
	int animationNumber;											//need for count what animation picture is now
	std::vector< sf::Sprite> spritesArr_teslaLine;				//vector of sprites that used in teslaCircle
	void setSpritesArr_line(int figureCorners, sf::Texture texture);		//init spritesArr_teslaCircle vector
	int numberTeslaParticals_line1;		//number of particals(small lines) 

	sf::RectangleShape _line2;				//use for boundering resulutions
	sf::Vector2f _line2_Pos;
	int numberTeslaParticals_line2;

	bool _isLoaded;

	sf::Font _font;		//for timer and "win" or "lose" title
	sf::Text _text;		//for timer and "win" or "lose" title

	CBodyBasics kinectApplication;
	int _trashHold;


};