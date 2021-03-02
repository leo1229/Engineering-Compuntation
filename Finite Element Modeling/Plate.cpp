/* The cpp file of the Plate class.
 * @author Zhewei Liu. AndrewID: zheweil.
 */
#include "Plate.h"
#include "ysglfontdata.h"
#include "DrawingUtilNG.h"

void Plate::drawOutline(Model2D& theModel, bool showLabel)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 4; i++) {
		theModel.screenVertex(nodes[i]->getX(), nodes[i]->getY());
	}
	glEnd();

	if (showLabel) {
		double x, y;
		double screenX, screenY;
		getNodeAverages(x, y);
		theModel.getScreenCoords(x, y, screenX, screenY);
		glRasterPos2i(screenX, screenY); // position
		YsGlDrawFontBitmap16x20(label.c_str()); // size and contains
	}

}

void Plate::drawFill(Model2D& theModel)
{
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++) {
		theModel.screenVertex(nodes[i]->getX(), nodes[i]->getY());
	}
	glEnd();
}

void Plate::drawFill(Model2D& theModel, double lowValue, double highValue)
{   
	double red, green, blue;
	double H;
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++) {
		if (nodes[i]->getDeflection() <= lowValue) {
			H = 240.0;
		}
		else if (nodes[i]->getDeflection() >= highValue){
			H = 0.0;
		}
		else {
			H = 240 * (nodes[i]->getDeflection() - lowValue) / (lowValue - highValue) + 240;
		}
		DrawingUtilNG::hsv2rgb(H, 1.0, 1.0, red, green, blue);
		glColor3f(red, green, blue);
		theModel.screenVertex(nodes[i]->getX(), nodes[i]->getY());
	}
	glEnd();
	
}

void Plate::getNodeAverages(double& xAvg, double& yAvg)
{
	double sumX = 0, sumY = 0;
	for (int i = 0; i < 4; i++) {
		sumX += nodes[i]->getX();
		sumY += nodes[i]->getY();
	}
	xAvg = sumX / 4;
	yAvg = sumY / 4;
}
