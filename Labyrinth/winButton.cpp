#include "winButton.h"

WinButton::WinButton()
{
	x = 500;
	y = 650;
	w = 126;
	h = 126;
	VisibleGameObject::Load("images/winButton.png");
	VisibleGameObject::SetPosition(x, y);
	_unbreakable = true;
	_center = sf::Vector2f(x + w/2, y + h/2);
	_radius = w/2;
	_win = false;
}

WinButton::~WinButton()
{

}

void WinButton::Update(sf::Event& event)
{
	if (VisibleGameObject::getStart()) _unbreakable = false;


	if (VisibleGameObject::getKinectControll()) {
		for (int i = 0; i < JointType_Count; i++) {

			joint_xy = sf::Vector2f(kinectApplication.SkeletPointsXY(i).x, kinectApplication.SkeletPointsXY(i).y);
			joint_z = kinectApplication.DepthSkeletonPoints(i);

			joint_xy.x = joint_xy.x * 1900 / 640 * 1 / 1; //translate to pixel
			joint_xy.y = joint_xy.y * 1080 / 280 * 1 / 1;//same

			if (joint_z >= _trashHold) {
				if (clock.getElapsedTime().asMilliseconds() > 100) {						//need instad (event.type == sf::Event::MouseButtonPressed) to avoid mass click to target
					if ((dist2(sf::Vector2f(joint_xy.x, joint_xy.y), _center) < _radius*_radius) && !_unbreakable)
					{
						_win = true;
					}
					clock.restart();
				}
			}
		}
	}
	else
	{
		if ((dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), _center) < _radius*_radius) && !_unbreakable)
		{
			_win = true;
		}
	}
}

float WinButton::dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

//bool WinButton::getWin() {
//	return _win;
//}

void WinButton::reInit() {
	VisibleGameObject::SetPosition(x, y);
	_unbreakable = true;
	_center = sf::Vector2f(x + w / 2, y + h / 2);
	_radius = w / 2;
	_win = false;
	//VisibleGameObject::setFinished(false);
	//VisibleGameObject::setStart(false);
}