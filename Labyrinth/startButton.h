#pragma once
#include "VisibleGameObject.h"
#include "Game.h"
#include "BodyBasics.h"


class StartButton : public VisibleGameObject
{
public:
	StartButton();
	~StartButton();
	void Update(sf::Event& event);
	bool getStart();
	void reInit();
private:
	float x;
	float y;
	int w;
	int h;
	//bool _unbreakable;
	float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2);
	sf::Vector2f _center;
	float _radius;
	bool _start;

	sf::Clock clock;
	bool kinectControl;
	sf::Vector2f joint_xy;
	float joint_z;
	float _trashHold;				//depth from sensor where interaction starts
	CBodyBasics kinectApplication;

};