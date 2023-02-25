#include "platform.h"
#include "image.h"
#include "gamescene.h"

using namespace ImageData;

void Platform::Draw(Camera* camera) {
	//�����ƻ����������ͼ��
	if (this->x2 < camera->x - 300 - 300 || this->x1 > camera->x + 500 + 300)
		return;
	IMAGE flipimg;
	transparentimage(NULL, 300 + this->x1 - camera->x, this->y1, &platformImg, &flipimg);
}

void Platform::Update(GameScene* gamescene) {
	//�뿪�����������ٶ���
	if (this->x2 < gamescene->camera->x - 300 - 300)
		this->Destroy(gamescene);

	switch (this->type) {
	case up:
		if (this->y2 < 0) {
			this->y1 = 780;
		}
		break;
	case down:
		if (this->y1 > 780) {
			this->y1 = -20;
		}
		break;
	case up_down:
		if ((this->y1 == this->loc1 || this->y2 == this->loc2) && this->vy != 0) {
			this->vy = 0;
			break;
		}
		if (this->y1 == this->loc1 && this->vy == 0)
			this->vy = -1;
		else if (this->y2 == this->loc2 && this->vy == 0)
			this->vy = 1;
		break;
	case right_left:
		if (this->x1 == this->loc1 || this->x2 == this->loc2)
			this->vx = -this->vx;
		break;
	}
	
	this->x1 += this->vx;
	this->y1 += this->vy;
	this->x2 = this->x1 + 121;
	this->y2 = this->y1 + 20;
}

void Platform::Destroy(GameScene* gamescene) {
	//���ٶ���
	for (int i = 0; i < gamescene->vecPlatform.size; i++)
	{//������̬����Ѱ����Ӧ����
		class Platform* pPlatform = (class Platform*)gamescene->vecPlatform.get(&gamescene->vecPlatform, i);
		if (pPlatform == this) {
			//�����Ӧ����
			gamescene->vecPlatform.remove(&gamescene->vecPlatform, i);
			free(pPlatform);
			//playAudio("powerup");
			break;
		}
	}
}

void PlatformDraw(GameScene* g) {
	//����ƽ̨���
	for (int i = 0; i < g->vecPlatform.size; i++)
	{//��������ƽ̨���л���
		class Platform* pPlatform = (class Platform*)g->vecPlatform.get(&g->vecPlatform, i);
		pPlatform->Draw(g->camera);
	}
}

void PlatformUpdate(GameScene* g) {
	//����ƽ̨���
	for (int i = 0; i < g->vecPlatform.size; i++)
	{//��������ƽ̨���и���
		class Platform* pPlatform = (class Platform*)g->vecPlatform.get(&g->vecPlatform, i);
		pPlatform->Update(g);
	}
}

void addPlatform(GameScene* gamescene, platformType type, int x, int y){
	//���ƽ̨����
	class Platform* pPlatform = (class Platform*)malloc(sizeof(class Platform));
	if (pPlatform == NULL)
		return;
	pPlatform->x1 = x;
	pPlatform->y1 = y;
	pPlatform->x2 = x + 121;
	pPlatform->y2 = y + 20;
	pPlatform->type = type;
	switch (type) {
	case down:
		pPlatform->vx = 0;
		pPlatform->vy = 1;
	break;
	case up:
		pPlatform->vx = 0;
		pPlatform->vy = -1;
		break;
	}
	gamescene->vecPlatform.append(&gamescene->vecPlatform, pPlatform);
}

void addPlatform(GameScene* gamescene, platformType type, int x, int y, int loc1, int loc2) {
	//���ƽ̨����
	class Platform* pPlatform = (class Platform*)malloc(sizeof(class Platform));
	if (pPlatform == NULL)
		return;
	pPlatform->x1 = x;
	pPlatform->y1 = y;
	pPlatform->x2 = x + 121;
	pPlatform->y2 = y + 20;
	pPlatform->type = type;
	pPlatform->loc1 = loc1;
	pPlatform->loc2 = loc2;
	switch (type) {
	case up_down:
		pPlatform->vx = 0;
		pPlatform->vy = 1;
		break;
	case right_left:
		pPlatform->vx = 1;
		pPlatform->vy = 0;
		break;
	}
	gamescene->vecPlatform.append(&gamescene->vecPlatform, pPlatform);
}

void PlatformInit(GameScene* gamescene) {
	//��ʼ��ƽ̨
	switch (gamescene->level->name) {
	case level1_2:
		addPlatform(gamescene, down, 5635, 100);
		addPlatform(gamescene, down, 5635, 500);
		addPlatform(gamescene, up, 6239, 160);
		addPlatform(gamescene, up, 6239, 560);
		break;
	case level1_3:
		addPlatform(gamescene, up_down, 2332, 404, 580, 170);
		addPlatform(gamescene, right_left, 3580, 323, 3435, 3810);
		addPlatform(gamescene, right_left, 3902, 363, 3810, 4088);
		addPlatform(gamescene, right_left, 5391, 243, 5246, 5680);
		break;
	}
}