#include "Level_2.h"


Level_2::Level_2()
	:_line1_Pos(Game::GetWindow().getSize().x/4, Game::GetWindow().getSize().y),
	_line2_Pos(-25, Game::GetWindow().getSize().y/2),
	_text("", _font, 250),
	lineAngl(330)
{
	animationClock.restart();
	animationNumber = 0;
	numberTeslaParticals_line1 = 5;
	numberTeslaParticals_line2 = 5;
	_font.loadFromFile("font/11583.ttf");
	_isLoaded = false;
	animationTime = 0;
	Level_2::Load("images/2/teslaColor");
	_trashHold = 2;
}

Level_2::~Level_2()
{

}

void Level_2::Load(std::string filename)
{


	VisibleGameObject::setFinished(false);

	///boundering figure. They are not visible, they only for itaraction

	_line1.setPosition(_line1_Pos.x, _line1_Pos.y + 45);
	_line1.setSize(sf::Vector2f(numberTeslaParticals_line1 * 215, 10));
	_line1.setRotation(lineAngl);

	_line2.setPosition(_line2_Pos.x, _line2_Pos.y + 45);
	_line2.setSize(sf::Vector2f(numberTeslaParticals_line2 * 215, 10));
	_line2.setRotation(lineAngl);

	loadTextureArr(filename, 12);	//loading all of the animations parts and save them in 'animationTextureArr_tesla'

	setSpritesArr_line(numberTeslaParticals_line1 + numberTeslaParticals_line2, _texture);	//fill the sprites array  'spriteArr_line' with the same _texture 
	for (int i = 0; i < numberTeslaParticals_line1; i++) {
		if (i == 0)
		{
			spritesArr_teslaLine[i].setPosition(_line1_Pos);		//init the start position of all sprites
		}
		else
		{
			sf::Vector2f oldPos = spritesArr_teslaLine[i - 1].getPosition() + sf::Vector2f(210, 0);
			sf::Vector2f centerOfRotation = spritesArr_teslaLine[i - 1].getPosition() ;
			sf::Vector2f newStartPos = Level::coordinateTransf(lineAngl, oldPos, centerOfRotation);
			spritesArr_teslaLine[i].setPosition(newStartPos);
		}
		spritesArr_teslaLine[i].setRotation(lineAngl);
	}

	
	for (int i = numberTeslaParticals_line1; i < numberTeslaParticals_line1 + numberTeslaParticals_line2; i++) {
		if (i == numberTeslaParticals_line1)
		{
			spritesArr_teslaLine[i].setPosition(_line2_Pos);		//init the start position of all sprites
		}
		else
		{
			sf::Vector2f oldpos = spritesArr_teslaLine[i - 1].getPosition() + sf::Vector2f(210, 0);
			sf::Vector2f centerofrotation = spritesArr_teslaLine[i - 1].getPosition();
			sf::Vector2f newstartpos = Level::coordinateTransf(lineAngl, oldpos, centerofrotation);
			spritesArr_teslaLine[i].setPosition(newstartpos);
		}
		spritesArr_teslaLine[i].setRotation(lineAngl);
	}

	_isLoaded = true;
}

void Level_2::loadTextureArr(std::string filename, int animationCount)
{
	for (int i = 1; i <= animationCount; i++) {
		std::string s = filename + std::to_string(i) + ".png";
		_image.loadFromFile(s);
		_texture.loadFromImage(_image);
		animationTextureArr_tesla.push_back(_texture);
	}
}

void Level_2::setSpritesArr_line(int lineCount, sf::Texture texture)
{
	for (int i = 0; i < lineCount; i++) {
		_sprite.setTexture(texture);
		spritesArr_teslaLine.push_back(_sprite);
	}
}

