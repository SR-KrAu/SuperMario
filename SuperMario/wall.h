#pragma once

class Wall {//墙类
public:
	int x1, y1, x2, y2;//起点坐标与终点坐标
	void WallDraw(class Camera*);//绘制碰撞箱
	void WallUpdate(class GameScene*);//更新墙体
	void WallDestroy(class GameScene*);//销毁墙体
};

void WallInit(class GameScene*);
void WallUpdate(class GameScene*);
void WallDraw(class GameScene*);