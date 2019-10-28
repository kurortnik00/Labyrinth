#include "level_3.h"

Level_3::Level_3()
	:line1(sf::Vector2f(300, 300),0, 2),
	line2(sf::Vector2f(1200, 300), 180, 2)
{

	
	_isLoaded = false;

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

		Level::drawLines(renderWindow, lines);
	}

	//drow the end of the game 
//last animation and score if win
//the fail map if lose
	else
	{

		Level::win_lose_Draw(renderWindow, lines);

	}

}

void Level_3::Update(sf::Event& event)
{
	Level::lineAnimationUpdate(lines);
	Level::linesUpdate(lines);


	if (!VisibleGameObject::getFinished() && VisibleGameObject::getStart())
	{
		for (int i = 0; i < lines.size(); i++)
		{
			lines[i]._angl += 0.01;
		}

		if (!VisibleGameObject::getKinectControll()) {
			for (int i = 0; i < lines.size(); i++) {
				if ((abs(Level::lineEquation(lines[i]._startPoint, lines[i]._endPoint, sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y))) <= 2000)
					//add for not action where line ends, canculate the distance betwin end line end mause pose, if dist > lineLength ==> false
					&& (dist2(sf::Vector2f(sf::Mouse::getPosition(Game::GetWindow()).x, sf::Mouse::getPosition(Game::GetWindow()).y), lines[i]._center) < lines[i].size.x * lines[i].size.x / 4))

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