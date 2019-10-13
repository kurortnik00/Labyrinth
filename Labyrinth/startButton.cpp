#include "startButton.h"

StartButton::StartButton()
{
	x = 50;
	y = 550;
	w = 156;
	h = 156;
	VisibleGameObject::Load("images/playButton.png");
	VisibleGameObject::SetPosition(x, y);
	_center = sf::Vector2f(x + w / 2, y + h / 2);
	_radius = w / 2;
}

StartButton::~StartButton()
{

}

void StartButton::Update(sf::Event& event)
{
	if ((dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), _center) < _radius*_radius))
	{
		VisibleGameObject::setStart(true);
		VisibleGameObject::setUnDraw(true);
	}
}

float StartButton::dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool StartButton::getStart() {
	return VisibleGameObject::getStart();
}

void StartButton::reInit() {
	VisibleGameObject::SetPosition(x, y);
	_center = sf::Vector2f(x + w / 2, y + h / 2);
	_radius = w / 2;
	VisibleGameObject::setStart(false);
	VisibleGameObject::setFinished(false);
	VisibleGameObject::setUnDraw(false);
}