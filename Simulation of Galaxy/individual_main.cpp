/* 
 * This is the main function for the individual project.
 * In this project I built a rough simulation system for the galaxey.
 * In this simulation, I assume all planets in the system are only affected by the gravitational force between them.
 * This project has two sub-systems which will be simulated.
 * 
 * The first one is a three-body system.
 * There are two stars and one planet in this system.
 * The planet has the same mass as earth and two stars have same mass as sun.
 * At the beginning, two stars are symmetrically distributed on both sides of the planet.
 * Through simulation, you can see how the three-body system works.
 * 
 * The second one is the inner solar system.(Sun, Mercury, Venus, Earth, Mars)
 * The mass and distance is the same as the real solar system.
 * Through simulation, you can see how our solar system works.
 * 
 * These two simulations will also show the orbit of these planets.
 * @author Zhewei Liu. AndrewId: zheweil.
 */
#include <string>
#include <vector>
#include <iostream>

#include "yspng.h"
#include "fssimplewindow.h"
#include "System.h"
#include "Planet.h"
#include "ysglfontdata.h"
#include "DrawingUtilNG.h"
#include "yssimplesound.h"


// This is the simulation time step.
#define STEPTIME 0.05
#define SIZE 1000

// The function which can initialize a image. 
void initialImage(GLuint& texId, YsRawPngDecoder& png);
// The function which can draw the image. 
void drawImage(GLuint& texId, YsRawPngDecoder& png, double imageX, double imageY);

