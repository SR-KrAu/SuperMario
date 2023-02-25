#include "wall.h"
#include "gamescene.h"
#include "collisionbox.h"

void Wall::WallDraw(Camera* camera) {
	//绘制墙体碰撞箱
	ShowCollisionbox(camera, this->x1, this->y1, this->x2, this->y2);
}

void Wall::WallUpdate(GameScene* gamescene) {
	//离开缓冲区将销毁对象
	if (this->x2 < gamescene->camera->x - 300 - 300)
		this->WallDestroy(gamescene);
}

void Wall::WallDestroy(GameScene* gamescene) {
	//销毁方块对象
	for (int i = 0; i < gamescene->vecWall.size; i++)
	{//遍历方块类动态数组寻找相应对象
		class Wall* pWall = (class Wall*)gamescene->vecWall.get(&gamescene->vecWall, i);
		if (pWall == this) {
			//清除相应对象
			gamescene->vecWall.remove(&gamescene->vecWall, i);
			free(pWall);
			break;
		}
	}
}

void WallDraw(GameScene* gamescene) {
	//绘制墙体入口
	for (int j = 0; j < gamescene->vecWall.size; j++)
	{
		class Wall* pWall = (class Wall*)gamescene->vecWall.get(&gamescene->vecWall, j);
		pWall->WallDraw(gamescene->camera);
	}
}

void WallUpdate(GameScene* gamescene) {
	//更新墙体入口
	for (int j = 0; j < gamescene->vecWall.size; j++)
	{
		class Wall* pWall = (class Wall*)gamescene->vecWall.get(&gamescene->vecWall, j);
		pWall->WallUpdate(gamescene);
	}
}

void addWall(GameScene* gamescene, int x1, int y1, int x2, int y2) {
	//添加墙对象
	class Wall* pWall = (class Wall*)malloc(sizeof(class Wall));
	if (pWall == NULL)
		return;
	pWall->x1 = x1;
	pWall->y1 = y1;
	pWall->x2 = x2;
	pWall->y2 = y2;
	gamescene->vecWall.append(&gamescene->vecWall, pWall);
}

