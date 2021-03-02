/* This is the main code of the Mesh Viewer program.
 * @author Zhewei Liu. AndrewID: zheweil
 */
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include<cstring>

#include "fssimplewindow.h"
#include "DrawingUtilNG.h"
#include "ysglfontdata.h"
#include "Node.h"
#include "Plate.h"
#include "Model2D.h"

using namespace std;

int main() {

	char loadFile;
	char cleanData;

	// 2. Press L on screen to ask user(in console) for file name to load.
	cout << "Hello, you need to press L to load file." << endl;
	cin >> loadFile;
	while (loadFile != 'L' && loadFile != 'l') {
		cout << "You need to press L to load file." << endl;
		cin >> loadFile;
	}
	string inputFileName;
	cout << "Please enter the file name you want to load." << endl;
	cin >> inputFileName;
	ifstream fin(inputFileName);
	Model2D m = Model2D(fin);
	fin.close();
	cout << "The data has been read from file " << inputFileName << endl;

	// 1. Press C on screen to clear all data (ask for confirmation on console).
	cout << "Do you want to delete all the data? (C for clean, N for no)" << endl;
	cin >> cleanData;
	if (cleanData == 'C' || cleanData == 'c') {
		cout << "Are you sure you want to delete all the data? (Y for yes, N for no)" << endl;
		char judge;
		cin >> judge;
		if (judge == 'Y' || judge == 'y') {
			m.clearAll();
			cout << "All the data has been deleted." << endl;
		} 
		else {
			cout << "You don't delete anything." << endl;
		}
	}
	cout << "You can press Esc to exit." << endl;
	FsOpenWindow(0, 0, 800, 600, 0);// Create the window.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	FsPollDevice();
	while (FSKEY_ESC != FsInkey()) {
		m.draw();
		glFlush();
		FsPollDevice();
		
		switch (FsInkey()) {
			// 3. Press arrow keys on screen to pan model up / down / left / right
		    case FSKEY_LEFT:
			    m.setOrigin(m.getXOrigin() - 5, m.getYOrigin());
			    break;
			case FSKEY_RIGHT:
				m.setOrigin(m.getXOrigin() + 5, m.getYOrigin());
				break;
			case FSKEY_UP:
				m.setOrigin(m.getXOrigin(), m.getYOrigin() - 5);
				break;
			case FSKEY_DOWN:
				m.setOrigin(m.getXOrigin(), m.getYOrigin() + 5);
				break;
			//	4. Press + on screen to zoom into model(make model appear bigger)
			case FSKEY_PLUS:
				m.setScale(m.getViewScale() + 1);
				break;
			//  5. Press ¨C on screen to zoom out of model (make model appear smaller)
			case FSKEY_MINUS:
				m.setScale(m.getViewScale() - 1);
				break;
            //  6. Press N on screen to cycle through node style (see Model2D.h for enum of node display styles)
			case FSKEY_N:
				m.nextNodeFormat();
				break;
			// 7. Press B on screen to cycle through 8 distinct node colors
			case FSKEY_B:
				m.nextNodeColor();
				break;
		    // 8. Press V on screen to toggle node labels on/off
			case FSKEY_V:
				m.toggleNodeLabels();
				break;
			// 9. Press P on screen to cycle through plate styles(see Model2D.h for enum of plate display styles)
			case FSKEY_P:
				m.nextPlateFormat();
				break;
            // 10. Press O (letter ohh) on screen to cycle through 8 distinct plate colors
			case FSKEY_O:
				m.nextPlateColor();
				break;
			// 11. Press I on screen to toggle plate labels on / off
			case FSKEY_I:
				m.togglePlateLabels();
				break;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		FsPollDevice();
		FsSleep(25);
	}
	cout << "GoodBye. Hope to see you soon." << endl;
	return 0;
}