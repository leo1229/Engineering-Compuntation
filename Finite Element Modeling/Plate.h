/* The head file of the Plate class.
 * @modifer Zhewei Liu. AndrewID: zheweil.
 */
#pragma once
#include <string>

#include "DrawingUtilNG.h"
#include "Node.h"
#include "Model2D.h"

using namespace std;

class Model2D;  // need this since Model2D.h includes Plate.h
class Node;

class Plate {
private:
	string label; 
	
	Node* nodes[4]; // pointers to each node (avoid data duplication)

public:
	Plate(const string& label) {
		this->label = label;  // this is how you differentiate variable names
		nodes[0] = nodes[1] = nodes[2] = nodes[3] = nullptr;
	}


	Node* getNode(int number) {   // give number as 1, 2, 3, or 4
		if (0 < number && number <= 4)
			return nodes[number - 1];
		else
			return nullptr;
	}

	void setNode(Node* newNode, int number) { // give number as is 1, 2, 3, or 4
		if (0 < number && number <= 4) 
			nodes[number - 1] = newNode;
	}

	void drawOutline(Model2D &theModel, bool showLabel = false);
	// draws an outline of the plate using the current color.
	// includes label "kindof centered" on plate if showLabel is true
	// text size is always about 20 pixels
	// 
	// uses parameter theModel to access the screenVertex() function 
	// instead of using glVertex2i() directly and uses getScreenCoords()
	// to place the label
		
	void drawFill(Model2D& theModel);
	// draws a filled quadrilateral of the plate using the current color
	// uses parameter theModel to access the screenVertex() function 
	// instead of using glVertex2i() directly

	void drawFill(Model2D &theModel, double lowValue, double highValue);
	// draws a color-contoured quadrilateral of the plate using the following:
	//    if defl of node <= lowValue, use H = 240  (blue)
	//    if defl of node >= highValue, use H = 0 (red)
	//    otherwise, interpolate the defl of the node between low and high 
	//         value to get corresponding color H between 240 and 0.
	// 
	// uses parameter theModel to access the screenVertex() function 
	// instead of using glVertex2i() directly

	
private:
	// the following are suggestions, you don't have to use them

	int getNodeColor(double value, double low, double high);
	// interpolates based on values to assign color

	void getNodeAverages(double& xAvg, double& yAvg);
	// finds average xCoord and average yCoord of the 4 nodes 
};