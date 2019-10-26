#include "level_4.h"

Level_4::Level_4()
	:blinkLine(sf::Vector2f(0, Game::GetWindow().getSize().y / 3 + 80), 0, 4),
	line2(sf::Vector2f(blinkLine.size.x , 0), 90, 2),
	line3(sf::Vector2f(blinkLine.size.x  + 200, 0), 90, 2),
	line4(sf::Vector2f(blinkLine.size.x + 200, line3._endPoint.y), 90, 1),
	line5(sf::Vector2f(blinkLine.size.x  + 200, Game::GetWindow().getSize().y), 270, 1)
{
	animationClock.restart();
	clockForBlinkLine.restart();
	animationNumber = 0;

	_isLoaded = false;
	animationTime = 0;
	Level_4::Load("images/2/teslaColor");
}

Level_4::~Level_4()
{

}

void Level_4::Load(std::string filename)
{
	Level::loadTextureArr(filename, 12, blinkLine);
	Level::loadTextureArr(filename, 12, line2);
	Level::loadTextureArr(filename, 12, line3);
	Level::loadTextureArr(filename, 12, line4);
	Level::loadTextureArr(filename, 12, line5);

	Level::setSpritesArr(blinkLine, blinkLine.animationTextureArr[0]);
	Level::setSpritesArr(line2, line2.animationTextureArr[0]);
	Level::setSpritesArr(line3, line3.animationTextureArr[0]);
	Level::setSpritesArr(line4, line4.animationTextureArr[0]);
	Level::setSpritesArr(line5, line5.animationTextureArr[0]);

	lines.push_back(blinkLine);
	lines.push_back(line2);
	lines.push_back(line3);
	lines.push_back(line4);
	lines.push_back(line5);

	_isLoaded = true;

}

void Level_4::Draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded && !VisibleGameObject::getFinished()) {

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

	//drow the end of the game 
//last animation and score if win
//the fail map if lose
	else
	{
		for (int j = 0; j < lines.size(); j++)
		{
			Level::win_lose_Draw(renderWindow, lines[j]);
		}
	}
}

void Level_4::Update(sf::Event& event)
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
	for (int i = 0; i < lines.size(); i++)
	{
		Level::lineUpdate(lines[i]);
	}

	if (!VisibleGameObject::getFinished() && VisibleGameObject::getStart())
	{
		for (int i = 0; i < lines.size(); i++)
		{
			blinkLineTime = clockForBlinkLine.getElapsedTime().asMilliseconds();
			if (blinkLineTime > 2500)
			{
				lines[0]._unActive = true;
					
				if (blinkLineTime > 3500)
				{
					clockForBlinkLine.restart();
					lines[0]._unActive = false;
				}
			}
			//when touched first action button 
			if (true)
			{
				lines[0]._unActive = true;
			}
			if (true && lines[3]._angl > 0)
			{
				lines[3]._angl -= 0.01;
				lines[4]._angl += 0.01;
			}
			//when touched second action button 
			if (true && lines[1]._velocity.x == 0)
			{
				lines[1]._velocity.x = -0.1;
				lines[2]._velocity.x = 0.1;


			}
			if (lines[1]._startPoint.x <= 0.0 || lines[1]._startPoint.x >= 1920.0) lines[1]._velocity.x = -lines[1]._velocity.x;
			if (lines[2]._startPoint.x <= 0.0 || lines[2]._startPoint.x >= 1920.0) lines[2]._velocity.x = -lines[2]._velocity.x;
		}

		

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