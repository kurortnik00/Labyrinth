#include "circleLvL.h"
#include <cmath>
#include "Game.h"
#include "winButton.h"
#include "startButton.h"
#define PI 3.14159265 

CircleLvL::CircleLvL() 
	:text("", font, 250),
	_startPos(150,150),
	_angVelocity(0.1),				//Rotation velocity
	_velocity(0.1,0.1),				//Center velocity, it moves _center
	_radius(400)			//_shape radiuse, it responsible of boundering shape. In fact it equils inscribed radius 
{
	_position = sf::Vector2f(_startPos);
	_angl = 0;
	_center = sf::Vector2f(_position.x + _radius, _position.y + _radius);
	_centerOfRotation = sf::Vector2f(_center.x - 100, _center.y - 100);			//dislocated center of rotation. made for shape movement 
	_winShapeRadius = 10;								//the start shape of win animation 
	_loseShapeRadius = 20;								//the shape that shows where you faild
	_win = false;
	gameResult = "You Lose!";
	lastAniamation = false;		//flag that win animation has been done, followed by score screen
	animationClock.restart();		//mabe it not necessaty
	numberTeslaParticals = 18;
	CircleLvL::Load("images/2/teslaColor");
	font.loadFromFile("font/11583.ttf");
	kinectControl = true;
	//kinectApplication = Game::getKinectApplication();
}

CircleLvL::~CircleLvL() {
	
}

void CircleLvL::Load(std::string filename)
{
	//if (_image.loadFromFile(filename) == false) _isLoaded = false;
	
	finished = false;

	///two boundering figure. They are not visible, they only for itaraction
	_shape.setRadius(_radius);
	_shape.setPosition(_position);

	_line.setPosition(_center);
	_line.setSize(sf::Vector2f(_radius, 10));
	lineEnd = sf::Vector2f(_line.getPosition().x + _line.getSize().x, _line.getPosition().y);


	//two shapece for end of the game, second one when you lose, it shows where did you fail
	//first one make a big bleaching of the screen
	_winShape.setFillColor(sf::Color(255, 255, 255));
	_winShape.setRadius(_winShapeRadius);
	_loseShape.setFillColor(sf::Color(255, 0, 0));
	_loseShape.setRadius(_loseShapeRadius);



	loadTextureArr(filename, 12);	//loading all of the animations parts and save them in 'animationTextureArr_tesla', 12 images
	animationNumber = 0;		//number of the current immage(freame)
	setSpritesArr_circle(numberTeslaParticals, _texture);			//fill the sprites array  'spritesArr_teslaCircle' with the same _texture 
	for (int i = 0; i < spritesArr_teslaCircle.size(); i++) {
		spritesArr_teslaCircle[i].setPosition(_position);			//init the start position of all sprites
	}

	setSpritesArr_line(2, _texture);	//fill the sprites array  'spriteArr_line' with the same _texture 
	for (int i = 0; i < spriteArr_line.size(); i++) {
		spriteArr_line[i].setPosition(_center - sf::Vector2f(5,45) + sf::Vector2f(210*i,0));		//init the start position of all sprites
	}
	_isLoaded = true;
}

void CircleLvL::Draw(sf::RenderWindow & renderWindow)
{
	//The main phase of game, while not win or lose
	//while has been loaded and not finished it will draw all sprites from 'spriteArr_line' and 'spritesArr_teslaCircle'
	//Buttons and timer draws in relevant classes
	if (_isLoaded && !finished)
	{
		for (int i = 0; i < spritesArr_teslaCircle.size(); i++) {
			renderWindow.draw(spritesArr_teslaCircle[i]);		
		}
		for (int i = 0; i < spriteArr_line.size(); i++) {
			renderWindow.draw(spriteArr_line[i]);
		}
	}
	//drow the end of the game 
	//last animation and score if win
	//the fail map if lose
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
				//Lose state
				//stop the moving animation 
				//shows the faill place

				for (int i = 0; i < spritesArr_teslaCircle.size(); i++) {
					renderWindow.draw(spritesArr_teslaCircle[i]);
				}
				for (int i = 0; i < spriteArr_line.size(); i++) {
					renderWindow.draw(spriteArr_line[i]);
				}
				renderWindow.draw(_loseShape);


				//text that you failed
				std::ostringstream timerStr;
				timerStr << gameResult;
				text.setString(timerStr.str());
				renderWindow.draw(text);
				text.setPosition(400, 200);
			}
			
		}
		else //when win proces comes here at first, then after a few moment it goes in win condition a litle bit higher
		{
			renderWindow.draw(_winShape);			//when win animation, 
		}
	}
}

