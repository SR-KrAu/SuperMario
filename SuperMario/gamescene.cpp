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
	ExMessage msg;//消息处理
	bool w = false, s = false, a = false, d = false, j = false, k = false, t = false;
	int j_trigger = 0;
}

using namespace ImageData;
using namespace GameSceneData;

void GameSceneDraw(GameScene* gamescene) {
	//绘制游戏场景
	cleardevice();//清空绘图窗口
	if (gamescene->loadCnt == 0) {
		putimage(300 - gamescene->camera->x, 0, &levelImg);//绘制世界背景
		WallDraw(gamescene);//绘制墙体
		PropDraw(gamescene);//绘制道具
		BlockDraw(gamescene);//绘制方块
		PlatformDraw(gamescene);//绘制平台
		gamescene->flag->Draw(gamescene->camera);//绘制旗帜
		MonsterDraw(gamescene);//绘制怪物
		gamescene->mario->Draw(gamescene);//绘制马里奥
		FireballDraw(gamescene);//绘制火球
		ParticleDraw(gamescene);//绘制粒子
		PipeDraw(gamescene);//绘制管道
	}
	GUIDraw(gamescene);//绘制GUI
	if (gamescene->loadCnt != 1)
		FlushBatchDraw();//执行批量绘图
}

void GameSceneControl(GameScene* gamescene) {
	//控制游戏场景

	if (gamescene->loadCnt != 0)
		return;//场景加载时无法进行控制

	if (gamescene->mario->is_death == true || gamescene->mario->is_enter == true || gamescene->mario->is_flag == true)
		return;//马里奥死亡或进入管道或抓旗后无法进行控制

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

	//按键结果反馈
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

	if (s && gamescene->mario->is_squat == false)//下蹲
		MarioSquatEvent(gamescene->mario);

	if (!s && gamescene->mario->is_squat == true && gamescene->mario->is_land == true)//取消下蹲
		MarioUnSquatEvent(gamescene->mario);

	gamescene->mario->is_speed = j;//加速奔跑

	if (k && gamescene->mario->is_jump == false && gamescene->mario->is_land == true) {
		MarioJumpEvent(gamescene->mario);//跳跃
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
	//更新游戏场景
	if (gamescene->loadCnt != 0) {
		gamescene->loadCnt--;
		if (gamescene->loadCnt == 0) {
			if (gamescene->life != 0)
				GameSceneLoad(gamescene);//加载游戏场景
			else
				exit(1);//关闭程序
		}
	}
	else {
		gamescene->camera->Update(gamescene);//更新摄像机
		gamescene->mario->Update(gamescene);//更新马里奥
		gamescene->flag->Update(gamescene);//更新旗帜
		WallUpdate(gamescene);//更新墙体
		BlockUpdate(gamescene);//更新方块
		PlatformUpdate(gamescene);//更新方块
		FireballUpdate(gamescene);//更新火球
		MonsterUpdate(gamescene);//更新怪物
		PropUpdate(gamescene);//更新道具
		ParticleUpdate(gamescene);//更新粒子
		PipeUpdate(gamescene);//更新管道

		CheckAll(gamescene);//检测所有

		if (gamescene->mario->is_death == false && gamescene->mario->is_enter == false && gamescene->mario->is_flag == false)
			gamescene->time -= 2;//时间减少
	}
}

void GameSceneLoop(GameScene* gamescene) {
	//游戏场景循环
	LARGE_INTEGER startCount, endCount, F;
	QueryPerformanceFrequency(&F);//精准帧率控制
	while (1) {
		QueryPerformanceCounter(&startCount);//精准帧率控制开始计时

		GameSceneDraw(gamescene);//绘制游戏场景

		GameSceneControl(gamescene);//控制游戏场景

		GameSceneUpdate(gamescene);//更新游戏场景

		QueryPerformanceCounter(&endCount);//精准帧率控制结束计时
		long long elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		while (elapse < 10000) {//控制时差(单位：微秒)
			Sleep(1);//休眠1毫秒(开启可减小CPU占用率)
			//当前游戏帧率:100帧/秒
			QueryPerformanceCounter(&endCount);
			elapse = (endCount.QuadPart - startCount.QuadPart) * 1000000 / F.QuadPart;
		}
	}
}

void GameSceneLoad(GameScene* gamescene) {
	//加载游戏场景

	gamescene->level->Init(gamescene);//初始化世界对象
	gamescene->mario->Init(gamescene);//初始化马里奥对象
	gamescene->camera->Init(gamescene);//初始化摄像机对象
	gamescene->flag->Init(gamescene);//初始化旗帜对象

	vectorInit(&gamescene->vecWall);//初始化墙类动态数组
	vectorInit(&gamescene->vecBlock);//初始化方块类动态数组
	vectorInit(&gamescene->vecParticle);//初始化粒子类动态数组
	vectorInit(&gamescene->vecProp);//初始化道具类动态数组
	vectorInit(&gamescene->vecFireball);//初始化火球类动态数组
	vectorInit(&gamescene->vecMonster);//初始化怪物类动态数组
	vectorInit(&gamescene->vecPipe);//初始化管道类动态数组
	vectorInit(&gamescene->vecPlatform);//初始化平台类动态数组

	WallInit(gamescene);//初始化墙体对象
	BlockInit(gamescene);//初始化方块对象
	PropInit(gamescene);//初始化道具对象
	MonsterInit(gamescene);//初始化怪物对象
	PipeInit(gamescene);//初始化管道对象
	PlatformInit(gamescene);//初始化平台对象

	playBGM(gamescene->level);//播放BGM
}

void GameSceneInit(GameScene* gamescene) {
	//初始化游戏场景

	gamescene->level = (class Level*)malloc(sizeof(class Level));//创建世界对象
	gamescene->mario = (class Mario*)malloc(sizeof(class Mario));//创建马里奥对象
	gamescene->camera = (class Camera*)malloc(sizeof(class Camera));//创建摄像机对象
	gamescene->flag = (class Flag*)malloc(sizeof(class Flag));//创建旗帜对象

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

	gamescene->level->Init(gamescene);//初始化世界对象
	
	//设置字体
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	//LOGFONT fontStyle;
	//gettextstyle(&fontStyle);//获取字体样式
	//fontStyle.lfQuality = ANTIALIASED_QUALITY;//开启抗锯齿
	//fontStyle.lfHeight = 40;//调整高度
	//settextstyle(&fontStyle);//设置字体样式

	BeginBatchDraw();//开启批量绘图
}

void GameSceneDestroy(GameScene* gamescene) {
	//销毁游戏场景

	//按键复位
	w = false;
	s = false;
	a = false;
	d = false;
	j = false;
	k = false;
	t = false;
	
	//销毁所有动态数组内对象
	for (int i = 0; i < gamescene->vecWall.size; i++)
	{
		class Wall* p = (class Wall*)gamescene->vecWall.get(&gamescene->vecWall, i);
		p->WallDestroy(gamescene);//销毁对象
	}
	vectorDestroy(&gamescene->vecWall);//销毁动态数组

	for (int i = 0; i < gamescene->vecBlock.size; i++)
	{
		class Block* p = (class Block*)gamescene->vecBlock.get(&gamescene->vecBlock, i);
		p->Destroy(gamescene);//销毁对象
	}
	vectorDestroy(&gamescene->vecBlock);//销毁动态数组


	for (int i = 0; i < gamescene->vecParticle.size; i++)
	{
		class Particle* p = (class Particle*)gamescene->vecParticle.get(&gamescene->vecParticle, i);
		p->Destroy(gamescene);//销毁对象
	}
	vectorDestroy(&gamescene->vecParticle);//销毁动态数组

	for (int i = 0; i < gamescene->vecProp.size; i++)
	{
		class Prop* p = (class Prop*)gamescene->vecProp.get(&gamescene->vecProp, i);
		p->Destroy(gamescene);//销毁对象
	}
	vectorDestroy(&gamescene->vecProp);//销毁动态数组

	for (int i = 0; i < gamescene->vecFireball.size; i++)
	{
		class Fireball* p = (class Fireball*)gamescene->vecFireball.get(&gamescene->vecFireball, i);
		p->Destroy(gamescene);//销毁对象
	}
	vectorDestroy(&gamescene->vecFireball);//销毁动态数组
	
	for (int i = 0; i < gamescene->vecMonster.size; i++)
	{
		class Monster* p = (class Monster*)gamescene->vecMonster.get(&gamescene->vecMonster, i);
		p->Destroy(gamescene);//销毁对象
	}
	vectorDestroy(&gamescene->vecMonster);//销毁动态数组

	for (int i = 0; i < gamescene->vecPipe.size; i++)
	{
		class Pipe* p = (class Pipe*)gamescene->vecPipe.get(&gamescene->vecPipe, i);
		p->Destroy(gamescene);//销毁对象
	}
	vectorDestroy(&gamescene->vecPipe);//销毁动态数组

	for (int i = 0; i < gamescene->vecPlatform.size; i++)
	{
		class Platform* p = (class Platform*)gamescene->vecPlatform.get(&gamescene->vecPlatform, i);
		p->Destroy(gamescene);//销毁对象
	}
	vectorDestroy(&gamescene->vecPlatform);//销毁动态数组
}

void GUIDraw(GameScene* gamescene) {
	//绘制GUI
	settextstyle(40, 0, "微软雅黑");
	char score[10], coin[10], time[10];
	IMAGE flipimg;
	sprintf(score, "%06d", gamescene->score);
	sprintf(coin, "×%02d", gamescene->coin);
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
			sprintf(life, "  ×    %d", gamescene->life);
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