#include "level_3.h"

Level_3::Level_3()
	:_text("", _font, 250),
	line1(sf::Vector2f(300, 300),0, 2),
	line2(sf::Vector2f(1200, 300), 180, 2)
{
	animationClock.restart();
	animationNumber = 0;
	_font.loadFromFile("font/11583.ttf");
	_isLoaded = false;
	animationTime = 0;
	Level_3::Load("images/2/teslaColor");
	
}

Level_3::~Level_3()
{

}

void Level_3::Load(std::string filename)
{
	
	Level::loadTextureArr(filename, 12, line1);
	Level::loadTextureArr(filename, 12, line2);
	Level::setSpritesArr(line1, line1.animationTextureArr[0]);
	Level::setSpritesArr(line2, line2.animationTextureArr[0]);
	
	lines.push_back(line1);
	lines.push_back(line2);
	_isLoaded = true;
}

void Level_3::Draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded && !VisibleGameObject::getFinished()) {

		for (int j = 0; j < lines.size(); j++)
		{
			renderWindow.draw(lines[j]._shape);

			for (int i = 0; i < lines[j].spritesArr.size(); i++) {
				renderWindow.draw(lines[j].spritesArr[i]);
			}
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
			for (int j = 0; j < lines.size(); j++)
			{
				for (int i = 0; i < lines[j].spritesArr.size(); i++) {
					renderWindow.draw(lines[j].spritesArr[i]);
				}
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

void Level_3::Update(sf::Event& event)
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


	std::cout << lines[0]._endPoint.x;
	std::cout << "\n";
	if (!VisibleGameObject::getFinished() && VisibleGameObject::getStart())
	{
		for (int i = 0; i < lines.size(); i++)
		{
			Level::lineUpdate(lines[i]);
			lines[i]._angl += 0.01;
		}

		if (!VisibleGameObject::getKinectControll()) {
			for (int i = 0; i < lines.size(); i++) {
				if ((abs(Level::lineEquation(lines[i]._startPoint, lines[i]._endPoint, sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y))) <= 2000)
					//add for not action where line ends, canculate the distance betwin end line end mause pose, if dist > lineLength ==> false
					&& (dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), lines[i]._startPoint) < lines[i].size.x * lines[i].size.x))

				{
					Level::lose(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y));
					
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

void Level_3::reInit()
{

}