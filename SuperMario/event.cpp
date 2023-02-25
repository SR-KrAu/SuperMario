#include "event.h"
#include "audio.h"
#include "block.h"
#include "particle.h"
#include "fireball.h"
#include "check.h"
#include "image.h"
#include "mario.h"
#include "wall.h"
#include "prop.h"
#include "fireball.h"
#include "monster.h"
#include "pipe.h"
#include "gamescene.h"
#include <math.h>

using namespace ImageData;

void MarioTouchFlagEvent(GameScene* gamescene) {
	//马里奥抓旗事件
	if (gamescene->mario->is_squat == true)
		MarioUnSquatEvent(gamescene->mario);
	if (gamescene->mario->in_time != 0) {
		stopAudio("invincible");
		loadimage(&childImg[0], "resources/image/entity/mario/0/child0.png");//小孩
	}
	gamescene->mario->x = gamescene->flag->x - gamescene->mario->width;
	gamescene->mario->is_flag = true;
	gamescene->mario->physic = false;
	gamescene->mario->is_squat = false;
	gamescene->mario->is_run = true;
	gamescene->mario->is_jump = false;
	gamescene->mario->im_time = 0;
	gamescene->mario->in_time = 0;
	gamescene->mario->mario_dir = 1;
	gamescene->mario->vx = 0;
	gamescene->mario->vy = 1;
	stopBGM(gamescene->level);
	playAudio("victory1");
	if (gamescene->mario->y <= gamescene->flag->y + 50) {
		addParticle(gamescene, gamescene->mario->x + 50, gamescene->flag->y_, text, 0, -2, "5000", 100);
		gamescene->score += 5000;
	}
	else if (gamescene->mario->y <= gamescene->flag->y + 150) {
		addParticle(gamescene, gamescene->mario->x + 50, gamescene->flag->y_, text, 0, -2, "2000", 100);
		gamescene->score += 2000;
	}
	else if (gamescene->mario->y <= gamescene->flag->y + 250) {
		addParticle(gamescene, gamescene->mario->x + 50, gamescene->flag->y_, text, 0, -2, "800", 100);
		gamescene->score += 800;
	}
	else {
		addParticle(gamescene, gamescene->mario->x + 50, gamescene->flag->y_, text, 0, -2, "100", 100);
		gamescene->score += 100;
	}
}

void MarioLeavePipeEvent(GameScene* gamescene, Pipe* pipe) {
	//马里奥钻出管道事件
	stopBGM(gamescene->level);
	gamescene->x = pipe->tran_x;
	gamescene->levelname = pipe->tran_level;
	if (pipe->type == down)
		gamescene->y = pipe->tran_y;
	else
		gamescene->y = pipe->tran_y - gamescene->mario->height;
	if (pipe->is_newlevel == false) {
		gamescene->loadCnt = 1;//赋于加载时间
		GameSceneDestroy(gamescene);//销毁游戏场景
	}
	else {
		GameSceneReloadEvent(gamescene);
	}
}

void MarioEnterPipeEvent(GameScene* gamescene, Pipe* pipe) {
	//马里奥进入管道事件
	if (pipe->type == right)
		gamescene->mario->is_run = true;
	else
		gamescene->mario->is_run = false;
	gamescene->mario->is_enter = true;
	gamescene->mario->is_jump = false;
	gamescene->mario->is_speed = false;
	gamescene->mario->im_time = 0;
	gamescene->mario->in_time = 0;
	playAudio("pipe");
	if (pipe->type == down) {
		gamescene->mario->vy = 1;
		gamescene->mario->vx = 0;
	}
	else {
		gamescene->mario->vy = 0;
		gamescene->mario->vx = 1;
	}
}

void GameSceneReloadEvent(GameScene* gamescene) {
	//游戏场景重载事件
	GameSceneDestroy(gamescene);//销毁游戏场景
	gamescene->level->Init(gamescene);//初始化世界对象
	gamescene->loadCnt = 300;//赋于加载时间
	gamescene->time = 40000;//重置游戏时间
	if (gamescene->life == 0) {
		gamescene->loadCnt = 500;
		playAudio("game_over");
	}
}

