#include "block.h"
#include "image.h"
#include "audio.h"
#include "gamescene.h"

using namespace ImageData;

int effF, effCnt;

void Block::Draw(Camera* camera) {
	//绘制方块

	//不绘制缓冲区以外的图像
	if (this->x2 < camera->x - 300 - 300 || this->x1 > camera->x + 500 + 300)
		return;

	IMAGE flipimg;
	switch (this->type) {
	case brick:
		transparentimage(NULL, 300 + this->x1 - camera->x, this->y1 - this->upHeight, &brickImg, &flipimg);
		break;
	case question:
		transparentimage(NULL, 300 + this->x1 - camera->x, this->y1 - this->upHeight, &questionblockImg[effF], &flipimg);
		break;
	case nullquestion:
		transparentimage(NULL, 300 + this->x1 - camera->x, this->y1 - this->upHeight, &questionblockImg[3], &flipimg);
		break;
	}
	this->WallDraw(camera);//调用墙类(父类)绘制碰撞箱的函数
}

void Block::Update(GameScene* gamescene) {
	//更新方块
	
	//离开缓冲区将销毁对象
	if (this->x2 < gamescene->camera->x - 300 - 300)
		this->Destroy(gamescene);
	
	if (this->prop == blockProp::coins && this->coins < 16 && this->coins > 1) {
		if (rand() % 51 == 0)//大量金币方块被撞击后随时间金币将逐渐减少为1
		this->coins--;
	}
	if (this->upHeight != 0) {//方块顶起动画刷新
		//使方块被顶起
		if (this->upDir == 1) {//上升
			this->upHeight++;
			if (this->upHeight == 12)
				this->upDir = -1;
		}
		else if (this->upDir == -1) {
			this->upHeight--;
			if (this->upHeight == 0)
				this->upDir = 0;
		}
	}
	
}

void Block::Destroy(GameScene* gamescene) {
	//销毁方块对象
	for (int i = 0; i < gamescene->vecBlock.size; i++)
	{//遍历方块类动态数组寻找相应对象
		class Block* pBlock = (class Block*)gamescene->vecBlock.get(&gamescene->vecBlock, i);
		if (pBlock == this) {
			//清除相应对象
			gamescene->vecBlock.remove(&gamescene->vecBlock, i);
			free(pBlock);
			//playAudio("powerup");
			break;
		}
	}
}

void BlockDraw(GameScene* g) {
	//绘制方块入口
	for (int i = 0; i < g->vecBlock.size; i++)
	{//遍历所有方块进行绘制
		class Block* pBlock = (class Block*)g->vecBlock.get(&g->vecBlock, i);
		pBlock->Draw(g->camera);
	}
}

void BlockUpdate(GameScene* gamescene) {
	//更新方块入口

	//更新方块对象
	for (int j = 0; j < gamescene->vecBlock.size; j++)
	{
		class Block* pBlock = (class Block*)gamescene->vecBlock.get(&gamescene->vecBlock, j);
		pBlock->Update(gamescene);
	}

	//特效动画帧刷新
	if (effCnt != 20) {
		effCnt++;
	}
	else {
		if (effF != 2) {
			effF++;
		}
		else {
			effF = 0;
		}
		effCnt = 0;
	}
}

void addBlock(GameScene* gamescene, int x1, int y1, blockType type, blockProp prop = null, int coins = 16) {
	//添加方块对象
	class Block* pBlock = (class Block*)malloc(sizeof(class Block));
	if (pBlock == NULL)
		return;
	pBlock->x1 = x1;
	pBlock->y1 = y1;
	pBlock->x2 = x1 + 40;
	pBlock->y2 = y1 + 40;
	pBlock->type = type;
	pBlock->prop = prop;
	pBlock->upHeight = 0;
	pBlock->upDir = 0;
	pBlock->coins = coins;
	gamescene->vecBlock.append(&gamescene->vecBlock, pBlock);
}

