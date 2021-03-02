#pragma once
#include "DrawingUtilNG.h"

class Block {
private:
	int leftUpperX;
	int leftUpperY;
	int size;
	bool whetherFilled;
	int color;

public:

	Block() {
		leftUpperX = 0;
		leftUpperY = 0;
		size = 10;
		whetherFilled = false;
		color = 0;
	}

	void setFilled(bool filled) {
		whetherFilled = filled;
	}

	void setX(int x) {
		leftUpperX = x;
	}

	void setY(int y) {
		leftUpperY = y;
	}

	void setSize(int size) {
		this->size = size;
	}

	void setColor(int color) {
		this->color = color;
	}

	int getX() {
		return leftUpperX;
	}

	int getY() {
		return leftUpperY;
	}

	bool getWhetherFilled() {
		return whetherFilled;
	}

	int getSize() {
		return size;
	}

	int getColor() {
		return color;
	}

	void draw();

	
};
