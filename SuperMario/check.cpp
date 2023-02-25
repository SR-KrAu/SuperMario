#include "check.h"
#include "event.h"
#include "block.h"
#include "prop.h"
#include "fireball.h"
#include "monster.h"
#include "audio.h"
#include "pipe.h"
#include "particle.h"
#include "platform.h"
#include "gamescene.h"
#include <math.h>

void MonsterTouchPlatformCheck(GameScene* g) {
	//怪物接触平台检测
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pEntity = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pEntity->physic == false || pEntity->status == handstand)
			continue;//未开启物理开关或倒立不参与检测
		bool island = pEntity->is_land;
		for (int j = 0; j < g->vecPlatform.size; j++)
		{
			class Platform* pWall = (class Platform*)g->vecPlatform.get(&g->vecPlatform, j);
			//向上
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pWall->y2 + 1;
				continue;
			}
			//水平方向
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//向右
				if (pEntity->x + pEntity->width + pEntity->vx > pWall->x1 && pEntity->x + pEntity->width < pWall->x2) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x1 - pEntity->width - 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
				//向左
				if (pEntity->x + pEntity->vx < pWall->x2 && pEntity->x > pWall->x1) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x2 + 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
			}
			//向下
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pWall->y1 && pEntity->y + pEntity->height < pWall->y2) {
				pEntity->vy = 0;
				pEntity->y = pWall->y1 - pEntity->height + pWall->vy;
				pEntity->is_land = true;
				if (pEntity->type2 == rtortoise && pEntity->status != shrunkenheaded) {
					if ((pEntity->x + pEntity->width / 2 > pWall->x2 - 5 && pEntity->vx > 0) || (pEntity->x + pEntity->width / 2 < pWall->x1 + 5 && pEntity->vx < 0))
						pEntity->vx = -pEntity->vx;
				}
			}
		}
	}
}

void FireballTouchPlatformCheck(GameScene* g) {
	//火球接触平台检测(不包括马里奥)
	for (int i = 0; i < g->vecFireball.size; i++)
	{
		class Fireball* pEntity = (class Fireball*)g->vecFireball.get(&g->vecFireball, i);
		if (pEntity->physic == false)
			continue;//未开启物理开关的实体不参与检测
		for (int j = 0; j < g->vecPlatform.size; j++)
		{
			class Platform* pWall = (class Platform*)g->vecPlatform.get(&g->vecPlatform, j);
			//向上
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				FireballBoomEvent(g, pEntity);
				break;
			}
			//水平方向
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//向右
				if (pEntity->x + pEntity->width + pEntity->vx > pWall->x1 && pEntity->x + pEntity->width < pWall->x2) {
					FireballBoomEvent(g, pEntity);
					break;
				}
				if (pEntity->x + pEntity->vx < pWall->x2 && pEntity->x > pWall->x1) {
					FireballBoomEvent(g, pEntity);
					break;
				}
			}
			//向下
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pWall->y1 && pEntity->y + pEntity->height < pWall->y2) {
				pEntity->vy = -5;
				pEntity->y = pWall->y1 - pEntity->height + pWall->vy;
			}
		}
	}
}

void PropTouchPlatformCheck(GameScene* g) {
	//道具接触平台检测
	for (int i = 0; i < g->vecProp.size; i++)
	{
		class Prop* pEntity = (class Prop*)g->vecProp.get(&g->vecProp, i);
		if (pEntity->physic == false)
			continue;//未开启物理开关的实体不参与检测
		bool island = pEntity->is_land;
		for (int j = 0; j < g->vecPlatform.size; j++)
		{
			class Platform* pWall = (class Platform*)g->vecPlatform.get(&g->vecPlatform, j);
			//向上
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pWall->y2 + 1;
				continue;
			}
			//水平方向
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//向右
				if (pEntity->x + pEntity->width + pEntity->vx > pWall->x1 && pEntity->x + pEntity->width < pWall->x2) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x1 - pEntity->width - 1;
					continue;
				}
				if (pEntity->x + pEntity->vx < pWall->x2 && pEntity->x > pWall->x1) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x2 + 1;
					continue;
				}
			}
			//向下
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pWall->y1 && pEntity->y + pEntity->height < pWall->y2) {
				if (pEntity->type == propType::star)
					pEntity->vy = rand() % (-6 - -9 + 1) + -9;
				else
					pEntity->vy = 0;
				pEntity->y = pWall->y1 - pEntity->height + pWall->vy;
				pEntity->is_land = true;
			}
		}
	}
}

