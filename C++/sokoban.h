#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <boost/multi_array.hpp>
#include <boost/array.hpp> 


using namespace std;

typedef boost::multi_array<int, 2> gameMap;

extern int mapWidth, mapHeight;
extern gameMap targetState;

int compareGameMap(const gameMap &map1, const gameMap &map2);
#endif