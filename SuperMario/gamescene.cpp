#include <graphics.h>
#include <stdio.h>
#include "gamescene.h"
#include "audio.h"
#include "image.h"
#include "event.h"
#include "check.h"
#include "block.h"
#include "prop.h"
#include "particle.h"
#include "fireball.h"
#include "monster.h"
#include "pipe.h"
#include "platform.h"

namespace GameSceneData {
	ExMessage msg;//��Ϣ����
	bool w = false, s = false, a = false, d = false, j = false, k = false, t = false;
	int j_trigger = 0;
}

using namespace ImageData;
using namespace GameSceneData;

void GameSceneDraw(GameScene* gamescene) {
	//������Ϸ����
	cleardevice();//��ջ�ͼ����
	if (gamescene->loadCnt == 0) {
		putimage(300 - gamescene->camera->x, 0, &levelImg);//�������米��
		WallDraw(gamescene);//����ǽ��
		PropDraw(gamescene);//���Ƶ���
		BlockDraw(gamescene);//���Ʒ���
		PlatformDraw(gamescene);//����ƽ̨
		gamescene->flag->Draw(gamescene->camera);//��������
		MonsterDraw(gamescene);//���ƹ���
		gamescene->mario->Draw(gamescene);//���������
		FireballDraw(gamescene);//���ƻ���
		ParticleDraw(gamescene);//��������
		PipeDraw(gamescene);//���ƹܵ�
	}
	GUIDraw(gamescene);//����GUI
	if (gamescene->loadCnt != 1)
		FlushBatchDraw();//ִ��������ͼ
}

void GameSceneControl(GameScene* gamescene) {
	//������Ϸ����

	if (gamescene->loadCnt != 0)
		return;//��������ʱ�޷����п���

	if (gamescene->mario->is_death == true || gamescene->mario->is_enter == true || gamescene->mario->is_flag == true)
		return;//��������������ܵ���ץ����޷����п���

	while (peekmessage(&msg, EX_KEY))
	{
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case 'W':		w = true;		break;
			case 'S':		s = true;		break;
			case 'A':		a = true;		break;
			case 'D':		d = true;		break;
			case 'J':		j = true;		break;
			case 'K':		k = true;		break;
			case 'T':		t = true;		break;
			}
		}
		if (msg.message == WM_KEYUP)
		{
			switch (msg.vkcode)
			{
			case 'W':		w = false;		break;
			case 'S':		s = false;		break;
			case 'A':		a = false;		break;
			case 'D':		d = false;		break;
			case 'J':		j = false;		break;
			case 'K':		k = false;		break;
			case 'T':		t = false;		break;
			}
		}
	}

	//�����������
	if (a) {
		gamescene->mario->mario_dir = -1;
		MarioSpeedEvent(gamescene->mario);
		gamescene->mario->is_run = true;
	}

	if (d) {
		gamescene->mario->mario_dir = 1;
		MarioSpeedEvent(gamescene->mario);
		gamescene->mario->is_run = true;
	}

	if (s && gamescene->mario->is_squat == false)//�¶�
		MarioSquatEvent(gamescene->mario);

	if (!s && gamescene->mario->is_squat == true && gamescene->mario->is_land == true)//ȡ���¶�
		MarioUnSquatEvent(gamescene->mario);

	gamescene->mario->is_speed = j;//���ٱ���

	if (k && gamescene->mario->is_jump == false && gamescene->mario->is_land == true) {
		MarioJumpEvent(gamescene->mario);//��Ծ
	}

	if (a == false && d == false && gamescene->mario->is_run == true) {
		gamescene->mario->is_run = false;
	}

	if (j) {
		if (j_trigger == 0)
			j_trigger = 1;
	}
	else {
		j_trigger = 0;
	}

	if (j_trigger == 1) {
		j_trigger = 2;
		if (gamescene->mario->body == old && gamescene->mario->is_squat == false) {
			MarioShootFireballEvent(gamescene);
		}
	}
}

