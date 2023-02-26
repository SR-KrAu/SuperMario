#include "collisionbox.h"

void ShowCollisionbox(Camera* camera, int x1, int y1, int x2, int y2) {
	//ÏÔÊ¾Åö×²Ïä
	//return;
	setlinecolor(RGB(0, 0, 255));
	setlinestyle(PS_SOLID,2);
	line(300 - camera->x + x1, y1, 300 - camera->x + x2, y1);
	line(300 - camera->x + x2, y1, 300 - camera->x + x2, y2);
	line(300 - camera->x + x2, y2, 300 - camera->x + x1, y2);
	line(300 - camera->x + x1, y1, 300 - camera->x + x1, y2);
	setfillcolor(RGB(255, 0, 0));
	setlinecolor(RGB(255, 0, 0));
	fillcircle(300 - camera->x + x1, y1, 3);
	fillcircle(300 - camera->x + x2, y1, 3);
	fillcircle(300 - camera->x + x2, y2, 3);
	fillcircle(300 - camera->x + x1, y2, 3);
}