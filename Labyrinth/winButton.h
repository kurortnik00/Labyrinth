#pragma once
#include "VisibleGameObject.h"
#include "Game.h"


class WinButton : public VisibleGameObject
{
public:
	WinButton();
	~WinButton();
	void Update(sf::Event& event);
	bool getWin();
	void reInit();
private:
	float x;
	float y;
	int w;
	int h;
	bool _unbreakable;
	float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2);
	sf::Vector2f _center;
	float _radius;
	bool _win;

};