#pragma once

class Camera {//摄像机类
public:
	int x;//摄像机位置
	void Init(class GameScene*);
	void Update(class GameScene*);
};