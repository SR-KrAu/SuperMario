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
	//����Ӵ�ƽ̨���
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pEntity = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pEntity->physic == false || pEntity->status == handstand)
			continue;//δ���������ػ�����������
		bool island = pEntity->is_land;
		for (int j = 0; j < g->vecPlatform.size; j++)
		{
			class Platform* pWall = (class Platform*)g->vecPlatform.get(&g->vecPlatform, j);
			//����
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pWall->y2 + 1;
				continue;
			}
			//ˮƽ����
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//����
				if (pEntity->x + pEntity->width + pEntity->vx > pWall->x1 && pEntity->x + pEntity->width < pWall->x2) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x1 - pEntity->width - 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
				//����
				if (pEntity->x + pEntity->vx < pWall->x2 && pEntity->x > pWall->x1) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x2 + 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
			}
			//����
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
	//����Ӵ�ƽ̨���(�����������)
	for (int i = 0; i < g->vecFireball.size; i++)
	{
		class Fireball* pEntity = (class Fireball*)g->vecFireball.get(&g->vecFireball, i);
		if (pEntity->physic == false)
			continue;//δ���������ص�ʵ�岻������
		for (int j = 0; j < g->vecPlatform.size; j++)
		{
			class Platform* pWall = (class Platform*)g->vecPlatform.get(&g->vecPlatform, j);
			//����
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				FireballBoomEvent(g, pEntity);
				break;
			}
			//ˮƽ����
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//����
				if (pEntity->x + pEntity->width + pEntity->vx > pWall->x1 && pEntity->x + pEntity->width < pWall->x2) {
					FireballBoomEvent(g, pEntity);
					break;
				}
				if (pEntity->x + pEntity->vx < pWall->x2 && pEntity->x > pWall->x1) {
					FireballBoomEvent(g, pEntity);
					break;
				}
			}
			//����
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pWall->y1 && pEntity->y + pEntity->height < pWall->y2) {
				pEntity->vy = -5;
				pEntity->y = pWall->y1 - pEntity->height + pWall->vy;
			}
		}
	}
}

