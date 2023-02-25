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
	levelName name;//世界名称
	levelType type;//世界类型
	char logo[4];//标识名称
	void Init(class GameScene*);
};