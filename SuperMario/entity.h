#pragma once

class Entity {//ʵ����
public:
	int x, y;//λ��
	double vx, vy;//�ٶ�
	int dir;//����
	int width, height;//���볤(��ײ��)
	bool physic;//������(�����������ܵ�ǽ����ײ)
	bool is_land;//�Ƿ񴥵�
	void EntityDraw(class Camera*);
	void EntityUpdate();
};