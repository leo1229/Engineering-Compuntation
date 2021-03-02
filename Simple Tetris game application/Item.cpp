#include "Item.h"

Item::Item(int size, Board& theBoard)
{
	blockSize = size;
	isAlive = true;
	int currentTime = time(NULL);
	srand(currentTime);
	int type = rand() % 5;
	int color = type * 50;
	itemType = type;
	allBlocks[0].setX(rand() % (theBoard.getCol() - 3) * blockSize);
	allBlocks[0].setY(0);
	allBlocks[0].setFilled(true);
	
	for (int i = 0; i < 4; i++) {
		allBlocks[i].setSize(blockSize);
		allBlocks[i].setColor(color);
	}

	switch (type) {
	case 0:
		for (int i = 1; i < 4; i++) {
			allBlocks[i].setX(allBlocks[i - 1].getX() + blockSize);
			allBlocks[i].setY(0);
			allBlocks[i].setFilled(true);
		}
		break;
	case 1:
		for (int i = 1; i < 3; i++) {
			allBlocks[i].setX(allBlocks[i - 1].getX() + blockSize);
			allBlocks[i].setY(0);
			allBlocks[i].setFilled(true);
		}
		allBlocks[3].setX(allBlocks[2].getX());
		allBlocks[3].setY(allBlocks[2].getY() + blockSize);
		allBlocks[3].setFilled(true);
		break;
	case 2:
		for (int i = 1; i < 3; i++) {
			allBlocks[i].setX(allBlocks[i - 1].getX() + blockSize);
			allBlocks[i].setY(0);
			allBlocks[i].setFilled(true);
		}
		allBlocks[3].setX(allBlocks[1].getX());
		allBlocks[3].setY(allBlocks[1].getY() + blockSize);
		allBlocks[3].setFilled(true);
		break;
	case 3:
		allBlocks[1].setX(allBlocks[0].getX() + blockSize);
		allBlocks[1].setY(allBlocks[0].getY());
		allBlocks[1].setFilled(true);
		allBlocks[2].setX(allBlocks[0].getX());
		allBlocks[2].setY(allBlocks[0].getY() + blockSize);
		allBlocks[2].setFilled(true);
		allBlocks[3].setX(allBlocks[0].getX() + blockSize);
		allBlocks[3].setY(allBlocks[0].getY() + blockSize);
		allBlocks[3].setFilled(true);
		break;
	case 4:
		allBlocks[1].setX(allBlocks[0].getX() + blockSize);
		allBlocks[1].setY(allBlocks[0].getY());
		allBlocks[1].setFilled(true);
		allBlocks[2].setX(allBlocks[0].getX() + blockSize);
		allBlocks[2].setY(allBlocks[0].getY() + blockSize);
		allBlocks[2].setFilled(true);
		allBlocks[3].setX(allBlocks[0].getX() + 2 * blockSize);
		allBlocks[3].setY(allBlocks[0].getY() + blockSize);
		allBlocks[3].setFilled(true);
		break;
	}
}

void Item::horizontalMove(int direction, Board& theBoard)
{
	Block* base = theBoard.getContent();
	int totalRow = theBoard.getRow();
	int totalCol = theBoard.getCol();
	int row, col;
	bool whetherMove = true;
	// Check whether it can move to right(left) or not.
	for (int i = 0; i < 4; i++) {
		row = allBlocks[i].getY() / blockSize + 1;
		col = allBlocks[i].getX() / blockSize + 1;
		if (col + direction > totalCol || col + direction < 1 
			|| base[(row - 1) * totalCol + (col + direction - 1)].getWhetherFilled()) {
			whetherMove = false;
			break;
		}
	}
	if (whetherMove) {
		for (int i = 0; i < 4; i++) {
			allBlocks[i].setX(allBlocks[i].getX() + blockSize * direction);
		}
	}

}

