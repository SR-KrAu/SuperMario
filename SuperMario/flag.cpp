#include "flag.h"
#include "image.h"
#include "gamescene.h"

void Flag::Init(GameScene* gamescene) {
	//初始化旗帜
	switch (gamescene->level->name)
	{
	case level1_1:
		this->is_exist = true;
		this->x = 7986;
		this->y = 119;
		this->y_ = 484;
		this->castle_x = 8210;
		this->flagImg = new IMAGE;
		loadimage(this->flagImg, "resources/image/flag/flag.png");
		break;
	case level1_2_ground:
		this->is_exist = true;
		this->x = 1028;
		this->y = 118;
		this->y_ = 483;
		this->castle_x = 1252;
		this->flagImg = new IMAGE;
		loadimage(this->flagImg, "resources/image/flag/flag.png");
		break;
	case level1_3:
		this->is_exist = true;
		this->x = 6294;
		this->y = 119;
		this->y_ = 484;
		this->castle_x = 6560;
		this->flagImg = new IMAGE;
		loadimage(this->flagImg, "resources/image/flag/flag.png");
		break;
	case level1_1_pipe:
	case level1_2:
	case level1_2_pipe:
		this->is_exist = false;
		break;
	}
}

void Flag::Draw(Camera* camera) {
	//绘制旗帜
	if (this->is_exist == false)
		return;
	//不绘制缓冲区以外的图像
	if (this->x > camera->x + 500 + 300)
		return;
	IMAGE flipimg;
	transparentimage(NULL, 300 + this->x - 40 - camera->x, this->y, this->flagImg, &flipimg);
}

void Flag::Update(GameScene* gamescene) {
	//更新旗帜
	if (this->is_exist == false)
		return;
	if (gamescene->mario->is_flag == true && this->y + 40 < this->y_) {
		this->y += 2;
	}
}