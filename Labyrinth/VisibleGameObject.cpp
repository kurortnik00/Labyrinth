#include "StdAfx.h"
#include "VisibleGameObject.h"

//Класс всех видимых объектов
VisibleGameObject::VisibleGameObject()
{
	_isLoaded = false;
	_plased = false;
	_finished = false;
	_start = false;
	_unDraw = false;
}


VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string filename)		//Простейшая загрузка спрайтов, загружается вся картинка целиком
{
	if (_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;

		_image.createMaskFromColor(sf::Color(255, 255, 255));
		_texture.loadFromImage(_image);
		_texture.setSmooth(true);


		sf::Sprite sprite;
		_sprite.setTexture(_texture);

		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if (_isLoaded && !_finished && !_unDraw)
	{
		renderWindow.draw(_sprite);
		
	}
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}

void VisibleGameObject::Update(sf::Event& event)
{

}


bool VisibleGameObject::getClickState()		
{
	return false;
}

sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}	

bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}


sf::Vector2f VisibleGameObject::getCenter() {
	sf::IntRect rect = _sprite.getTextureRect();
	return sf::Vector2f(_sprite.getPosition().x + rect.width / 2, _sprite.getPosition().y + rect.height / 2);
}

//void VisibleGameObject::Restart() {				//Для обновления игры, переопределяется в дочерних классах
//
//}

//void VisibleGameObject::setUnbreakable(bool ans)
//{
//
//}
//
//bool VisibleGameObject::getUnbreakable()
//{
//	return true;
//}

void VisibleGameObject::setFinished(bool res)
{
	_finished = res;
}

bool VisibleGameObject::getFinished() {
	return _finished;
}

void VisibleGameObject::setPlased(bool res)
{
	_plased = res;
}

bool VisibleGameObject::getPlased() {
	return _plased;
}

void VisibleGameObject::setClickState(bool ans)
{

}
void VisibleGameObject::reInit() {

}

void VisibleGameObject::countIncroment() {

}

bool VisibleGameObject::getWin() {
	return false;
}
void VisibleGameObject::win(sf::Vector2f pos) {

}

void VisibleGameObject::setStart(bool start) {
	_start = start;
}

bool VisibleGameObject::getStart() {
	return _start;
}

void VisibleGameObject::setUnDraw(bool unDraw) {
	_unDraw = unDraw;
}

bool VisibleGameObject::getUnDraw() {
	return _unDraw;
}