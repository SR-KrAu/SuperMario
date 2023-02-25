#include "gamescene.h"

/****************************************/
//C++仿制"超级马里奥Super Mario"小游戏
//开源项目，禁止商用
//使用EasyX图形库编写，请先安装EaxyX图形库
//EasyX官网: https://easyx.cn/
//制作者QQ：1351041691
//制作完成时间: 2023年2月24日
/****************************************/

int main() {
	initgraph(800, 600);//创建800*600像素大小的绘图窗口
	GameScene gamescene;//创建游戏场景对象
	GameSceneInit(&gamescene);//初始化游戏场景
	GameSceneLoop(&gamescene);//进入游戏场景总循环
	return 0;
}