void BlockInit(GameScene* gamescene) {
	//初始化方块
	effF = 0;
	effCnt = 0;
	switch (gamescene->level->name) {
	case level1_1:
		addBlock(gamescene, 643, 363, question, coin);
		addBlock(gamescene, 845, 363, question, grow);
		addBlock(gamescene, 925, 363, question, coin);
		addBlock(gamescene, 885, 202, question, coin);
		addBlock(gamescene, 3138, 363, question, grow);
		addBlock(gamescene, 3782, 202, question, coin);
		addBlock(gamescene, 4266, 363, question, coin);
		addBlock(gamescene, 4386, 363, question, coin);
		addBlock(gamescene, 4507, 363, question, coin);
		addBlock(gamescene, 4386, 202, question, grow);
		addBlock(gamescene, 5191, 202, question, coin);
		addBlock(gamescene, 5231, 202, question, coin);
		addBlock(gamescene, 6841, 363, question, coin);
		addBlock(gamescene, 805, 363, brick);
		addBlock(gamescene, 885, 363, brick);
		addBlock(gamescene, 965, 363, brick);
		addBlock(gamescene, 3098, 363, brick);
		addBlock(gamescene, 3178, 363, brick);
		addBlock(gamescene, 3219, 202, brick);
		addBlock(gamescene, 3259, 202, brick);
		addBlock(gamescene, 3299, 202, brick);
		addBlock(gamescene, 3339, 202, brick);
		addBlock(gamescene, 3379, 202, brick);
		addBlock(gamescene, 3419, 202, brick);
		addBlock(gamescene, 3459, 202, brick);
		addBlock(gamescene, 3499, 202, brick);
		addBlock(gamescene, 3539, 202, brick);
		addBlock(gamescene, 3662, 202, brick);
		addBlock(gamescene, 3702, 202, brick);
		addBlock(gamescene, 3782, 363, brick, coins);
		addBlock(gamescene, 4024, 363, brick);
		addBlock(gamescene, 4064, 363, brick, star);
		addBlock(gamescene, 4774, 363, brick);
		addBlock(gamescene, 4869, 202, brick);
		addBlock(gamescene, 4909, 202, brick);
		addBlock(gamescene, 4949, 202, brick);
		addBlock(gamescene, 5151, 202, brick);
		addBlock(gamescene, 5191, 363, brick);
		addBlock(gamescene, 5231, 363, brick);
		addBlock(gamescene, 5271, 202, brick);
		addBlock(gamescene, 6761, 363, brick);
		addBlock(gamescene, 6801, 363, brick);
		addBlock(gamescene, 6881, 363, brick);
		addBlock(gamescene, 3742, 202, brick);
		addBlock(gamescene, 2616, 323, hide, oneup);
		break;
	case level1_2:
		for (int i = 221; i < 5530; i += 40) {
			if (i == 3581)
				addBlock(gamescene, i, 82, brick, oneup);
			else
				addBlock(gamescene, i, 82, brick, null);
		}
		addBlock(gamescene, 403, 362, question, grow);
		addBlock(gamescene, 443, 362, question, coin);
		addBlock(gamescene, 483, 362, question, coin);
		addBlock(gamescene, 523, 362, question, coin);
		addBlock(gamescene, 563, 362, question, coin);
		addBlock(gamescene, 1167, 322, brick, coins);
		addBlock(gamescene, 1570, 282, brick);
		addBlock(gamescene, 1570, 322, brick);
		addBlock(gamescene, 1570, 362, brick);
		addBlock(gamescene, 1610, 362, brick);
		addBlock(gamescene, 1650, 362, brick);
		addBlock(gamescene, 1650, 322, brick);
		addBlock(gamescene, 1650, 282, brick);
		addBlock(gamescene, 1690, 282, brick);
		addBlock(gamescene, 1730, 282, brick);
		addBlock(gamescene, 1770, 282, brick);
		addBlock(gamescene, 1770, 322, brick);
		addBlock(gamescene, 1770, 362, brick);
		addBlock(gamescene, 1810, 362, brick);
		addBlock(gamescene, 1850, 362, brick);
		addBlock(gamescene, 1850, 322, brick);
		addBlock(gamescene, 1850, 282, brick, star);
		addBlock(gamescene, 2093, 202, brick);
		addBlock(gamescene, 2093, 242, brick);
		addBlock(gamescene, 2093, 282, brick);
		addBlock(gamescene, 2093, 322, brick);
		addBlock(gamescene, 2093, 362, brick);
		addBlock(gamescene, 2133, 202, brick);
		addBlock(gamescene, 2133, 242, brick);
		addBlock(gamescene, 2133, 282, brick);
		addBlock(gamescene, 2133, 322, brick);
		addBlock(gamescene, 2133, 362, brick);
		addBlock(gamescene, 2174, 122, brick);
		addBlock(gamescene, 2174, 162, brick);
		addBlock(gamescene, 2214, 122, brick);
		addBlock(gamescene, 2214, 162, brick);
		addBlock(gamescene, 2173, 362, brick);
		addBlock(gamescene, 2173, 402, brick);
		addBlock(gamescene, 2173, 442, brick);
		addBlock(gamescene, 2213, 362, brick);
		addBlock(gamescene, 2213, 402, brick);
		addBlock(gamescene, 2213, 442, brick);
		addBlock(gamescene, 2335, 122, brick);
		addBlock(gamescene, 2335, 162, brick);
		addBlock(gamescene, 2375, 122, brick);
		addBlock(gamescene, 2375, 162, brick);
		addBlock(gamescene, 2415, 122, brick);
		addBlock(gamescene, 2415, 162, brick);
		addBlock(gamescene, 2455, 122, brick);
		addBlock(gamescene, 2455, 162, brick);
		addBlock(gamescene, 2495, 122, brick);
		addBlock(gamescene, 2495, 162, brick);
		addBlock(gamescene, 2535, 122, brick);
		addBlock(gamescene, 2535, 162, brick);
		addBlock(gamescene, 2495, 202, brick);
		addBlock(gamescene, 2535, 202, brick);
		addBlock(gamescene, 2495, 242, brick);
		addBlock(gamescene, 2535, 242, brick);
		addBlock(gamescene, 2495, 282, brick);
		addBlock(gamescene, 2535, 282, brick);
		addBlock(gamescene, 2495, 322, brick);
		addBlock(gamescene, 2535, 322, brick);
		addBlock(gamescene, 2495, 362, brick);
		addBlock(gamescene, 2535, 362, brick);
		addBlock(gamescene, 2455, 362, brick);
		addBlock(gamescene, 2415, 362, brick);
		addBlock(gamescene, 2375, 362, brick);
		addBlock(gamescene, 2335, 362, brick);
		addBlock(gamescene, 2657, 122, brick);
		addBlock(gamescene, 2657, 162, brick);
		addBlock(gamescene, 2697, 122, brick);
		addBlock(gamescene, 2697, 162, brick);
		addBlock(gamescene, 2737, 122, brick);
		addBlock(gamescene, 2737, 162, brick);
		addBlock(gamescene, 2777, 122, brick);
		addBlock(gamescene, 2777, 162, brick);
		addBlock(gamescene, 2697, 202, brick);
		addBlock(gamescene, 2697, 242, brick);
		addBlock(gamescene, 2697, 282, brick);
		addBlock(gamescene, 2697, 322, brick);
		addBlock(gamescene, 2697, 362, brick);
		addBlock(gamescene, 2737, 362, brick);
		addBlock(gamescene, 2777, 362, brick);
		addBlock(gamescene, 2777, 322, brick, grow);
		addBlock(gamescene, 2898, 202, brick);
		addBlock(gamescene, 2938, 202, brick);
		addBlock(gamescene, 2898, 242, brick);
		addBlock(gamescene, 2938, 242, brick);
		addBlock(gamescene, 2898, 282, brick);
		addBlock(gamescene, 2938, 282, brick);
		addBlock(gamescene, 2898, 322, brick);
		addBlock(gamescene, 2938, 322, brick, coins);
		addBlock(gamescene, 2898, 362, brick);
		addBlock(gamescene, 2938, 362, brick);
		addBlock(gamescene, 3059, 122, brick);
		addBlock(gamescene, 3099, 122, brick);
		addBlock(gamescene, 3139, 122, brick);
		addBlock(gamescene, 3179, 122, brick);
		addBlock(gamescene, 3059, 162, brick);
		addBlock(gamescene, 3099, 162, brick);
		addBlock(gamescene, 3139, 162, brick);
		addBlock(gamescene, 3179, 162, brick);
		addBlock(gamescene, 3059, 362, brick);
		addBlock(gamescene, 3099, 362, brick);
		addBlock(gamescene, 3139, 362, brick);
		addBlock(gamescene, 3179, 362, brick);
		addBlock(gamescene, 3381, 282, brick);
		addBlock(gamescene, 3421, 282, brick);
		addBlock(gamescene, 3461, 282, brick);
		addBlock(gamescene, 3501, 282, brick);
		addBlock(gamescene, 3541, 282, brick);
		addBlock(gamescene, 3581, 282, brick);
		addBlock(gamescene, 3381, 322, brick);
		addBlock(gamescene, 3421, 322, brick);
		addBlock(gamescene, 3461, 322, brick);
		addBlock(gamescene, 3501, 322, brick);
		addBlock(gamescene, 3541, 322, brick);
		addBlock(gamescene, 3581, 322, brick);
		addBlock(gamescene, 5836, 322, brick);
		addBlock(gamescene, 5876, 322, brick);
		addBlock(gamescene, 5916, 322, brick);
		addBlock(gamescene, 5956, 322, brick);
		addBlock(gamescene, 5996, 322, brick);
		addBlock(gamescene, 6036, 322, brick, grow);
		addBlock(gamescene, 6727, 80, brick);
		addBlock(gamescene, 6687, 80, brick);
		addBlock(gamescene, 6647, 80, brick);
		addBlock(gamescene, 6607, 80, brick);
		addBlock(gamescene, 6567, 80, brick);
		addBlock(gamescene, 6527, 80, brick);
		addBlock(gamescene, 6487, 80, brick);
		break;
	case level1_2_pipe:
		addBlock(gamescene, 119, 362, brick);
		addBlock(gamescene, 159, 362, brick);
		addBlock(gamescene, 199, 362, brick);
		addBlock(gamescene, 239, 362, brick);
		addBlock(gamescene, 279, 362, brick);
		addBlock(gamescene, 319, 362, brick);
		addBlock(gamescene, 359, 362, brick);
		addBlock(gamescene, 399, 362, brick);
		addBlock(gamescene, 439, 362, brick);
		addBlock(gamescene, 479, 362, brick, coins);
		for (int i = 0; i <= 202; i += 40)
			for (int j = 119; j <= 479; j += 40)
				addBlock(gamescene, j, i, brick);
		break;
	case level1_3:
		addBlock(gamescene, 2493, 404, question, grow);
		break;
	}
}