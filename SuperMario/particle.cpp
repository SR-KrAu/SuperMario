#include "particle.h"
#include "image.h"
#include "gamescene.h"
#include "audio.h"
#include <stdio.h>

using namespace ImageData;

void Particle::Draw(Camera* camera) {
	//��������

	//�����ƻ����������ͼ��
	if (this->x < camera->x - 300 - 300 || this->x > camera->x + 500 + 300)
		return;

	IMAGE flipimg;
	switch (this->type) {
	case particleType::text:
		if (this->time <= 100) {
			settextstyle(30, 0, "΢���ź�");
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
	//��������
	
	//�뿪�����������ٶ���
	if (this->y > 700 || this->x < gamescene->camera->x - 300 - 300 || this->x > gamescene->camera->x + 500 + 300)
		this->Destroy(gamescene);

	//λ���ƶ�
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
		this->vy += 2 * 2 * 40 * 4 * 0.01 / 5 / 5;//��������
		break;
	case flycoin://���н��
		if (this->vy > 7)//���ٷ��н�����Ӷ���
			this->Destroy(gamescene);
		this->vy += 2 * 2 * 40 * 4 * 0.01 / 5 / 5;//��������
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
	case boom://����ը
		if (this->effCnt != 3) {
			this->effCnt++;
		}
		else {
			if (this->effF != 2) {
				this->effF++;
			}
			else {
				this->Destroy(gamescene);//ɾ�������Ӷ���
			}
			this->effCnt = 0;
		}
		break;
	}
	
}

void Particle::Destroy(GameScene* gamescene) {
	//�������Ӷ���
	for (int i = 0; i < gamescene->vecParticle.size; i++)
	{//���������ද̬����Ѱ����Ӧ����
		class Particle* pParticle = (class Particle*)gamescene->vecParticle.get(&gamescene->vecParticle, i);
		if (pParticle == this) {
			//�������ද̬�������������
			gamescene->vecParticle.remove(&gamescene->vecParticle, i);
			free(pParticle);
			//playAudio("powerup");
			break;
		}
	}
}

void ParticleDraw(GameScene* g) {
	//�����������
	for (int i = 0; i < g->vecParticle.size; i++)
	{//�����������ӽ��л���
		class Particle* pParticle = (class Particle*)g->vecParticle.get(&g->vecParticle, i);
		pParticle->Draw(g->camera);
	}
}

void ParticleUpdate(GameScene* g) {
	//�����������
	for (int i = 0; i < g->vecParticle.size; i++)
	{//�����������ӽ��л���
		class Particle* pParticle = (class Particle*)g->vecParticle.get(&g->vecParticle, i);
		pParticle->Update(g);
	}
}

void addParticle(GameScene* gamescene, int x, int y, particleType type, double vx, double vy, const char text[], int time) {
	//������Ӷ���
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