void PropTouchPlatformCheck(GameScene* g) {
	//���߽Ӵ�ƽ̨���
	for (int i = 0; i < g->vecProp.size; i++)
	{
		class Prop* pEntity = (class Prop*)g->vecProp.get(&g->vecProp, i);
		if (pEntity->physic == false)
			continue;//δ���������ص�ʵ�岻������
		bool island = pEntity->is_land;
		for (int j = 0; j < g->vecPlatform.size; j++)
		{
			class Platform* pWall = (class Platform*)g->vecPlatform.get(&g->vecPlatform, j);
			//����
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pWall->y2 + 1;
				continue;
			}
			//ˮƽ����
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//����
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
			//����
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
	//����½Ӵ�ƽ̨����
	if (g->mario->physic == false)
		return;
	bool island = g->mario->is_land;
	for (int j = 0; j < g->vecPlatform.size; j++)
	{
		class Platform* pPlatform = (class Platform*)g->vecPlatform.get(&g->vecPlatform, j);
		//����
		if (g->mario->x + g->mario->width > pPlatform->x1 + 5 && g->mario->x < pPlatform->x2 - 5 && g->mario->y + g->mario->vy < pPlatform->y2 && g->mario->y + g->mario->height > pPlatform->y2) {
			g->mario->vy = -g->mario->vy / 2;
			g->mario->y = pPlatform->y2 + 1;
			continue;
		}
		//ˮƽ����
		if (g->mario->y + g->mario->height > pPlatform->y1 + 1 && g->mario->y < pPlatform->y2 - 1) {
			//����
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
		//����
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
	//�����ץ����
	if (g->mario->x + g->mario->width >= g->flag->x && g->mario->is_flag == false && g->flag->is_exist == true)
		MarioTouchFlagEvent(g);//�����ץ���¼�
}

void MarioEnterPipeCheck(GameScene* g) {
	//����½���ܵ����
	if (g->mario->is_death == true || g->mario->is_stealth == true)
		return;
		for (int i = 0; i < g->vecPipe.size; i++)
		{
			class Pipe* pPipe = (class Pipe*)g->vecPipe.get(&g->vecPipe, i);
			if (pPipe->is_tran == false)//���߱����͹��ܵĹܵ�
				continue;
			if (pPipe->type == pipeType::down) {
				if (g->mario->is_squat == true && g->mario->is_enter == false && g->mario->x >= pPipe->x && g->mario->x + g->mario->width <= pPipe->x + 70 && abs(g->mario->y + g->mario->height - pPipe->y) < 3)
					MarioEnterPipeEvent(g, pPipe);//����½���ܵ��¼�
				if (g->mario->is_enter == true && g->mario->x >= pPipe->x && g->mario->x + g->mario->width <= pPipe->x + 70 && g->mario->y + g->mario->height >= pPipe->tran_location)
					MarioLeavePipeEvent(g, pPipe);//���������ܵ��¼�
			}
			else {
				if (g->mario->is_squat == false && g->mario->is_enter == false && g->mario->y >= pPipe->y && g->mario->y + g->mario->height <= pPipe->y + 80 && g->mario->vy == 0 && g->mario->vx > 0 && abs(g->mario->x + g->mario->width - pPipe->x) < 3)
					MarioEnterPipeEvent(g, pPipe);//����½���ܵ��¼�
				if (g->mario->is_squat == false && g->mario->is_enter == true && g->mario->y >= pPipe->y && g->mario->y + g->mario->height <= pPipe->y + 80 && g->mario->vy == 0 && g->mario->vx > 0 && g->mario->x + g->mario->width >= pPipe->tran_location)
					MarioLeavePipeEvent(g, pPipe);//���������ܵ��¼�
			}
		}
}

void MonsterTouchMonsterCheck(GameScene* g) {
	//����Ӵ���������
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pMonster1 = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pMonster1->is_exist == false || pMonster1->deathCnt != 0 || pMonster1->status == handstand)//��������
			continue;
		for (int j = i + 1; j < g->vecMonster.size; j++)
		{
			class Monster* pMonster2 = (class Monster*)g->vecMonster.get(&g->vecMonster, j);
			if (pMonster2->is_exist == false || pMonster2->deathCnt != 0 || pMonster2->status == handstand)//��������
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
	//����Ӵ���������
	for (int j = 0; j < g->vecFireball.size; j++)
	{
		class Fireball* pFireball = (class Fireball*)g->vecFireball.get(&g->vecFireball, j);
		for (int i = 0; i < g->vecMonster.size; i++)
		{
			class Monster* pMonster = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
			if (pMonster->is_exist == false || pMonster->deathCnt != 0 || pMonster->status == handstand)//δ���ɣ��Ѳ��������������Ĺ��ﲻ������
				continue;
			if (pFireball->x + pFireball->width > pMonster->x && pFireball->x < pMonster->x + pMonster->width && pFireball->y + pFireball->height > pMonster->y && pFireball->y < pMonster->y + pMonster->height) {
					MonsterHandstandEvent(g, pMonster);
					FireballBoomEvent(g, pFireball, false);
			}
		}
	}
}

void BlockStrikeMonsterCheck(GameScene* g, Block* block) {
	//����ײ��������
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pEntity = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pEntity->physic == false || pEntity->status == handstand || pEntity->type == piranha)
			continue;//δ���������غ͵��������Ĳ�������
		if (pEntity->x + pEntity->width >= block->x1 && pEntity->x <= block->x2 && pEntity->y + pEntity->height >= block->y1 - 5 && pEntity->y < block->y2) {
			MonsterHandstandEvent(g, pEntity);//���ﵹ������
		}
	}
}

void MarioTouchMonsterCheck(GameScene* g) {
	//����½Ӵ���������
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pMonster = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pMonster->is_exist == false || pMonster->deathCnt != 0 || pMonster->status == handstand)//δ���ɣ��Ѳ��������������Ĺ��ﲻ������
			continue;
		if (g->mario->x + g->mario->width > pMonster->x && g->mario->x < pMonster->x + pMonster->width && g->mario->y + g->mario->height > pMonster->y && g->mario->y < pMonster->y + pMonster->height) {
			if (g->mario->in_time != 0) {
				//�޵�ģʽɱ������
				MonsterHandstandEvent(g, pMonster);
				continue;
			}
			if (pMonster->type == piranha) {//ʳ�˻�
				if (g->mario->im_time == 0) {
					MarioDamageEvent(g);//����������¼�
				}
				continue;
			}
			if (g->mario->y + g->mario->height < pMonster->y + pMonster->height / 2 && g->mario->vy > 0) {
				MarioStompMonsterEvent(g, pMonster);//����²ȹ����¼�
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
					MarioDamageEvent(g);//����������¼�
				}
			}
		}
	}
}

