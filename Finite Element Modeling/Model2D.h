/* The head file of the Model2D class.
 * @modifer Zhewei Liu. AndrewID: zheweil. 
 */
#pragma once
#include <fstream>
#include <string>
#include <vector>

#include "fssimplewindow.h"
#include "Node.h"
#include "Plate.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

using namespace std;

enum NodeStyles { n_hide, n_outline, n_filled };
enum PlateStyles { p_hide, p_outline, p_filled, p_contour };

class Plate;
class Node;

class Model2D {
private:
	string name;
	vector<Plate> thePlates;
	vector<Node> theNodes;

	// view preferences
	NodeStyles nodeFormat;
	bool showNodeLabels;

	PlateStyles plateFormat;
	bool showPlateLabels;

	int nodeColor;  // H value for node color (S = 1, V = 1)
	int plateColor; // H value for plate color (S = 1, V = 1)

	int xOrigin, yOrigin;  // screen coords of model coords 0,0
	double viewScale;  // must be greater than zero

	// aggregate values
	double lowDefl, highDefl;
	double minX, minY, maxX, maxY;  // useful for finding default origin and scale

public:
	Model2D();
	// default constructor sets initial model and viewing parameters

	Model2D(ifstream& inFile) : Model2D() { readFile(inFile); }
	// calls default constructor and then readFile()

	void readFile(ifstream& inFile);
	// reads the given file, adding nodes and plates as needed
	// it is a good idea to keep track of lowest and highest node defl

	Node* findNode(const string& givenLabel);
	// returns a pointer to the node that matches the label
	// return nullptr if the node cannot be found in 

	void clearAll();

	void toggleNodeLabels() { showNodeLabels = !showNodeLabels; }
	void togglePlateLabels() { showPlateLabels = !showPlateLabels; }

	// cycle through colors
	void nextNodeColor() { nodeColor = (nodeColor + 240 / 8) % 240; }
	void nextPlateColor() { plateColor = (plateColor + 240 / 8) % 240; }

	// cycle through styles
	void nextNodeFormat() { nodeFormat = (NodeStyles)((nodeFormat + 1) % 3); }
	void nextPlateFormat() { plateFormat = (PlateStyles)((plateFormat + 1) % 4); }

	void setOrigin(double newX, double newY) {
		// allows for "panning" on the view of the model
		xOrigin = newX; yOrigin = newY;
	}
	void setScale(double newScale) {
		// allows for scaling the view of the model
		if (newScale > 0)
			viewScale = newScale;
	}

	double getXOrigin() { return xOrigin; }
	double getYOrigin() { return yOrigin; }
	double getViewScale() { return viewScale; }

	void draw();
	// draws all plates and nodes based on view preferences
	// example of how you use the current Model2D as a parameter:
	//    thePlates[i].drawFill(*this);

	void getScreenCoords(double modelX, double modelY,
		double& screenX, double& screenY);
	// given model coordinates, function calculates screen coordinates
	// converting for translation and scale

	void screenVertex(double modelX, double modelY);
	// given model coordinates, function adds a vertex on screen
	// after converting for translation and scale

};

// bodies of last two functions (move into Model2D.cpp)

/*
==================================================
void Model2D::screenVertex(double modelX, double modelY)
{
	// given model coordinates, function adds a vertex on screen
	// after converting for translation and scale

	double screenX, screenY;

	getScreenCoords(modelX, modelY, screenX, screenY);
	glVertex2i(screenX, screenY);

}

void Model2D::getScreenCoords(double modelX, double modelY, double& screenX, double& screenY)
{
	// given model coordinates, function calculates screen coordinates
	// converting for translation and scale
	screenX = modelX * viewScale + xOrigin;
	screenY = modelY * -viewScale + yOrigin; // takes care of y-axis upwards

	// do rotation (try if adventurous, but perhaps later)
	// double tempX, tempY;
	//double rotAngle = viewRotation * PI_NG / 180.;
	//double tempX = modelX * viewScale + xOrigin - rotOriginX;
	//double tempY = modelY * -viewScale + yOrigin - rotOriginY;
	//
	//screenX = roundf(tempX * cos(rotAngle) - tempY * sin(rotAngle) + rotOriginX);
	//screenY = roundf(tempX * sin(rotAngle) + tempY * cos(rotAngle) + rotOriginY);


}


==================================================

*/