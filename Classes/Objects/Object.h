#pragma once
class LogObject
{
protected:
	cocos2d::Sprite* sprite;
public:
	LogObject::LogObject(cocos2d::Sprite* obj);
	bool createCollisionBox(cocos2d::Size proportion, const cocos2d::PhysicsMaterial& material = cocos2d::PHYSICSSHAPE_MATERIAL_DEFAULT);//������� �������
	bool createCollisionCircle(size_t radius, const cocos2d::PhysicsMaterial& material = cocos2d::PHYSICSSHAPE_MATERIAL_DEFAULT);//������� �����
	void setPosition(cocos2d::Vec2 pos);
	void LogObject::setRotation(size_t angle);
	cocos2d::Sprite* getSprite();
	cocos2d::Vec2 getPosition();
	void setEnableCollisionEvent(bool on);//�������� ������

	virtual LogObject::~LogObject();//����� ����� dynamic_cast 
};
