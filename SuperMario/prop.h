#pragma once

#include "entity.h"


namespace PropData {
	enum propType {
		coin,//金币
		rmushroom,//红蘑菇
		sunflower,//太阳花
		gmushroom,//绿蘑菇
		star//五角星
	};
}

using namespace PropData;

class Prop :public Entity {//道具类
public:
	propType type;//类型
	int effF, effCnt;//特效动画帧与计数器
	int createTime;//生成时间(无法被拾取)
	void Draw(class Camera*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void PropInit(GameScene* gamescene);
void PropUpdate(GameScene*);
void PropDraw(GameScene*);
void addProp(GameScene* gamescene, int x, int y, propType type);