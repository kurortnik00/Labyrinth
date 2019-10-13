#include "circleLvL.h"
#include <cmath>
#include "Game.h"
#include "winButton.h"
#include "startButton.h"
#define PI 3.14159265 

CircleLvL::CircleLvL() 
	:text("", font, 250),
	_startPos(150,150),
	_angVelocity(0.1),
	_velocity(0.1,0.1),
	_radius(390)
{
	_position = sf::Vector2f(_startPos);
	_angl = 0;
	_center = sf::Vector2f(_position.x + _radius, _position.y + _radius);
	_centerOfRotation = sf::Vector2f(_center.x - 100, _center.y - 100);
	_winShapeRadius = 10;								//the start shape of win animation 
	_loseShapeRadius = 20;								//the shape that shows where you faild
	_win = false;
	gameResult = "You Lose!";
	lastAniamation = false;

	animationClock.restart();

	CircleLvL::Load("images/circleLvL.png");
	font.loadFromFile("font/11583.ttf");
	
}
CircleLvL::~CircleLvL() {
	
}
void CircleLvL::Load(std::string filename)
{
	if (_image.loadFromFile(filename) == false) _isLoaded = false;
	else _isLoaded = true;
	finished = false;

	_image.createMaskFromColor(sf::Color(255, 255, 255));
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);
	_sprite.setPosition(_position);


	//shape for canculate the bounding 
	//It will be invisible when I make good animation 
	_shape.setFillColor(sf::Color(0,0,0));
	_shape.setRadius(_radius);
	_shape.setOutlineThickness(10);
	_shape.setOutlineColor(sf::Color(250, 150, 100));
	_shape.setPosition(_position);
	
	//the same as priviouse
	_line.setPosition(_center);
	_line.setFillColor(sf::Color(255, 255, 255));
	_line.setSize(sf::Vector2f(_radius, 10));
	lineEnd = sf::Vector2f(_line.getPosition().x + _line.getSize().x, _line.getPosition().y);


	_winShape.setFillColor(sf::Color(255, 255, 255));
	_winShape.setRadius(_winShapeRadius);

	_loseShape.setFillColor(sf::Color(255, 0, 0));
	_loseShape.setRadius(_loseShapeRadius);
}

void CircleLvL::Draw(sf::RenderWindow & renderWindow)
{
	//The main phase of game, while not win or lose
	if (_isLoaded && !finished)
	{
		renderWindow.draw(_shape, transform);
		renderWindow.draw(_line);
		renderWindow.draw(_sprite, transform);
	}
	else
	{
		if (lastAniamation || !_win) {				//lastAnimation == true when plaer win

			if (_win) {
				std::ostringstream timerStr;
				timerStr << gameResult;
				text.setString(timerStr.str());
				renderWindow.draw(text);
				text.setPosition(400, 200);
			}
			else
			{
				renderWindow.draw(_shape, transform);
				renderWindow.draw(_line);
				renderWindow.draw(_sprite, transform);
				renderWindow.draw(_loseShape);

				std::ostringstream timerStr;
				timerStr << gameResult;
				text.setString(timerStr.str());
				renderWindow.draw(text);
				text.setPosition(400, 200);
			}
			
		}
		else
		{
			renderWindow.draw(_winShape);			//when win animation
		}
	}
}

void CircleLvL::Update(sf::Event& event) {
	if (!finished && VisibleGameObject::getStart())
	{
		float animationTime = animationClock.getElapsedTime().asMilliseconds();
		if (animationTime > 5) {
			_angl += _angVelocity;

			transform.rotate(_angVelocity, _centerOfRotation);
			animationClock.restart();

			_center = coordinateTransf(_angVelocity, _center, _centerOfRotation);
			lineEnd = coordinateTransf(_angVelocity, lineEnd, _centerOfRotation);

			_line.setRotation(_angl);
			_line.setPosition(_center);
		}
		if (_angl > 360) _angl -= 360;
		if (_centerOfRotation.x > 2 * _radius || _centerOfRotation.y > 2 * _radius) {
			_velocity = -_velocity;
		}
		if (_centerOfRotation.x < _radius / 2 || _centerOfRotation.y < _radius / 2) {
			_velocity = -_velocity;
		}

		if ((dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), _center) > _radius*_radius))
		{
			lose(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y));
		}
		else if ((abs(lineEquation(_center, lineEnd, sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y))) <= 2000)
			&& (dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), lineEnd) < _radius*_radius))
		{
			lose(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y));
		}
	}
	//Run win animation when screan circly go white
	//In future better do with variable that depends from screeen values
	else if (_win && (_winShapeRadius < 1500))												//Const of the animation PODGONIAN 
	{
		_winShapeRadius +=1.9;																//Const of the animation PODGONIAN 
		_winShape.setRadius(_winShapeRadius);
		_winShape.setPosition(_winShape.getPosition() - sf::Vector2f(1.6,1.6));				//Const of the animation PODGONIAN 
	}
	if (_winShapeRadius >= 1500 && _winShapeRadius <= 1600)									//when radiuse more then screeen 
	{
		lastAniamation = true;//finish of last animation
		_winShapeRadius += 105;//some kosteli
	}
}

float CircleLvL::dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

sf::Vector2f CircleLvL::coordinateTransf(float angl, sf::Vector2f & oldPoint, sf::Vector2f & centerOfRotation) {

	float X = oldPoint.x - centerOfRotation.x;
	float Y = oldPoint.y - centerOfRotation.y;

	float NewCenter_X = X * cos(angl * PI / 180) - Y * sin(angl* PI / 180);
	float NewCenter_Y = X * sin(angl * PI / 180) + Y * cos(angl* PI / 180);

	return sf::Vector2f(NewCenter_X + centerOfRotation.x, NewCenter_Y + centerOfRotation.y); 
}


//equation for canculate coordinates of line when it rotate
float CircleLvL::lineEquation(sf::Vector2f & point1, sf::Vector2f & point2, sf::Vector2f const & mouse) {
	return (point1.y - point2.y)*mouse.x + (point2.x - point1.x)*mouse.y + (point1.x*point2.y - point2.x*point1.y);
}

void CircleLvL::win(sf::Vector2f pos) {
	finished = true;
	gameResult = "You Win!";
	_winShape.setPosition(pos);
	_win = true;
}

void CircleLvL::lose(sf::Vector2f pos) {
	finished = true;
	gameResult = "You Lose!";
	pos.x -= _loseShapeRadius;
	pos.y -= _loseShapeRadius;
	_loseShape.setPosition(pos);
}

bool CircleLvL::getFinished() {
	return finished;
}

void CircleLvL::reInit() {
	_position = sf::Vector2f(_startPos);
	transform.rotate(360 - _angl, _centerOfRotation);
	_angl = 0;
	_line.setRotation(_angl);
	_center = sf::Vector2f(_position.x + _radius, _position.y + _radius);
	_winShapeRadius = 10;
	_loseShapeRadius = 20;
	_win = false;
	lastAniamation = false;
	animationClock.restart();
	Load("images/circleLvL.png");
	VisibleGameObject::setStart(false);
	
}
