#pragma once
class StaticObject : public LogObject//класс для статичных объектов - (таких как земля или горы), есть коллизия
{
public:
	StaticObject::StaticObject(cocos2d::Sprite* obj);
	void createCollisionBox(cocos2d::Vec2 pro, bool dinamic);
	void createCollisionCircle(size_t radius, bool dinamic);
};