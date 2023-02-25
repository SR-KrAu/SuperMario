#pragma once

#include "entity.h"

namespace MonsterData {
	enum monsterType {
		chestnut,
		tortoise,
		piranha
	};
	enum monsterType2 {
		null,
		gtortoise,
		rtortoise,
		flyrtortoise
	};
	enum monsterStatus {
		normal,
		handstand,
		shrunkenheaded
	};
}

using namespace MonsterData;

class Monster :public Entity {
public:
	monsterType type;//����
	monsterType2 type2;//������
	monsterStatus status;//״̬
	bool is_exist;//�Ƿ����(���Ƿ�������)
	int effF, effCnt;//��Ч����֡�������
	int deathCnt;//������������
	int piranha_y;//ʳ�˻��̶�λ��
	int piranha_time;//ʳ�˻�����ʱ��
	void Draw(class Camera*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void MonsterInit(class GameScene*);
void MonsterDraw(class GameScene*);
void MonsterUpdate(class GameScene*);