void MonsterTouchBlockCheck(GameScene* g) {
	//����Ӵ���������
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pEntity = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pEntity->physic == false || pEntity->status == handstand)
			continue;//δ���������ػ�����������
		bool island = false;
		for (int j = 0; j < g->vecBlock.size; j++)
		{
			class Block* pBlock = (class Block*)g->vecBlock.get(&g->vecBlock, j);
			//����
			if (pBlock->type == hide)
				continue;//���ط����޷���������µ�ʵ�崥��
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->vy < pBlock->y2 && pEntity->y + pEntity->height > pBlock->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pBlock->y2 + 1;
				continue;
			}
			//ˮƽ����
			if (pEntity->y + pEntity->height > pBlock->y1 && pEntity->y < pBlock->y2) {
				//����
				if (pEntity->x + pEntity->width + pEntity->vx > pBlock->x1 && pEntity->x + pEntity->width < pBlock->x2) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pBlock->x1 - pEntity->width - 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
				//����
				if (pEntity->x + pEntity->vx < pBlock->x2 && pEntity->x > pBlock->x1) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pBlock->x2 + 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
			}
			//����
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
	//����Ӵ�ǽ����
	for (int i = 0; i < g->vecMonster.size; i++)
	{
		class Monster* pEntity = (class Monster*)g->vecMonster.get(&g->vecMonster, i);
		if (pEntity->physic == false || pEntity->status == handstand)
			continue;//δ���������ػ�����������
		bool island = pEntity->is_land;
		for (int j = 0; j < g->vecWall.size; j++)
		{
			class Wall* pWall = (class Wall*)g->vecWall.get(&g->vecWall, j);
			//����
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pWall->y2 + 1;
				continue;
			}
			//ˮƽ����
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//����
				if (pEntity->x + pEntity->width + pEntity->vx > pWall->x1 && pEntity->x + pEntity->width < pWall->x2) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x1 - pEntity->width - 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
				//����
				if (pEntity->x + pEntity->vx < pWall->x2 && pEntity->x > pWall->x1) {
					pEntity->vx = -pEntity->vx;
					pEntity->x = pWall->x2 + 1;
					if (pEntity->type == tortoise && pEntity->status == shrunkenheaded && pEntity->vx != 0)
						playAudio("bump");
					continue;
				}
			}
			//����
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
	//����ײ�����߼��
	for (int i = 0; i < g->vecProp.size; i++)
	{
		class Prop* pEntity = (class Prop*)g->vecProp.get(&g->vecProp, i);
		if (pEntity->createTime != 0)//��������
			continue;
		if (pEntity->x + pEntity->width > block->x1 && pEntity->x < block->x2 && pEntity->y + pEntity->height >= block->y1 && pEntity->y < block->y2) {
			if (pEntity->type == propType::coin) {
				addParticle(g, block->x1 + 1, block->y1 - 40, flycoin, 0, -6);
				addParticle(g, block->x1, block->y1 + 20, text, 0, -1, "200", 150);
				MarioEatPropEvent(g, pEntity);
				pEntity->Destroy(g);//���ٽ��
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
	//����Ӵ���������(�����������)
	for (int i = 0; i < g->vecFireball.size; i++)
	{
		class Fireball* pEntity = (class Fireball*)g->vecFireball.get(&g->vecFireball, i);
		if (pEntity->physic == false)
			continue;//δ���������ص�ʵ�岻������
		for (int j = 0; j < g->vecBlock.size; j++)
		{
			class Block* pBlock = (class Block*)g->vecBlock.get(&g->vecBlock, j);
			//����
			if (pBlock->type == hide)
				continue;//���ط����޷���������µ�ʵ�崥��
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->vy < pBlock->y2 && pEntity->y + pEntity->height > pBlock->y2) {
				FireballBoomEvent(g, pEntity);
				break;
			}
			//ˮƽ����
			if (pEntity->y + pEntity->height > pBlock->y1 && pEntity->y < pBlock->y2) {
				//����
				if (pEntity->x + pEntity->width + pEntity->vx > pBlock->x1 && pEntity->x + pEntity->width < pBlock->x2) {
					FireballBoomEvent(g, pEntity);
					break;
				}
				if (pEntity->x + pEntity->vx < pBlock->x2 && pEntity->x > pBlock->x1) {
					FireballBoomEvent(g, pEntity);
					break;
				}
			}
			//����
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pBlock->y1 && pEntity->y + pEntity->height < pBlock->y2) {
				pEntity->vy = -5;
				pEntity->y = pBlock->y1 - pEntity->height;
			}
		}

	}
}

