#include "stdafx.h"
#include "PathFinder.h"
#include "player.h"
#include "Map/Map.h"


struct CONNECTION
{
	int nEnd; // index of the destination node
	float cost; // cost of the transition
};

struct NODE
{
	CVector pos; // 2D position of the node
	list<CONNECTION> conlist; // list of connections
	float costSoFar;
	int nConnection;
	bool open, closed;
};

float Coords[][2] =
{
	//bathroom 5
	{ 370, 65 },
	{ 370, 235 },
	{ 627, 115 },
	{ 627, 260 },
	{ 780, 285 },
	{ 445, 310 },
	//first Room bottom  4
	{ 315, 570 },
	{ 235, 665 },
	{ 445, 665 },
	{ 700, 665 },
	//first Room top 3
	{ 235, 1000 },
	{ 445, 1000 },
	{700, 1000 },
	//coridor between rooms 2
	{820, 820 },
	{1100, 820 },

	//room two top
	{ 1290, 666 },
	{ 1450, 666 },
	{ 1740, 666 },
	{ 1900, 666 },


	//room two mid
	{ 1290, 410 },
	{ 1450, 410 },
	{ 1740, 410 },
	{ 1900, 410 },

	//room two bottom
	{ 1450, 210 },
	{ 1840, 210 },
	//kitchen
	{ 1200, 1400 },
	{ 1826, 1400 },

};

int Connections[][2] =
{
	//bathroom
	{ 0, 1 },
	{ 0, 2 },
	{ 1, 5 },
	{ 2, 3 },
	{ 3, 4 },
	{ 3, 5 },
	{ 5, 6 },
	//first Room bottom
	{ 6, 7 },
	{ 6, 8 },
	{ 6, 9 },
	{ 7, 10 },
	{ 8, 9 },
	{ 8, 11 },
	{ 9, 13 },
	{ 9, 12 },
	//first Room top
	{ 10, 11 },
	{ 11, 12 },
	{ 12, 13 },

	//coridor between rooms
	{ 13, 14 },
	{ 14, 15 },
	{ 14, 19 },
	{ 14, 25 },

	//room two top
	{ 15, 16 },
	{ 15, 19 },
	{ 16, 20 },
	{ 16, 17 },
	{ 17, 18 },
	{ 17, 21 },
	{ 18, 22 },

	//room two mid
	{ 19, 20 },
	{ 19, 23 },
	{ 20, 21 },
	{ 20, 23 },
	{ 21, 22 },
	{ 21, 24 },

	//room two bottom
	{ 23, 24 },
	{ 24, 22 },

	//kitchen
	{ 25, 26 }
};

//INTERSECTION
bool Intersection(CVector a, CVector b, CVector c, CVector d, float& k1, float& k2)
{
	CVector v1 = b - a;
	CVector v2 = d - c;
	CVector con = c - a;
	float det = v1.m_x * v2.m_y - v1.m_y * v2.m_x;
	if (det != 0)
	{
		k1 = (v2.m_y * con.m_x - v2.m_x * con.m_y) / det;
		k2 = (v1.m_y * con.m_x - v1.m_x * con.m_y) / det;
		return true;
	}
	else
		return false;
}

// returns true is the line segments a-b and c-d intersect
bool Intersection(CVector a, CVector b, CVector c, CVector d)
{
	float k1, k2;
	if (!Intersection(a, b, c, d, k1, k2))
		return false;
	return k1 >= 0 && k1 <= 1.f && k2 >= 0 && k2 <= 1.f;
}

PathFinder::PathFinder(Player& p, Map& m) : player(p), map(m)
{
	//create all nodes with given coordinates
	for (float* coord : Coords)
		m_graph.push_back(NODE{ CVector(coord[0], coord[1]) });

	for (int* conn : Connections)
	{
		//start & end node
		int ind1 = conn[0];
		int ind2 = conn[1];

		//find reference to nodes according their index from connection list
		NODE& node1 = m_graph[ind1];
		NODE& node2 = m_graph[ind2];

		//calculate distance to save as a transfer cost
		float dist = Distance(node1.pos, node2.pos);

		//save connection index and transfer cost into connection for each node
		node1.conlist.push_back(CONNECTION{ ind2, dist });
		node2.conlist.push_back(CONNECTION{ ind1, dist });
	}

	for (auto x : Coords)
	{
		CSprite* newObj = new CSprite();
		newObj->LoadImage("testobstacles.jpg");
		newObj->SetImage("testobstacles.jpg");
		newObj->SetSize(50, 50);
		newObj->SetPosition(CVector(x[0], x[1]));
		testNodes.push_back(newObj);
	}
}

PathFinder::~PathFinder()
{
}

