#include <iostream>
#include "Block.h"
#include "ysglfontdata.h"
#include "fssimplewindow.h"
#include "DrawingUtilNG.h"
#include "yspng.h"


void Block::draw()
{
    double planetRed, planetGreen, planetBlue;
	if (!whetherFilled) {
        DrawingUtilNG::hsv2rgb(240, 1.0, 1.0, planetRed, planetGreen, planetBlue);
        glColor3f(planetRed, planetGreen, planetBlue);
        glBegin(GL_LINE_LOOP);
        glVertex2i(leftUpperX, leftUpperY);
        glVertex2i(leftUpperX + size, leftUpperY);
        glVertex2i(leftUpperX + size, leftUpperY + size);
        glVertex2i(leftUpperX, leftUpperY + size);
        glEnd();
		return;
	}
   
    DrawingUtilNG::hsv2rgb(color, 1.0, 1.0, planetRed, planetGreen, planetBlue);
    glColor3f(planetRed, planetGreen, planetBlue);
    glBegin(GL_QUADS);
    glVertex2i(leftUpperX, leftUpperY);
    glVertex2i(leftUpperX + size,leftUpperY);
    glVertex2i(leftUpperX + size, leftUpperY + size);
    glVertex2i(leftUpperX, leftUpperY + size);
    glEnd();

    DrawingUtilNG::hsv2rgb(240, 1.0, 1.0, planetRed, planetGreen, planetBlue);
    glColor3f(planetRed, planetGreen, planetBlue);
    glBegin(GL_LINE_LOOP);
    glVertex2i(leftUpperX, leftUpperY);
    glVertex2i(leftUpperX + size, leftUpperY);
    glVertex2i(leftUpperX + size, leftUpperY + size);
    glVertex2i(leftUpperX, leftUpperY + size);
    glEnd();

}
