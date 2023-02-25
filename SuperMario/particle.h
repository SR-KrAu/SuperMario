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

class Particle {//������
public:
	particleType type;//����
	char text[10];//��������
	int x, y;//λ��
	double vx, vy;//�ٶ�
	int effF, effCnt;//��Ч����֡�������
	int time;//����ʱ��
	void Draw(class Camera*);
	void Update(class GameScene*);
	void Destroy(class GameScene*);
};

void ParticleDraw(class GameScene* g);
void ParticleUpdate(class GameScene* g);
void addParticle(class GameScene* gamescene, int x, int y, particleType type, double vx, double vy, const char text[] = "0", int time = 0);