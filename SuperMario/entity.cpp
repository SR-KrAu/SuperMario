#include "entity.h"
#include "event.h"
#include "collisionbox.h"

void Entity::EntityDraw(Camera* camera) {
	ShowCollisionbox(camera, this->x, this->y, this->x + this->width, this->y + this->height);
	//��ʾ��ײ��
}

void Entity::EntityUpdate() {
	//ʵ�����ݸ���

	EntityFallEvent(this);//ʵ��׹���¼�

	//�ı�ʵ�峯��
	if (this->vx > 0 && this->dir != 1)
		this->dir = 1;
	else if(this->vx < 0 && this->dir != -1)
		this->dir = -1;
	
	//ʵ���ƶ�
	
	
	this->x += this->vx;
	this->y += this->vy;
}