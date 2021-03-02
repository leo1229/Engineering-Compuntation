#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include "Block.h"
#include "Board.h"
using namespace std;

class Item {
private:
	Block allBlocks[4];
	bool isAlive;
	int blockSize;
	int itemType;
public:
	Item(int size, Board& theBoard); 
	
	bool getIsAlive() {
		return isAlive;
	}

	// Press arrow keys on screen to move the item to left/right.
	// When you want to move to left, direction = -1.
	// When you want to move to right, direction = 1.
	void horizontalMove(int direction, Board& theBoard);

	void goDown(Board& theBoard);

	void rotation(Board& theBoard);

	bool changeShape(int& score, int& hint, int& loss);

	void draw();


};
