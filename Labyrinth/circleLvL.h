#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include <sstream>
#include "BodyBasics.h"

class CircleLvL : public VisibleGameObject
{
public:
	CircleLvL ();
	~CircleLvL ();
	
	void Draw(sf::RenderWindow & renderWindow);
	void Update(sf::Event& event);
	sf::CircleShape shape();
	float radius();
	sf::Vector2f & position();
	sf::Vector2f & velocity();
	sf::Vector2f & line();
	bool getFinished();
	void win(sf::Vector2f pos);
	void lose(sf::Vector2f pos);
	void reInit();

private:
	sf::Sprite  _sprite;
	sf::Sprite  _sprite2;
	sf::Texture _texture;
	sf::Image _image;
	bool finished;
	bool _isLoaded;
	void Load(std::string filename);
	sf::CircleShape _shape;
	sf::CircleShape _winShape;
	float _winShapeRadius;
	sf::CircleShape _loseShape;
	float _loseShapeRadius;
	float _radius;
	sf::Vector2f _position;
	sf::Vector2f _velocity;
	sf::RectangleShape _line;
	float _angl;
	sf::Transform transform;
	float _angVelocity;
	sf::Clock animationClock;
	sf::Vector2f _centerOfRotation;
	sf::Vector2f _center;
	float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2);
	sf::Vector2f coordinateTransf(float angl, sf::Vector2f & oldPoint, sf::Vector2f & centerOfRotation);
	sf::Vector2f lineEnd;
	float lineEquation(sf::Vector2f & point1, sf::Vector2f & point2, sf::Vector2f const & mouse);
	bool  _win;
	sf::Font font;
	sf::Text text;
	std::string gameResult;
	bool lastAniamation;
	sf::Vector2f _startPos;
	std::vector< sf::Texture> animationTextureArr_tesla;
	void loadTextureArr(std::string filename, int animationCount);
	int animationNumber;											//need for count what animation picture is now
	std::vector< sf::Sprite> spritesArr_teslaCircle;
	void setSpritesArr_circle(int figureCorners, sf::Texture texture);
	int deltaAngleCircleTesla;
	sf::Clock animationClock2;
	std::vector<sf::Sprite> spriteArr_line;
	void setSpritesArr_line(int figureCorners, sf::Texture texture);
	float animationTime;
	int numberTeslaParticals;
	float animationTime_dinamic;


	bool kinectControl;
	sf::Vector2f HANDRIGHT_xy;
	float HANDRIGHT_z;
	float _trashHold;				//depth from sensor where interaction starts
	CBodyBasics kinectApplication;

	
};