void MarioTouchPlatformCheck(GameScene* g) {
	//马里奥接触平台类检测
	if (g->mario->physic == false)
		return;
	bool island = g->mario->is_land;
	for (int j = 0; j < g->vecPlatform.size; j++)
	{
		class Platform* pPlatform = (class Platform*)g->vecPlatform.get(&g->vecPlatform, j);
		//向上
		if (g->mario->x + g->mario->width > pPlatform->x1 + 5 && g->mario->x < pPlatform->x2 - 5 && g->mario->y + g->mario->vy < pPlatform->y2 && g->mario->y + g->mario->height > pPlatform->y2) {
			g->mario->vy = -g->mario->vy / 2;
			g->mario->y = pPlatform->y2 + 1;
			continue;
		}
		//水平方向
		if (g->mario->y + g->mario->height > pPlatform->y1 + 1 && g->mario->y < pPlatform->y2 - 1) {
			//向右
			if (g->mario->x + g->mario->width + g->mario->vx > pPlatform->x1 && g->mario->x + g->mario->width < pPlatform->x2) {
				g->mario->vx = 0;
				g->mario->x = pPlatform->x1 - g->mario->width - 1;
				continue;
			}
			if (g->mario->x + g->mario->vx < pPlatform->x2 && g->mario->x > pPlatform->x1) {
				g->mario->vx = 0;
				g->mario->x = pPlatform->x2 + 1;
				continue;
			}
		}
		//向下
		if (g->mario->x + g->mario->width > pPlatform->x1 + 5 && g->mario->x < pPlatform->x2 - 5 && g->mario->y + g->mario->height + g->mario->vy >= pPlatform->y1 && g->mario->y + g->mario->height < pPlatform->y2) {
			g->mario->vy = 0;
			g->mario->y = pPlatform->y1 - g->mario->height + pPlatform->vy;
			g->mario->is_land = true;
			if (pPlatform->type == right_left)
				g->mario->x += pPlatform->vx;
		}
	}
}

void MarioTouchFlagCheck(GameScene* g) {
	//马里奥抓旗检测
	if (g->mario->x + g->mario->width >= g->flag->x && g->mario->is_flag == false && g->flag->is_exist == true)
		MarioTouchFlagEvent(g);//马里奥抓旗事件
}

void MarioEnterPipeCheck(GameScene* g) {
	//马里奥进入管道检测
	if (g->mario->is_death == true || g->mario->is_stealth == true)
		return;
		for (int i = 0; i < g->vecPipe.size; i++)
		{
			class Pipe* pPipe = (class Pipe*)g->vecPipe.get(&g->vecPipe, i);
			if (pPipe->is_tran == false)//不具备传送功能的管道
				continue;
			if (pPipe->type == pipeType::down) {
				if (g->mario->is_squat == true && g->mario->is_enter == false && g->mario->x >= pPipe->x && g->mario->x + g->mario->width <= pPipe->x + 70 && abs(g->mario->y + g->mario->height - pPipe->y) < 3)
					MarioEnterPipeEvent(g, pPipe);//马里奥进入管道事件
				if (g->mario->is_enter == true && g->mario->x >= pPipe->x && g->mario->x + g->mario->width <= pPipe->x + 70 && g->mario->y + g->mario->height >= pPipe->tran_location)
					MarioLeavePipeEvent(g, pPipe);//马里奥钻出管道事件
			}
			else {
				if (g->mario->is_squat == false && g->mario->is_enter == false && g->mario->y >= pPipe->y && g->mario->y + g->mario->height <= pPipe->y + 80 && g->mario->vy == 0 && g->mario->vx > 0 && abs(g->mario->x + g->mario->width - pPipe->x) < 3)
					MarioEnterPipeEvent(g, pPipe);//马里奥进入管道事件
				if (g->mario->is_squat == false && g->mario->is_enter == true && g->mario->y >= pPipe->y && g->mario->y + g->mario->height <= pPipe->y + 80 && g->mario->vy == 0 && g->mario->vx > 0 && g->mario->x + g->mario->width >= pPipe->tran_location)
					MarioLeavePipeEvent(g, pPipe);//马里奥钻出管道事件
			}
		}
}

