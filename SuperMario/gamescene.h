#pragma once

#include "vector.h"
#include "mario.h"
#include "level.h"
#include "camera.h"
#include "flag.h"

class GameScene {//��Ϸ������
public:
    int loadCnt;//���ؼ�����
    levelName levelname;//��������
    marioBody body;//���������
    int x, y;//������
    int life;//������
    int score;//����
    int coin;//�����
    int time;//ʱ��
    Level* level;//�������
    Camera* camera;//���������
    Mario* mario;//����¶���
    Flag* flag;//���Ķ���
    vector vecProp;//�����ද̬����
    vector vecWall;//ǽ�ද̬����
    vector vecBlock;//�����ද̬����
    vector vecMonster;//�����ද̬����
    vector vecFireball;//�����ද̬����
    vector vecParticle;//�����ද̬����
    vector vecPipe;//�ܵ��ද̬����
    vector vecPlatform;//ƽ̨�ද̬����
};

void GameSceneInit(GameScene*);
void GameSceneLoop(GameScene*);
void GameSceneDestroy(GameScene*);
void GameSceneLoad(GameScene*);
void GUIDraw(GameScene*);