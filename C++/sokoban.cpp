#include <string> 

#include "sokoban.h"
#include "stateNode.h"

int mapWidth = 9;
int mapHeight = 8;
gameMap targetState;

int main () {
	vector<stateNode*> Nodes, AllNodes;

	//list<stateNode*> Nodes;

	gameMap start(boost::extents[mapHeight][mapWidth]),
		targetState(boost::extents[mapHeight][mapWidth]);
	int mapArray[8][9] = 
	{
	{-1, -1, -1, -1, -1, -1, -1, -1, -1},
	{-1, -1,  0,  0,  0,  0,  0, -1, -1},
	{-1, -1,  0,  2,  0, -1, -1, -1, -1},
	{-1, -1, -1, -2,  0,  0,  0,  0, -1},
	{-1,  0,  0,  0, -1, -2, -1,  0, -1},
	{-1,  0, -2,  0, -1,  0,  0,  0, -1},
	{-1,  0,  0,  0, -1, -1, -1, -1, -1},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1}
	};
	int targetArray[8][9] = 
	{
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1, 1, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
	for (int i=0; i<mapHeight; i++)
		for (int j=0; j<mapWidth; j++)
			start[i][j] = mapArray[i][j];
	stateNode *root = new stateNode(start, 0, (int**)targetArray);
	//stateNode root(start, 0, (int**)targetArray);
	//Nodes.push_back(&root);
	AllNodes.push_back(root);
	root->generateChilds((int**)targetArray);
	for(auto iter = root->childs.begin(); iter != root->childs.end(); iter++){
		(*iter)->parent = root;
		Nodes.push_back(*iter);
		AllNodes.push_back(*iter);
	}
	/*int size = root.childs.size();
	for (int i=0; i < size; i++){
		stateNode * tmp = root.childs.[i];
		Nodes.push_back(tmp);
	}*/
	stateNode * destination;
	while(1){
		auto nearestNode_iter = Nodes.begin();//init
		stateNode * nearestNode_ptr;

		int shortestDistance = (*nearestNode_iter)->distance + (*nearestNode_iter)->passedDistance;

		for(auto iter = Nodes.rbegin(); iter != Nodes.rend(); iter++){
			if((*iter)->distance + (*iter)->passedDistance < shortestDistance){
				shortestDistance = (*iter)->distance + (*iter)->passedDistance;
				// use rbegin() and base() for the reason that i donot want my role change target box
				// too frequently
				nearestNode_iter = iter.base()-1; 
			}
		}
		nearestNode_ptr = *(nearestNode_iter);
		Nodes.erase(nearestNode_iter);
		if (nearestNode_ptr->isCompleted((int**)targetArray)){
			destination = nearestNode_ptr;
			cout << "Find the way" << endl;
			break;
		}
		//cout << "Generating nodes........................................." << endl;
		nearestNode_ptr->generateChilds((int**)targetArray);
		for(auto iter = nearestNode_ptr->childs.begin(); iter != nearestNode_ptr->childs.end(); iter++){
			//check if this state is repeated
			(*iter)->parent = nearestNode_ptr;
			int isRepeat = 0;
			for ( auto iter2 = AllNodes.begin(); iter2 != AllNodes.end(); iter2++){
				if (compareGameMap((*iter2)->currentState, (*iter)->currentState)){
					isRepeat = 1;
					break;
				}
			}
			AllNodes.push_back(*iter);
			if (!isRepeat)
				Nodes.push_back(*iter);
		}

	}

	stateNode * tmp = destination;
	stack<stateNode *> nodeStack;
	nodeStack.push(tmp);
	while(tmp){
		/*for (int i=0; i<mapHeight; i++){
			for (int j=0; j<mapWidth; j++){
				switch(tmp->currentState[i][j]){
				case -2: printf("#"); break;
				case -1: printf("&", 10); break;
				case 0: break;
				case 1: printf("_", 48); break;
				case 2: printf("@"); break;
				}
				cout << "\t";
			}
			cout<< endl;	
		}
		cout  << "=======================================================================" << endl;*/
		nodeStack.push(tmp);
		tmp = tmp->parent;
	}
	cout << endl << "Let's go!"<<endl;
	while(!nodeStack.empty()){
		tmp = nodeStack.top();
		nodeStack.pop();

		for (int i=0; i<mapHeight; i++){
			for (int j=0; j<mapWidth; j++){
				switch(tmp->currentState[i][j]){
				case -2: printf("#"); break;
				case -1: printf("&", 10); break;
				case 0: break;
				case 1: printf("_", 48); break;
				case 2: printf("@"); break;
				}
				cout << "\t";
			}
			cout << endl;	
		}
		cout << "=======================================================================" << endl;
	}

	system("pause");
	return 0;
}

int compareGameMap(const gameMap &map1, const gameMap &map2){
	for (int i = 0; i < mapHeight; i++){
		for (int j = 0; j < mapWidth; j++){
			if (map1[i][j] != map2[i][j])
				return 0;
		}	
	}
	return 1;//totally equal

}