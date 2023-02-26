#include "level.h"
#include "image.h"
#include "gamescene.h"
#include <stdio.h>

void Level::Init(GameScene* gamescene) {
	//��ʼ���������

	this->name = gamescene->levelname;//������������

	switch (name) {//������������
	case level1_1:
	case level1_2_ground:
	case level1_3:
		type = ground;//����
		break;
	case level1_1_pipe:
	case level1_2:
	case level1_2_pipe:
		type = underground;//����
		break;
	case level1_4:
		type = castle;//�Ǳ�
		break;
	}

	switch (name) {//���������ʶ����logo
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

	loadImages(name, type);//������ͼ
}