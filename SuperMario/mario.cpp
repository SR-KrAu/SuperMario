#include <stdio.h>
#include "mario.h"
#include "image.h"
#include "event.h"
#include "collisionbox.h"
#include "gamescene.h"
#include "event.h"
#include "audio.h"

using namespace ImageData;

void Mario::Init(GameScene* gamescene) {
	//��ʼ������¶���
	gamescene->mario->x = gamescene->x;
	gamescene->mario->y = gamescene->y;
	gamescene->mario->body = gamescene->body;
	gamescene->mario->width = 40;
	gamescene->mario->vx = 0;
	gamescene->mario->vy = 0;
	gamescene->mario->physic = true;
	gamescene->mario->is_run = false;
	gamescene->mario->is_speed = false;
	gamescene->mario->is_land = false;
	gamescene->mario->is_jump = false;
	gamescene->mario->is_enter = false;
	gamescene->mario->is_flag = false;
	gamescene->mario->is_squat = false;
	gamescene->mario->is_death = false;
	gamescene->mario->is_stealth = false;
	gamescene->mario->fireCnt = 0;
	gamescene->mario->body = gamescene->body;
	gamescene->mario->dir = 1;
	gamescene->mario->mario_dir = 1;
	gamescene->mario->runF = 0;
	gamescene->mario->runCnt = 0;
	gamescene->mario->transf_time = 0;
	gamescene->mario->in_time = 0;
	gamescene->mario->im_time = 0;
	if (gamescene->mario->body == child)
		gamescene->mario->height = 40;
	else
		gamescene->mario->height = 80;
}

void Mario::Draw(GameScene* gamescene) {
	//���������
	this->EntityDraw(gamescene->camera);//��ʾ��ײ��
	IMAGE flipimg;
	IMAGE* marioimg = &childImg[0];
	marioBody body = this->body;
	if (this->is_stealth == true)//����
		return;
	if (this->is_flag == true && gamescene->flag-> x == this->x + 40) {//���������ץ��ͼ��
		int F;
		if (this->runF % 2 == 0)
			F = 7;
		else
			F = 8;
		switch (this->body) {
		case child:		marioimg = &childImg[F];	break;
		case adult:		marioimg = &adultImg[F];	break;
		case old:		marioimg = &oldImg[F];		break;
		}
		transparentimage(NULL, 300 + this->x + 10 - gamescene->camera->x, this->y, marioimg, &flipimg, this->mario_dir);
		return;
	}
	if (this->is_death == true) {
		transparentimage(NULL, 300 + this->x - gamescene->camera->x, this->y, &childImg[6], &flipimg, this->mario_dir);
		//���������������ͼ��
		return;
	}
	if (this->transf_time != 0) {
		switch (body) {
		case child:
			if (this->transf_time % 2 == 0) {
				this->body = adult;
				if (this->is_squat == false)
					this->y -= 40;
			}
			else {
				this->body = child;
			}
			break;
		case adult:
			if (this->transf_time % 2 == 0) {
				this->body = child;
				if (this->is_squat == false)
					this->y += 40;
			}
			else {
				this->body = adult;
			}
			break;
		case old:
			if (this->transf_time % 2 == 0) {
				this->body = adult;
			}
			else {
				this->body = old;
			}
			break;
		}
	}
	switch (this->body) {
	case child:
		if (this->is_jump == true)
			marioimg = &childImg[5];
		else if (this->is_run == false)
			marioimg = &childImg[0];
		else
			marioimg = &childImg[runF];
		break;
	case adult:
		if (this->is_squat == true)
			marioimg = &adultImg[6];
		else if (this->is_jump == true)
			marioimg = &adultImg[5];
		else if (this->is_run == false)
			marioimg = &adultImg[0];
		else
			marioimg = &adultImg[runF];
		break;
	case old:
		if (this->is_squat == true)
			marioimg = &oldImg[6];
		else if (this->fireCnt != 0)
			marioimg = &oldImg[9];
		else if (this->is_jump == true)
			marioimg = &oldImg[5];
		else if (this->is_run == false)
			marioimg = &oldImg[0];
		else
			marioimg = &oldImg[runF];
		break;
	}
	if (this->im_time % 2 == 0) {
		if (this->is_squat == false || this->body == child)
			transparentimage(NULL, 300 + this->x - gamescene->camera->x, this->y, marioimg, &flipimg, this->mario_dir);
		else
			transparentimage(NULL, 300 + this->x - gamescene->camera->x, this->y - 40, marioimg, &flipimg, this->mario_dir);
	}
	if (this->transf_time != 0) {
		if (this->body == child && body == adult) {
			if (this->is_squat == false)
				this->y -= 40;
		}
		if (this->body == adult && body == child) {
			if (this->is_squat == false)
				this->y += 40;
		}
		this->body = body;
	}
}

