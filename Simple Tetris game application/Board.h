#pragma once

#include "Block.h"
#include "yspng.h"
#include "fssimplewindow.h"

class Board {
private:
	// TotalX and totalY must be divisible by 10.
	int totalX;
	int totalY;
	Block* content;
	int row;
	int col;
	int blockSize;

public:
	Board(int x, int y, int size){
		totalX = x;
		totalY = y;
		blockSize = size;
		row = totalY / blockSize;
		col = totalX / blockSize;
		content = new Block[row * col];
		for (int i = 1; i <= row; i++) {
			for (int j = 1; j <= col; j++) {
				content[(i - 1) * col + (j - 1)].setX((j - 1) * blockSize);
				content[(i - 1) * col + (j - 1)].setY((i - 1) * blockSize);
				content[(i - 1) * col + (j - 1)].setFilled(false);
				content[(i - 1) * col + (j - 1)].setSize(blockSize);
				content[(i - 1) * col + (j - 1)].setColor(0);
			}
		}
	}

	~Board() {
		delete[] content;
	}

	int getRow() {
		return row;
	}

	int getCol() {
		return col;
	}

	Block* getContent() {
		return content;
	}
	void update(int& score, int& number);

    bool filled(int x, int y, int& score, int& hint, int& loss);

	void draw();

	bool whetherEnd();

};