void MonsterTouchMonsterCheck(GameScene* g) {
	//怪物接触怪物类检测
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pMonster1 = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pMonster1->is_exist == false || pMonster1->deathCnt != 0 || pMonster1->status == handstand)//不参与检测
			continue;
		for (int j = i + 1; j < g->vecMonster.size; j++)
		{
			class Monster* pMonster2 = (class Monster*)g->vecMonster.get(&g->vecMonster, j);
			if (pMonster2->is_exist == false || pMonster2->deathCnt != 0 || pMonster2->status == handstand)//不参与检测
				continue;
			if (pMonster1->x + pMonster1->width > pMonster2->x + 10 && pMonster1->x < pMonster2->x + pMonster2->width - 10 && pMonster1->y + pMonster1->height > pMonster2->y && pMonster1->y < pMonster2->y + pMonster2->height) {
				if (pMonster1->type == tortoise && pMonster1->status == shrunkenheaded && pMonster1->vx != 0) {
					MonsterHandstandEvent(g, pMonster2);
				}
				else if (pMonster2->type == tortoise && pMonster2->status == shrunkenheaded && pMonster2->vx != 0) {
					MonsterHandstandEvent(g, pMonster1);
				}
				else {
					pMonster1->vx = -pMonster1->vx;
					pMonster2->vx = -pMonster2->vx;
				}
			}
		}
	}
}

void FireballTouchMonsterCheck(GameScene* g) {
	//火球接触怪物类检测
	for (int j = 0; j < g->vecFireball.size; j++)
	{
		class Fireball* pFireball = (class Fireball*)g->vecFireball.get(&g->vecFireball, j);
		for (int i = 0; i < g->vecMonster.size; i++)
		{
			class Monster* pMonster = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
			if (pMonster->is_exist == false || pMonster->deathCnt != 0 || pMonster->status == handstand)//未生成，已踩死，倒立死亡的怪物不参与检测
				continue;
			if (pFireball->x + pFireball->width > pMonster->x && pFireball->x < pMonster->x + pMonster->width && pFireball->y + pFireball->height > pMonster->y && pFireball->y < pMonster->y + pMonster->height) {
					MonsterHandstandEvent(g, pMonster);
					FireballBoomEvent(g, pFireball, false);
			}
		}
	}
}

void BlockStrikeMonsterCheck(GameScene* g, Block* block) {
	//方块撞击怪物检测
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pEntity = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pEntity->physic == false || pEntity->status == handstand || pEntity->type == piranha)
			continue;//未开启物理开关和倒立死亡的不参与检测
		if (pEntity->x + pEntity->width >= block->x1 && pEntity->x <= block->x2 && pEntity->y + pEntity->height >= block->y1 - 5 && pEntity->y < block->y2) {
			MonsterHandstandEvent(g, pEntity);//怪物倒立死亡
		}
	}
}

