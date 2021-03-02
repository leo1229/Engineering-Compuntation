/* 
 * This is the head file of a galaxy.
 * You can add planets into the system class to build your own galaxy.
 * This class can also simulate how the system works based on the given initial condition.
 * @author: Zhewei Liu. AndrewId: zheweil
 */
#pragma once

#include <string>
#include <vector>

#include "yspng.h"
#include "fssimplewindow.h"
#include "Planet.h"

using namespace std;

class System {
private:
	// Store all planets in this system.
	vector<Planet> planetList;
	// Store all the color of planets.
	vector<double> colorList;
	// Store the X and Y position of planets
	vector<double> imageX;
	vector<double> imageY;
	// This is the step time of the simulation system.
	double dt;
	// This is the size of this system.
	int size;
	// This is the scale of the system.
	double range;
	// This is the center position of this system.
	// These two valuse help to show the whole systm on the screen.
	int centerX, centerY;
public:
	// The constructor of the system.
	System(double stepTime, double range, int centerX, int centerY);
	// The function which can add a planet into this system.
	void add(Planet p);
	// Simulate the system.
	void simulate();
	// Returen the current X and Y position of all the planets.(For image)
	vector<double> getImageX() { 
		vector<double> result;
		int length = imageX.size();
		for (int i = 0; i < size; i++) {
			result.push_back(imageX[length - size + i]);
		}
		return result; 
	}
	vector<double> getImageY() { 
		vector<double> result;
		int length = imageY.size();
		for (int i = 0; i < size; i++) {
			result.push_back(imageY[length - size + i]);
		}
		return result;
	}
};