void MonsterHandstandEvent(GameScene* gamescene, Monster* monster) {
	//怪物倒立事件(被无敌模式杀死或被方块撞击死亡)
	playAudio("kick");
	gamescene->score += 100;
	addParticle(gamescene, monster->x, monster->y, text, 0, -1, "100", 100);
	if (monster->type == piranha) {
		monster->Destroy(gamescene);
	}
	else {
		monster->vy = -5;
		monster->status = handstand;
		if (monster->type2 == flyrtortoise) {
			monster->type2 = rtortoise;
			monster->physic = true;
		}
	}
}

void MarioDeathEvent(GameScene* gamescene) {
	//马里奥死亡事件
	if (gamescene->mario->in_time != 0) {
		stopAudio("invincible");
		loadimage(&childImg[0], "resources/image/entity/mario/0/child0.png");//小孩
	}
	gamescene->mario->is_death = true;
	gamescene->mario->is_land = false;
	gamescene->mario->vy = -8;
	gamescene->mario->vx = 0;
	gamescene->mario->in_time = 0;
	gamescene->mario->im_time = 0;
	gamescene->life--;
	gamescene->body = child;
	switch (gamescene->level->name) {//设定重生点
	case level1_1:
		if (gamescene->mario->x >= 3039) {
			gamescene->x = 3339;
			gamescene->y = 484;
		}
		else {
			gamescene->x = 300;
			gamescene->y = 484;
		}
		break;
	case level1_1_pipe:
		gamescene->levelname = level1_1;
		gamescene->x = 300;
		gamescene->y = 484;
		break;
	case level1_2:
		if (gamescene->mario->x >= 3725) {
			gamescene->x = 4025;
			gamescene->y = 482;
		}
		else {
			gamescene->x = 60;
			gamescene->y = 60;
		}
		break;
	case level1_2_pipe:
		gamescene->levelname = level1_2;
		gamescene->x = 4025;
		gamescene->y = 482;
		break;
	}
	stopBGM(gamescene->level);
	playAudio("death");
}

void MarioDamageEvent(GameScene* gamescene) {
	//马里奥受伤事件
	if (gamescene->mario->body == child) {
		MarioDeathEvent(gamescene);//马里奥死亡
	}
	else {
		//变回小孩
		playAudio("pipe");
		gamescene->mario->transf_time = 12;
		gamescene->mario->body = child;
		gamescene->body = child;
		gamescene->mario->height = 40;
		gamescene->mario->im_time = 200;
		if (gamescene->mario->is_squat == false)
			gamescene->mario->y += 40;
	}

}

void MarioStompMonsterEvent(GameScene* gamescene, Monster* monster) {
	//马里奥踩怪物事件
	playAudio("stomp");
	gamescene->score += 100;
	addParticle(gamescene, monster->x, monster->y, text, 0, -1, "100", 100);
	gamescene->mario->vy = -5;
	switch (monster->type) {
	case chestnut:
		monster->deathCnt = 50;
		monster->vx = -1;
		monster->physic = true;
		break;
	case tortoise:
		if (monster->type2 == flyrtortoise) {
			monster->type2 = rtortoise;
			monster->physic = true;
			monster->vy = 0;
			monster->vx = -1;
			break;
		}
		if (monster->status == normal) {
			monster->vx = 0;
			monster->status = shrunkenheaded;
		}
		else if (monster->status == shrunkenheaded) {
			if (monster->vx == 0) {
				if (gamescene->mario->x <= monster->x)
					monster->vx = 6;
				else
					monster->vx = -6;
			}
			else {
				monster->vx = 0;
			}
		}
		break;
	}
}

void FireballBoomEvent(GameScene* gamescene, Fireball* fireball, bool bump) {
	//火球爆炸事件
	addParticle(gamescene, fireball->x - 10, fireball->y - 10, boom, 0, 0);	//创建爆炸粒子效果
	fireball->Destroy(gamescene);
	if (bump == true)
		playAudio("bump");
}

void MarioShootFireballEvent(GameScene* gamescene) {
	//马里奥发射火球事件
	gamescene->mario->fireCnt = 10;
	addFireball(gamescene);
	playAudio("fireball");
}