void MarioTouchMonsterCheck(GameScene* g) {
	//马里奥接触怪物类检测
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pMonster = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pMonster->is_exist == false || pMonster->deathCnt != 0 || pMonster->status == handstand)//未生成，已踩死，倒立死亡的怪物不参与检测
			continue;
		if (g->mario->x + g->mario->width > pMonster->x && g->mario->x < pMonster->x + pMonster->width && g->mario->y + g->mario->height > pMonster->y && g->mario->y < pMonster->y + pMonster->height) {
			if (g->mario->in_time != 0) {
				//无敌模式杀死怪物
				MonsterHandstandEvent(g, pMonster);
				continue;
			}
			if (pMonster->type == piranha) {//食人花
				if (g->mario->im_time == 0) {
					MarioDamageEvent(g);//马里奥受伤事件
				}
				continue;
			}
			if (g->mario->y + g->mario->height < pMonster->y + pMonster->height / 2 && g->mario->vy > 0) {
				MarioStompMonsterEvent(g, pMonster);//马里奥踩怪物事件
			}
			else if (g->mario->y + g->mario->height > pMonster->y + pMonster->height / 2 && g->mario->im_time == 0) {
				if (pMonster->status == shrunkenheaded && pMonster->vx == 0) {
					playAudio("stomp");
					if(g->mario->x <= pMonster->x)
						pMonster->vx = 6;
					else
						pMonster->vx = -6;
				}
				else {
					MarioDamageEvent(g);//马里奥受伤事件
				}
			}
		}
	}
}

void MonsterTouchBlockCheck(GameScene* g) {
	//怪物接触方块类检测
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pEntity = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pEntity->physic == false || pEntity->status == handstand)
			continue;//未开启物理开关或倒立不参与检测
		bool island = false;
		for (int j = 0; j < g->vecBlock.size; j++)
		{
			class Block* pBlock = (class Block*)g->vecBlock.get(&g->vecBlock, j);
			//向上
			if (pBlock->type == hide)
				continue;//隐藏方块无法被非马里奥的实体触碰
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->vy < pBlock->y2 && pEntity->y + pEntity->height > pBlock->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pBlock->y2 + 1;
				continue;
			}
			//水平方向
			if (pEntity->y + pEntity->height > pBlock->y1 && pEntity->y < pBlock->y2) {
				//向右
				if (pEntity->x + pEntity->width + pEntity->vx > pBlock->x1 && pEntity->x + pEntity->width < pBlock->x2) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pBlock->x1 - pEntity->width - 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
				//向左
				if (pEntity->x + pEntity->vx < pBlock->x2 && pEntity->x > pBlock->x1) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pBlock->x2 + 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
			}
			//向下
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pBlock->y1 && pEntity->y + pEntity->height < pBlock->y2) {
				pEntity->vy = 0;
				pEntity->y = pBlock->y1 - pEntity->height;
				island = true;
			}
			else {
				pEntity->is_land = false;
			}
		}
		pEntity->is_land = island;
	}
}

void MonsterTouchWallCheck(GameScene* g) {
	//怪物接触墙体检测
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pEntity = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pEntity->physic == false || pEntity->status == handstand)
			continue;//未开启物理开关或倒立不参与检测
		bool island = pEntity->is_land;
		for (int j = 0; j < g->vecWall.size; j++)
		{
			class Wall* pWall = (class Wall*)g->vecWall.get(&g->vecWall, j);
			//向上
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pWall->y2 + 1;
				continue;
			}
			//水平方向
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//向右
				if (pEntity->x + pEntity->width + pEntity->vx > pWall->x1 && pEntity->x + pEntity->width < pWall->x2) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x1 - pEntity->width - 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
				//向左
				if (pEntity->x + pEntity->vx < pWall->x2 && pEntity->x > pWall->x1) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x2 + 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
			}
			//向下
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pWall->y1 && pEntity->y + pEntity->height < pWall->y2) {
				pEntity->vy = 0;
				pEntity->y = pWall->y1 - pEntity->height;
				pEntity->is_land = true;
				if (pEntity->type2 == rtortoise && pEntity->status != shrunkenheaded) {
					if ((pEntity->x + pEntity->width / 2 > pWall->x2 - 5 && pEntity->vx > 0) || (pEntity->x + pEntity->width / 2 < pWall->x1 + 5 && pEntity->vx < 0))
						pEntity->vx = -pEntity->vx;
				}
			}
		}
	}
}

