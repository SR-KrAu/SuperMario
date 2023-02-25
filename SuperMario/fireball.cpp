#include "fireball.h"
#include "gamescene.h"
#include "image.h"

using namespace ImageData;

void Fireball::Draw(Camera* camera) {
	//绘制火球对象

	//不绘制缓冲区以外的图像
	if (this->x < camera->x - 300 - 300 || this->x > camera->x + 500 + 300)
		return;

	this->EntityDraw(camera);//显示碰撞箱
	IMAGE flipimg;
	transparentimage(NULL, 300 + this->x - camera->x, this->y, &fireballImg[this->effF], &flipimg);
}

void Fireball::Update(GameScene* gamescene) {
	//更新火球对象
	//离开缓冲区将销毁对象
	if (this->y > 700 || this->x < gamescene->camera->x - 300 - 300 || this->x > gamescene->camera->x + 500 + 300)
		this->Destroy(gamescene);
	//特效动画帧刷新
	if (this->effCnt != 10) {
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
	this->EntityUpdate();//调用实体类更新函数
}

void Fireball::Destroy(GameScene* gamescene) {
	//销毁火球对象
	for (int i = 0; i < gamescene->vecFireball.size; i++)
	{//遍历火球类动态数组寻找相应对象
		class Fireball* pFireball = (class Fireball*)gamescene->vecFireball.get(&gamescene->vecFireball, i);
		if (pFireball == this) {
			//清除对象
			gamescene->vecFireball.remove(&gamescene->vecFireball, i);
			free(pFireball);
			//playAudio("coin");//提示音
			break;
		}
	}
}

void FireballDraw(GameScene* g) {
	//绘制火球入口
	for (int i = 0; i < g->vecFireball.size; i++)
	{//遍历所有火球进行绘制
		class Fireball* pFireball = (class Fireball*)g->vecFireball.get(&g->vecFireball, i);
		pFireball->Draw(g->camera);
	}
}

void FireballUpdate(GameScene* g) {
	//更新火球入口
	for (int i = 0; i < g->vecFireball.size; i++)
	{//遍历所有火球进行更新
		class Fireball* pFireball = (class Fireball*)g->vecFireball.get(&g->vecFireball, i);
		pFireball->Update(g);
	}
}

void addFireball(GameScene* gamescene) {
	//添加火球对象
	class Fireball* pFireball = (class Fireball*)malloc(sizeof(class Fireball));
	if (pFireball == NULL)
		return;
	if (gamescene->mario->mario_dir == 1) {
		pFireball->x = gamescene->mario->x + 30;
	}
	else {
		pFireball->x = gamescene->mario->x;
	}
	pFireball->y = gamescene->mario->y + 20;
	pFireball->vx = 6 * gamescene->mario->mario_dir;
	pFireball->vy = 2;
	pFireball->dir = gamescene->mario->mario_dir;
	pFireball->width = 20;
	pFireball->height = 20;
	pFireball->physic = true;
	pFireball->is_land = false;
	pFireball->effF = 0;
	pFireball->effCnt = 0;
	gamescene->vecFireball.append(&gamescene->vecFireball, pFireball);
}