void GameSceneUpdate(GameScene* gamescene) {
	//������Ϸ����
	if (gamescene->loadCnt != 0) {
		gamescene->loadCnt--;
		if (gamescene->loadCnt == 0) {
			if (gamescene->life != 0)
				GameSceneLoad(gamescene);//������Ϸ����
			else
				exit(1);//�رճ���
		}
	}
	else {
		gamescene->camera->Update(gamescene);//���������
		gamescene->mario->Update(gamescene);//���������
		gamescene->flag->Update(gamescene);//��������
		WallUpdate(gamescene);//����ǽ��
		BlockUpdate(gamescene);//���·���
		PlatformUpdate(gamescene);//���·���
		FireballUpdate(gamescene);//���»���
		MonsterUpdate(gamescene);//���¹���
		PropUpdate(gamescene);//���µ���
		ParticleUpdate(gamescene);//��������
		PipeUpdate(gamescene);//���¹ܵ�

		CheckAll(gamescene);//�������

		if (gamescene->mario->is_death == false && gamescene->mario->is_enter == false && gamescene->mario->is_flag == false)
			gamescene->time -= 2;//ʱ�����
	}
}

void GameSceneLoop(GameScene* gamescene) {
	//��Ϸ����ѭ��
	LARGE_INTEGER startCount, endCount, F;
	QueryPerformanceFrequency(&F);//��׼֡�ʿ���
	while (1) {
		QueryPerformanceCounter(&startCount);//��׼֡�ʿ��ƿ�ʼ��ʱ

		GameSceneDraw(gamescene);//������Ϸ����

		GameSceneControl(gamescene);//������Ϸ����

		GameSceneUpdate(gamescene);//������Ϸ����

		QueryPerformanceCounter(&endCount);//��׼֡�ʿ��ƽ�����ʱ
		long long elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		while (elapse < 10000) {//����ʱ��(��λ��΢��)
			Sleep(1);//����1����(�����ɼ�СCPUռ����)
			//��ǰ��Ϸ֡��:100֡/��
			QueryPerformanceCounter(&endCount);
			elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		}
	}
}

void GameSceneLoad(GameScene* gamescene) {
	//������Ϸ����

	gamescene->level->Init(gamescene);//��ʼ���������
	gamescene->mario->Init(gamescene);//��ʼ������¶���
	gamescene->camera->Init(gamescene);//��ʼ�����������
	gamescene->flag->Init(gamescene);//��ʼ�����Ķ���

	vectorInit(&gamescene->vecWall);//��ʼ��ǽ�ද̬����
	vectorInit(&gamescene->vecBlock);//��ʼ�������ද̬����
	vectorInit(&gamescene->vecParticle);//��ʼ�������ද̬����
	vectorInit(&gamescene->vecProp);//��ʼ�������ද̬����
	vectorInit(&gamescene->vecFireball);//��ʼ�������ද̬����
	vectorInit(&gamescene->vecMonster);//��ʼ�������ද̬����
	vectorInit(&gamescene->vecPipe);//��ʼ���ܵ��ද̬����
	vectorInit(&gamescene->vecPlatform);//��ʼ��ƽ̨�ද̬����

	WallInit(gamescene);//��ʼ��ǽ�����
	BlockInit(gamescene);//��ʼ���������
	PropInit(gamescene);//��ʼ�����߶���
	MonsterInit(gamescene);//��ʼ���������
	PipeInit(gamescene);//��ʼ���ܵ�����
	PlatformInit(gamescene);//��ʼ��ƽ̨����

	playBGM(gamescene->level);//����BGM
}

void GameSceneInit(GameScene* gamescene) {
	//��ʼ����Ϸ����

	gamescene->level = (class Level*)malloc(sizeof(class Level));//�����������
	gamescene->mario = (class Mario*)malloc(sizeof(class Mario));//��������¶���
	gamescene->camera = (class Camera*)malloc(sizeof(class Camera));//�������������
	gamescene->flag = (class Flag*)malloc(sizeof(class Flag));//�������Ķ���

	gamescene->loadCnt = 100;
	gamescene->body = child;

	gamescene->levelname = level1_1;
	gamescene->x = 300;
	gamescene->y = 484;

	/*gamescene->levelname = level1_3;
	gamescene->x = 2750;
	gamescene->y = 30;*/

	gamescene->life = 3;
	gamescene->score = 0;
	gamescene->coin = 0;
	gamescene->time = 40000;

	gamescene->level->Init(gamescene);//��ʼ���������
	
	//��������
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	//LOGFONT fontStyle;
	//gettextstyle(&fontStyle);//��ȡ������ʽ
	//fontStyle.lfQuality = ANTIALIASED_QUALITY;//���������
	//fontStyle.lfHeight = 40;//�����߶�
	//settextstyle(&fontStyle);//����������ʽ

	BeginBatchDraw();//����������ͼ
}

