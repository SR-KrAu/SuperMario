#include "audio.h"
#include "level.h"
#include <stdio.h>
#include <graphics.h>

using namespace LevelData;

void playAudio(const char name[], bool repeat) {
	//������Ƶ
	char audioPath[50];
	sprintf(audioPath, "close resources//audio//%s.mp3", name);
	mciSendString(audioPath, NULL, 0, NULL);
	if (repeat == true) {//�ظ�����
		sprintf(audioPath, "play resources//audio//%s.mp3 repeat", name);
	}
	else {//���β���
		sprintf(audioPath, "play resources//audio//%s.mp3", name);
	}
	mciSendString(audioPath, NULL, 0, NULL);
}



void stopAudio(const char name[]) {
	//ֹͣ������Ƶ
	char audioPath[50];
	sprintf(audioPath, "stop resources//audio//%s.mp3", name);
	mciSendString(audioPath, NULL, 0, NULL);
}

void playBGM(Level* level) {
	//����BGM
	switch (level->type)
	{
	case ground:
		playAudio("ground", true);
		break;
	case underground:
		playAudio("underground", true);
		break;
	case castle:
		playAudio("castle", true);
		break;
	case water:
		break;
	case sky:
		break;
	}
}

void stopBGM(Level* level) {
	//ֹͣBGM
	switch (level->type)
	{
	case ground:
		stopAudio("ground");
		break;
	case underground:
		stopAudio("underground");
		break;
	case castle:
		stopAudio("castle");
		break;
	case water:
		break;
	case sky:
		break;
	}
}