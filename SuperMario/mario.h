#pragma once

#include "entity.h"

namespace MarioData {
	enum marioBody {
		child,//С��
		adult,//����
		old//����
	};
}

using namespace MarioData;

class Mario :public Entity {//�������
public:
	bool is_run;//�Ƿ���
	bool is_speed;//�Ƿ����
	bool is_squat;//�Ƿ����
	bool is_jump;//�Ƿ���Ծ
	bool is_death;//�Ƿ�����
	bool is_enter;//�Ƿ����ܵ�
	bool is_flag;//�Ƿ�ץ��
	bool is_stealth;//�Ƿ�����
	int fireCnt;//������������
	int mario_dir;//����³���
	int runF, runCnt;//���ܶ���֡�������
	int frameCnt;//��֡������
	int in_time;//�޵�ʱ��
	int im_time;//����ʱ��
	int transf_time;//����ʱ��
	marioBody body;//����
	void Init(class GameScene*);
	void Draw(class GameScene*);
	void Update(class GameScene*);
	void WinUpdate(class GameScene*);
};