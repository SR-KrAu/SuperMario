#include "fireball.h"
#include "gamescene.h"
#include "image.h"

using namespace ImageData;

void Fireball::Draw(Camera* camera) {
	//���ƻ������

	//�����ƻ����������ͼ��
	if (this->x < camera->x - 300 - 300 || this->x > camera->x + 500 + 300)
		return;

	this->EntityDraw(camera);//��ʾ��ײ��
	IMAGE flipimg;
	transparentimage(NULL, 300 + this->x - camera->x, this->y, &fireballImg[this->effF], &flipimg);
}

void Fireball::Update(GameScene* gamescene) {
	//���»������
	//�뿪�����������ٶ���
	if (this->y > 700 || this->x < gamescene->camera->x - 300 - 300 || this->x > gamescene->camera->x + 500 + 300)
		this->Destroy(gamescene);
	//��Ч����֡ˢ��
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
	this->EntityUpdate();//����ʵ������º���
}

void Fireball::Destroy(GameScene* gamescene) {
	//���ٻ������
	for (int i = 0; i < gamescene->vecFireball.size; i++)
	{//���������ද̬����Ѱ����Ӧ����
		class Fireball* pFireball = (class Fireball*)gamescene->vecFireball.get(&gamescene->vecFireball, i);
		if (pFireball == this) {
			//�������
			gamescene->vecFireball.remove(&gamescene->vecFireball, i);
			free(pFireball);
			//playAudio("coin");//��ʾ��
			break;
		}
	}
}

void FireballDraw(GameScene* g) {
	//���ƻ������
	for (int i = 0; i < g->vecFireball.size; i++)
	{//�������л�����л���
		class Fireball* pFireball = (class Fireball*)g->vecFireball.get(&g->vecFireball, i);
		pFireball->Draw(g->camera);
	}
}

void FireballUpdate(GameScene* g) {
	//���»������
	for (int i = 0; i < g->vecFireball.size; i++)
	{//�������л�����и���
		class Fireball* pFireball = (class Fireball*)g->vecFireball.get(&g->vecFireball, i);
		pFireball->Update(g);
	}
}

void addFireball(GameScene* gamescene) {
	//��ӻ������
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