#pragma once

#include "entity.h"


class Fireball :public Entity {//火球类
public:
	int effF, effCnt;//特效动画帧与计数器
	void Draw(class Camera*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void addFireball(class GameScene*);
void FireballDraw(class GameScene*);
void FireballUpdate(class GameScene*);