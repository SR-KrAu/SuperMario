#pragma once

class Wall {//ǽ��
public:
	int x1, y1, x2, y2;//����������յ�����
	void WallDraw(class Camera*);//������ײ��
	void WallUpdate(class GameScene*);//����ǽ��
	void WallDestroy(class GameScene*);//����ǽ��
};

void WallInit(class GameScene*);
void WallUpdate(class GameScene*);
void WallDraw(class GameScene*);