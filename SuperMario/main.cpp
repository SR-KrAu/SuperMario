#include "gamescene.h"

/****************************************/
//C++����"���������Super Mario"С��Ϸ
//��Դ��Ŀ����ֹ����
//ʹ��EasyXͼ�ο��д�����Ȱ�װEaxyXͼ�ο�
//EasyX����: https://easyx.cn/
//������QQ��1351041691
//�������ʱ��: 2023��2��24��
/****************************************/

int main() {
	initgraph(800, 600);//����800*600���ش�С�Ļ�ͼ����
	GameScene gamescene;//������Ϸ��������
	GameSceneInit(&gamescene);//��ʼ����Ϸ����
	GameSceneLoop(&gamescene);//������Ϸ������ѭ��
	return 0;
}