bool PathFinder::PathFind(vector<NODE>& graph, int nStart, int nGoal, vector<int>& path)
{
	list<int> openNodes;
	// mark all nodes in the graph as unvisited
	for (auto& node : m_graph)
	{
		node.open = false;
		node.closed = false; // for next search
	}


	// Closes node to player EG. START node
	m_graph[nStart].open = true;
	m_graph[nStart].costSoFar = 0;
	m_graph[nStart].nConnection = -1;
	openNodes.push_back(nStart);

	//_____________
	while (!openNodes.empty())
	{
		// lambda returns the smallest costSoFar in current open nodes;
		//first loop lest say node[0] cost = 0;
		//+ Heuristic prediction A* algo
		int curNode = *min_element(openNodes.begin(), openNodes.end(),
			[this, nGoal](int n1, int n2) {
				float f1 = m_graph[n1].costSoFar + Distance(m_graph[n1].pos, m_graph[nGoal].pos);
				float f2 = m_graph[n2].costSoFar + Distance(m_graph[n2].pos, m_graph[nGoal].pos);
				return f1 < f2;
			});

		// Found the goal node?
		if (curNode == nGoal)
			break;

		//for each conn in node[0] end connection id 1 (as we have only 1 now)
		for each (auto conn in m_graph[curNode].conlist)
		{
			//id1
			int endNode = conn.nEnd;
			float newCostSoFar = m_graph[curNode].costSoFar + conn.cost;

			// for open nodes, ignore if the current route worse then the old one
			if (m_graph[endNode].open && m_graph[endNode].costSoFar <= newCostSoFar)
				continue;

			// Wow, we've found a better route!
			m_graph[endNode].costSoFar = newCostSoFar;
			m_graph[endNode].nConnection = curNode;

			// if unvisited yet, add to the open list
			if (!m_graph[endNode].open)
			{
				m_graph[endNode].open = true;
				//add endNode to the list of open nodes;
				openNodes.push_back(endNode);
			}
		}

		// We can now close the current graph...
		m_graph[curNode].closed = true;
		//	remove the current node from the open nodes list;
		openNodes.remove(curNode);
	}

	// Collect the path from the generated graph data
	if (openNodes.empty())
		return false; // path not found!
	int i = nGoal;

	while (m_graph[i].nConnection >= 0)
	{
		path.push_back(i);
		i = m_graph[i].nConnection;
	}

	path.push_back(i);
	reverse(path.begin(), path.end());

	return true;
}

void PathFinder::PathSmoothing()
{
	if (m_waypoints.size() <= 1) return;
	bool hasObstacle = false;
	CSprite* platerPos = player.playerSprite;
	// Check each obstacle to see if there’s an intersection
	for (auto obstacle : map.checkObects) {
		if (Intersection(CVector(platerPos->GetLeft(), platerPos->GetBottom()), m_waypoints[1],
			CVector(obstacle->GetLeft(), obstacle->GetTop()),
			CVector(obstacle->GetRight(), obstacle->GetBottom())) ||
			Intersection(player.playerSprite->GetPos(), m_waypoints[1],
				CVector(obstacle->GetLeft(), obstacle->GetBottom()),
				CVector(obstacle->GetRight(), obstacle->GetTop())))
		{
			hasObstacle = true;
			break;
		}
	}
	if (!hasObstacle)
	{
 
		m_waypoints.erase(m_waypoints.begin()); // Remove the reached waypoint
		player.playerSprite->SetVelocity(0, 0);
		player.playerSprite->SetRotation(0);

	}
}

bool PathFinder::IsPlaceAllowed(CVector mousePos)
{
	
	for (auto obstacle : map.checkObects)
		if (obstacle->HitTest(mousePos))
		{
			cout << "FALSE";
			return false;
			m_waypoints.clear();
		}
	return true;
}


void PathFinder::Move(Uint16 x, Uint16 y)
{

	CVector dest(x, y);
	dest -= map.currentScrollOffset;


	if (!IsPlaceAllowed(dest))
	{
		m_waypoints.clear();
		return;
	}


	//  NPC node
	vector<NODE>::iterator iFirst =
		min_element(m_graph.begin(), m_graph.end(), [this](NODE& n1, NODE& n2) -> bool {
		return Distance(n1.pos, player.playerSprite->GetPos()) < Distance(n2.pos, player.playerSprite->GetPos());
			});

	int nFirst = iFirst - m_graph.begin();

	//Destination node
	vector<NODE>::iterator iLast =
		min_element(m_graph.begin(), m_graph.end(), [dest](NODE& n1, NODE& n2) -> bool {
		return Distance(n1.pos, dest) < Distance(n2.pos, dest);
			});

	int nLast = iLast - m_graph.begin();



	// just reset if mouse clicked again
	if (!m_waypoints.empty())
	{
		m_waypoints.clear();
		player.playerSprite->SetVelocity(0, 0);
	}

	// call the path finding algorithm to complete the waypoints
	vector<int> path;
	if (PathFind(m_graph, nFirst, nLast, path))
	{

		// pust CVector representation in waypoints forming the path
		//m_waypoints.push_back(player.playerSprite->GetPos()); // push player pos
		for (int nodeI : path)
			m_waypoints.push_back(m_graph[nodeI].pos);
		m_waypoints.push_back(dest); //+ finall coordinate where mouse where clicked


		for (CVector nodeI : m_waypoints)
			cout << nodeI.GetX() << "  " << nodeI.GetY() << endl;

		//PathSmoothing();
		cout << endl << endl << endl << endl << endl;
		for (CVector nodeI : m_waypoints)
			cout << nodeI.GetX() << "  " << nodeI.GetY() << endl;
	}
}