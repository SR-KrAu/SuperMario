#pragma once

#include "level.h"
#include <graphics.h>

using namespace LevelData;

class Flag {//旗帜类
public:
	bool is_exist;//是否存在
	int x;//旗杆x位置
	int y;//旗帜y位置
	int y_;//旗杆底部砖块上方位置
	int castle_x;//城堡x坐标位置
	IMAGE* flagImg;//旗帜图片
	void Init(class GameScene*);
	void Draw(class Camera*);
	void Update(class GameScene*);
};