void BlockStrikePropCheck(GameScene* g, Block* block) {
	//方块撞击道具检测
	for (int i = 0; i < g->vecProp.size; i++)
	{
		class Prop* pEntity = (class Prop*)g->vecProp.get(&g->vecProp, i);
		if (pEntity->createTime != 0)//不参与检测
			continue;
		if (pEntity->x + pEntity->width > block->x1 && pEntity->x < block->x2 && pEntity->y + pEntity->height >= block->y1 && pEntity->y < block->y2) {
			if (pEntity->type == propType::coin) {
				addParticle(g, block->x1 + 1, block->y1 - 40, flycoin, 0, -6);
				addParticle(g, block->x1, block->y1 + 20, text, 0, -1, "200", 150);
				MarioEatPropEvent(g, pEntity);
				pEntity->Destroy(g);//销毁金币
				continue;
			}
			else if (pEntity->physic == false) {
				continue;
			}
			if ((pEntity->x + pEntity->width < block->x1 + 20 && pEntity->dir == 1) || (pEntity->x > block->x1 + 20 && pEntity->dir == -1))
				pEntity->vx = -pEntity->vx;
			pEntity->vy = -4;
		}
	}
}

void FireballTouchBlockCheck(GameScene* g) {
	//火球接触方块类检测(不包括马里奥)
	for (int i = 0; i < g->vecFireball.size; i++)
	{
		class Fireball* pEntity = (class Fireball*)g->vecFireball.get(&g->vecFireball, i);
		if (pEntity->physic == false)
			continue;//未开启物理开关的实体不参与检测
		for (int j = 0; j < g->vecBlock.size; j++)
		{
			class Block* pBlock = (class Block*)g->vecBlock.get(&g->vecBlock, j);
			//向上
			if (pBlock->type == hide)
				continue;//隐藏方块无法被非马里奥的实体触碰
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->vy < pBlock->y2 && pEntity->y + pEntity->height > pBlock->y2) {
				FireballBoomEvent(g, pEntity);
				break;
			}
			//水平方向
			if (pEntity->y + pEntity->height > pBlock->y1 && pEntity->y < pBlock->y2) {
				//向右
				if (pEntity->x + pEntity->width + pEntity->vx > pBlock->x1 && pEntity->x + pEntity->width < pBlock->x2) {
					FireballBoomEvent(g, pEntity);
					break;
				}
				if (pEntity->x + pEntity->vx < pBlock->x2 && pEntity->x > pBlock->x1) {
					FireballBoomEvent(g, pEntity);
					break;
				}
			}
			//向下
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pBlock->y1 && pEntity->y + pEntity->height < pBlock->y2) {
				pEntity->vy = -5;
				pEntity->y = pBlock->y1 - pEntity->height;
			}
		}

	}
}

void FireballTouchWallCheck(GameScene* g) {
	//火球接触墙体检测(不包括马里奥)
	for (int i = 0; i < g->vecFireball.size; i++)
	{
		class Fireball* pEntity = (class Fireball*)g->vecFireball.get(&g->vecFireball, i);
		if (pEntity->physic == false)
			continue;//未开启物理开关的实体不参与检测
		for (int j = 0; j < g->vecWall.size; j++)
		{
			class Wall* pWall = (class Wall*)g->vecWall.get(&g->vecWall, j);
			//向上
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				FireballBoomEvent(g, pEntity);
				break;
			}
			//水平方向
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//向右
				if (pEntity->x + pEntity->width + pEntity->vx > pWall->x1 && pEntity->x + pEntity->width < pWall->x2) {
					FireballBoomEvent(g, pEntity);
					break;
				}
				if (pEntity->x + pEntity->vx < pWall->x2 && pEntity->x > pWall->x1) {
					FireballBoomEvent(g, pEntity);
					break;
				}
			}
			//向下
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pWall->y1 && pEntity->y + pEntity->height < pWall->y2) {
				pEntity->vy = -5;
				pEntity->y = pWall->y1 - pEntity->height;
			}
		}
	}
}

