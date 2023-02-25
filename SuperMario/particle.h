#pragma once

namespace ParticleData {
	enum particleType {
		brokenbrick,
		boom,
		flycoin,
		text
	};
}

using namespace ParticleData;

class Particle {//粒子类
public:
	particleType type;//类型
	char text[10];//文字内容
	int x, y;//位置
	double vx, vy;//速度
	int effF, effCnt;//特效动画帧与计数器
	int time;//持续时间
	void Draw(class Camera*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void ParticleDraw(class GameScene* g);
void ParticleUpdate(class GameScene* g);
void addParticle(class GameScene* gamescene, int x, int y, particleType type, double vx, double vy, const char text[] = "0", int time = 0);