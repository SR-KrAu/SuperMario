#pragma once

#include <graphics.h>
#include "level.h"

namespace PipeData {
	enum pipeType {
		down,
		right
	};
}

using namespace LevelData;
using namespace PipeData;

class Pipe {//�ܵ���
public:
	bool is_tran;//�Ƿ���д��͹���
	levelName tran_level;//��������
	pipeType type;//����
	int x, y;//λ��
	int tran_location;//����λ��
	int tran_x, tran_y;//��������
	IMAGE* pipeImg;//ͼƬ
	bool is_newlevel;//�Ƿ�����µĹؿ�
	void Draw(class GameScene*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void PipeInit(GameScene*);
void PipeDraw(GameScene*);
void PipeUpdate(GameScene*);