void FireballTouchWallCheck(GameScene* g) {
	//����Ӵ�ǽ����(�����������)
	for (int i = 0; i < g->vecFireball.size; i++)
	{
		class Fireball* pEntity = (class Fireball*)g->vecFireball.get(&g->vecFireball, i);
		if (pEntity->physic == false)
			continue;//δ���������ص�ʵ�岻������
		for (int j = 0; j < g->vecWall.size; j++)
		{
			class Wall* pWall = (class Wall*)g->vecWall.get(&g->vecWall, j);
			//����
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				FireballBoomEvent(g, pEntity);
				break;
			}
			//ˮƽ����
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//����
				if (pEntity->x + pEntity->width + pEntity->vx > pWall->x1 && pEntity->x + pEntity->width < pWall->x2) {
					FireballBoomEvent(g, pEntity);
					break;
				}
				if (pEntity->x + pEntity->vx < pWall->x2 && pEntity->x > pWall->x1) {
					FireballBoomEvent(g, pEntity);
					break;
				}
			}
			//����
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->height + pEntity->vy >= pWall->y1 && pEntity->y + pEntity->height < pWall->y2) {
				pEntity->vy = -5;
				pEntity->y = pWall->y1 - pEntity->height;
			}
		}
	}
}

void MarioTouchPropCheck(GameScene* g) {
	//����½Ӵ���������
	for (int i = 0; i < g->vecProp.size; i++)
	{
		class Prop* pProp = (class Prop*)g->vecProp.get(&g->vecProp, i);
		if (g->mario->x + g->mario->width > pProp->x && g->mario->x < pProp->x + pProp->width && g->mario->y + g->mario->height > pProp->y && g->mario->y < pProp->y + pProp->height) {
			MarioEatPropEvent(g, pProp);//����³Ե����¼�
			pProp->Destroy(g);//���ٵ���
		}
	}
}

