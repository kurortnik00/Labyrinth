#include "Level.h"


Level::Level() 
	:_text("", _font, 250)
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
	_font.loadFromFile("font/11583.ttf");
	animationNumber = 0;
	_trashHold = 2;
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


Level::Line::Line(sf::Vector2f startPoint, float angl, float length)
	:_startPoint(startPoint), _angl(angl), _length(length)
{
	size = sf::Vector2f(_length, 10);
	_shape.setSize(size);
	_shape.setPosition(startPoint);
	_shape.setRotation(_angl);
	_endPoint = _startPoint + size;
	_endPoint = coordinateTransf(_angl, _endPoint, _startPoint);
	_center = sf::Vector2f((_startPoint.x + _endPoint.x) / 2, (_startPoint.y + _endPoint.y) / 2);
	_unActive = false;
	_velocity = sf::Vector2f(0, 0);
}

Level::Button::Button(sf::Vector2f position, float radius, std::string filename, sf::IntRect textureRect)
	:_position(position), _radius(radius)
{
	_image.loadFromFile(filename);
	_image.createMaskFromColor(sf::Color(237, 28, 36));
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(textureRect);
	_sprite.setPosition(_position);


	_center = sf::Vector2f(_position.x + _radius, _position.y + _radius);
	_unDrowable = false;
	_hasClicked = false;
}


void Level::loadTextureArr(std::string filename, int animationCount, Line& line)
{
	for (int i = 1; i <= animationCount; i++) {
		std::string s = filename + std::to_string(i) + ".png";
		sf::Image image;
		image.loadFromFile(s);
		sf::Texture texture;
		texture.loadFromImage(image);
		line.animationTextureArr.push_back(texture);
	}
}

void Level::setSpritesArr(Line& line, sf::Texture texture)
{
	//for (int i = 0; i < line._numberTeslaParticals; i++) {
		sf::Sprite _sprite;
		_sprite.setTexture(texture);
		line.spritesArr.push_back(_sprite);
		//if (i == 0)
		//{
			line.spritesArr[0].setPosition(line._startPoint);		//init the start position of all sprites
			line.spritesArr[0].setScale(line.size.x / 210, 1);
		//}
		//else
		//{
		//	sf::Vector2f oldPos = line.spritesArr[i - 1].getPosition() + sf::Vector2f(210, 0);
		//	sf::Vector2f centerOfRotation = line.spritesArr[i - 1].getPosition();
		//	sf::Vector2f newStartPos = Level::coordinateTransf(line._angl, oldPos, centerOfRotation );
		//	line.spritesArr[i].setPosition(newStartPos);
	//	}
	//	line.spritesArr[i].setRotation(line._angl);
	//	
	//}
}


void Level::linesUpdate(std::vector<Line>& lines)
{
	for (int i = 0; i < lines.size(); i++)
	{
		lines[i]._shape.setPosition(lines[i]._startPoint);
		lines[i]._shape.setRotation(lines[i]._angl);
		sf::Vector2f oldPos = lines[i]._startPoint + lines[i].size;
		lines[i]._endPoint = Level::coordinateTransf(lines[i]._angl, oldPos, lines[i]._startPoint);
		lines[i]._center = sf::Vector2f((lines[i]._startPoint.x + lines[i]._endPoint.x) / 2, (lines[i]._startPoint.y + lines[i]._endPoint.y) / 2);
		for (int j = 0; j < lines[i].spritesArr.size(); j++) {
			lines[i].spritesArr[j].setPosition(lines[i]._startPoint - sf::Vector2f(38 * sin((lines[i]._angl + 180)*PI / 180) + 10 * sin((lines[i]._angl + 180)*PI / 180), 38 * cos(lines[i]._angl*PI / 180)) + sf::Vector2f(210 * j*cos(lines[i]._angl*PI / 180), 210 * j*sin(lines[i]._angl*PI / 180)));
			//some kosteli and podgonian to make the rigtht ratation and make the same pace with bounding figure
			lines[i].spritesArr[j].setRotation(lines[i]._angl);
		}
		lines[i]._startPoint += lines[i]._velocity;
	}


	if (!VisibleGameObject::getFinished() && VisibleGameObject::getStart())
	{
		if (!VisibleGameObject::getKinectControll()) {
			for (int i = 0; i < lines.size(); i++) {
				if ((abs(Level::lineEquation(lines[i]._startPoint, lines[i]._endPoint, sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y))) <= 2000)
					//add for not action where line ends, canculate the distance betwin end line end mause pose, if dist > lineLength ==> false
					&& (dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), lines[i]._center) < lines[i].size.x * lines[i].size.x / 4))

				{
					if (!lines[i]._unActive) Level::lose(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y));

				}
			}
		}
		else
		{  //NOT TESTED
			for (int i = 0; i < JointType_Count; i++) {
				for (int j = 0; j < lines.size(); j++) {
					sf::Vector2f joint_xy = sf::Vector2f(Game::getKinectApplication().SkeletPointsXY(i).x, Game::getKinectApplication().SkeletPointsXY(i).y);
					float joint_z = Game::getKinectApplication().DepthSkeletonPoints(i);

					joint_xy.x = joint_xy.x * 1900 / 640 * 1 / 1; //translate to pixel
					joint_xy.y = joint_xy.y * 1080 / 280 * 1 / 1;//same


					if (joint_z >= _trashHold) {
						if (animationClock.getElapsedTime().asMilliseconds() > 100) {						//need instad (event.type == sf::Event::MouseButtonPressed) to avoid mass click to target
							if (((abs(lineEquation(lines[j]._startPoint, lines[j]._endPoint, sf::Vector2f(joint_xy.x, joint_xy.y))) <= 2000)
								&& (dist2(sf::Vector2f(joint_xy.x, joint_xy.y), lines[j]._center) < lines[j].size.x * lines[j].size.x / 4)))
								
							{
								Level::lose(sf::Vector2f(joint_xy.x, joint_xy.y));
							}
						}
					}
				}
			}
		}
	}
}

