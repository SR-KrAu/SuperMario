#include "image.h"
#include <stdio.h>
//#include <conio.h>
// ���øÿ����ʹ�� AlphaBlend ����
#pragma comment( lib, "MSIMG32.LIB")

namespace ImageData {
	//���ڴ��IMAGE����ͼƬ�������ռ�
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
	// ��ת src����ת���ͼ�񱣴浽 dst
	int w = srcimg->getwidth();		// ��ȡԴͼ����
	int h = srcimg->getheight();		// ��ȡԴͼ��߶�

	// ���Ŀ��ͼ����Դͼ��ߴ粻ͬ������Ŀ��ͼ��
	if (flipimg->getwidth() != w || flipimg->getheight() != h)
		flipimg->Resize(w, h);

	// ��ȡԴͼ����Ŀ��ͼ�����ʾ��������ַ
	DWORD* s = GetImageBuffer(srcimg);
	DWORD* d = GetImageBuffer(flipimg);

	//��תģʽmode=1����ת��-1���ҷ�ת��2���·�ת
	if (mode == -1) {
		// ���ҷ�תÿһ�е�����
		for (int x = 1; x < w; x++)
			for (int y = 0; y < h; y++)
				d[y * w + w - x] = s[y * w + x];
	}
	else if (mode == 2) {
		// ���·�תÿһ��������
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
	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸��
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

void loadLevelImage(const char name[]) {
	//����������ͼ
	char imgPath[50];
	sprintf(imgPath, "resources/image/level/%s.png", name);
	loadimage(&levelImg, imgPath);
}

void loadImages(levelName name, levelType type) {
	//������ͼ
	switch (name) {//����������ͼ
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
	switch (type) {//�����������ͼ��ز�ͬ���͵���ͼ
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
	loadimage(&rmushroomImg, "resources/image/entity/prop/rmushroom.png");//��Ģ��
	loadimage(&gmushroomImg, "resources/image/entity/prop/gmushroom.png");//��Ģ��
	sprintf(imgPath, "resources/image/particle/%s/brokenbrick.png", leveltype);
	loadimage(&brokenbrickImg, imgPath);//��ש
	sprintf(imgPath, "resources/image/wall/block/%s/brick.png", leveltype);
	loadimage(&brickImg, imgPath);//ש��
	loadimage(&platformImg, "resources/image/wall/platform/platform.png");//ƽ̨
	for (int i = 0; i < 2; i++) {
		sprintf(imgPath, "resources/image/entity/monster/%s/piranha%d.png", leveltype, i);
		loadimage(&piranhaImg[i], imgPath);//ʳ�˻�
		sprintf(imgPath, "resources/image/entity/monster/flyrtortoise%d.png", i);
		loadimage(&flytortoiseImg[i], imgPath);//�����ڹ�
	}
	for (int i = 0; i < 3; i++) {
		sprintf(imgPath, "resources/image/entity/monster/%s/chestnut%d.png", leveltype, i);
		loadimage(&chestnutImg[i], imgPath);//����
		sprintf(imgPath, "resources/image/entity/monster/%s/tortoise%d.png", leveltype, i);
		loadimage(&tortoiseImg[i], imgPath);//�ڹ�
		sprintf(imgPath, "resources/image/entity/monster/rtortoise%d.png", i);
		loadimage(&rtortoiseImg[i], imgPath);//���ڹ�
		sprintf(imgPath, "resources/image/particle/boom%d.png", i);
		loadimage(&boomImg[i], imgPath);//��ըЧ��
	}
	for (int i = 0; i < 4; i++) {
		sprintf(imgPath, "resources/image/entity/fireball/fireball%d.png", i);
		loadimage(&fireballImg[i], imgPath);//����
		sprintf(imgPath, "resources/image/entity/prop/%s/coin%d.png", leveltype, i);
		loadimage(&coinImg[i], imgPath);//���
		sprintf(imgPath, "resources/image/entity/prop/star%d.png", i);
		loadimage(&starImg[i], imgPath);//�����
		sprintf(imgPath, "resources/image/entity/prop/sunflower%d.png", i);
		loadimage(&sunflowerImg[i], imgPath);//̫����
		sprintf(imgPath, "resources/image/particle/flycoin%d.png", i);
		loadimage(&flycoinImg[i], imgPath);//���н��
		sprintf(imgPath, "resources/image/wall/block/%s/questionblock%d.png", leveltype, i);
		loadimage(&questionblockImg[i], imgPath);//�ʺŷ���
	}
	for (int i = 0; i < 10; i++) {
		sprintf(imgPath, "resources/image/entity/mario/0/child%d.png", i);
		loadimage(&childImg[i], imgPath);//С��
		sprintf(imgPath, "resources/image/entity/mario/0/adult%d.png", i);
		loadimage(&adultImg[i], imgPath);//����
		sprintf(imgPath, "resources/image/entity/mario/0/old%d.png", i);
		loadimage(&oldImg[i], imgPath);//����
	}
}