void MarioTouchPropCheck(GameScene* g) {
	//马里奥接触道具类检测
	for (int i = 0; i < g->vecProp.size; i++)
	{
		class Prop* pProp = (class Prop*)g->vecProp.get(&g->vecProp, i);
		if (g->mario->x + g->mario->width > pProp->x && g->mario->x < pProp->x + pProp->width && g->mario->y + g->mario->height > pProp->y && g->mario->y < pProp->y + pProp->height) {
			MarioEatPropEvent(g, pProp);//马里奥吃道具事件
			pProp->Destroy(g);//销毁道具
		}
	}
}

void MarioTouchBlockCheck(GameScene* g) {
	//马里奥接触方块类检测
	if (g->mario->physic == false)
		return;
	bool island = false;
	for (int j = 0; j < g->vecBlock.size; j++)
	{
		class Block* pBlock = (class Block*)g->vecBlock.get(&g->vecBlock, j);
		//向上
		if (g->mario->vy < 0 && g->mario->x + g->mario->width > pBlock->x1 + 5 && g->mario->x < pBlock->x2 - 5 && g->mario->y + g->mario->vy < pBlock->y2 && g->mario->y + g->mario->height > pBlock->y2) {
			g->mario->vy = -g->mario->vy / 2;
			g->mario->y = pBlock->y2;
			BlockStrikeEvent(g, pBlock, g->mario);
			continue;
		}
		if (pBlock->type != hide) {
			//水平方向
			if (g->mario->y + g->mario->height > pBlock->y1 && g->mario->y < pBlock->y2) {
				//向右
				if (g->mario->x + g->mario->width + g->mario->vx > pBlock->x1 && g->mario->x + g->mario->width < pBlock->x2) {
					g->mario->vx = 0;
					g->mario->x = pBlock->x1 - g->mario->width - 1;
					continue;
				}
				if (g->mario->x + g->mario->vx < pBlock->x2 && g->mario->x > pBlock->x1) {
					g->mario->vx = 0;
					g->mario->x = pBlock->x2 + 1;
					continue;
				}
			}

			//向下
			if (g->mario->x + g->mario->width > pBlock->x1 + 3 && g->mario->x < pBlock->x2 - 3 && g->mario->y + g->mario->height + g->mario->vy >= pBlock->y1 && g->mario->y + g->mario->height < pBlock->y2) {
				g->mario->vy = 0;
				g->mario->y = pBlock->y1 - g->mario->height;
				island = true;
			}
			else {
				g->mario->is_land = false;
			}
		}
	}
	g->mario->is_land = island;
}

