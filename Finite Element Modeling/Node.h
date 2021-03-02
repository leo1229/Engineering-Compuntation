/* The head file of the Node class.
 * @modifer Zhewei Liu. AndrewID: zheweil.
 */
#pragma once
#include <string>
#include "Model2D.h"

using namespace std;
class Model2D;

class Node {
private:
	string label;
	double x, y, z;   // coordinates of the node
	double deflection;  // a preliminary result

public:
	Node(const string &aLabel, double xCoord, double yCoord, 
		double zCoord = 0., double defl = 0.);
	// default constructor for the class, setting all parameters.

	// get and set for all member variables
	string getLabel() { return label; }
	double getX() { return x; }
	double getY() { return y; }
	double getZ() { return z; }
	double getDeflection() { return deflection; }

	bool setLabel(const string& newLabel) { label = newLabel; }
	bool setX(double xCoord) { x = xCoord; }
	bool setY(double yCoord) { y = yCoord; }
	bool setZ(double zCoord) { z = zCoord; }
	bool setDeflection(double defl) { deflection = defl; }

	void draw(Model2D &theModel, int size = 2, 
		bool filled = true, bool showLabel = false);
	// draws a symbol (programmer's choice) of the node, filled as given
	// uses size (default = 2) to determine model size of node symbol
	// includes label a bit off-center if showLabel is true	
	// 
	// uses parameter theModel to access the getScreenCoords() function
	// to place the label and perhaps assure node symbol does not scale

};