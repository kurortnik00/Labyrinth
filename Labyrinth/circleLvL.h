#pragma once
#include "stdafx.h"
#include "VisibleGameObject.h"
#include <sstream>
#include "BodyBasics.h"

class CircleLvL : public VisibleGameObject
{
public:
	CircleLvL ();
	~CircleLvL ();
	
	void Draw(sf::RenderWindow & renderWindow);
	void Update(sf::Event& event);
	bool getFinished();
	void win(sf::Vector2f pos);
	void losePoint(sf::Vector2f pos);
	void reInit();

private:
	sf::Sprite  _sprite;					//sprite of each one animation partical tesla
	sf::Texture _texture;					//same for texture
	sf::Image _image;						//--------------------
	bool finished;							//flag of finish game set in win() and lose() functions
	bool _isLoaded;							//set in Load()
	void Load(std::string filename);		//use in Init() function 
	sf::CircleShape _shape;					//use for boundering resulutions
	sf::CircleShape _winShape;				//shape of win animation
	float _winShapeRadius;					
	sf::CircleShape _loseShape;				//shape that shows wher euou faild
	float _loseShapeRadius;					
	float _radius;							//inscribed radius of mainCircle 
	sf::Vector2f _position;					//pos of maiCircle left top corner
	sf::Vector2f _velocity;					//velocity of center of rotation //not used
	sf::RectangleShape _line;				//use for boundering resulutions
	float _angl;							//angl of rotation
	sf::Transform transform;				//function that rotate coordinate system
	float _angVelocity;						//rotation velocity
	sf::Clock animationClock;				//animation of moving
	sf::Vector2f _centerOfRotation;			//pos of rotation center
	sf::Vector2f _center;					//pos mainCircles center
	float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2);			//sqwere of dist betwin two points
	sf::Vector2f coordinateTransf(float angl, sf::Vector2f & oldPoint, sf::Vector2f & centerOfRotation);		//returns new point after rotation around the point
	sf::Vector2f lineEnd;	//end line point, use in lineEquasion() function
	float lineEquation(sf::Vector2f & point1, sf::Vector2f & point2, sf::Vector2f const & mouse);		//function use for canculate collisions with line
	bool  _win;		//flag set in win() function
	sf::Font font;		//for timer and "win" or "lose" title
	sf::Text text;		//for timer and "win" or "lose" title
	std::string gameResult;	 //contains "win" or "lose" title
	bool lastAniamation;				//flag is lastAnimation has been finished
	sf::Vector2f _startPos;			//use in Init() and reInit()
	std::vector< sf::Texture> animationTextureArr_tesla;			//vector of tetures that used in teslaCircle
	void loadTextureArr(std::string filename, int animationCount);		//load textures and init animationTextureArr_tesla vector
	int animationNumber;											//need for count what animation picture is now
	std::vector< sf::Sprite> spritesArr_teslaCircle;				//vector of sprites that used in teslaCircle
	void setSpritesArr_circle(int figureCorners, sf::Texture texture);		//init spritesArr_teslaCircle vector					
	sf::Clock animationClock2;			//clock for animation speed of teslaCircle 
	std::vector<sf::Sprite> spriteArr_line;		////vector of sprites that used in teslaLine
	void setSpritesArr_line(int figureCorners, sf::Texture texture);	////set  spriteArr_line vector 
	float animationTime;		//contains count of miliSeconds from last sprite change (animation)
	int numberTeslaParticals;		//number of particals(small lines) in mainCircle
	float animationTime_dinamic;	////the time of velocity animation, contains  count of miliSeconds from last move (move animation)


	bool kinectControl;		//if kinectControl == false than mouse control of game 
	sf::Vector2f joint_xy;		//one of joints pos 
	float joint_z;				//one of joints depth
	float _trashHold;				//depth from sensor where interaction starts
	CBodyBasics kinectApplication;		//object that contains kinect functions

};