void MarioTouchBlockCheck(GameScene* g) {
	//����½Ӵ���������
	if (g->mario->physic == false)
		return;
	bool island = false;
	for (int j = 0; j < g->vecBlock.size; j++)
	{
		class Block* pBlock = (class Block*)g->vecBlock.get(&g->vecBlock, j);
		//����
		if (g->mario->vy < 0 && g->mario->x + g->mario->width > pBlock->x1 + 5 && g->mario->x < pBlock->x2 - 5 && g->mario->y + g->mario->vy < pBlock->y2 && g->mario->y + g->mario->height > pBlock->y2) {
			g->mario->vy = -g->mario->vy / 2;
			g->mario->y = pBlock->y2;
			BlockStrikeEvent(g, pBlock, g->mario);
			continue;
		}
		if (pBlock->type != hide) {
			//ˮƽ����
			if (g->mario->y + g->mario->height > pBlock->y1 && g->mario->y < pBlock->y2) {
				//����
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

			//����
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
	//����½Ӵ�ǽ����
	if (g->mario->physic == false)
		return;
	bool island = g->mario->is_land;
	for (int j = 0; j < g->vecWall.size; j++)
	{
		class Wall* pWall = (class Wall*)g->vecWall.get(&g->vecWall, j);
		//����
		if (g->mario->x + g->mario->width > pWall->x1 + 5 && g->mario->x < pWall->x2 - 5 && g->mario->y + g->mario->vy < pWall->y2 && g->mario->y + g->mario->height > pWall->y2) {
			g->mario->vy = -g->mario->vy / 2;
			g->mario->y = pWall->y2 + 1;
			continue;
		}
		//ˮƽ����
		if (g->mario->y + g->mario->height > pWall->y1 && g->mario->y < pWall->y2) {
			//����
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
		//����
		if (g->mario->x + g->mario->width > pWall->x1 + 5 && g->mario->x < pWall->x2 - 5 && g->mario->y + g->mario->height + g->mario->vy >= pWall->y1 && g->mario->y + g->mario->height < pWall->y2) {
			g->mario->vy = 0;
			g->mario->y = pWall->y1 - g->mario->height;
			g->mario->is_land = true;
		}
	}
}
/*
void entityTouchBlockCheck(GameScene* g) {
	//ʵ��Ӵ���������(�����������)
	for (int i = 0; i < g->vecEntity.size; i++)
	{
		class Entity* pEntity = (class Entity*)g->vecEntity.get(&g->vecEntity, i);
		if (pEntity->physic == false)
			continue;//δ���������ص�ʵ�岻������
		bool island = false;
		for (int j = 0; j < g->vecBlock.size; j++)
		{
			class Block* pBlock = (class Block*)g->vecBlock.get(&g->vecBlock, j);
			//����
			if (pBlock->type == hide)
				continue;//���ط����޷���������µ�ʵ�崥��
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->vy < pBlock->y2 && pEntity->y + pEntity->height > pBlock->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pBlock->y2 + 1;
				continue;
			}
			//ˮƽ����
			if (pEntity->y + pEntity->height > pBlock->y1 && pEntity->y < pBlock->y2) {
				//����
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
			//����
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
	//ʵ��Ӵ�ǽ����(�����������)
	for (int i = 0; i < g->vecEntity.size; i++)
	{
		class Entity* pEntity = (class Entity*)g->vecEntity.get(&g->vecEntity, i);
		if (pEntity->physic == false)
			continue;//δ���������ص�ʵ�岻������
		bool island = pEntity->is_land;
		for (int j = 0; j < g->vecWall.size; j++)
		{
			class Wall* pWall = (class Wall*)g->vecWall.get(&g->vecWall, j);
			//����
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pWall->y2 + 1;
				continue;
			}
			//ˮƽ����
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//����
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
			//����
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
	//���߽Ӵ���������
	for (int i = 0; i < g->vecProp.size; i++)
	{
		class Prop* pEntity = (class Prop*)g->vecProp.get(&g->vecProp, i);
		if (pEntity->physic == false)
			continue;//δ���������ص�ʵ�岻������
		bool island = false;
		for (int j = 0; j < g->vecBlock.size; j++)
		{
			class Block* pBlock = (class Block*)g->vecBlock.get(&g->vecBlock, j);
			//����
			if (pBlock->type == hide)
				continue;//���ط����޷���������µ�ʵ�崥��
			if (pEntity->x + pEntity->width > pBlock->x1 + 5 && pEntity->x < pBlock->x2 - 5 && pEntity->y + pEntity->vy < pBlock->y2 && pEntity->y + pEntity->height > pBlock->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pBlock->y2 + 1;
				continue;
			}
			//ˮƽ����
			if (pEntity->y + pEntity->height > pBlock->y1 && pEntity->y < pBlock->y2) {
				//����
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
			//����
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
	//���߽Ӵ�ǽ����
	for (int i = 0; i < g->vecProp.size; i++)
	{
		class Prop* pEntity = (class Prop*)g->vecProp.get(&g->vecProp, i);
		if (pEntity->physic == false)
			continue;//δ���������ص�ʵ�岻������
		bool island = pEntity->is_land;
		for (int j = 0; j < g->vecWall.size; j++)
		{
			class Wall* pWall = (class Wall*)g->vecWall.get(&g->vecWall, j);
			//����
			if (pEntity->x + pEntity->width > pWall->x1 + 5 && pEntity->x < pWall->x2 - 5 && pEntity->y + pEntity->vy < pWall->y2 && pEntity->y + pEntity->height > pWall->y2) {
				pEntity->vy = -pEntity->vy / 2;
				pEntity->y = pWall->y2 + 1;
				continue;
			}
			//ˮƽ����
			if (pEntity->y + pEntity->height > pWall->y1 && pEntity->y < pWall->y2) {
				//����
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
			//����
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
	//�������

	if (!(gamescene->mario->is_death == true || gamescene->mario->is_enter == true)) {
		MarioTouchBlockCheck(gamescene);
		//����½Ӵ�������

		MarioTouchWallCheck(gamescene);
		//����½Ӵ�ǽ����

		MarioTouchPlatformCheck(gamescene);
		//����½Ӵ�ƽ̨���

		MarioTouchPropCheck(gamescene);
		//����½Ӵ����߼��

		MarioTouchMonsterCheck(gamescene);
		//����½Ӵ�������

		MarioTouchFlagCheck(gamescene);
		//�����ץ����
	}
	
	MarioEnterPipeCheck(gamescene);
	//����½���ܵ����

	PropTouchBlockCheck(gamescene);
	//���߽Ӵ�������

	PropTouchWallCheck(gamescene);
	//���߽Ӵ�ǽ����

	PropTouchPlatformCheck(gamescene);
	//���߽Ӵ�ƽ̨���

	FireballTouchBlockCheck(gamescene);
	//����Ӵ�������

	FireballTouchWallCheck(gamescene);
	//����Ӵ�ǽ����

	FireballTouchPlatformCheck(gamescene);
	//����Ӵ�ƽ̨���

	MonsterTouchBlockCheck(gamescene);
	//����Ӵ�������

	MonsterTouchWallCheck(gamescene);
	//����Ӵ�ǽ����

	MonsterTouchPlatformCheck(gamescene);
	//����Ӵ�ƽ̨���

	MonsterTouchMonsterCheck(gamescene);
	//����Ӵ�������

	FireballTouchMonsterCheck(gamescene);
	//����Ӵ�������
}