void MarioTouchWallCheck(GameScene* g) {
	//马里奥接触墙类检测
	if (g->mario->physic == false)
		return;
	bool island = g->mario->is_land;
	for (int j = 0; j < g->vecWall.size; j++)
	{
		class Wall* pWall = (class Wall*)g->vecWall.get(&g->vecWall, j);
		//向上
		if (g->mario->x + g->mario->width > pWall->x1 + 5 && g->mario->x < pWall->x2 - 5 && g->mario->y + g->mario->vy < pWall->y2 && g->mario->y + g->mario->height > pWall->y2) {
			g->mario->vy = -g->mario->vy / 2;
			g->mario->y = pWall->y2 + 1;
			continue;
		}
		//水平方向
		if (g->mario->y + g->mario->height > pWall->y1 && g->mario->y < pWall->y2) {
			//向右
			if (g->mario->x + g->mario->width + g->mario->vx > pWall->x1 && g->mario->x + g->mario->width < pWall->x2) {
				g->mario->vx = 0;
				g->mario->x = pWall->x1 - g->mario->width - 1;
				continue;
			}
			if (g->mario->x + g->mario->vx < pWall->x2 && g->mario->x > pWall->x1) {
				g->mario->vx = 0;
				g->mario->x = pWall->x2 + 1;
				continue;
			}
		}
		//向下
		if (g->mario->x + g->mario->width > pWall->x1 + 5 && g->mario->x < pWall->x2 - 5 && g->mario->y + g->mario->height + g->mario->vy >= pWall->y1 && g->mario->y + g->mario->height < pWall->y2) {
			g->mario->vy = 0;
			g->mario->y = pWall->y1 - g->mario->height;
			g->mario->is_land = true;
		}
	}
}
/*
void entityTouchBlockCheck(GameScene* g) {
	//实体接触方块类检测(不包括马里奥)
	for (int i = 0; i < g->vecEntity.size; i++)
	{
		class Entity* pEntity = (class Entity*)g->vecEntity.get(&g->vecEntity, i);
		if (pEntity->physic == false)
			continue;//未开启物理开关的实体不参与检测
		bool island = false;
		for (int j = 0; j < g->vecBlock.size; j++)
		{
			class Block* pBlock = (class Block*)g->vecBlock.get(&g->vecBlock, j);
			//向上
			if (pBlock->type == hide)
				continue;//隐藏方块无法被非马里奥的实体触碰
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->vy < pBlock->y2 && pEntity->y + pEntity->height > pBlock->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pBlock->y2 + 1;
				continue;
			}
			//水平方向
			if (pEntity->y + pEntity->height > pBlock->y1 && pEntity->y < pBlock->y2) {
				//向右
				if (pEntity->x + pEntity->width + pEntity->vx > pBlock->x1 && pEntity->x + pEntity->width < pBlock->x2) {
					pEntity->vx = 0;
					pEntity->x = pBlock->x1 - pEntity->width - 1;
					continue;
				}
				if (pEntity->x + pEntity->vx < pBlock->x2 && pEntity->x > pBlock->x1) {
					pEntity->vx = 0;
					pEntity->x = pBlock->x2 + 1;
					continue;
				}
			}
			//向下
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pBlock->y1 && pEntity->y + pEntity->height < pBlock->y2) {
				pEntity->vy = 0;
				pEntity->y = pBlock->y1 - pEntity->height;
				island = true;
			}
			else {
				pEntity->is_land = false;
			}
		}
		pEntity->is_land = island;
	}
}

void entityTouchWallCheck(GameScene* g) {
	//实体接触墙体检测(不包括马里奥)
	for (int i = 0; i < g->vecEntity.size; i++)
	{
		class Entity* pEntity = (class Entity*)g->vecEntity.get(&g->vecEntity, i);
		if (pEntity->physic == false)
			continue;//未开启物理开关的实体不参与检测
		bool island = pEntity->is_land;
		for (int j = 0; j < g->vecWall.size; j++)
		{
			class Wall* pWall = (class Wall*)g->vecWall.get(&g->vecWall, j);
			//向上
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pWall->y2 + 1;
				continue;
			}
			//水平方向
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//向右
				if (pEntity->x + pEntity->width + pEntity->vx > pWall->x1 && pEntity->x + pEntity->width < pWall->x2) {
					pEntity->vx = 0;
					pEntity->x = pWall->x1 - pEntity->width - 1;
					continue;
				}
				if (pEntity->x + pEntity->vx < pWall->x2 && pEntity->x > pWall->x1) {
					pEntity->vx = 0;
					pEntity->x = pWall->x2 + 1;
					continue;
				}
			}
			//向下
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pWall->y1 && pEntity->y + pEntity->height < pWall->y2) {
				pEntity->vy = 0;
				pEntity->y = pWall->y1 - pEntity->height;
				pEntity->is_land = true;
			}
		}
	}
}
*/
void PropTouchBlockCheck(GameScene* g) {
	//道具接触方块类检测
	for (int i = 0; i < g->vecProp.size; i++)
	{
		class Prop* pEntity = (class Prop*)g->vecProp.get(&g->vecProp, i);
		if (pEntity->physic == false)
			continue;//未开启物理开关的实体不参与检测
		bool island = false;
		for (int j = 0; j < g->vecBlock.size; j++)
		{
			class Block* pBlock = (class Block*)g->vecBlock.get(&g->vecBlock, j);
			//向上
			if (pBlock->type == hide)
				continue;//隐藏方块无法被非马里奥的实体触碰
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->vy < pBlock->y2 && pEntity->y + pEntity->height > pBlock->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pBlock->y2 + 1;
				continue;
			}
			//水平方向
			if (pEntity->y + pEntity->height > pBlock->y1 && pEntity->y < pBlock->y2) {
				//向右
				if (pEntity->x + pEntity->width + pEntity->vx > pBlock->x1 && pEntity->x + pEntity->width < pBlock->x2) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pBlock->x1 - pEntity->width - 1;
					continue;
				}
				if (pEntity->x + pEntity->vx < pBlock->x2 && pEntity->x > pBlock->x1) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pBlock->x2 + 1;
					continue;
				}
			}
			//向下
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pBlock->y1 && pEntity->y + pEntity->height < pBlock->y2) {
				if (pEntity->type == propType::star)
					pEntity->vy = rand() % (-6 - -9 + 1) + -9;
				else
					pEntity->vy = 0;
				pEntity->y = pBlock->y1 - pEntity->height;
				island = true;
			}
			else {
				pEntity->is_land = false;
			}
		}
		pEntity->is_land = island;
	}
}

