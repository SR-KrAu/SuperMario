#pragma once

#include <graphics.h>
#include "level.h"

namespace PipeData {
	enum pipeType {
		down,
		right
	};
}

using namespace LevelData;
using namespace PipeData;

class Pipe {//管道类
public:
	bool is_tran;//是否具有传送功能
	levelName tran_level;//传送世界
	pipeType type;//类型
	int x, y;//位置
	int tran_location;//传送位置
	int tran_x, tran_y;//传送坐标
	IMAGE* pipeImg;//图片
	bool is_newlevel;//是否进入新的关卡
	void Draw(class GameScene*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void PipeInit(GameScene*);
void PipeDraw(GameScene*);
void PipeUpdate(GameScene*);