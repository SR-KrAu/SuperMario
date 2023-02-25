#include "pipe.h"
#include "gamescene.h"
#include <stdio.h>

using namespace LevelData;

void Pipe::Draw(GameScene* gamescene) {
	//���ƹܵ�
	//�����ƻ����������ͼ��
	if (this->x + 300 < gamescene->camera->x - 300 - 300 || this->x > gamescene->camera->x + 500 + 300)
		return;

	putimage(300 + this->x - gamescene->camera->x, this->y, this->pipeImg);
}

void Pipe::Update(GameScene* gamescene) {
	//���¹ܵ�
	//�뿪�����������ٶ���
	if (this->x + 300 < gamescene->camera->x - 300 - 300)
		this->Destroy(gamescene);
}

void Pipe::Destroy(GameScene* gamescene) {
	//���ٹܵ�����
	for (int i = 0; i < gamescene->vecPipe.size; i++)
	{//�����ܵ��ද̬����Ѱ����Ӧ����
		class Pipe* pPipe = (class Pipe*)gamescene->vecPipe.get(&gamescene->vecPipe, i);
		if (pPipe == this) {
			//�����Ӧ����
			delete pPipe->pipeImg;//����ͼƬ
			gamescene->vecPipe.remove(&gamescene->vecPipe, i);
			free(pPipe);
			break;
		}
	}
}

void PipeDraw(GameScene* g) {
	//���ƹܵ����
	for (int i = 0; i < g->vecPipe.size; i++)
	{//�������йܵ����л���
		class Pipe* pPipe = (class Pipe*)g->vecPipe.get(&g->vecPipe, i);
		pPipe->Draw(g);
	}
}

void PipeUpdate(GameScene* g) {
	//���¹ܵ����
	for (int i = 0; i < g->vecPipe.size; i++)
	{//�������йܵ����л���
		class Pipe* pPipe = (class Pipe*)g->vecPipe.get(&g->vecPipe, i);
		pPipe->Update(g);
	}
}

void addPipe(GameScene* gamescene, levelName tran_level, pipeType type, int x, int y, int tran_location, int tran_x, int tran_y, const char IMG[10], bool is_newlevel = false) {
	//��ӹܵ�����(�д��͹���)
	class Pipe* pPipe = (class Pipe*)malloc(sizeof(class Pipe));
	if (pPipe == NULL)
		return;
	pPipe->is_tran = true;
	pPipe->tran_level = tran_level;
	pPipe->type = type;
	pPipe->x = x;
	pPipe->y = y;
	pPipe->tran_location = tran_location;
	pPipe->tran_x = tran_x;
	pPipe->tran_y = tran_y;
	pPipe->pipeImg = new IMAGE;
	pPipe->is_newlevel = is_newlevel;
	char imgPath[50];
	sprintf(imgPath, "resources/image/pipe/%s.png", IMG);
	loadimage(pPipe->pipeImg, imgPath);
	gamescene->vecPipe.append(&gamescene->vecPipe, pPipe);
}

void addPipe(GameScene* gamescene, int x, int y, const char IMG[10]) {
	//��ӹܵ�����(�޴��͹���)
	class Pipe* pPipe = (class Pipe*)malloc(sizeof(class Pipe));
	if (pPipe == NULL)
		return;
	pPipe->is_tran = false;
	pPipe->x = x;
	pPipe->y = y;
	pPipe->pipeImg = new IMAGE;
	char imgPath[50];
	sprintf(imgPath, "resources/image/pipe/%s.png", IMG);
	loadimage(pPipe->pipeImg, imgPath);
	gamescene->vecPipe.append(&gamescene->vecPipe, pPipe);
}

void PipeInit(GameScene* gamescene) {
	//��ʼ���ܵ�
	switch (gamescene->level->name) {
	case level1_1:
		addPipe(gamescene, level1_1_pipe, down, 2298, 363, 523, 66, 80, "1-1_pipe");
		addPipe(gamescene, level1_2, right, 8532, 444, 8687, 64, 120, "1-1_pipe2", true);
		break;
	case level1_1_pipe:
		addPipe(gamescene, level1_1, right, 523, 443, 678, 6584, 443, "1-1_pipe_pipe");
		break;
	case level1_2:
		addPipe(gamescene, level1_2_pipe, down, 4151, 402, 522, 66, 80, "1-2_pipe");
		addPipe(gamescene, 4392, 362, "1-2_pipe2");
		addPipe(gamescene, 4634, 443, "1-2_pipe3");
		addPipe(gamescene, level1_2_ground, right, 6681, 322, 6839, 275, 442, "1-1_pipe_pipe");
		break;
	case level1_2_pipe:
		addPipe(gamescene, level1_2, right, 518, 444, 679, 4657, 442, "1-1_pipe_pipe");
		break;
	}
}