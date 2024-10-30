#pragma once
#include "PathFinder.h"
class Map;

class Player  
{
public:
	
	Player(Map& map);
	~Player();
	void Draw(CGraphics* g);
	void Update(float time);
	void MoveToWaypoint(float time);
	void Animation();
	void OnLButtonDown(Uint16 x, Uint16 y);
	CSprite* playerSprite;
	int newState;
	PathFinder pathFinder;
	enum playerStatus { WALK_RIGHT , WALK_LEFT, WALK_UP, WALK_DOWN, IDLE};
private:
 
};
 