void MarioOnInvincibilityEvent(GameScene* gamescene) {
	//马里奥进入无敌模式事件
	gamescene->mario->in_time = 1000;
	gamescene->mario->im_time = 0;
	stopBGM(gamescene->level);
	playAudio("invincible");
}

void MarioOffInvincibilityEvent(GameScene* gamescene) {
	//马里奥退出无敌模式事件
	stopAudio("invincible");
	playBGM(gamescene->level);
}

void MarioGrowEvent(GameScene* gamescene) {
	//马里奥成长事件
	gamescene->mario->im_time = 0;
	gamescene->score += 1000;
	addParticle(gamescene, gamescene->mario->x, gamescene->mario->y, text, 0, -1, "1000", 100);
	if (gamescene->mario->body == child) {
		gamescene->mario->body = adult;
		gamescene->body = adult;
		gamescene->mario->transf_time = 12;
		if (gamescene->mario->is_squat == false) {
			gamescene->mario->y -= 40;
			gamescene->mario->height = 80;
		}
	}
	else if (gamescene->mario->body == adult) {
		gamescene->body = old;
		gamescene->mario->body = old;
		gamescene->mario->transf_time = 12;
	}
	playAudio("powerup");
}

void MarioEatPropEvent(GameScene* gamescene, Prop* prop) {
	//马里奥吃道具事件
	switch (prop->type) {
	case propType::coin:
		gamescene->coin++;
		gamescene->score += 200;
		playAudio("coin");
		break;
	case rmushroom:
	case sunflower:
		MarioGrowEvent(gamescene);
		break;
	case gmushroom:
		gamescene->life++;
		addParticle(gamescene, gamescene->mario->x, gamescene->mario->y, text, 0, -1, "1UP", 100);
		playAudio("one_up");
		break;
	case propType::star:
		MarioOnInvincibilityEvent(gamescene);
		break;
	}
}

void CreatePropEvent(GameScene* gamescene, Block* block) {
	//生成道具事件
	if (block->prop == coins) {//大量金币方块，金币数量递减
		if (block->coins == 1)
			block->type = nullquestion;
		else
			block->coins--;
	}
	else {
		block->type = nullquestion;
	}
	switch (block->prop) {
	case blockProp::coin:
	case coins:
		//创建飞行金币粒子效果
		gamescene->coin++;
		addParticle(gamescene, block->x1 + 1, block->y1 - 40, flycoin, 0, -6);
		gamescene->score += 200;
		addParticle(gamescene, block->x1, block->y1 + 20, text, 0, -1, "200", 150);
		break;
	case grow:
		if(gamescene->mario->body == child)
			addProp(gamescene, block->x1 + 1, block->y1 - 40, rmushroom);
		else
			addProp(gamescene, block->x1 + 1, block->y1 - 40, sunflower);
		break;
	case oneup:
		addProp(gamescene, block->x1 + 1, block->y1 - 40, gmushroom);
		break;
	case blockProp::star:
		addProp(gamescene, block->x1 + 1, block->y1 - 40, propType::star);
		break;
	}
	
}

void BlockUpEvent(Block* block) {
	//方块顶起事件
	block->upDir = 1;
	block->upHeight = 1;
}

void BrickCrashEvent(GameScene* gamescene, Block* block) {
	//砖块碎裂事件
	for (int i = 0; i < gamescene->vecBlock.size; i++)
	{//遍历方块类动态数组寻找相应对象
		class Block* pBlock = (class Block*)gamescene->vecBlock.get(&gamescene->vecBlock, i);
		if (pBlock == block) {
			//添加四个碎裂砖块的粒子对象
			addParticle(gamescene, block->x1, block->y1, brokenbrick, -2, -4);
			addParticle(gamescene, block->x1 + 20, block->y1, brokenbrick, 2, -4);
			addParticle(gamescene, block->x1, block->y1 + 20, brokenbrick, -2, -1);
			addParticle(gamescene, block->x1 + 20, block->y1 + 20, brokenbrick, 2, -1);
			gamescene->score += 50;
			//从方块类动态数组中清除对象
			gamescene->vecBlock.remove(&gamescene->vecBlock, i);
			free(pBlock);
			playAudio("brick_smash");
			break;
		}
	}
}