void PropTouchWallCheck(GameScene* g) {
	//道具接触墙体检测
	for (int i = 0; i < g->vecProp.size; i++)
	{
		class Prop* pEntity = (class Prop*)g->vecProp.get(&g->vecProp, i);
		if (pEntity->physic == false)
			continue;//未开启物理开关的实体不参与检测
		bool island = pEntity->is_land;
		for (int j = 0; j < g->vecWall.size; j++)
		{
			class Wall* pWall = (class Wall*)g->vecWall.get(&g->vecWall, j);
			//向上
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pWall->y2 + 1;
				continue;
			}
			//水平方向
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//向右
				if (pEntity->x + pEntity->width + pEntity->vx > pWall->x1 && pEntity->x + pEntity->width < pWall->x2) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x1 - pEntity->width - 1;
					continue;
				}
				if (pEntity->x + pEntity->vx < pWall->x2 && pEntity->x > pWall->x1) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x2 + 1;
					continue;
				}
			}
			//向下
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pWall->y1 && pEntity->y + pEntity->height < pWall->y2) {
				if (pEntity->type == propType::star)
					pEntity->vy = rand() % (-6 - -9 + 1) + -9;
				else
					pEntity->vy = 0;
				pEntity->y = pWall->y1 - pEntity->height;
				pEntity->is_land = true;
			}
		}
	}
}

void CheckAll(GameScene* gamescene) {
	//检测所有

	if (!(gamescene->mario->is_death == true || gamescene->mario->is_enter == true)) {
		MarioTouchBlockCheck(gamescene);
		//马里奥接触方块检测

		MarioTouchWallCheck(gamescene);
		//马里奥接触墙体检测

		MarioTouchPlatformCheck(gamescene);
		//马里奥接触平台检测

		MarioTouchPropCheck(gamescene);
		//马里奥接触道具检测

		MarioTouchMonsterCheck(gamescene);
		//马里奥接触怪物检测

		MarioTouchFlagCheck(gamescene);
		//马里奥抓旗检测
	}
	
	MarioEnterPipeCheck(gamescene);
	//马里奥进入管道检测

	PropTouchBlockCheck(gamescene);
	//道具接触方块检测

	PropTouchWallCheck(gamescene);
	//道具接触墙体检测

	PropTouchPlatformCheck(gamescene);
	//道具接触平台检测

	FireballTouchBlockCheck(gamescene);
	//火球接触方块检测

	FireballTouchWallCheck(gamescene);
	//火球接触墙体检测

	FireballTouchPlatformCheck(gamescene);
	//火球接触平台检测

	MonsterTouchBlockCheck(gamescene);
	//怪物接触方块检测

	MonsterTouchWallCheck(gamescene);
	//怪物接触墙体检测

	MonsterTouchPlatformCheck(gamescene);
	//怪物接触平台检测

	MonsterTouchMonsterCheck(gamescene);
	//怪物接触怪物检测

	FireballTouchMonsterCheck(gamescene);
	//火球接触怪物检测
}