void WallInit(GameScene* gamescene) {
	//初始化墙体
	switch (gamescene->level->name) {
	case level1_1:
		addWall(gamescene, 0, 524, 2816, 700);
		addWall(gamescene, 2897, 524, 3460, 700);
		addWall(gamescene, 3581, 524, 6156, 700);
		addWall(gamescene, 6238, 524, 8770, 700);
		addWall(gamescene, 1131, 444, 1201, 523);
		addWall(gamescene, 1534, 404, 1603, 523);
		addWall(gamescene, 1856, 363, 1925, 523);
		addWall(gamescene, 2298, 363, 2368, 523);
		addWall(gamescene, 6565, 444, 6634, 523);
		addWall(gamescene, 7209, 444, 7278, 523);
		addWall(gamescene, 5393, 484, 5553, 523);
		addWall(gamescene, 5433, 444, 5553, 484);
		addWall(gamescene, 5473, 404, 5553, 444);
		addWall(gamescene, 5513, 363, 5553, 404);
		addWall(gamescene, 5634, 363, 5673, 404);
		addWall(gamescene, 5634, 404, 5714, 444);
		addWall(gamescene, 5634, 444, 5754, 484);
		addWall(gamescene, 5634, 484, 5794, 523);
		addWall(gamescene, 5956, 484, 6156, 523);
		addWall(gamescene, 5996, 444, 6156, 484);
		addWall(gamescene, 6036, 404, 6156, 444);
		addWall(gamescene, 6078, 363, 6156, 404);
		addWall(gamescene, 6238, 363, 6277, 404);
		addWall(gamescene, 6238, 404, 6317, 444);
		addWall(gamescene, 6238, 444, 6357, 484);
		addWall(gamescene, 6238, 484, 6398, 523);
		addWall(gamescene, 7284, 484, 7645, 523);
		addWall(gamescene, 7324, 444, 7645, 484);
		addWall(gamescene, 7365, 404, 7645, 444);
		addWall(gamescene, 7405, 363, 7645, 404);
		addWall(gamescene, 7445, 323, 7645, 363);
		addWall(gamescene, 7485, 283, 7645, 323);
		addWall(gamescene, 7526, 243, 7645, 283);
		addWall(gamescene, 7566, 202, 7645, 243);
		addWall(gamescene, 7968, 484, 8008, 523);
		break;
	case level1_1_pipe:
		addWall(gamescene, 0, 0, 40, 522);
		addWall(gamescene, 0, 523, 807,	600);
		addWall(gamescene, 161, 402, 443, 522);
		addWall(gamescene, 523, 443, 683, 522);
		addWall(gamescene, 609, 0, 678, 442);
		break;
	case level1_2:
		addWall(gamescene, 0, 0, 40, 522);
		addWall(gamescene, 0, 523, 3220, 700);
		addWall(gamescene, 3341, 523, 4830, 700);
		addWall(gamescene, 4911, 402, 4991, 700);
		addWall(gamescene, 5072, 523, 5554, 700);
		addWall(gamescene, 5836, 523, 6158, 700);
		addWall(gamescene, 684, 483, 724, 522);
		addWall(gamescene, 765, 443, 805, 522);
		addWall(gamescene, 845, 402, 885, 522);
		addWall(gamescene, 926, 362, 966, 522);
		addWall(gamescene, 1006, 362, 1046, 522);
		addWall(gamescene, 1087, 402, 1127, 522);
		addWall(gamescene, 1248, 402, 1288, 522);
		addWall(gamescene, 1328, 443, 1368, 522);
		addWall(gamescene, 4151, 402, 4220, 522);
		addWall(gamescene, 4392, 362, 4462, 522);
		addWall(gamescene, 4634, 443, 4703, 522);
		addWall(gamescene, 5353, 483, 5554, 522);
		addWall(gamescene, 5394, 443, 5554, 482);
		addWall(gamescene, 5434, 402, 5554, 442);
		addWall(gamescene, 5475, 362, 5554, 401);
		addWall(gamescene, 6440, 402, 6841, 700);
		addWall(gamescene, 6681, 322, 6841, 401);
		addWall(gamescene, 6767, 80, 6841, 321);
		addWall(gamescene, 6842, 80, 7123, 700);
		addWall(gamescene, 7124, 523, 7646, 700);
		addWall(gamescene, 7647, 0, 7768, 700);
		addWall(gamescene, 7169, 402, 7239, 522);
		addWall(gamescene, 7330, 402, 7400, 522);
		addWall(gamescene, 7491, 402, 7561, 522);
		addWall(gamescene, 7124, 80, 7527, 120);
		break;
	case level1_2_pipe:
		addWall(gamescene, 0, 524, 800, 700);
		addWall(gamescene, 0, 0, 38, 523);
		addWall(gamescene, 519, 0, 800, 523);
		break;
	case level1_2_ground:
		addWall(gamescene, 0, 523, 1695, 700);
		addWall(gamescene, 252, 443, 320, 522);
		addWall(gamescene, 327, 483, 688, 522);
		addWall(gamescene, 367, 443, 688, 482);
		addWall(gamescene, 407, 403, 688, 442);
		addWall(gamescene, 447, 363, 688, 402);
		addWall(gamescene, 487, 323, 688, 362);
		addWall(gamescene, 527, 283, 688, 322);
		addWall(gamescene, 567, 243, 688, 282);
		addWall(gamescene, 607, 202, 688, 242);
		addWall(gamescene, 1011, 483, 1051, 522);
		break;
	case level1_3:
		addWall(gamescene, 0, 524, 762, 700);
		addWall(gamescene, 843, 484, 1003, 523);
		addWall(gamescene, 1085, 363, 1406, 403);
		addWall(gamescene, 1165, 202, 1365, 242);
		addWall(gamescene, 1407, 484, 1526, 523);
		addWall(gamescene, 1527, 323, 1728, 362);
		addWall(gamescene, 1729, 162, 2009, 201);
		addWall(gamescene, 2131, 524, 2291, 564);
		addWall(gamescene, 2493, 524, 2694, 564);
		addWall(gamescene, 2534, 202, 2694, 242);
		addWall(gamescene, 2735, 524, 2935, 564);
		addWall(gamescene, 2936, 363, 3056, 403);
		addWall(gamescene, 3178, 243, 3418, 282);
		addWall(gamescene, 4103, 444, 4263, 483);
		addWall(gamescene, 4345, 283, 4666, 322);
		addWall(gamescene, 4707, 524, 4828, 564);
		addWall(gamescene, 4828, 363, 4988, 403);
		addWall(gamescene, 5069, 363, 5229, 403);
		addWall(gamescene, 5351, 524, 7178, 700);
		addWall(gamescene, 5713, 363, 5954, 523);
		addWall(gamescene, 5794, 283, 5954, 362);
		addWall(gamescene, 5874, 202, 5954, 282);
		break;
	}
}