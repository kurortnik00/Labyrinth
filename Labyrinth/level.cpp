#include "Level.h"


Level::Level() 
	
{
	_winShapeRadius = 10;								//the start shape of win animation 
	_loseShapeRadius = 20;								//the shape that shows where you faild
	_win = false;
	_gameResult = "You Lose!";
	_lastAniamation = false;		//flag that win animation has been done, followed by score screen
	_winShape.setFillColor(sf::Color(255, 255, 255));
	_winShape.setRadius(_winShapeRadius);
	_loseShape.setFillColor(sf::Color(255, 0, 0));
	_loseShape.setRadius(_loseShapeRadius);
}

Level::~Level()
{

}

void Level::win(sf::Vector2f pos)
{
	VisibleGameObject::setFinished(true);
	_gameResult = "You Win!";
	_winShape.setPosition(pos);
	_win = true;
	
}


void Level::lose(sf::Vector2f pos)
{
	VisibleGameObject::setFinished(true);
	_gameResult = "You Lose!";
	//place the red shape on faid point (cordinate)
	_loseShape.setPosition(pos);
}

sf::CircleShape Level::getWinShape()
{
	return _winShape;
}

sf::CircleShape Level::getLoseShape()
{
	return _loseShape;
}

float Level::dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

sf::Vector2f Level::coordinateTransf(float angl, sf::Vector2f & oldPoint, sf::Vector2f & centerOfRotation) {

	float X = oldPoint.x - centerOfRotation.x;
	float Y = oldPoint.y - centerOfRotation.y;

	float NewCenter_X = X * cos(angl * PI / 180) - Y * sin(angl* PI / 180);
	float NewCenter_Y = X * sin(angl * PI / 180) + Y * cos(angl* PI / 180);

	return sf::Vector2f(NewCenter_X + centerOfRotation.x, NewCenter_Y + centerOfRotation.y);
}


//equation for canculate coordinates of line when it rotate
float Level::lineEquation(sf::Vector2f & point1, sf::Vector2f & point2, sf::Vector2f const & mouse) {
	return (point1.y - point2.y)*mouse.x + (point2.x - point1.x)*mouse.y + (point1.x*point2.y - point2.x*point1.y);
}

std::string Level::getGameResult()
{
	return _gameResult;
}

void Level::setGameResult(std::string gameResult)
{
	_gameResult = _gameResult;
}

void Level::setLastAnimation(bool lastAnimation)

{
	_lastAniamation = lastAnimation;
}


bool Level::getLastAnimation()
{
	return _lastAniamation;
}

bool Level::getWin()
{
	return _win;
}

void Level::winRadiusIncr()
{
	_winShapeRadius += 1.9;
	_winShape.setRadius(_winShapeRadius);
	_winShape.setPosition(_winShape.getPosition() - sf::Vector2f(1.6, 1.6));
}