void BlockStrikeEvent(GameScene* gamescene, Block* block, Mario* mario) {
	//方块撞击事件
	playAudio("bump");
	if (block->type != nullquestion) {
		BlockStrikePropCheck(gamescene, block);///方块撞击道具检测
		BlockStrikeMonsterCheck(gamescene, block);//方块撞击怪物检测
	}
	switch (block->type) {
	case brick:
		if (block->prop == blockProp::null) {
			if (mario->body == child) {
				BlockUpEvent(block);
			}
			else {
				BrickCrashEvent(gamescene, block);
			}
		}
		else {
			BlockUpEvent(block);//方块顶起事件
			CreatePropEvent(gamescene, block);//生成道具事件
		}
		break;
	case question:
	case hide:
		BlockUpEvent(block);//方块顶起事件
		CreatePropEvent(gamescene, block);//生成道具事件
		break;
	}
}

void EntityFallEvent(Entity* entity) {
	//实体坠落事件(重力)
	if (entity->physic == false)
		return;//未开启物理开关的实体不受重力
	if (entity->is_land == false)//未触地
		entity->vy += 2 * 2 * 40 * 4 * 0.01 / 5 / 5;//竖直方向受重力
}

void MarioSquatEvent(Mario* mario) {
	//马里奥下蹲事件
	mario->is_squat = true;
	if (mario->body != child) {
		mario->height = 40;
		mario->y += 40;
	}
}

void MarioUnSquatEvent(Mario* mario) {
	//马里奥取消下蹲事件
	mario->is_squat = false;
	if (mario->body != child) {
		mario->height = 80;
		mario->y -= 40;
	}
}

void MarioJumpEvent(Mario* mario) {
	//马里奥跳跃事件
	mario->is_jump = true;
	mario->is_land = false;
	mario->vy = -32 * sqrt(2) * 0.04 * 5;
	playAudio("big_jump");
}

void MarioTouchBorderEvent(Mario* mario, Camera* camera) {
	//马里奥接触地图边界事件
	if (mario->x < camera->x - 300) {
		mario->x = camera->x - 300;
		mario->vx = 0;
	}
}

void MarioSlowEvent(Mario* mario) {
	//马里奥减速事件(摩擦力)

	if (mario->is_run == false && mario->runF == 4)
		mario->runF = 0;//修正刹车动画帧

	if (mario->is_land == false)
		return;//未触地不会产生摩擦力

	if (mario->is_jump == true)
		mario->is_jump = false;//触地时解除跳跃状态

	float vmax = 3.5;
	if (mario->is_speed == true) {
		vmax = 5;
	}

	if (mario->vx > 0) {
		if (mario->vx > vmax)
			mario->vx -= 0.06;
		mario->vx -= 0.05;
	}else if (mario->vx < 0) {
		if (mario->vx < -vmax)
			mario->vx += 0.06;
		mario->vx += 0.05;
	}

	if (fabs(mario->vx) <= 0.05 && mario->is_run == false) {
		mario->vx = 0;//未奔跑时使速度完全消除
	}

}

void MarioSpeedEvent(Mario* mario) {
	//马里奥加速事件
	if (mario->mario_dir == 1) {
		if (mario->vx < -3)
			mario->runF = 4;
		mario->vx += 0.1;
	}
	else {
		if (mario->vx > 3)
			mario->runF = 4;
		mario->vx -= 0.1;
	}

	if (mario->is_land == false && mario->is_speed == false) {
		//在空中超速时修正速度
		if (mario->vx > 3.5)
			mario->vx = 3.5;
		else if(mario->vx < -3.5)
			mario->vx = -3.5;
	}

	if (mario->vx > 5) {
		mario->vx = 5;
	}
	else if (mario->vx < -5) {
		mario->vx = -5;
	}

	if (mario->runF == 4 && (fabs(mario->vx) <= 1 || mario->dir * mario->vx < 0)) {//修正刹车动画帧
		mario->runF = 0;
	}
}