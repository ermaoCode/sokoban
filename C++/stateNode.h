#ifndef STATENODE_H
#define STATENODE_H

#include "sokoban.h"

class stateNode{
public:
	stateNode(const gameMap &stateMatrix, int pdDistance, int** targetArray);

	bool isCompleted(int** targetArray);
	int generateChilds(int** targetArray);
	
	//vector<stateNode *> childs;
	stateNode * parent;
	list<stateNode *> childs;

	int distance;
	int passedDistance;
	gameMap currentState;
private:
	
	
	int role_y, role_x;
	int caculateDistance(int** targetArray);
	int findNeighbors(int y_coordinate, int x_coordinate);
	
};

#endif // !STATENODE_H
