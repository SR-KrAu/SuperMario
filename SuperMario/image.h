#pragma once

#include <graphics.h>
#include "level.h"


namespace ImageData {
	extern IMAGE levelImg;
	extern IMAGE fireballImg[4], childImg[10], adultImg[10], oldImg[10];
	extern IMAGE chestnutImg[3], tortoiseImg[3], rtortoiseImg[3], flytortoiseImg[2], piranhaImg[2];
	extern IMAGE coinImg[4], gmushroomImg, rmushroomImg, starImg[4], sunflowerImg[4];
	extern IMAGE brokenbrickImg, boomImg[3], flycoinImg[4];
	extern IMAGE brickImg, questionblockImg[4], platformImg;
}

void loadLevelImage(const char name[]);
void loadImages(levelName name, levelType type);
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, IMAGE* flipimg, int = 1);