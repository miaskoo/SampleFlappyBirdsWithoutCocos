#pragma once
class Wall : virtual public DinamicObject//объект стен
{
public:
	Wall(cocos2d::Sprite* obj, cocos2d::Size proportion);
	void setEnable(bool x);
};
