#pragma once

#include "entity.h"


namespace PropData {
	enum propType {
		coin,//���
		rmushroom,//��Ģ��
		sunflower,//̫����
		gmushroom,//��Ģ��
		star//�����
	};
}

using namespace PropData;

class Prop :public Entity {//������
public:
	propType type;//����
	int effF, effCnt;//��Ч����֡�������
	int createTime;//����ʱ��(�޷���ʰȡ)
	void Draw(class Camera*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void PropInit(GameScene* gamescene);
void PropUpdate(GameScene*);
void PropDraw(GameScene*);
void addProp(GameScene* gamescene, int x, int y, propType type);