#include "camera.h"
#include "gamescene.h"

void Camera::Init(GameScene* gamescene) {
	//初始化摄像机对象
	if (gamescene->mario->x <= 300)
		gamescene->camera->x = 300;
	else
		gamescene->camera->x = gamescene->mario->x;
}

void Camera::Update(GameScene* gamescene) {
	//更新摄像机数据
	if (gamescene->level->name == level1_1_pipe || gamescene->level->name == level1_2_pipe)//在这些世界中不更新摄像机位置
		return;
	if (gamescene->mario->is_flag == true || gamescene->mario->is_enter == true)//不更新摄像机位置
		return;
	if (gamescene->mario->x > x) {
		x = gamescene->mario->x;
	}
}