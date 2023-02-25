#include "monster.h"
#include "image.h"
#include "gamescene.h"
#include <math.h>

using namespace ImageData;

void Monster::Draw(Camera* camera) {
	//���ƹ������

	if (this->is_exist == false)//δ���ɵĹ��ﲻ�������
		return;

	//�����ƻ����������ͼ��
	if (this->x < camera->x - 300 - 300 || this->x > camera->x + 500 + 300)
		return;

	this->EntityDraw(camera);//��ʾ��ײ��

	IMAGE flipImg;
	switch (this->type) {
	case chestnut:
		if (this->status == handstand)
			transparentimage(NULL, 300 + this->x - camera->x, this->y, &chestnutImg[this->effF], &flipImg, 2);
		else
			transparentimage(NULL, 300 + this->x - camera->x, this->y, &chestnutImg[this->effF], &flipImg, this->dir);
		break;
	case tortoise:
		if (this->type2 == gtortoise) {
			if (this->status == handstand)
				transparentimage(NULL, 300 + this->x - camera->x, this->y - 20, &tortoiseImg[2], &flipImg, 2);
			else if (this->status == shrunkenheaded)
				transparentimage(NULL, 300 + this->x - camera->x, this->y - 20, &tortoiseImg[2], &flipImg, -this->dir);
			else
				transparentimage(NULL, 300 + this->x - camera->x, this->y - 20, &tortoiseImg[this->effF], &flipImg, -this->dir);
		}
		else if (this->type2 == rtortoise) {
			if (this->status == handstand)
				transparentimage(NULL, 300 + this->x - camera->x, this->y - 20, &rtortoiseImg[2], &flipImg, 2);
			else if (this->status == shrunkenheaded)
				transparentimage(NULL, 300 + this->x - camera->x, this->y - 20, &rtortoiseImg[2], &flipImg, -this->dir);
			else
				transparentimage(NULL, 300 + this->x - camera->x, this->y - 20, &rtortoiseImg[this->effF], &flipImg, -this->dir);
		}
		else if (this->type2 == flyrtortoise) {
			transparentimage(NULL, 300 + this->x - camera->x, this->y - 20, &flytortoiseImg[this->effF], &flipImg, 1);
		}
		break;
	case piranha:
		transparentimage(NULL, 300 + this->x - camera->x, this->y, &piranhaImg[this->effF], &flipImg, 1);
		break;
	}
}

void Monster::Update(GameScene* gamescene) {
	//���¹������

	//ˢ��
	if (this->x < gamescene->camera->x + 500 + 200 && this->is_exist == false) {
		//playAudio("coin");
		this->is_exist = true;
	}

	if (this->is_exist == false)//δ���ɵĹ��ﲻ�������и���
		return;

	//�뿪�����������ٶ���
	if (this->y > 700 || this->x < gamescene->camera->x - 300 - 300 || this->x > gamescene->camera->x + 500 + 300)
		this->Destroy(gamescene);

	//ʳ�˻������ƶ�
	if (this->type == piranha) {
		if (this->vy > 0 && this->y == this->piranha_y + this->height) {
			this->vy = 0;
			this->piranha_time = 200;
		}
		if (this->vy < 0 && this->y == this->piranha_y - this->height + 1) {
			this->vy = 0;
			this->piranha_time = 200;
		}
		if (this->piranha_time != 0) {
			this->piranha_time--;
			if (this->piranha_time == 0) {
				if (this->y == this->piranha_y + this->height)
					this->vy = -1;
				else
					this->vy = 1;
			}
		}
	}

	//�����ڹ������ƶ�
	if (this->type2 == flyrtortoise) {
		if (this->vy > 0 && this->y >= 450)
			this->vy = -1;
		if (this->vy < 0 && this->y <= 150)
			this->vy = 1;
	}

	//������������ˢ��
	if (this->deathCnt != 0) {
		this->deathCnt--;
		this->effF = 2;
		if (this->deathCnt == 0)
			this->Destroy(gamescene);
		return;
	}

	this->EntityUpdate();//����ʵ������º���

	if (this->status == handstand) {//���������Ĺ���̶�״̬
		this->is_land = false;
		return;
	}

	//��Ч����֡ˢ��
	if (this->effCnt != 10) {
		this->effCnt++;
	}
	else {
		if (this->effF != 1) {
			this->effF++;
		}
		else {
			this->effF = 0;
		}
		this->effCnt = 0;
	}

}

void Monster::Destroy(GameScene* gamescene) {
	//���ٹ������
	for (int i = 0; i < gamescene->vecMonster.size; i++)
	{//���������ද̬����Ѱ����Ӧ����
		class Monster* pMonster = (class Monster*)gamescene->vecMonster.get(&gamescene->vecMonster, i);
		if (pMonster == this) {
			//�������
			gamescene->vecMonster.remove(&gamescene->vecMonster, i);
			free(pMonster);
			//playAudio("coin");//��ʾ��
			break;
		}
	}
}

