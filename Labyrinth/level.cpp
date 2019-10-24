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


Level::Line::Line(sf::Vector2f startPoint, float angl, int numberTeslaParticals, sf::Vector2f correction)
	:_startPoint(startPoint), _angl(angl), _numberTeslaParticals(numberTeslaParticals)
{
	size = sf::Vector2f(_numberTeslaParticals * 210, 10);
	_shape.setSize(size);
	_shape.setPosition(startPoint + correction);
	_shape.setRotation(_angl);
	_endPoint = _startPoint + size;
	_endPoint = coordinateTransf(_angl, _endPoint, _startPoint);
	_center = sf::Vector2f((_startPoint.x + _endPoint.x) / 2, (_startPoint.y + _endPoint.y) / 2);

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
	for (int i = 0; i < line._numberTeslaParticals; i++) {
		sf::Sprite _sprite;
		_sprite.setTexture(texture);
		line.spritesArr.push_back(_sprite);
		if (i == 0)
		{
			line.spritesArr[i].setPosition(line._startPoint);		//init the start position of all sprites
		}
		else
		{
			sf::Vector2f oldPos = line.spritesArr[i - 1].getPosition() + sf::Vector2f(210, 0);
			sf::Vector2f centerOfRotation = line.spritesArr[i - 1].getPosition();
			sf::Vector2f newStartPos = Level::coordinateTransf(line._angl, oldPos, centerOfRotation );
			line.spritesArr[i].setPosition(newStartPos);
		}
		line.spritesArr[i].setRotation(line._angl);
	}
}


void Level::lineUpdate(Line& line)
{
	line._shape.setPosition(line._startPoint);
	line._shape.setRotation(line._angl);
	sf::Vector2f oldPos = line._startPoint + sf::Vector2f(210 * line._numberTeslaParticals, 0);
	line._endPoint = Level::coordinateTransf(line._angl, oldPos, line._startPoint);
	line._center = sf::Vector2f((line._startPoint.x + line._endPoint.x) / 2, (line._startPoint.y + line._endPoint.y) / 2);
	for (int i = 0; i < line.spritesArr.size(); i++) {
		line.spritesArr[i].setPosition(line._startPoint - sf::Vector2f(38 * sin((line._angl + 180)*PI / 180) + 10 * sin((line._angl + 180)*PI / 180), 38 * cos(line._angl*PI / 180)) + sf::Vector2f(210 * i*cos(line._angl*PI / 180), 210 * i*sin(line._angl*PI / 180)));
		//some kosteli and podgonian to make the rigtht ratation and make the same pace with bounding figure
		line.spritesArr[i].setRotation(line._angl);
	}
}

void Level::win_lose_Draw(sf::RenderWindow & renderWindow, Line& line)
{
	if (Level::getLastAnimation() || !Level::getWin()) {				//lastAnimation == true when plaer win

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
			for (int i = 0; i < line.spritesArr.size(); i++) {
				renderWindow.draw(line.spritesArr[i]);
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
	else //when win proces comes here at first, then after a few moment it goes in win condition a litle bit higher
	{

		renderWindow.draw(Level::getWinShape());			//when win animation, 
	}
}