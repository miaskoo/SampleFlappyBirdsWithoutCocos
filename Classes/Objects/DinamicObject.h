#pragma once
class DinamicObject : public LogObject//����� ���������� ��������
{
public:
	DinamicObject::DinamicObject(cocos2d::Sprite* obj);
	void addImpulse(cocos2d::Vec2 impulse);
	void setMass(float mass);
	void setLinearDamping(size_t LinearDamping);
	void setGravity(bool on);//���� �� �������������� � ����������� ����
};