void Item::goDown(Board& theBoard)
{
	Block* base = theBoard.getContent();
	int totalRow = theBoard.getRow();
	int totalCol = theBoard.getCol();
	int row, col;
	// Check whether this item can go down or not.
	for (int i = 0; i < 4; i++) {
		row = allBlocks[i].getY() / blockSize + 1;
		col = allBlocks[i].getX() / blockSize + 1;
		if (row + 1 > totalRow || base[row * totalCol + (col - 1)].getWhetherFilled()) {
			isAlive = false;
			break;
		}
	}
	if (isAlive) {
		for (int i = 0; i < 4; i++) {
			allBlocks[i].setY(allBlocks[i].getY() + blockSize);
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			row = allBlocks[i].getY() / blockSize + 1;
			col = allBlocks[i].getX() / blockSize + 1;
			base[(row - 1) * totalCol + (col - 1)].setFilled(true);
			base[(row - 1) * totalCol + (col - 1)].setColor(allBlocks[i].getColor());
		}
	}
}

void Item::rotation(Board& theBoard)
{
	Block* base = theBoard.getContent();
	int totalRow = theBoard.getRow();
	int totalCol = theBoard.getCol();
	int newX[4];
	int newY[4];
	int row, col;
	bool whetherRote = true;
	newX[0] = allBlocks[0].getX();
	newY[0] = allBlocks[0].getY();
	for (int i = 1; i < 4; i++) {
		newX[i] = allBlocks[0].getX() + allBlocks[0].getY() - allBlocks[i].getY();
		newY[i] = allBlocks[0].getY() + allBlocks[i].getX() - allBlocks[0].getX();
		row = newY[i] / blockSize + 1;
		col = newX[i] / blockSize + 1;
		if (row > totalRow || row < 1 || col > totalCol || col < 1
			|| base[(row - 1) * totalCol + (col - 1)].getWhetherFilled()) {
			whetherRote = false;
			break;
		}
	}

	if (whetherRote) {
		for (int i = 0; i < 4; i++) {
			allBlocks[i].setX(newX[i]);
			allBlocks[i].setY(newY[i]);
		}

	}
	

}

bool Item::changeShape(int& score, int& hint, int& loss)
{
	if (score < 20) {
		return false;
	}
	score -= 20;
	hint += 1;
	loss += 20;
	int currentTime = time(NULL);
	srand(currentTime);
	int type = rand() % 5;
	while (itemType == type)
	{
		type = rand() % 5;
	}
	int color = type * 50;
	for (int i = 0; i < 4; i++) {
		allBlocks[i].setColor(color);
	}

	itemType = type;
	switch (type) {
	case 0:
		for (int i = 1; i < 4; i++) {
			allBlocks[i].setX(allBlocks[i - 1].getX() + blockSize);
			allBlocks[i].setY(allBlocks[0].getY());
		}
		break;
	case 1:
		for (int i = 1; i < 3; i++) {
			allBlocks[i].setX(allBlocks[i - 1].getX() + blockSize);
			allBlocks[i].setY(allBlocks[0].getY());
		}
		allBlocks[3].setX(allBlocks[2].getX());
		allBlocks[3].setY(allBlocks[2].getY() + blockSize);
		break;
	case 2:
		for (int i = 1; i < 3; i++) {
			allBlocks[i].setX(allBlocks[i - 1].getX() + blockSize);
			allBlocks[i].setY(allBlocks[0].getY());
		}
		allBlocks[3].setX(allBlocks[1].getX());
		allBlocks[3].setY(allBlocks[1].getY() + blockSize);
		break;
	case 3:
		allBlocks[1].setX(allBlocks[0].getX() + blockSize);
		allBlocks[1].setY(allBlocks[0].getY());
		allBlocks[2].setX(allBlocks[0].getX());
		allBlocks[2].setY(allBlocks[0].getY() + blockSize);
		allBlocks[3].setX(allBlocks[0].getX() + blockSize);
		allBlocks[3].setY(allBlocks[0].getY() + blockSize);
		break;
	case 4:
		allBlocks[1].setX(allBlocks[0].getX() + blockSize);
		allBlocks[1].setY(allBlocks[0].getY());
		allBlocks[2].setX(allBlocks[0].getX() + blockSize);
		allBlocks[2].setY(allBlocks[0].getY() + blockSize);
		allBlocks[3].setX(allBlocks[0].getX() + 2 * blockSize);
		allBlocks[3].setY(allBlocks[0].getY() + blockSize);
		break;
	}
	return true;
}

void Item::draw()
{
	if (isAlive) {
		for (int i = 0; i < 4; i++) {
			allBlocks[i].draw();
		}
	}
	
}
