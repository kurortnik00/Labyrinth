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
	kinectApplication = Game::getKinectApplication();
}

StartButton::~StartButton()
{

}

void StartButton::Update(sf::Event& event)
{

	if (VisibleGameObject::getKinectControll()) {
		for (int i = 0; i < JointType_Count; i++) {

			joint_xy = sf::Vector2f(kinectApplication.SkeletPointsXY(i).x, kinectApplication.SkeletPointsXY(i).y);
			joint_z = kinectApplication.DepthSkeletonPoints(i);

			joint_xy.x = joint_xy.x * 1900 / 640 * 1 / 1; //translate to pixel
			joint_xy.y = joint_xy.y * 1080 / 280 * 1 / 1;//same

			if (joint_z >= _trashHold) {
				if (clock.getElapsedTime().asMilliseconds() > 100) {						//need instad (event.type == sf::Event::MouseButtonPressed) to avoid mass click to target
					if ((dist2(sf::Vector2f(joint_xy.x, joint_xy.y), _center) < _radius*_radius))
					{
						VisibleGameObject::setStart(true);
						VisibleGameObject::setUnDraw(true);
					}
					clock.restart();
				}
			}
		}
	}
	else {

		if ((dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), _center) < _radius*_radius))
		{
			VisibleGameObject::setStart(true);
			VisibleGameObject::setUnDraw(true);
		}
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