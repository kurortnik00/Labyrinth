#include "circleLvL.h"
#include <cmath>
#include "Game.h"
#include "winButton.h"
#include "startButton.h"
#define PI 3.14159265 

CircleLvL::CircleLvL() 
	:_startPos(150, 150),
	_angVelocity(0.1),				//Rotation velocity
	_velocity(0.1, 0.1),				//Center velocity, it moves _center
	_radius(400),			//_shape radiuse, it responsible of boundering shape. In fact it equils inscribed radius 
	line1(_center, 90, 440),
	startButton(sf::Vector2f(300, 800), 50, "images/playButton.png", sf::IntRect(0, 0, 156, 156)),
	winButton(sf::Vector2f(700, 200), 50, "images/winButton.png", sf::IntRect(0, 0, 126, 126))
{
	_position = sf::Vector2f(_startPos);
	_angl = 0;
	_center = sf::Vector2f(_position.x + _radius, _position.y + _radius);
	_centerOfRotation = sf::Vector2f(_center.x - 100, _center.y - 100);			//dislocated center of rotation. made for shape movement 

	animationClock.restart();		//mabe it not necessaty
	numberTeslaParticals = 18;
	CircleLvL::Load("images/2/teslaColor");

}

CircleLvL::~CircleLvL() {
	
}

void CircleLvL::Load(std::string filename)
{
	_shape.setRadius(_radius);
	_shape.setPosition(_position);

	Level::loadTextureArr(filename, 12, line1);
	Level::setSpritesArr(line1, line1.animationTextureArr[0]);

	line1._startPoint = _center;
	lines.push_back(line1);

	buttons.push_back(startButton);
	buttons.push_back(winButton);


	setSpritesArr_circle(numberTeslaParticals, line1.animationTextureArr[0]);			//fill the sprites array  'spritesArr_teslaCircle' with the same _texture 
	for (int i = 0; i < spritesArr_teslaCircle.size(); i++) {
		spritesArr_teslaCircle[i].setPosition(_position);			//init the start position of all sprites
	}
	_isLoaded = true;
}

void CircleLvL::Draw(sf::RenderWindow & renderWindow)
{
	//The main phase of game, while not win or lose
	//while has been loaded and not finished it will draw all sprites from 'spriteArr_line' and 'spritesArr_teslaCircle'
	//Buttons and timer draws in relevant classes
	if (_isLoaded && !VisibleGameObject::getFinished())
	{
		for (int i = 0; i < spritesArr_teslaCircle.size(); i++) {
			renderWindow.draw(spritesArr_teslaCircle[i]);		
		}
		Level::drawLines(renderWindow, lines);
		Level::drawButtons(renderWindow, buttons);
	}
	//drow the end of the game 
	//last animation and score if win
	//the fail map if lose
	else
	{

		Level::win_lose_Draw(renderWindow, lines);

	}
}

void CircleLvL::Update(sf::Event& event) {


	Level::lineAnimationUpdate(lines);
	Level::linesUpdate(lines);
	Level::buttonsUpdate(buttons);

	animationTime = animationClock2.getElapsedTime().asMilliseconds();		//time for tesla animation
	if (animationNumber == 12) animationNumber = 0;				//loop the animation
	if (animationTime > 40) {								//the speed of animation
		//int angleCircleTesla = 0;
		for (int i = 0; i < spritesArr_teslaCircle.size(); i++) {
			spritesArr_teslaCircle[i].setTexture(line1.animationTextureArr[animationNumber]);

			double R = 390*1.2; //������ ��������� ����������
			double angle = 0; //���� ������� ����������� ��������������

			for (int j = 0; j < numberTeslaParticals; j++)
			{
				spritesArr_teslaCircle[j].setPosition(sf::Vector2f(_center.x + R * cos(angle*PI / 180) , _center.y + R * sin(angle*PI / 180))); //fill the all next cordinates (sqwears)
				angle = angle + 360 / numberTeslaParticals;				//����������� ���� �� �������� ���� ����������� ��������������
				spritesArr_teslaCircle[j].setRotation(angle+80);			//the rotation of iach tesla partical, if ratation == 0 all particals are parallel  
				
			}	
		}
		
		animationNumber++;		
		animationClock2.restart();
	}
	
	//this part runs when play button presed
	//and runnig until not lost or win (finished)
	if (!VisibleGameObject::getFinished() && VisibleGameObject::getStart())
	{
		animationTime_dinamic = animationClock.getElapsedTime().asMilliseconds();			//the time of velocity animation
		//this animation rotates and move the KILL_ring
		if (animationTime_dinamic > 5) {						//the animation speed

			_angl += _angVelocity;
			_center = coordinateTransf(_angVelocity, _center, _centerOfRotation);		//canculation of new position of _center (the center of KILL_ring)

			//rotation of kill line 
			//not visible, only for canculations of itaractions
			for (int j = 0; j < lines.size(); j++) {
				lines[j]._startPoint = _center;
				lines[j]._angl = _angl;
			}
			animationClock.restart();
		}
		if (_angl > 360) _angl -= 360;


		//attampt of making the varible rotation point (faild) to hard to canculate
		/*if (_centerOfRotation.x > 2 * _radius || _centerOfRotation.y > 2 * _radius) {
			_velocity = -_velocity;
		}
		if (_centerOfRotation.x < _radius / 2 || _centerOfRotation.y < _radius / 2) {
			_velocity = -_velocity;
		}*/


		//canculate and Update the iteraction with the plaer
		//responsible of losing state
		//win check in "winButton"
		if (!VisibleGameObject::getKinectControll()) {
			if ((dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), _center) > _radius*_radius))
			{
				Level::lose(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y));
			}
			
		}
		
	}

}


void CircleLvL::reInit() {

}


void CircleLvL::setSpritesArr_circle(int figureCorners, sf::Texture texture)
{
	for (int i = 0; i < figureCorners; i++) {
		_sprite.setTexture(texture);
		spritesArr_teslaCircle.push_back(_sprite);
	}
}
