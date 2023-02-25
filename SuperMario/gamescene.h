#pragma once

#include "vector.h"
#include "mario.h"
#include "level.h"
#include "camera.h"
#include "flag.h"

class GameScene {//游戏场景类
public:
    int loadCnt;//加载计数器
    levelName levelname;//世界名称
    marioBody body;//马里奥体型
    int x, y;//重生点
    int life;//生命数
    int score;//分数
    int coin;//金币数
    int time;//时间
    Level* level;//世界对象
    Camera* camera;//摄像机对象
    Mario* mario;//马里奥对象
    Flag* flag;//旗帜对象
    vector vecProp;//道具类动态数组
    vector vecWall;//墙类动态数组
    vector vecBlock;//方块类动态数组
    vector vecMonster;//怪物类动态数组
    vector vecFireball;//火球类动态数组
    vector vecParticle;//粒子类动态数组
    vector vecPipe;//管道类动态数组
    vector vecPlatform;//平台类动态数组
};

void GameSceneInit(GameScene*);
void GameSceneLoop(GameScene*);
void GameSceneDestroy(GameScene*);
void GameSceneLoad(GameScene*);
void GUIDraw(GameScene*);