void Level_2::Draw(sf::RenderWindow & renderWindow)
{

	renderWindow.draw(_line1);
	renderWindow.draw(_line2);
	//The main phase of game, while not win or lose
	//while has been loaded and not finished it will draw all sprites from 'spritesArr_teslaLine'
	//Buttons and timer draws in relevant classes
	if (_isLoaded && !VisibleGameObject::getFinished())
	{
		for (int i = 0; i < spritesArr_teslaLine.size(); i++) {
			renderWindow.draw(spritesArr_teslaLine[i]);
		}

	}


	//drow the end of the game 
	//last animation and score if win
	//the fail map if lose
	else
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
				for (int i = 0; i < spritesArr_teslaLine.size(); i++) {
					renderWindow.draw(spritesArr_teslaLine[i]);
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
}

void Level_2::Update(sf::Event& event)
{

	animationTime = animationClock.getElapsedTime().asMilliseconds();		//time for tesla animation
	if (animationNumber == 12) animationNumber = 0;				//loop the animation
	if (animationTime > 40) {								//the speed of animation

		//lop for KILL_line 
		for (int i = 0; i < spritesArr_teslaLine.size(); i++) {
			spritesArr_teslaLine[i].setTexture(animationTextureArr_tesla[animationNumber]);
		}
		//next animation image
		animationNumber++;
		animationClock.restart();
	}

	//this part runs when play button presed
	//and runnig until not lost or win (finished)
	if (!VisibleGameObject::getFinished() && VisibleGameObject::getStart())
	{

		//canculate and Update the iteraction with the plaer
		//responsible of losing state
		//win check in "winButton"
		sf::Vector2f oldPos = _line1_Pos + _line1.getSize();
		sf::Vector2f centerOfRotation = _line1_Pos;
		sf::Vector2f lineEnd1 = Level::coordinateTransf(330, oldPos, centerOfRotation);;
		sf::Vector2f lineStart1 = sf::Vector2f(_line1.getPosition() - sf::Vector2f(15, 0));

		oldPos = _line2_Pos + _line2.getSize();
		centerOfRotation = _line2_Pos;
		sf::Vector2f lineEnd2 = Level::coordinateTransf(330, oldPos, centerOfRotation);;
		sf::Vector2f lineStart2 = sf::Vector2f(_line2.getPosition() - sf::Vector2f(15, 0));


		if (!VisibleGameObject::getKinectControll()) {
			if (((abs(Level::lineEquation(lineStart1, lineEnd1, sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y))) <= 2000)
				//add for not action where line ends, canculate the distance betwin end line end mause pose, if dist > lineLength ==> false
					&& (dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), lineStart1) < _line1.getSize().x*_line1.getSize().x))
				|| ((abs(Level::lineEquation(lineStart2, lineEnd2, sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y))) <= 2000)
					&& (dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), lineStart2) < _line2.getSize().x*_line2.getSize().x)))
			{
				Level::lose(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y));
			}
		}
		else
		{  //NOT TESTED
			for (int i = 0; i < JointType_Count; i++) {

				sf::Vector2f joint_xy = sf::Vector2f(Game::getKinectApplication().SkeletPointsXY(i).x, Game::getKinectApplication().SkeletPointsXY(i).y);
				float joint_z = Game::getKinectApplication().DepthSkeletonPoints(i);

				joint_xy.x = joint_xy.x * 1900 / 640 * 1 / 1; //translate to pixel
				joint_xy.y = joint_xy.y * 1080 / 280 * 1 / 1;//same

				sf::Vector2f oldPos = _line1_Pos + _line1.getSize();
				sf::Vector2f centerOfRotation = _line1_Pos;
				sf::Vector2f lineEnd1 = Level::coordinateTransf(330, oldPos, centerOfRotation);;
				sf::Vector2f lineStart1 = sf::Vector2f(_line1.getPosition() - sf::Vector2f(15, 0));

				oldPos = _line2_Pos + _line2.getSize();
				centerOfRotation = _line2_Pos;
				sf::Vector2f lineEnd2 = Level::coordinateTransf(330, oldPos, centerOfRotation);;
				sf::Vector2f lineStart2 = sf::Vector2f(_line2.getPosition() - sf::Vector2f(15, 0));

				if (joint_z >= _trashHold) {
					if (animationClock.getElapsedTime().asMilliseconds() > 100) {						//need instad (event.type == sf::Event::MouseButtonPressed) to avoid mass click to target
						if (((abs(lineEquation(lineStart1, lineEnd1, sf::Vector2f(joint_xy.x, joint_xy.y))) <= 2000)
								&& (dist2(sf::Vector2f(joint_xy.x, joint_xy.y), lineEnd1) < _line1.getSize().x*_line1.getSize().x))
							|| ((abs(lineEquation(lineStart2, lineEnd2, sf::Vector2f(joint_xy.x, joint_xy.y))) <= 2000)
								&& (dist2(sf::Vector2f(joint_xy.x, joint_xy.y), lineEnd2) < _line2.getSize().x*_line2.getSize().x)))
						{
							Level::lose(sf::Vector2f(joint_xy.x, joint_xy.y));
						}
					}
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


void Level_2::reInit()
{

}