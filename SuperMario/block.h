#pragma once

#include "wall.h"

namespace BlockData {
	enum blockType {
		brick,//砖块
		question,//问号方块
		nullquestion,//失效的问号方块
		hide//隐藏方块
	};

	enum blockProp {
		null,//不存在
		coin,//金币
		grow,//生长剂(红蘑菇/太阳花)
		oneup,//绿蘑菇
		star,//五角星
		coins//大量金币
	};
}

using namespace BlockData;

class Block:public Wall {//方块类
public:
	blockType type;//类型
	blockProp prop;//道具
	int coins;//大量金币的数量
	int upHeight, upDir;//被顶起高度和移动方向
	void Draw(Camera*);//绘制方块
	void Update(GameScene*);//更新方块
	void Destroy(GameScene*);//销毁方块
};

void BlockUpdate(GameScene* gamescene);
void BlockInit(GameScene* gamescene);
void BlockDraw(GameScene* gamescene);