#pragma once

class Entity {//实体类
public:
	int x, y;//位置
	double vx, vy;//速度
	int dir;//朝向
	int width, height;//宽与长(碰撞箱)
	bool physic;//物理开关(开启重力且受到墙体碰撞)
	bool is_land;//是否触地
	void EntityDraw(class Camera*);
	void EntityUpdate();
};