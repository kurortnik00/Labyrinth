#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"

//Класс отвечающий за удаление, добавление и хранение объектов а так же за их Общую отрисовку и обновление 

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;
		_gameObjects.erase(results);
	}
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;

}

int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}


void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		if (itr->second->getPlased()) itr->second->Draw(renderWindow);
		itr++;
	}
}

void GameObjectManager::UpdateAll(sf::Event& event)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	
	while (itr != _gameObjects.end())
	{
		itr->second->Update(event);

		if (itr->second->getStart()) {
			Get("timer1")->setStart(true);
			Get("winButton")->setStart(true);
			//Get("circleLvL")->setStart(true);
			Get("level_1")->setStart(true);
		}


		if (itr->second->getFinished() && !Get("timer1")->getFinished()) {   ///Lose the levl
			Get("timer1")->setFinished(true);
			Get("winButton")->setFinished(true);

			
		}
		if (itr->second->getWin() && !Get("timer1")->getFinished()) {		//Win the LVL
			Get("timer1")->setFinished(true);
			Get("winButton")->setFinished(true);
			//Get("circleLvL")->win(Get("winButton")->GetPosition());
			Get("level_1")->win(Get("winButton")->GetPosition());
			
		}
		itr++;
	}
}

void GameObjectManager::setAllPlased()
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->setPlased(true);
		itr++;
	}
}