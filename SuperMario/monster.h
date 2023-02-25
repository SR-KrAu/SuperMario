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
	monsterType type;//类型
	monsterType2 type2;//子类型
	monsterStatus status;//状态
	bool is_exist;//是否存在(即是否已生成)
	int effF, effCnt;//特效动画帧与计数器
	int deathCnt;//被踩死计数器
	int piranha_y;//食人花固定位置
	int piranha_time;//食人花蜷缩时间
	void Draw(class Camera*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void MonsterInit(class GameScene*);
void MonsterDraw(class GameScene*);
void MonsterUpdate(class GameScene*);