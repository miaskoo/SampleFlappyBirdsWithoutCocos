#pragma once
class StaticObject : public LogObject//����� ��� ��������� �������� - (����� ��� ����� ��� ����), ���� ��������
{
public:
	StaticObject::StaticObject(cocos2d::Sprite* obj);
	void createCollisionBox(cocos2d::Vec2 pro, bool dinamic);
	void createCollisionCircle(size_t radius, bool dinamic);
};