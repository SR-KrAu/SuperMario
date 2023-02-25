#pragma once

#include "level.h"
#include <graphics.h>

using namespace LevelData;

class Flag {//������
public:
	bool is_exist;//�Ƿ����
	int x;//���xλ��
	int y;//����yλ��
	int y_;//��˵ײ�ש���Ϸ�λ��
	int castle_x;//�Ǳ�x����λ��
	IMAGE* flagImg;//����ͼƬ
	void Init(class GameScene*);
	void Draw(class Camera*);
	void Update(class GameScene*);
};