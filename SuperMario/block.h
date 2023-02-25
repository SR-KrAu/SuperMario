#pragma once

#include "wall.h"

namespace BlockData {
	enum blockType {
		brick,//ש��
		question,//�ʺŷ���
		nullquestion,//ʧЧ���ʺŷ���
		hide//���ط���
	};

	enum blockProp {
		null,//������
		coin,//���
		grow,//������(��Ģ��/̫����)
		oneup,//��Ģ��
		star,//�����
		coins//�������
	};
}

using namespace BlockData;

class Block:public Wall {//������
public:
	blockType type;//����
	blockProp prop;//����
	int coins;//������ҵ�����
	int upHeight, upDir;//������߶Ⱥ��ƶ�����
	void Draw(Camera*);//���Ʒ���
	void Update(GameScene*);//���·���
	void Destroy(GameScene*);//���ٷ���
};

void BlockUpdate(GameScene* gamescene);
void BlockInit(GameScene* gamescene);
void BlockDraw(GameScene* gamescene);