void MonsterDraw(GameScene* g) {
	//���ƹ������
	for (int i = 0; i < g->vecMonster.size; i++)
	{//�������й�����л���
		class Monster* pMonster = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		pMonster->Draw(g->camera);
	}
}

void MonsterUpdate(GameScene* g) {
	//���¹������
	for (int i = 0; i < g->vecMonster.size; i++)
	{//�������й�����л���
		class Monster* pMonster = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		pMonster->Update(g);
	}
}

void addMonster(GameScene* gamescene, int x, int y, monsterType type, monsterType2 type2 = null) {
	//��ӹ���
	if (abs(x - gamescene->mario->x) <= 200)//ʹ�����������ʱ�����Ĺ��ﲻˢ��
		return;
	class Monster* pMonster = (class Monster*)malloc(sizeof(class Monster));
	if (pMonster == NULL)
		return;
	pMonster->x = x;
	pMonster->y = y;
	pMonster->vx = -1;
	pMonster->vy = 0;
	pMonster->dir = -1;
	pMonster->width = 40;
	pMonster->height = 40;
	pMonster->physic = true;
	pMonster->is_land = true;
	pMonster->is_exist = false;
	pMonster->effF = 0;
	pMonster->effCnt = 0;
	pMonster->deathCnt = 0;
	pMonster->type = type;
	pMonster->type2 = type2;
	pMonster->status = normal;
	switch (type) {
	case piranha:
		pMonster->height = 60;
		pMonster->piranha_y = y;
		pMonster->physic = false;
		pMonster->piranha_time = 0;
		pMonster->vx = 0;
		pMonster->vy = -1;
		break;
	case tortoise:
		if (pMonster->type2 == flyrtortoise) {
			pMonster->vx = 0;
			pMonster->vy = 1;
			pMonster->physic = false;
		}
		break;
	}
	gamescene->vecMonster.append(&gamescene->vecMonster, pMonster);
}

void MonsterInit(GameScene* gamescene) {
	//��ʼ������
	switch (gamescene->level->name) {
	case level1_1:
		addMonster(gamescene, 1047, 484, chestnut);
		addMonster(gamescene, 1773, 484, chestnut);
		addMonster(gamescene, 2118, 484, chestnut);
		addMonster(gamescene, 2168, 484, chestnut);
		addMonster(gamescene, 3270, 160, chestnut);
		addMonster(gamescene, 3320, 160, chestnut);
		addMonster(gamescene, 4020, 484, chestnut);
		addMonster(gamescene, 4070, 484, chestnut);
		addMonster(gamescene, 4872, 484, chestnut);
		addMonster(gamescene, 4922, 484, chestnut);
		addMonster(gamescene, 5271, 484, chestnut);
		addMonster(gamescene, 5321, 484, chestnut);
		addMonster(gamescene, 5451, 350, chestnut);
		addMonster(gamescene, 7024, 484, chestnut);
		addMonster(gamescene, 7074, 484, chestnut);
		addMonster(gamescene, 4588, 484, tortoise, gtortoise);
		break;
	case level1_2:
		addMonster(gamescene, 600, 482, chestnut);
		addMonster(gamescene, 650, 482, chestnut);
		addMonster(gamescene, 1180, 482, chestnut);
		addMonster(gamescene, 1815, 482, tortoise, gtortoise);
		addMonster(gamescene, 1865, 482, tortoise, gtortoise);
		addMonster(gamescene, 2340, 482, tortoise, gtortoise);
		addMonster(gamescene, 2500, 482, chestnut);
		addMonster(gamescene, 2550, 482, chestnut);
		addMonster(gamescene, 2945, 135, chestnut);
		addMonster(gamescene, 3150, 322, chestnut);
		addMonster(gamescene, 3200, 322, chestnut);
		addMonster(gamescene, 3985, 482, chestnut);
		addMonster(gamescene, 4035, 482, chestnut);
		addMonster(gamescene, 4085, 482, chestnut);
		addMonster(gamescene, 4545, 482, chestnut);
		addMonster(gamescene, 5470, 290, chestnut);
		addMonster(gamescene, 5520, 290, chestnut);
		addMonster(gamescene, 6080, 482, tortoise, rtortoise);
		addMonster(gamescene, 4166, 402, piranha);
		addMonster(gamescene, 4407, 362, piranha);
		addMonster(gamescene, 4649, 443, piranha);
		break;
	case level1_3:
		addMonster(gamescene, 1300, 160, tortoise, rtortoise);
		addMonster(gamescene, 1880, 120, chestnut);
		addMonster(gamescene, 1930, 120, chestnut);
		addMonster(gamescene, 3339, 180, chestnut);
		addMonster(gamescene, 4554, 234, tortoise, rtortoise);
		addMonster(gamescene, 5582, 466, tortoise, rtortoise);
		addMonster(gamescene, 3108, 291, tortoise, flyrtortoise);
		addMonster(gamescene, 4750, 300, tortoise, flyrtortoise);
		break;
	}
}