void CircleLvL::Update(sf::Event& event) {

	animationTime = animationClock2.getElapsedTime().asMilliseconds();		//time for tesla animation
	if (animationNumber == 12) animationNumber = 0;				//loop the animation
	if (animationTime > 40) {								//the speed of animation
		//int angleCircleTesla = 0;
		for (int i = 0; i < spritesArr_teslaCircle.size(); i++) {
			spritesArr_teslaCircle[i].setTexture(animationTextureArr_tesla[animationNumber]);

			double R = 390*1.2; //Радиус описанной окружности
			double angle = 0; //Угол наклона правильного многоугольника

			for (int j = 0; j < numberTeslaParticals; j++)
			{
				spritesArr_teslaCircle[j].setPosition(sf::Vector2f(_center.x + R * cos(angle*PI / 180) , _center.y + R * sin(angle*PI / 180))); //fill the all next cordinates (sqwears)
				angle = angle + 360 / numberTeslaParticals;				//Увеличиваем угол на величину угла правильного многоугольника
				spritesArr_teslaCircle[j].setRotation(angle+80);			//the rotation of iach tesla partical, if ratation == 0 all particals are parallel  
				
			}	
		}
		//lop for KILL_line 
		for (int i = 0; i < spriteArr_line.size(); i++) {
			spriteArr_line[i].setTexture(animationTextureArr_tesla[animationNumber]);
			spriteArr_line[i].setRotation(_angl);
			spriteArr_line[i].setPosition(_center - sf::Vector2f(38*sin((_angl + 180)*PI/180) + 10*sin((_angl + 180 )*PI / 180), 38*cos(_angl*PI/180)) + sf::Vector2f(210 * i*cos(_angl*PI / 180), 210 * i*sin(_angl*PI / 180)));
			//some kosteli and podgonian to make the rigtht ratation and make the same pace with bounding figure
		}
		//next animation image
		animationNumber++;		
		animationClock2.restart();
	}
	
	//this part runs when play button presed
	//and runnig until not lost or win (finished)
	if (!finished && VisibleGameObject::getStart())
	{
		animationTime_dinamic = animationClock.getElapsedTime().asMilliseconds();			//the time of velocity animation
		//this animation rotates and move the KILL_ring
		if (animationTime_dinamic > 5) {						//the animation speed
			_angl += _angVelocity;
			//transform.rotate(_angVelocity, _centerOfRotation);  //can be delited after make god lose screen
			animationClock.restart();

			_center = coordinateTransf(_angVelocity, _center, _centerOfRotation);		//canculation of new position of _center (the center of KILL_ring)
			lineEnd = coordinateTransf(_angVelocity, lineEnd, _centerOfRotation);		//canculate the new pos of the line and citcle intersection point

			//rotation of kill line 
			//not visible, only for canculations of itaractions
			_line.setRotation(_angl);
			_line.setPosition(_center);

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
				losePoint(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y));
			}
			else if ((abs(lineEquation(_center, lineEnd, sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y))) <= 2000)
				&& (dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), lineEnd) < _radius*_radius))
			{
				losePoint(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y));
			}
		}
		else
		{
			for (int i = 0; i < JointType_Count; i++) {

				joint_xy = sf::Vector2f(kinectApplication.SkeletPointsXY(i).x, kinectApplication.SkeletPointsXY(i).y);
				joint_z = kinectApplication.DepthSkeletonPoints(i);

				joint_xy.x = joint_xy.x * 1900 / 640 * 1 / 1; //translate to pixel
				joint_xy.y = joint_xy.y * 1080 / 280 * 1 / 1;//same

				if (joint_z >= _trashHold) {
					if (animationClock.getElapsedTime().asMilliseconds() > 100) {						//need instad (event.type == sf::Event::MouseButtonPressed) to avoid mass click to target
						if ((dist2(sf::Vector2f(joint_xy.x, joint_xy.y), _center) > _radius*_radius))
						{
							losePoint(sf::Vector2f(joint_xy.x, joint_xy.y));
						}
						else if ((abs(lineEquation(_center, lineEnd, sf::Vector2f(joint_xy.x, joint_xy.y))) <= 2000)
							&& (dist2(sf::Vector2f(joint_xy.x, joint_xy.y), lineEnd) < _radius*_radius))
						{
							losePoint(sf::Vector2f(joint_xy.x, joint_xy.y));
						}
					}
				}
			}
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

//returns the sqwere of distance betvin two points
//is used to canculate the iteraction with player
float CircleLvL::dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

//returns new point after rotation around the point
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

void CircleLvL::losePoint(sf::Vector2f pos) {
	finished = true;
	gameResult = "You Lose!";
	//place the red shape on faid point (cordinate)
	pos.x -= _loseShapeRadius;
	pos.y -= _loseShapeRadius;
	_loseShape.setPosition(pos);
}

//need for state mathine  
bool CircleLvL::getFinished() {
	return finished;
}

void CircleLvL::reInit() {

	//back to init pos from rotation and moving
	_position = sf::Vector2f(_startPos);
	transform.rotate(360 - _angl, _centerOfRotation);
	_angl = 0;
	_line.setRotation(_angl);
	_center = sf::Vector2f(_position.x + _radius, _position.y + _radius);
	_winShapeRadius = 10;
	animationClock.restart();
	//set the reInition of boundering objcts posetions
	_sprite.setPosition(_position);
	_line.setPosition(_center);
	lineEnd = sf::Vector2f(_line.getPosition().x + _line.getSize().x, _line.getPosition().y);

	//reinit flag states
	_win = false;
	lastAniamation = false;
	finished = false;
	VisibleGameObject::setStart(false);
	
	//reInei the value of vin shape, that used in lastAnimation
	_winShape.setRadius(_winShapeRadius);

	animationNumber = 0;
}

void CircleLvL::loadTextureArr(std::string filename, int animationCount) {
	for (int i = 1; i <= animationCount; i++) {
		std::string s = filename + std::to_string(i) + ".png";
		_image.loadFromFile(s);
		_texture.loadFromImage(_image);
	 	animationTextureArr_tesla.push_back(_texture);
	}
}

void CircleLvL::setSpritesArr_circle(int figureCorners, sf::Texture texture)
{
	for (int i = 0; i < figureCorners; i++) {
		_sprite.setTexture(texture);
		spritesArr_teslaCircle.push_back(_sprite);
	}
}

void CircleLvL::setSpritesArr_line(int lineCount, sf::Texture texture)
{
	for (int i = 0; i < lineCount; i++) {
		_sprite.setTexture(texture);
		spriteArr_line.push_back(_sprite);
	}
}