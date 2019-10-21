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
	sf::Vector2f coordinateTransf(float angl, sf::Vector2f & oldPoint, sf::Vector2f & centerOfRotation);		//returns new point after rotation around the point
	float lineEquation(sf::Vector2f & point1, sf::Vector2f & point2, sf::Vector2f const & mouse);		//function use for canculate collisions with line
	void setGameResult(std::string gameResult);			//set "win" or "lose" title
	std::string getGameResult();
	void setLastAnimation(bool lastAnimation);			//set flag that last animation hss fineshed
	bool getLastAnimation();
	bool getWin();
	void winRadiusIncr();


	

private:
	//void init();
	bool _win;
	sf::CircleShape _winShape;				//shape of win animation
	float _winShapeRadius;
	sf::CircleShape _loseShape;				//shape that shows wher euou faild
	float _loseShapeRadius;
	std::string _gameResult;	 //contains "win" or "lose" title
	bool _lastAniamation;				//flag is lastAnimation has been finished
	
	//bool _finished;

};