#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include <sstream>
#include <cmath>
#include "BodyBasics.h"
#define PI 3.14159265 

class Level : public VisibleGameObject
{
public:
	Level();
	~Level();
	void win(sf::Vector2f pos);
	void lose(sf::Vector2f pos);
	
	sf::CircleShape getWinShape();
	sf::CircleShape getLoseShape();
	float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2);			//sqwere of dist betwin two points
	static sf::Vector2f coordinateTransf(float angl, sf::Vector2f & oldPoint, sf::Vector2f & centerOfRotation);		//returns new point after rotation around the point
	float lineEquation(sf::Vector2f & point1, sf::Vector2f & point2, sf::Vector2f const & mouse);		//function use for canculate collisions with line
	void setGameResult(std::string gameResult);			//set "win" or "lose" title
	std::string getGameResult();
	void setLastAnimation(bool lastAnimation);			//set flag that last animation hss fineshed
	bool getLastAnimation();
	bool getWin();
	void winRadiusIncr();

	

//protected:
	struct Line
	{
	public:
		Line(sf::Vector2f startPoint, float angl, int numberTeslaParticals);
		sf::RectangleShape _shape;
		sf::Vector2f size;
		sf::Vector2f _startPoint;
		sf::Vector2f _endPoint;
		float _angl;
		int _numberTeslaParticals;
		std::vector< sf::Texture> animationTextureArr;			//vector of tetures that used in teslaCircle
		std::vector< sf::Sprite> spritesArr;				//vector of sprites that used in teslaCircle
		sf::Vector2f _center;
		sf::Vector2f _velocity;
		bool _unActive;
		
	};

	void loadTextureArr(std::string filename, int animationCount, Line& line);		//load textures and init animationTextureArr_tesla vector
	void setSpritesArr(Line& line, sf::Texture texture);		//init spritesArr_teslaCircle vector
	//void setLineCorrection(Line& line, sf::Vector2f correction);
	void lineUpdate(Line& line);
	void win_lose_Draw(sf::RenderWindow & renderWindow, Line& line);

	

private:
	//void init();
	bool _win;
	sf::CircleShape _winShape;				//shape of win animation
	float _winShapeRadius;
	sf::CircleShape _loseShape;				//shape that shows wher euou faild
	float _loseShapeRadius;
	std::string _gameResult;	 //contains "win" or "lose" title
	bool _lastAniamation;				//flag is lastAnimation has been finished
	sf::Font _font;		//for timer and "win" or "lose" title
	sf::Text _text;		//for timer and "win" or "lose" title
	
	//bool _finished;

};