#include "entity.h"
#include "event.h"
#include "collisionbox.h"

void Entity::EntityDraw(Camera* camera) {
	ShowCollisionbox(camera, this->x, this->y, this->x + this->width, this->y + this->height);
	//显示碰撞箱
}

void Entity::EntityUpdate() {
	//实体数据更新

	EntityFallEvent(this);//实体坠落事件

	//改变实体朝向
	if (this->vx > 0 && this->dir != 1)
		this->dir = 1;
	else if(this->vx < 0 && this->dir != -1)
		this->dir = -1;
	
	//实体移动
	
	
	this->x += this->vx;
	this->y += this->vy;
}