/* The cpp file of the Model2D class.
 * @author Zhewei Liu. AndrewID: zheweil.
 */
#include<sstream>
#include<cstring>

#include "Model2D.h"
#include "DrawingUtilNG.h"

using namespace std;

Model2D::Model2D()
{   
	viewScale = 10.0;

	nodeFormat = n_outline;
	
	plateFormat = p_filled;
	
	nodeColor = 0; // red
	plateColor = 240; // blue
	// I change the initial value of xOrigin and yOrigin to make the plot easier to see.
	xOrigin = WIN_WIDTH / 2; yOrigin = WIN_HEIGHT / 2 + 100 ;
	
	showNodeLabels = false;
	showPlateLabels = false;

	lowDefl = DBL_MAX; highDefl = DBL_MIN;
	minX = DBL_MAX; minY = DBL_MAX; maxX = DBL_MIN; maxY = DBL_MIN;
}

void Model2D::readFile(ifstream& inFile)
{
	string inputLine;
	bool startInputNodes = false;
	bool startInputPlates = false;	
	while (getline(inFile, inputLine)) {
		if (inputLine.find("Name") != -1) {
			int start = inputLine.find(":");
			start += 1;
			while (start < inputLine.size() && 
				!((inputLine[start] <= 'Z' && inputLine[start] >= 'A') || (inputLine[start] <= 'z' && inputLine[start] >= 'a'))) {
				start += 1;
			}
			string modelName = inputLine.substr(start);
			name = modelName;
		}
		if (inputLine.find("Nodes") != -1) {
			startInputNodes = !startInputNodes;
			continue;
		}
		if (inputLine.find("Plates") != -1) {
			startInputPlates = !startInputPlates;
			continue;
		}
		if (startInputNodes) {
			string nodeName;
			double x, y, z, deflection;
			stringstream inputStream;
			inputStream.str(inputLine);
			inputStream >> nodeName >> x >> y >> z >> deflection;
			Node n = Node(nodeName, x, y, z, deflection);
			theNodes.push_back(n);
			if (y < minY) {
				minY = y;
			}
			if (y > maxY) {
				maxY = y;
			}
			if (x < minX) {
				minX = x;
			}
			if (x > maxX) {
				maxX = x;
			}
			if (deflection < lowDefl) {
				lowDefl = deflection;
			}
			if (deflection > highDefl) {
				highDefl = deflection;
			}
		}
		if (startInputPlates) {
			string plateLabel;
			string addNode[4];
			stringstream inputStream;
			inputStream.str(inputLine);
			inputStream >> plateLabel >> addNode[0] >> addNode[1] >> addNode[2] >> addNode[3];
			Plate p = Plate(plateLabel);
			int itemNumber;
			for (int i = 0; i < 4; i++) {
				itemNumber = stoi(addNode[i].substr(addNode[i].find("N") + 1));
				p.setNode(&theNodes[itemNumber - 1], i + 1);
			}
			thePlates.push_back(p);
		}
	}
}

Node* Model2D::findNode(const string& givenLabel)
{   
	for (int i = 0; i < theNodes.size(); i++) {
		if (theNodes[i].getLabel() == givenLabel) {
			return &theNodes[i];
		}
	}
	return nullptr;
}

void Model2D::clearAll()
{   
	name.clear();
	theNodes.clear();
	thePlates.clear();

	viewScale = 10.0;

	nodeFormat = n_outline;

	plateFormat = p_filled;

	nodeColor = 0; // red
	plateColor = 240; // blue
	// I change the initial value of xOrigin and yOrigin to make the plot easier to see.
	xOrigin = WIN_WIDTH / 2; yOrigin = WIN_HEIGHT / 2 + 100;

	showNodeLabels = false;
	showPlateLabels = false;

	lowDefl = DBL_MAX; highDefl = DBL_MIN;
	minX = DBL_MAX; minY = DBL_MAX; maxX = DBL_MIN; maxY = DBL_MIN;
}

void Model2D::draw()
{    
	// if plates are not hidden then, 
	// set plate color as color
	// for each plates
	// if platestyle is p_filled then call draw fill
	// if platestyle is p_outline then call drawOutLine
	// if style is contour, call draw with lowdefl and high defl
	// if style is contour or filled, call drawOutLine using black
	double plateRed, plateGreen, plateBlue;
	double nodeRed, nodeGreen, nodeBlue;
	DrawingUtilNG::hsv2rgb(plateColor, 1.0, 1.0, plateRed, plateGreen, plateBlue);
	DrawingUtilNG::hsv2rgb(nodeColor, 1.0, 1.0, nodeRed, nodeGreen, nodeBlue);
	
	switch (plateFormat) {
	    case p_hide:
		      break;
		case p_outline:
			glColor3f(plateRed, plateGreen, plateBlue);
			for (int i = 0; i < thePlates.size(); i++) {
				thePlates[i].drawOutline(*this, showPlateLabels);
			}
			break;
		case p_filled:
			glColor3f(plateRed, plateGreen, plateBlue);
			for (int i = 0; i < thePlates.size(); i++) {
				thePlates[i].drawFill(*this);
			}
			break;
		case p_contour:
			for (int i = 0; i < thePlates.size(); i++) {
				thePlates[i].drawFill(*this, lowDefl, highDefl);
			}
			break;
	}
	// if nodes are not hidden, then
	// set node color as color
	// for each of the nodes
	// call its draw function, accounting for filled and/or labels
	switch (nodeFormat) {
	    case n_hide:
		    break;
	    case n_outline:
			glColor3f(nodeRed, nodeGreen, nodeBlue);
			for (int i = 0; i < theNodes.size(); i++) {
				theNodes[i].draw(*this, 2, false, showNodeLabels);
			}
		    break;
	    case n_filled:
			glColor3f(nodeRed, nodeGreen, nodeBlue);
			for (int i = 0; i < theNodes.size(); i++) {
				theNodes[i].draw(*this, 2, true, showNodeLabels);
			}
		    break;
	}
	

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

void Model2D::screenVertex(double modelX, double modelY)
{
	// given model coordinates, function adds a vertex on screen
	// after converting for translation and scale

	double screenX, screenY;

	getScreenCoords(modelX, modelY, screenX, screenY);
	glVertex2f(screenX, screenY);
}

