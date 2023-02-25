#pragma once

#include "entity.h"

namespace MarioData {
	enum marioBody {
		child,//小孩
		adult,//成人
		old//老人
	};
}

using namespace MarioData;

class Mario :public Entity {//马里奥类
public:
	bool is_run;//是否奔跑
	bool is_speed;//是否加速
	bool is_squat;//是否蹲下
	bool is_jump;//是否跳跃
	bool is_death;//是否死亡
	bool is_enter;//是否进入管道
	bool is_flag;//是否抓旗
	bool is_stealth;//是否隐身
	int fireCnt;//开火动作计数器
	int mario_dir;//马里奥朝向
	int runF, runCnt;//奔跑动画帧与计数器
	int frameCnt;//定帧计数器
	int in_time;//无敌时间
	int im_time;//免疫时间
	int transf_time;//变身时间
	marioBody body;//体型
	void Init(class GameScene*);
	void Draw(class GameScene*);
	void Update(class GameScene*);
	void WinUpdate(class GameScene*);
};