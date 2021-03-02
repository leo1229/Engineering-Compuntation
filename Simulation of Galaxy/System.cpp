/*
 * This is the .cpp file of the System.h file.
 * @author Zhewei Liu. AndrewID: zheweil
 */

#include <vector>
#include "System.h"
#include "ysglfontdata.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"
#include "yspng.h"

using namespace std;

System::System(double stepTime, double range, int centerX, int centerY)
{
	this->range = range;
	this->centerX = centerX;
	this->centerY = centerY;
	dt = stepTime;
	size = 0;
}

void System::add(Planet p)
{
	size += 1;
	planetList.push_back(p);
	colorList.push_back(p.getColor());
}


void System::simulate()
{   
	double x, y;
	// Draw the planet.
	for (Planet p: planetList) {
		p.draw(range, x, y, centerX, centerY);
		imageX.push_back(x);
		imageY.push_back(y);
	}
	// Draw the orbit.
	for (int i = 0; i < imageX.size(); i++) {
		int index = i % size;
		double nodeRed, nodeGreen, nodeBlue, x, y;
		x = imageX[i]; y = imageY[i];
		DrawingUtilNG::hsv2rgb(colorList[index], 1.0, 1.0, nodeRed, nodeGreen, nodeBlue);
		glColor3f(nodeRed, nodeGreen, nodeBlue);
		glBegin(GL_QUADS);
		glVertex2f(x - 2, y);
		glVertex2f(x, y + 2);
		glVertex2f(x + 2, y);
		glVertex2f(x, y - 2);
		glEnd();
	}
	vector <double> xForce;
	vector <double> yForce;
	for (Planet p: planetList) {
		xForce.push_back(p.calcNetForceExertedByX(planetList));
		yForce.push_back(p.calcNetForceExertedByY(planetList));
	}
	for (int i = 0; i < size; i++) {
		planetList[i].update(dt, xForce[i], yForce[i]);
	}
}
