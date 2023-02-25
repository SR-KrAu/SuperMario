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
	platformType type;//����
	int vx, vy;//�ٶ�
	int loc1, loc2;//�����ƶ�ƽ̨�Ĺ̶�����
	void Draw(class Camera*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void PlatformInit(GameScene*);
void PlatformDraw(GameScene*);
void PlatformUpdate(GameScene*);