void GameSceneDestroy(GameScene* gamescene) {
	//������Ϸ����

	//������λ
	w = false;
	s = false;
	a = false;
	d = false;
	j = false;
	k = false;
	t = false;
	
	//�������ж�̬�����ڶ���
	for (int i = 0; i < gamescene->vecWall.size; i++)
	{
		class Wall* p = (class Wall*)gamescene->vecWall.get(&gamescene->vecWall, i);
		p->WallDestroy(gamescene);//���ٶ���
	}
	vectorDestroy(&gamescene->vecWall);//���ٶ�̬����

	for (int i = 0; i < gamescene->vecBlock.size; i++)
	{
		class Block* p = (class Block*)gamescene->vecBlock.get(&gamescene->vecBlock, i);
		p->Destroy(gamescene);//���ٶ���
	}
	vectorDestroy(&gamescene->vecBlock);//���ٶ�̬����


	for (int i = 0; i < gamescene->vecParticle.size; i++)
	{
		class Particle* p = (class Particle*)gamescene->vecParticle.get(&gamescene->vecParticle, i);
		p->Destroy(gamescene);//���ٶ���
	}
	vectorDestroy(&gamescene->vecParticle);//���ٶ�̬����

	for (int i = 0; i < gamescene->vecProp.size; i++)
	{
		class Prop* p = (class Prop*)gamescene->vecProp.get(&gamescene->vecProp, i);
		p->Destroy(gamescene);//���ٶ���
	}
	vectorDestroy(&gamescene->vecProp);//���ٶ�̬����

	for (int i = 0; i < gamescene->vecFireball.size; i++)
	{
		class Fireball* p = (class Fireball*)gamescene->vecFireball.get(&gamescene->vecFireball, i);
		p->Destroy(gamescene);//���ٶ���
	}
	vectorDestroy(&gamescene->vecFireball);//���ٶ�̬����
	
	for (int i = 0; i < gamescene->vecMonster.size; i++)
	{
		class Monster* p = (class Monster*)gamescene->vecMonster.get(&gamescene->vecMonster, i);
		p->Destroy(gamescene);//���ٶ���
	}
	vectorDestroy(&gamescene->vecMonster);//���ٶ�̬����

	for (int i = 0; i < gamescene->vecPipe.size; i++)
	{
		class Pipe* p = (class Pipe*)gamescene->vecPipe.get(&gamescene->vecPipe, i);
		p->Destroy(gamescene);//���ٶ���
	}
	vectorDestroy(&gamescene->vecPipe);//���ٶ�̬����

	for (int i = 0; i < gamescene->vecPlatform.size; i++)
	{
		class Platform* p = (class Platform*)gamescene->vecPlatform.get(&gamescene->vecPlatform, i);
		p->Destroy(gamescene);//���ٶ���
	}
	vectorDestroy(&gamescene->vecPlatform);//���ٶ�̬����
}

void GUIDraw(GameScene* gamescene) {
	//����GUI
	settextstyle(40, 0, "΢���ź�");
	char score[10], coin[10], time[10];
	IMAGE flipimg;
	sprintf(score, "%06d", gamescene->score);
	sprintf(coin, "��%02d", gamescene->coin);
	sprintf(time, "%03d", gamescene->time / 100);
	outtextxy(50, 10, "MARIO");
	outtextxy(450, 10, "WORLD");
	outtextxy(650, 10, "TIME");
	outtextxy(50, 40, score);
	outtextxy(270, 40, coin);
	if (gamescene->time != 40000)
		outtextxy(660, 40, time);
	outtextxy(475, 40, gamescene->level->logo);
	transparentimage(NULL, 235, 40, &coinImg[0], &flipimg);
	if (gamescene->loadCnt != 0) {
		if (gamescene->life != 0) {
			char life[11];
			sprintf(life, "  ��    %d", gamescene->life);
			outtextxy(250, 250, "WORLD");
			outtextxy(350, 300, life);
			outtextxy(420, 250, gamescene->level->logo);
			transparentimage(NULL, 300, 300, &childImg[0], &flipimg);
		}
		else {
			outtextxy(275, 300, "GAME    OVER");
		}
	}
}