void Level::lineAnimationUpdate(std::vector<Line>& lines)
{
	animationTime = animationClock.getElapsedTime().asMilliseconds();		//time for tesla animation
	if (animationNumber == 12) animationNumber = 0;				//loop the animation
	if (animationTime > 40) {								//the speed of animation

		for (int j = 0; j < lines.size(); j++)
		{
			for (int i = 0; i < lines[j].spritesArr.size(); i++) {
				lines[j].spritesArr[i].setTexture(lines[j].animationTextureArr[animationNumber]);
			}
		}
		//next animation image
		animationNumber++;
		animationClock.restart();
	}

}

void Level::win_lose_Draw(sf::RenderWindow & renderWindow, std::vector<Line>& lines)
{
	
	if (Level::getLastAnimation() || !Level::getWin()) {				//lastAnimation == true when plaer win
		for (int j = 0; j < lines.size(); j++)
		{
			if (Level::getWin()) {
				std::ostringstream timerStr;
				timerStr << Level::getGameResult();
				_text.setString(timerStr.str());
				renderWindow.draw(_text);
				_text.setPosition(400, 200);
			}
			else
			{

				//Lose state
				//stop the moving animation 
				//shows the faill place
				for (int i = 0; i < lines[j].spritesArr.size(); i++) {
					if (!lines[j]._unActive) renderWindow.draw(lines[j].spritesArr[i]);
				}
				renderWindow.draw(Level::getLoseShape());


				//text that you failed
				std::ostringstream timerStr;
				timerStr << Level::getGameResult();
				_text.setString(timerStr.str());
				renderWindow.draw(_text);
				_text.setPosition(400, 200);
			}
		}

	}
	else //when win proces comes here at first, then after a few moment it goes in win condition a litle bit higher
	{

		renderWindow.draw(Level::getWinShape());			//when win animation, 
	}
}


void Level::drawLines(sf::RenderWindow & renderWindow, std::vector<Line>& lines)
{
	for (int j = 0; j < lines.size(); j++)
	{
		if (!lines[j]._unActive) {
			renderWindow.draw(lines[j]._shape);

			for (int i = 0; i < lines[j].spritesArr.size(); i++) {
				renderWindow.draw(lines[j].spritesArr[i]);
			}
		}

	}
}

void Level::drawButtons(sf::RenderWindow & renderWindow, std::vector<Button>& buttons)
{
	for (int i = 0; i < buttons.size(); i++) {
		if (!buttons[i]._unDrowable) renderWindow.draw(buttons[i]._sprite);
	}

}

void Level::setWin(bool win)
{
	_win = win;
}

void Level::buttonsUpdate(std::vector<Button>& buttons)
{
	if (dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), buttons[START_BUTTON]._center) < buttons[START_BUTTON]._radius*buttons[START_BUTTON]._radius)
	{
		buttons[START_BUTTON]._hasClicked = true;
		buttons[START_BUTTON]._unDrowable = true;
	}
	if (buttons[START_BUTTON]._hasClicked)
	{
		VisibleGameObject::setStart(true);
	}

	if (!VisibleGameObject::getFinished() && VisibleGameObject::getStart())
	{
		if (buttons[WIN_BUTTON]._hasClicked)
		{
			Level::setWin(true);
			Level::win(buttons[WIN_BUTTON]._position);
		}
		if (!VisibleGameObject::getKinectControll()) {
			for (int i = 0; i < buttons.size(); i++)
			{
				if (dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), buttons[i]._center) < buttons[i]._radius*buttons[i]._radius)
				{

					buttons[i]._hasClicked = true;
					buttons[i]._unDrowable = true;
				}

			}
		}
	}

	//Run win animation when screan circly go white
	//In future better do with variable that depends from screeen values
	else if (Level::getWin() && (Level::getWinShape().getRadius() < 1500))												//Const of the animation PODGONIAN 
	{
		Level::winRadiusIncr();

	}
	if (Level::getWinShape().getRadius() >= 1500 && !Level::getLastAnimation())									//when radiuse more then screeen 
	{
		Level::setLastAnimation(true);//finish of last animation
	}
	
}