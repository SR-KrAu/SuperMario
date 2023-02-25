#pragma once

namespace LevelData {
	enum levelName {
		level1_1,
		level1_1_pipe,
		level1_2,
		level1_2_pipe,
		level1_2_ground,
		level1_3
	};
	enum levelType {
		ground,
		underground,
		castle,
		water,
		sky
	};
}

using namespace LevelData;

class Level {
public:
	levelName name;//��������
	levelType type;//��������
	char logo[4];//��ʶ����
	void Init(class GameScene*);
};