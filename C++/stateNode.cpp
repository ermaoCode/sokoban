#include <stdio.h> //print special char
#include "stateNode.h"


stateNode::stateNode(const gameMap &stateMatrix, int pdDistance, int** targetArray){
	//mapWidth = stateMatrix.shape()[0];
	//mapHeight = stateMatrix.shape()[1];  
	parent = NULL;
	passedDistance = pdDistance +1;
	currentState.resize(boost::extents[mapHeight][mapWidth]);
	currentState = stateMatrix;
	//cout << "============================================"<< endl;

	/*for (int i=0; i<mapHeight; i++){
		for (int j=0; j<mapWidth; j++){
			switch(currentState[i][j]){
			case -2: printf("#"); break;
			case -1: printf("&", 10); break;
			case 0: break;
			case 1: printf("_", 48); break;
			case 2: printf("@"); break;
			}
			cout << "\t";
		}
		cout << endl << endl;	
	}
	cout << "-------------------------------------------"<< endl;*/

	role_y = -1;
	role_x = -1;
	for (int i=0; i<mapHeight; i++){
		for (int j=0; j<mapWidth; j++){
			if( currentState[i][j] == 2){
				role_y = i;
				role_x = j;
			}
			if (currentState[i][j] == 1)
				currentState[i][j] = 0;//initialize the map
			//cout << currentState[i][j] << "\t" ;
		}
		//cout << endl;	
	}
			
	if(role_y == -1 || role_x == -1){
		cout << "Cann`t find the role!" << endl;
		return;
	}
	
	findNeighbors(role_y, role_x);

	/*for (int i=0; i<mapHeight; i++){
		for (int j=0; j<mapWidth; j++){
			switch(currentState[i][j]){
			case -2: printf("#"); break;
			case -1: printf("&", 10); break;
			case 0: break;
			case 1: printf("_", 48); break;
			case 2: printf("@"); break;
			}
			cout << "\t";
		}
		cout << endl << endl;	
	}*/

	caculateDistance(targetArray);



	//generateChilds();
}

int stateNode::findNeighbors(int y_coordinate, int x_coordinate){// set all place accessible 1
	if(currentState[y_coordinate-1][x_coordinate] == 0){
		currentState[y_coordinate-1][x_coordinate] = 1;
		findNeighbors(y_coordinate-1, x_coordinate);
	}
	if(currentState[y_coordinate+1][x_coordinate] == 0){
		currentState[y_coordinate+1][x_coordinate] = 1;
		findNeighbors(y_coordinate+1, x_coordinate);
	}
	if(currentState[y_coordinate][x_coordinate-1] == 0){
		currentState[y_coordinate][x_coordinate-1] = 1;
		findNeighbors(y_coordinate, x_coordinate-1);
	}
	if(currentState[y_coordinate][x_coordinate+1] == 0){
		currentState[y_coordinate][x_coordinate+1] = 1;
		findNeighbors(y_coordinate, x_coordinate+1);
	}
	return 0;
}

bool stateNode::isCompleted(int** targetArray){
	for (int i=0; i<mapHeight; i++){
		for (int j=0; j<mapWidth; j++){
			if ( *((int*)targetArray + mapWidth*i + j) && currentState[i][j] != -2){
				return false;
			}
		}
	}
	return true;
}
int stateNode::generateChilds(int** targetArray){
	int direction = 0;
	for (int i=0; i<mapHeight; i++){
		for (int j=0; j<mapWidth; j++)
			if( currentState[i][j] == -2){//find possible direction
				if(currentState[i-1][j]>0 && (currentState[i+1][j]==0 || currentState[i+1][j]==1)){
					gameMap nextState = currentState;
					nextState[i-1][j] = 1;
					nextState[role_y][role_x] = 0; 
					nextState[i][j] = 2;
					nextState[i+1][j] = -2;
					stateNode *next = new stateNode(nextState, passedDistance, targetArray);
					childs.push_back(next);
				}
				if(currentState[i+1][j]>0 && (currentState[i-1][j]==0 || currentState[i-1][j]==1)){
					gameMap nextState = currentState;
					nextState[i+1][j] = 1;
					nextState[role_y][role_x] = 0; 
					nextState[i][j] = 2;
					nextState[i-1][j] = -2;
					/*stateNode next(nextState, passedDistance, targetArray);
					childs.push_back(&next);*/
					stateNode *next = new stateNode(nextState, passedDistance, targetArray);
					childs.push_back(next);
				}
				if(currentState[i][j-1]>0 && (currentState[i][j+1]==0 || currentState[i][j+1]==1)){
					gameMap nextState = currentState;
					nextState[i][j-1] = 1;
					nextState[role_y][role_x] = 0; 
					nextState[i][j] = 2;
					nextState[i][j+1] = -2;
					stateNode *next = new stateNode(nextState, passedDistance, targetArray);
					childs.push_back(next);
				}
				if(currentState[i][j+1]>0 && (currentState[i][j-1]==0 || currentState[i][j-1]==1)){
					gameMap nextState = currentState;
					nextState[i][j+1] = 1;
					nextState[role_y][role_x] = 0; 
					nextState[i][j] = 2;
					nextState[i][j-1] = -2;
					/*stateNode next(nextState, passedDistance, targetArray);
					childs.push_back(&next);*/
					stateNode *next = new stateNode(nextState, passedDistance, targetArray);
					childs.push_back(next);
				}
			}
	}
	return 0;
}

// the distance = the sum of distance between all boxs and the nearest target
int stateNode::caculateDistance(int** targetArray){
	distance = 0;
	vector<boost::array<int, 2>> boxs, targets;
	boost::array<int, 2> tmp = {-1,-1};
	for (int i=0; i<mapHeight; i++){
		for (int j=0; j<mapWidth; j++){
			if (currentState[i][j] == -2){
				tmp[0] = i;
				tmp[1] = j;
				boxs.push_back(tmp);
			}
			if ( *((int*)targetArray + mapWidth*i + j) == 1){// to simulate targetArray[i][j]
				tmp[0] = i;
				tmp[1] = j;
				targets.push_back(tmp);
			}
		}
	}
	if(boxs.size() != targets.size()){
		cout << "Targets number or boxs number incorrect!" << endl;
		return -1;
	}
	for(auto iter1=boxs.cbegin(); iter1!=boxs.cend(); iter1++){
		int min_distance = abs((*iter1)[1] - targets[0][1]) + abs((*iter1)[0] - targets[0][0]);
		for(auto iter2=targets.cbegin(); iter2!=targets.cend(); iter2++){
			int manhattan_distance = abs((*iter1)[1] - (*iter2)[1]) + abs((*iter1)[0] - (*iter2)[0]);
			if ( min_distance > manhattan_distance)
				min_distance = manhattan_distance;
		}
		distance += min_distance;
	}
	return distance;
}

 