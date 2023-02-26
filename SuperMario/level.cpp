#include "level.h"
#include "image.h"
#include "gamescene.h"
#include <stdio.h>

void Level::Init(GameScene* gamescene) {
	//初始化世界对象

	this->name = gamescene->levelname;//设置世界名称

	switch (name) {//设置世界类型
	case level1_1:
	case level1_2_ground:
	case level1_3:
		type = ground;//地面
		break;
	case level1_1_pipe:
	case level1_2:
	case level1_2_pipe:
		type = underground;//地下
		break;
	case level1_4:
		type = castle;//城堡
		break;
	}

	switch (name) {//设置世界标识名称logo
	case level1_1:
	case level1_1_pipe:
		sprintf(logo, "1 - 1");
		break;
	case level1_2:
	case level1_2_pipe:
	case level1_2_ground:
		sprintf(logo, "1 - 2");
		break;
	case level1_3:
		sprintf(logo, "1 - 3");
		break;
	case level1_4:
		sprintf(logo, "1 - 4");
		break;
	}

	loadImages(name, type);//加载贴图
}