#include "prop.h"
#include "image.h"
#include "gamescene.h"
#include "audio.h"

using namespace ImageData;

void Prop::Draw(Camera* camera) {
	//绘制道具

	//不绘制缓冲区以外的图像
	if (this->x < camera->x - 300 - 300 || this->x > camera->x + 500 + 300)
		return;

	this->EntityDraw(camera);//显示碰撞箱
	IMAGE flipImg;
	switch (type) {
	case coin:
		transparentimage(NULL, 300 + this->x - camera->x, this->y + this->createTime, &coinImg[effF], &flipImg);
		break;
	case sunflower:
		transparentimage(NULL, 300 + this->x - camera->x, this->y + this->createTime, &sunflowerImg[effF], &flipImg);
		break;
	case rmushroom:
		transparentimage(NULL, 300 + this->x - camera->x, this->y + this->createTime, &rmushroomImg, &flipImg, this->dir);
		break;
	case gmushroom:
		transparentimage(NULL, 300 + this->x - camera->x, this->y + this->createTime, &gmushroomImg, &flipImg, this->dir);
		break;
	case star:
		transparentimage(NULL, 300 + this->x - camera->x, this->y + this->createTime, &starImg[effF], &flipImg, this->dir);
		break;
	}
}

void Prop::Update(GameScene* gamescene) {
	//更新道具

	if (this->type != coin) {//金币不参与
		//离开缓冲区将销毁对象
		if (this->y > 700 || this->x < gamescene->camera->x - 300 - 300 || this->x > gamescene->camera->x + 500 + 300)
			this->Destroy(gamescene);
	}

	switch (type) {//特效动画帧与计数器刷新
	case coin:
		if (this->effCnt != 20) {
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
	case sunflower:
	case star:
		if (this->effCnt != 5) {
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
	}
	if (this->createTime != 0) {
		if (rand() % 3 == 0)
			this->createTime--;
	}
	else {
		this->EntityUpdate();//调用实体类更新函数
	}
}

void Prop::Destroy(GameScene* gamescene) {
	//销毁道具对象
	for (int i = 0; i < gamescene->vecProp.size; i++)
	{//遍历道具类动态数组寻找相应对象
		class Prop* pProp = (class Prop*)gamescene->vecProp.get(&gamescene->vecProp, i);
		if (pProp == this) {
			//清除对象
			gamescene->vecProp.remove(&gamescene->vecProp, i);
			free(pProp);
			//playAudio("coin");//提示音
			break;
		}
	}
}

void PropDraw(GameScene* g) {
	//绘制道具入口
	for (int i = 0; i < g->vecProp.size; i++)
	{//遍历所有道具进行绘制
		class Prop* pProp = (class Prop*)g->vecProp.get(&g->vecProp, i);
		pProp->Draw(g->camera);
	}
}

void PropUpdate(GameScene* g) {
	//更新道具入口
	for (int i = 0; i < g->vecProp.size; i++)
	{//遍历所有道具进行更新
		class Prop* pProp = (class Prop*)g->vecProp.get(&g->vecProp, i);
		pProp->Update(g);
	}
}

void addProp(GameScene* gamescene, int x, int y, propType type) {
	//添加方块对象
	class Prop* pProp = (class Prop*)malloc(sizeof(class Prop));
	if (pProp == NULL)
		return;
	pProp->x = x;
	pProp->y = y;
	pProp->dir = 1;
	pProp->width = 40;
	pProp->height = 40;
	pProp->is_land = true;
	pProp->effF = 0;
	pProp->effCnt = 0;
	switch (type) {
	case coin:
		pProp->type = coin;
		pProp->vx = 0;
		pProp->vy = 0;
		pProp->physic = false;
		pProp->createTime = 0;
		break;
	case rmushroom:
		pProp->type = rmushroom;
		pProp->vx = 1;
		pProp->vy = 0;
		pProp->physic = true;
		pProp->createTime = 28;
		playAudio("powerup_appears");
		break;
	case gmushroom:
		pProp->type = gmushroom;
		pProp->vx = 1;
		pProp->vy = 0;
		pProp->physic = true;
		pProp->createTime = 28;
		playAudio("powerup_appears");
		break;
	case star:
		pProp->type = star;
		pProp->vx = 2;
		pProp->vy = rand() % (-6 - -9 + 1) + -9;
		pProp->physic = true;
		pProp->createTime = 28;
		playAudio("powerup_appears");
		break;
	case sunflower:
		pProp->type = sunflower;
		pProp->vx = 0;
		pProp->vy = 0;
		pProp->physic = false;
		pProp->createTime = 28;
		playAudio("powerup_appears");
		break;
	}
	gamescene->vecProp.append(&gamescene->vecProp, pProp);
}

void PropInit(GameScene* gamescene) {
	//初始化道具
	switch (gamescene->level->name) {
	case level1_1_pipe:
		addProp(gamescene, 161, 362, coin);
		addProp(gamescene, 161, 282, coin);
		addProp(gamescene, 201, 362, coin);
		addProp(gamescene, 201, 282, coin);
		addProp(gamescene, 201, 202, coin);
		addProp(gamescene, 241, 362, coin);
		addProp(gamescene, 241, 282, coin);
		addProp(gamescene, 241, 202, coin);
		addProp(gamescene, 281, 362, coin);
		addProp(gamescene, 281, 282, coin);
		addProp(gamescene, 281, 202, coin);
		addProp(gamescene, 321, 362, coin);
		addProp(gamescene, 321, 282, coin);
		addProp(gamescene, 321, 202, coin);
		addProp(gamescene, 361, 362, coin);
		addProp(gamescene, 361, 282, coin);
		addProp(gamescene, 361, 202, coin);
		addProp(gamescene, 401, 362, coin);
		addProp(gamescene, 401, 282, coin);
		break;
	case level1_2:
		addProp(gamescene, 1610, 322, coin);
		addProp(gamescene, 1810, 322, coin);
		addProp(gamescene, 1650, 202, coin);
		addProp(gamescene, 1690, 202, coin);
		addProp(gamescene, 1730, 202, coin);
		addProp(gamescene, 1770, 202, coin);
		addProp(gamescene, 2335, 322, coin);
		addProp(gamescene, 2375, 322, coin);
		addProp(gamescene, 2415, 322, coin);
		addProp(gamescene, 2455, 322, coin);
		addProp(gamescene, 2737, 322, coin);
		addProp(gamescene, 3381, 202, coin);
		addProp(gamescene, 3421, 202, coin);
		addProp(gamescene, 3461, 202, coin);
		addProp(gamescene, 3501, 202, coin);
		addProp(gamescene, 3541, 202, coin);
		addProp(gamescene, 3581, 202, coin);
		break;
	case level1_2_pipe:
		addProp(gamescene, 119, 482, coin);
		addProp(gamescene, 159, 482, coin);
		addProp(gamescene, 199, 482, coin);
		addProp(gamescene, 239, 482, coin);
		addProp(gamescene, 279, 482, coin);
		addProp(gamescene, 319, 482, coin);
		addProp(gamescene, 359, 482, coin);
		addProp(gamescene, 399, 482, coin);
		addProp(gamescene, 439, 482, coin);
		addProp(gamescene, 479, 482, coin);
		addProp(gamescene, 159, 322, coin);
		addProp(gamescene, 199, 322, coin);
		addProp(gamescene, 239, 322, coin);
		addProp(gamescene, 279, 322, coin);
		addProp(gamescene, 319, 322, coin);
		addProp(gamescene, 359, 322, coin);
		addProp(gamescene, 399, 322, coin);
		addProp(gamescene, 439, 322, coin);
		break;
	case level1_3:
		addProp(gamescene, 1207, 162, coin);
		addProp(gamescene, 1247, 162, coin);
		addProp(gamescene, 1287, 162, coin);
		addProp(gamescene, 1448, 444, coin);
		addProp(gamescene, 1609, 82, coin);
		addProp(gamescene, 1649, 82, coin);
		addProp(gamescene, 2133, 243, coin);
		addProp(gamescene, 2173, 243, coin);
		addProp(gamescene, 2535, 162, coin);
		addProp(gamescene, 2575, 162, coin);
		addProp(gamescene, 2615, 162, coin);
		addProp(gamescene, 2655, 162, coin);
		addProp(gamescene, 3541, 202, coin);
		addProp(gamescene, 3581, 202, coin);
		addProp(gamescene, 3905, 162, coin);
		addProp(gamescene, 3945, 162, coin);
		addProp(gamescene, 4065, 162, coin);
		addProp(gamescene, 4105, 162, coin);
		addProp(gamescene, 4709, 484, coin);
		addProp(gamescene, 4749, 484, coin);
		addProp(gamescene, 4789, 484, coin);
		addProp(gamescene, 4990, 202, coin);
		addProp(gamescene, 5030, 202, coin);
		break;
	}
}