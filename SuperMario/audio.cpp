#include "audio.h"
#include "level.h"
#include <stdio.h>
#include <graphics.h>

using namespace LevelData;

void playAudio(const char name[], bool repeat) {
	//²¥·ÅÒôÆµ
	char audioPath[50];
	sprintf(audioPath, "close resources//audio//%s.mp3", name);
	mciSendString(audioPath, NULL, 0, NULL);
	if (repeat == true) {//ÖØ¸´²¥·Å
		sprintf(audioPath, "play resources//audio//%s.mp3 repeat", name);
	}
	else {//µ¥´Î²¥·Å
		sprintf(audioPath, "play resources//audio//%s.mp3", name);
	}
	mciSendString(audioPath, NULL, 0, NULL);
}



void stopAudio(const char name[]) {
	//Í£Ö¹²¥·ÅÒôÆµ
	char audioPath[50];
	sprintf(audioPath, "stop resources//audio//%s.mp3", name);
	mciSendString(audioPath, NULL, 0, NULL);
}

void playBGM(Level* level) {
	//²¥·ÅBGM
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
	//Í£Ö¹BGM
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