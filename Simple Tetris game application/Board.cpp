#include <iostream>
#include "Board.h"
#include "yspng.h"
#include "fssimplewindow.h"

using namespace std;
void Board::update(int& score, int& number)
{
	bool whetherDelete;
	for (int i = row; i > 1; i--) {
		whetherDelete = true;
		for (int j = 1; j <= col; j++) {
			if (!content[(i - 1) * col + (j - 1)].getWhetherFilled()) {
				whetherDelete = false;
				break;
			}
		}
		if (whetherDelete) {
			score += 100;
			number += 1;
			for (int nr = i; nr > 1; nr--) {
				for (int nc = 1; nc <= col; nc++) {
					content[(nr - 1) * col + (nc - 1)].setFilled(content[(nr - 2) * col + (nc - 1)].getWhetherFilled());
				}
			}
			i = i + 1;
		}
	
	}
}

bool Board::filled(int x, int y, int& score, int& hint, int& loss)
{
	if (x < 0 || x > totalX || y < 0 || y > totalY) {
		return true;
	}
	if (score < 20) {
		return false;
	}
	int minX, minY, maxX, maxY;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			minX = content[i * col + j].getX();
			minY = content[i * col + j].getY();
			maxX = minX + blockSize;
			maxY = minY + blockSize;
			if (x <= maxX && x >= minX && y <= maxY && y >= minY && !content[i * col + j].getWhetherFilled()) {
				content[i * col + j].setFilled(true);
				content[i * col + j].setColor(0);
				score -= 20;
				hint += 1;
				loss += 20;
			}
		}
	}
	return true;
}

void Board::draw()
{
	for (int i = 1; i <= row; i++) {
		for (int j = 1; j <= col; j ++) {
			content[(i - 1) * col + (j - 1)].draw();
		}
	}
}

bool Board::whetherEnd()
{
	bool result = false;
	for (int i = 1; i <= col; i++) {
		if (content[i - 1].getWhetherFilled()) {
			result = true;
			break;
		}
	}
	return result;
}

