#include "camera.h"
#include "gamescene.h"

void Camera::Init(GameScene* gamescene) {
	//��ʼ�����������
	if (gamescene->mario->x <= 300)
		gamescene->camera->x = 300;
	else
		gamescene->camera->x = gamescene->mario->x;
}

void Camera::Update(GameScene* gamescene) {
	//�������������
	if (gamescene->level->name == level1_1_pipe || gamescene->level->name == level1_2_pipe)//����Щ�����в����������λ��
		return;
	if (gamescene->mario->is_flag == true || gamescene->mario->is_enter == true)//�����������λ��
		return;
	if (gamescene->mario->x > x) {
		x = gamescene->mario->x;
	}
}