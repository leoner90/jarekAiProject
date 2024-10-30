#pragma once
class Player;
class Map;
class NODE;

class PathFinder
{
public:
	PathFinder(Player& p, Map& m);
	~PathFinder();
	bool PathFind(vector<NODE>& graph, int nStart, int nGoal, vector<int>& path);
	void PathSmoothing();
	bool IsPlaceAllowed(CVector mousePos);
	void Move(Uint16 x, Uint16 y);
	vector<NODE> m_graph;
	std::vector <CVector> m_waypoints;


	CSpriteList testNodes;


	Player& player;
	Map& map;
private:
	
};
 
