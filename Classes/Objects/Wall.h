#pragma once
class Wall : virtual public DinamicObject//������ ����
{
public:
	Wall(cocos2d::Sprite* obj, cocos2d::Size proportion);
	void setEnable(bool x);
};
