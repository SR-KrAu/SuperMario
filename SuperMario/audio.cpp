#include "audio.h"
#include "level.h"
#include <stdio.h>
#include <graphics.h>

using namespace LevelData;

void playAudio(const char name[], bool repeat) {
	//≤•∑≈“Ù∆µ
	char audioPath[50];
	sprintf(audioPath, "close resources//audio//%s.mp3", name);
	mciSendString(audioPath, NULL, 0, NULL);
	if (repeat == true) {//÷ÿ∏¥≤•∑≈
		sprintf(audioPath, "play resources//audio//%s.mp3 repeat", name);
	}
	else {//µ•¥Œ≤•∑≈
		sprintf(audioPath, "play resources//audio//%s.mp3", name);
	}
	mciSendString(audioPath, NULL, 0, NULL);
}



void stopAudio(const char name[]) {
	//Õ£÷π≤•∑≈“Ù∆µ
	char audioPath[50];
	sprintf(audioPath, "stop resources//audio//%s.mp3", name);
	mciSendString(audioPath, NULL, 0, NULL);
}

void playBGM(Level* level) {
	//≤•∑≈BGM
	switch (level->type)
	{
	case ground:
		playAudio("ground", true);
		break;
	case underground:
		playAudio("underground", true);
		break;
	case castle:
		break;
	case water:
		break;
	case sky:
		break;
	}
}

void stopBGM(Level* level) {
	//Õ£÷πBGM
	switch (level->type)
	{
	case ground:
		stopAudio("ground");
		break;
	case underground:
		stopAudio("underground");
		break;
	case castle:
		break;
	case water:
		break;
	case sky:
		break;
	}
}
/*
void pauseAudio(const char name[]) {
	//‘›Õ£“Ù∆µ
	char audioPath[50];
	sprintf(audioPath, "pause resources//audio//%s.mp3", name);
	mciSendString(audioPath, NULL, 0, NULL);
}

void resumeAudio(const char name[]) {
	//ºÃ–¯≤•∑≈“Ù∆µ
	char audioPath[50];
	sprintf(audioPath, "resume resources//audio//%s.mp3", name);
	mciSendString(audioPath, NULL, 0, NULL);
}*/