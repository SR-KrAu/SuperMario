#pragma once

#include "entity.h"


class Fireball :public Entity {//������
public:
	int effF, effCnt;//��Ч����֡�������
	void Draw(class Camera*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void addFireball(class GameScene*);
void FireballDraw(class GameScene*);
void FireballUpdate(class GameScene*);