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
	sf::RectangleShape _line;				//use for boundering resulutions
	sf::Vector2f _linePos;

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
	int numberTeslaParticals;		//number of particals(small lines) in mainCircle

	bool _isLoaded;

	sf::Font _font;		//for timer and "win" or "lose" title
	sf::Text _text;		//for timer and "win" or "lose" title

};