void Mario::WinUpdate(GameScene* gamescene) {
	//ͨ�ظ���
	if (gamescene->mario->y + gamescene->mario->height >= gamescene->flag->y_) {//ץ��˺�ͣ��ש����
		gamescene->mario->vy = 0;
	}
	if (gamescene->mario->x == gamescene->flag->x - gamescene->mario->width && gamescene->flag->y + 40 >= gamescene->flag->y_ && gamescene->mario->y + gamescene->mario->height >= gamescene->flag->y_) {//�����������
		gamescene->mario->x = gamescene->flag->x + 25;
		gamescene->mario->y = gamescene->flag->y_ + 40 - gamescene->mario->height;
		gamescene->mario->vx = 1;
		playAudio("count_down");
	}
	if (this->x == gamescene->flag->castle_x)//����½���Ǳ�������
		this->is_stealth = true;
	if (gamescene->mario->vx == 1) {//ʱ��תΪ����
		if (gamescene->time > 0) {
			gamescene->time -= 100;
			gamescene->score += 65;
		}
		else {
			stopAudio("count_down");
		}
	}
	switch (gamescene->level->name) {//ͨ�ض�������
	case level1_1:
		if (this->x > 8600 && this->is_stealth == true) {
			gamescene->camera->x = 8320;
			this->is_stealth = false;
			this->x = 8250;
			playAudio("ground");
		}
		if (this->x + this->width == 8532 && this->is_stealth == false) {
			stopAudio("ground");
		}
		break;
	case level1_2_ground:
		if (this->x + this->width == 1535) {
			gamescene->levelname = level1_3;
			gamescene->x = 202;
			gamescene->y = 524 - gamescene->mario->height;
			GameSceneReloadEvent(gamescene);
		}
		break;
	case level1_3:
		if (this->x + this->width == 6920) {
			gamescene->levelname = level1_4;
			gamescene->x = 115;
			gamescene->y = 199;
			GameSceneReloadEvent(gamescene);
		}
		break;
	}

}
	
void Mario::Update(GameScene* gamescene) {
	//���������

	if (gamescene->coin == 100) {//�������100��һ����
		gamescene->life++;
		playAudio("one_up");
		gamescene->coin = 0;
	}

	gamescene->mario->EntityUpdate();//����ʵ��������ݸ���(���³����ʵ���ƶ�)

	MarioTouchBorderEvent(gamescene->mario, gamescene->camera);//����½Ӵ���ͼ�߽��¼�

	if (gamescene->mario->is_enter == false && gamescene->mario->is_flag == false)
		MarioSlowEvent(gamescene->mario);//����¼����¼�(Ħ����)

	if (this->is_death == true && this->y > 10000)
		GameSceneReloadEvent(gamescene);//������Ϸ����

	if (this->is_death == true)//����������󲻽������¸���
		return;

	if (gamescene->time <= 0 && this->is_flag == false)//��Ϸʱ�����ʹ���������
		MarioDeathEvent(gamescene);
	

	if (gamescene->mario->y > 600)//�����׹�����º�ʹ������
		MarioDeathEvent(gamescene);

	if (gamescene->mario->fireCnt != 0)//������������ˢ��
		gamescene->mario->fireCnt--;

	if (gamescene->mario->im_time != 0)//����ʱ��ˢ��
		gamescene->mario->im_time--;

	if (gamescene->mario->transf_time != 0) {//����ʱ��ˢ��
		gamescene->mario->transf_time--;
		Sleep(50);//����ʱ��֡����
	}
	if (gamescene->mario->in_time != 0) {//�޵�ʱ��ˢ��
		char imgPath[50];
		int num = rand() % (3 - 1 + 1) + 1;
	for (int i = 0; i < 7; i++) {
		sprintf(imgPath, "resources/image/entity/mario/%d/child%d.png", num, i);
		loadimage(&childImg[i], imgPath);//С��
		sprintf(imgPath, "resources/image/entity/mario/%d/adult%d.png", num, i);
		loadimage(&adultImg[i], imgPath);//����
		loadimage(&oldImg[i], imgPath);//����
	}
	sprintf(imgPath, "resources/image/entity/mario/%d/adult9.png", num);
	loadimage(&oldImg[9], imgPath);//����
		gamescene->mario->in_time--;
		if (gamescene->mario->in_time == 100)
			MarioOffInvincibilityEvent(gamescene);
		if (gamescene->mario->in_time == 0) {
			//�޵�ģʽ���
			for (int i = 0; i < 10; i++) {
				sprintf(imgPath, "resources/image/entity/mario/0/child%d.png", i);
				loadimage(&childImg[i], imgPath);//С��
				sprintf(imgPath, "resources/image/entity/mario/0/adult%d.png", i);
				loadimage(&adultImg[i], imgPath);//����
				sprintf(imgPath, "resources/image/entity/mario/0/old%d.png", i);
				loadimage(&oldImg[i], imgPath);//����
			}
		}
	}

	//���ܵĶ���֡�������ˢ��
	if (gamescene->mario->runCnt < 10) {
		gamescene->mario->runCnt++;
		if(gamescene->mario->is_speed == true)
			gamescene->mario->runCnt++;
	}
	else {
		if (gamescene->mario->runF < 3) {
			gamescene->mario->runF++;
		}
		else if(gamescene->mario->runF != 4){
			gamescene->mario->runF = 0;
		}
		gamescene->mario->runCnt = 0;
	}

	if (gamescene->mario->is_flag == true) //�����ͨ�ظ���
		this->WinUpdate(gamescene);
}