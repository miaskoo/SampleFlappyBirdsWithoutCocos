#pragma once
class Bird : public DinamicObject//������ ����
{
private:
	cocos2d::EventListenerMouse *Bird_Touch_Listener;
	bool dead;
public:
	Bird::Bird(cocos2d::Sprite* obj);
	void Bird::onMouseDown();
	void setDead(bool n);
};
