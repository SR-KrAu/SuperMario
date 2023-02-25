#pragma once

#include "wall.h"

namespace PlatformData {
	enum platformType {
		up,
		down,
		up_down,
		right_left
	};
}

using namespace PlatformData;

class Platform :public Wall {
public:
	platformType type;//类型
	int vx, vy;//速度
	int loc1, loc2;//来回移动平台的固定坐标
	void Draw(class Camera*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void PlatformInit(GameScene*);
void PlatformDraw(GameScene*);
void PlatformUpdate(GameScene*);