int main() {

	

	// Three body problem. 
	double threeBodySystemRange = 1.25e11;
	// Build the three-body system.
	System threeBodySystem = System(STEPTIME, threeBodySystemRange, 500, 300);
	Planet s1 = Planet("sun1", 240.0, 0.000e00, 4.500e10, 3.000e04, 0.000e00, 1.989e30);
	Planet e = Planet("earth", 0.0, 0.000e00, 0.000e00, 0.0080e04, 0.000e00, 5.974e24);
	Planet s2 = Planet("sun2", 240.0, 0.000e00, -4.500e10, - 3.000e04, 0.000e00, 1.989e30);
	threeBodySystem.add(s1); threeBodySystem.add(e); threeBodySystem.add(s2);

	// Inner solar system.
	double innerSolarSystemRange = 2.50e+11;
	// Build the inner solar system.
	System innerSolarSystem = System(STEPTIME, innerSolarSystemRange, 500, 500);
	Planet sun = Planet("Sun", 240.0, 0.0000e+00, 0.0000e+00, 0.0000e+00, 0.0000e+00, 1.9890e+30);
	Planet mercury = Planet("Mercury", 180.0, 5.7900e+10, 0.0000e+00, 0.0000e+00, 4.7900e+04, 3.3020e+23);
	Planet venus = Planet("Venus", 120.0, 1.0820e+11, 0.0000e+00, 0.0000e+00, 3.5000e+04, 4.8690e+24);
	Planet earth = Planet("Earth", 60.0, 1.4960e+11, 0.0000e+00, 0.0000e+00, 2.9800e+04, 5.9740e+24);
	Planet mars = Planet("Mars", 0.0, 2.2790e+11, 0.0000e+00, 0.0000e+00, 2.4100e+04, 6.4190e+23);
	innerSolarSystem.add(sun); innerSolarSystem.add(mercury); innerSolarSystem.add(venus);
	innerSolarSystem.add(earth); innerSolarSystem.add(mars);

	// Import all the images we will use in this project. 
	YsRawPngDecoder png[7];
	png[0].Decode("earth1.png");
	png[1].Decode("sun1.png");
	png[2].Decode("mercury.png");
	png[3].Decode("venus.png");
	png[4].Decode("mars.png");
	png[5].Decode("sun2.png");
	png[6].Decode("earth2.png");


	FsOpenWindow(0, 0, SIZE, SIZE, 0);

	// Play Background sound.
	YsSoundPlayer player1;
	YsSoundPlayer::SoundData myWav1;
	string fileNames = "Cosmic_Voyage.wav";
	myWav1.LoadWav(fileNames.c_str());
	player1.Start();
	player1.PlayBackground(myWav1);

	
	GLuint texId[7];
	// Initialize all the images.
	for (int i = 0; i < 7; i++) {
		initialImage(texId[i], png[i]);
	}
	
	int times = 0;

	while (times <= 2000) {
		// Simulation for the three-body system.
		if (times <= 716) {
			times += 1;

			int wid, hei;
			FsGetWindowSize(wid, hei);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			// Simulate the three-body system.
			threeBodySystem.simulate();
			vector <double> imageX = threeBodySystem.getImageX();
			vector <double> imageY = threeBodySystem.getImageY();
			
			// This is a brief introduction of the three-body system.
			if (times <= 200) {
				double red, green, blue;
				DrawingUtilNG::hsv2rgb(0, 1, 1, red, green, blue);
				glColor3f(red, green, blue);
				glRasterPos2i(100, 100);
				YsGlDrawFontBitmap16x20("This is a simulation of a three-body problem.");
				glRasterPos2i(100, 130);
				YsGlDrawFontBitmap16x20("This system contains two stars and one planet.");
				glRasterPos2i(100, 160);
				YsGlDrawFontBitmap16x20("The star has the same mass as the sun.");
				glRasterPos2i(100, 190);
				YsGlDrawFontBitmap16x20("The planet has the same mass as the earth.");
			}
			
			//  create a projection
			glViewport(0, 0, wid, hei);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glColor4d(1.0, 1.0, 1.0, 1.0);   // this color will "tint" the image

			// enable texture mapping
			glEnable(GL_TEXTURE_2D);

			// Draw the image of the first sun1.
			drawImage(texId[1], png[1], imageX[0], imageY[0]);
			// Draw the image for the second sun1.
			drawImage(texId[1], png[1], imageX[2], imageY[2]);
			// Draw the image of earth1.
			drawImage(texId[0], png[0], imageX[1], imageY[1]);

			glFlush();
			FsPollDevice();
			FsSleep(50);
		}
		// Simulation for the inner solar system.
		else {
			times += 1;
			int wid, hei;
			FsGetWindowSize(wid, hei);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			// Simulate the inner solar system.
			innerSolarSystem.simulate();
			vector <double> imageX = innerSolarSystem.getImageX();
			vector <double> imageY = innerSolarSystem.getImageY();

			// A brief introduction of this system.
			if (times <= 916) {
				double red, green, blue;
				DrawingUtilNG::hsv2rgb(0, 1, 1, red, green, blue);
				glColor3f(red, green, blue);
				glRasterPos2i(100, 100);
				YsGlDrawFontBitmap16x20("This is a simulation of our inner solar system.");
				glRasterPos2i(50, 130);
				YsGlDrawFontBitmap16x20("This system contains Sun, Mercury, Venus, Earth and Mars.");
			}
			
			//  create a projection
			glViewport(0, 0, wid, hei);
			
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, (float)wid - 1, (float)hei - 1, 0, -1, 1);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glColor4d(1.0, 1.0, 1.0, 1.0);   // this color will "tint" the image

			// enable texture mapping
			glEnable(GL_TEXTURE_2D);
			// Draw the image of sun2.
			drawImage(texId[5], png[5], imageX[0], imageY[0]);
			// Draw the image of mercury.
			drawImage(texId[2], png[2], imageX[1], imageY[1]);
			// Draw the image of venus.
			drawImage(texId[3], png[3], imageX[2], imageY[2]);
			// Draw the image of earth2.
			drawImage(texId[6], png[6], imageX[3], imageY[3]);
			// Draw the image of mars.
			drawImage(texId[4], png[4], imageX[4], imageY[4]);

			glFlush();
			FsPollDevice();
			FsSleep(50);
		}
	}
	player1.End();
	return 0;
}

// This is the function which can initialize the image.
void initialImage(GLuint& texId, YsRawPngDecoder& png) {
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
}

// This is the function which can draw the image.
void drawImage(GLuint& texId, YsRawPngDecoder& png, double imageX, double imageY) {
	glBindTexture(GL_TEXTURE_2D, texId);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	glVertex2i(imageX - png.wid / 2, imageY - png.hei / 2);
	glTexCoord2d(1.0, 0.0);
	glVertex2i(imageX + png.wid / 2, imageY - png.hei / 2);

	glTexCoord2d(1.0, 1.0);
	glVertex2i(imageX + png.wid / 2, imageY + png.hei / 2);

	glTexCoord2d(0.0, 1.0);
	glVertex2i(imageX - png.wid / 2, imageY + png.hei / 2);
	glEnd();
}
