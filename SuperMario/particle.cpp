#include "particle.h"
#include "image.h"
#include "gamescene.h"
#include "audio.h"
#include <stdio.h>

using namespace ImageData;

void Particle::Draw(Camera* camera) {
	//绘制粒子

	//不绘制缓冲区以外的图像
	if (this->x < camera->x - 300 - 300 || this->x > camera->x + 500 + 300)
		return;

	IMAGE flipimg;
	switch (this->type) {
	case particleType::text:
		if (this->time <= 100) {
			settextstyle(30, 0, "微软雅黑");
			outtextxy(300 + this->x - camera->x, this->y, this->text);
		}
		break;
	case brokenbrick:
		putimage(300 + this->x - camera->x, this->y, &brokenbrickImg);
		break;
	case flycoin:
		transparentimage(NULL, 300 + this->x - camera->x, this->y, &flycoinImg[effF], &flipimg);
		break;
	case boom:
		transparentimage(NULL, 300 + this->x - camera->x, this->y, &boomImg[effF], &flipimg);
		break;
	}
}

void Particle::Update(GameScene* gamescene) {
	//更新粒子
	
	//离开缓冲区将销毁对象
	if (this->y > 700 || this->x < gamescene->camera->x - 300 - 300 || this->x > gamescene->camera->x + 500 + 300)
		this->Destroy(gamescene);

	//位置移动
	this->x += this->vx;
	this->y += this->vy;

	switch (this->type) {
	case particleType::text:
		if (this->time != 0)
			this->time--;
		else
			this->Destroy(gamescene);
		break;
	case brokenbrick:
		this->vy += 2 * 2 * 40 * 4 * 0.01 / 5 / 5;//自由落体
		break;
	case flycoin://飞行金币
		if (this->vy > 7)//销毁飞行金币粒子对象
			this->Destroy(gamescene);
		this->vy += 2 * 2 * 40 * 4 * 0.01 / 5 / 5;//自由落体
		if (this->effCnt != 3) {
			this->effCnt++;
		}
		else {
			if (this->effF != 3) {
				this->effF++;
			}
			else {
				this->effF = 0;
			}
			this->effCnt = 0;
		}
		break;
	case boom://火球爆炸
		if (this->effCnt != 3) {
			this->effCnt++;
		}
		else {
			if (this->effF != 2) {
				this->effF++;
			}
			else {
				this->Destroy(gamescene);//删除该粒子对象
			}
			this->effCnt = 0;
		}
		break;
	}
	
}

void Particle::Destroy(GameScene* gamescene) {
	//销毁粒子对象
	for (int i = 0; i < gamescene->vecParticle.size; i++)
	{//遍历粒子类动态数组寻找相应对象
		class Particle* pParticle = (class Particle*)gamescene->vecParticle.get(&gamescene->vecParticle, i);
		if (pParticle == this) {
			//从粒子类动态数组中清除对象
			gamescene->vecParticle.remove(&gamescene->vecParticle, i);
			free(pParticle);
			//playAudio("powerup");
			break;
		}
	}
}

void ParticleDraw(GameScene* g) {
	//绘制粒子入口
	for (int i = 0; i < g->vecParticle.size; i++)
	{//遍历所有粒子进行绘制
		class Particle* pParticle = (class Particle*)g->vecParticle.get(&g->vecParticle, i);
		pParticle->Draw(g->camera);
	}
}

void ParticleUpdate(GameScene* g) {
	//更新粒子入口
	for (int i = 0; i < g->vecParticle.size; i++)
	{//遍历所有粒子进行绘制
		class Particle* pParticle = (class Particle*)g->vecParticle.get(&g->vecParticle, i);
		pParticle->Update(g);
	}
}

void addParticle(GameScene* gamescene, int x, int y, particleType type, double vx, double vy, const char text[], int time) {
	//添加粒子对象
	class Particle* pParticle = (class Particle*)malloc(sizeof(class Particle));
	if (pParticle == NULL)
		return;
	pParticle->x = x;
	pParticle->y = y;
	pParticle->type = type;
	pParticle->vx = vx;
	pParticle->vy = vy;
	sprintf(pParticle->text, text);
	pParticle->effF = 0;
	pParticle->effCnt = 0;
	pParticle->time = time;
	gamescene->vecParticle.append(&gamescene->vecParticle, pParticle);
	if(type == flycoin)
	playAudio("coin");
}