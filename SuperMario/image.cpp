#include "image.h"
#include <stdio.h>
//#include <conio.h>
// 引用该库才能使用 AlphaBlend 函数
#pragma comment( lib, "MSIMG32.LIB")

namespace ImageData {
	//用于存放IMAGE类型图片的命名空间
	IMAGE levelImg;
	IMAGE fireballImg[4], childImg[10], adultImg[10], oldImg[10];
	IMAGE chestnutImg[3], tortoiseImg[3], rtortoiseImg[3], flytortoiseImg[2], piranhaImg[2];
	IMAGE coinImg[4], gmushroomImg, rmushroomImg, starImg[4], sunflowerImg[4];
	IMAGE brokenbrickImg, boomImg[3], flycoinImg[4];
	IMAGE brickImg, questionblockImg[4], platformImg;
}

using namespace ImageData;

void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, IMAGE* flipimg, int mode)
{
	// 翻转 src，翻转后的图像保存到 dst
	int w = srcimg->getwidth();		// 获取源图像宽度
	int h = srcimg->getheight();		// 获取源图像高度

	// 如果目标图像与源图像尺寸不同，调整目标图像
	if (flipimg->getwidth() != w || flipimg->getheight() != h)
		flipimg->Resize(w, h);

	// 获取源图像与目标图像的显示缓冲区地址
	DWORD* s = GetImageBuffer(srcimg);
	DWORD* d = GetImageBuffer(flipimg);

	//翻转模式mode=1不翻转，-1左右翻转，2上下翻转
	if (mode == -1) {
		// 左右翻转每一行的像素
		for (int x = 1; x < w; x++)
			for (int y = 0; y < h; y++)
				d[y * w + w - x] = s[y * w + x];
	}
	else if (mode == 2) {
		// 上下翻转每一竖的像素
		for (int x = 1; x < w; x++)
			for (int y = 0; y < h; y++)
				d[y * w + w - x] = s[(h - y) * w + x];
	}
	HDC srcDC;
	HDC dstDC = GetImageHDC(dstimg);
	if (mode == 1)
		srcDC = GetImageHDC(srcimg);
	else
		srcDC = GetImageHDC(flipimg);
	w = srcimg->getwidth();
	h = srcimg->getheight();
	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

void loadLevelImage(const char name[]) {
	//加载世界贴图
	char imgPath[50];
	sprintf(imgPath, "resources/image/level/%s.png", name);
	loadimage(&levelImg, imgPath);
}

void loadImages(levelName name, levelType type) {
	//加载贴图
	switch (name) {//加载世界贴图
	case level1_1:
		loadLevelImage("1-1");
		break;
	case level1_1_pipe:
		loadLevelImage("1-1_pipe");
		break;
	case level1_2:
		loadLevelImage("1-2");
		break;
	case level1_2_pipe:
		loadLevelImage("1-2_pipe");
		break;
	case level1_2_ground:
		loadLevelImage("1-2_ground");
		break;
	case level1_3:
		loadLevelImage("1-3");
		break;
	case level1_4:
		loadLevelImage("1-4");
		break;
	}

	char leveltype[15];
	switch (type) {//根据世界类型加载不同类型的贴图
	case ground:
		sprintf(leveltype, "ground");
		break;
	case underground:
		sprintf(leveltype, "underground");
		break;
	case castle:
		sprintf(leveltype, "castle");
		break;
	case water:
		break;
	case sky:
		break;
	default:
		break;
	}
	char imgPath[80];
	loadimage(&rmushroomImg, "resources/image/entity/prop/rmushroom.png");//红蘑菇
	loadimage(&gmushroomImg, "resources/image/entity/prop/gmushroom.png");//绿蘑菇
	sprintf(imgPath, "resources/image/particle/%s/brokenbrick.png", leveltype);
	loadimage(&brokenbrickImg, imgPath);//碎砖
	sprintf(imgPath, "resources/image/wall/block/%s/brick.png", leveltype);
	loadimage(&brickImg, imgPath);//砖块
	loadimage(&platformImg, "resources/image/wall/platform/platform.png");//平台
	for (int i = 0; i < 2; i++) {
		sprintf(imgPath, "resources/image/entity/monster/%s/piranha%d.png", leveltype, i);
		loadimage(&piranhaImg[i], imgPath);//食人花
		sprintf(imgPath, "resources/image/entity/monster/flyrtortoise%d.png", i);
		loadimage(&flytortoiseImg[i], imgPath);//飞行乌龟
	}
	for (int i = 0; i < 3; i++) {
		sprintf(imgPath, "resources/image/entity/monster/%s/chestnut%d.png", leveltype, i);
		loadimage(&chestnutImg[i], imgPath);//板栗
		sprintf(imgPath, "resources/image/entity/monster/%s/tortoise%d.png", leveltype, i);
		loadimage(&tortoiseImg[i], imgPath);//乌龟
		sprintf(imgPath, "resources/image/entity/monster/rtortoise%d.png", i);
		loadimage(&rtortoiseImg[i], imgPath);//红乌龟
		sprintf(imgPath, "resources/image/particle/boom%d.png", i);
		loadimage(&boomImg[i], imgPath);//爆炸效果
	}
	for (int i = 0; i < 4; i++) {
		sprintf(imgPath, "resources/image/entity/fireball/fireball%d.png", i);
		loadimage(&fireballImg[i], imgPath);//火球
		sprintf(imgPath, "resources/image/entity/prop/%s/coin%d.png", leveltype, i);
		loadimage(&coinImg[i], imgPath);//金币
		sprintf(imgPath, "resources/image/entity/prop/star%d.png", i);
		loadimage(&starImg[i], imgPath);//五角星
		sprintf(imgPath, "resources/image/entity/prop/sunflower%d.png", i);
		loadimage(&sunflowerImg[i], imgPath);//太阳花
		sprintf(imgPath, "resources/image/particle/flycoin%d.png", i);
		loadimage(&flycoinImg[i], imgPath);//飞行金币
		sprintf(imgPath, "resources/image/wall/block/%s/questionblock%d.png", leveltype, i);
		loadimage(&questionblockImg[i], imgPath);//问号方块
	}
	for (int i = 0; i < 10; i++) {
		sprintf(imgPath, "resources/image/entity/mario/0/child%d.png", i);
		loadimage(&childImg[i], imgPath);//小孩
		sprintf(imgPath, "resources/image/entity/mario/0/adult%d.png", i);
		loadimage(&adultImg[i], imgPath);//成人
		sprintf(imgPath, "resources/image/entity/mario/0/old%d.png", i);
		loadimage(&oldImg[i], imgPath);//老人
	}
}