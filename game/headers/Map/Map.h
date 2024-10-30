#pragma once

class ObjCoord;

class Map
{
public:
	CSprite gameBg;
	Map();
	~Map();
	void Draw(CGraphics* g, CVector playerPos);
	CSpriteList checkObects;
	CVector currentScrollOffset;

 
private:
	//limits and map scrolling
	int leftScreenLimit = 300;
	int rightScreenLimit = 1238;
	int scrollOffset = 0;
	int topScrollLimit = 1488;
	int bottomScrollLimit = 300;
	

	
};