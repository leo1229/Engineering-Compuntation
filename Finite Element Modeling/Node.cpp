/* The cpp file of the Node class.
 * @author Zhewei Liu. AndrewID: zheweil.
 */
#include "Node.h"
#include "ysglfontdata.h"

Node::Node(const string& aLabel, double xCoord, double yCoord, double zCoord, double defl)
{
	label = aLabel;
	x = xCoord;
	y = yCoord;
	z = zCoord;
	deflection = defl;
}

void Node::draw(Model2D& theModel, int size, bool filled, bool showLabel)
{
	// account for filled or not
	if (filled) {
		glBegin(GL_QUADS);
	}
	else {
		glBegin(GL_LINE_LOOP);
	}

	// simple diamond surrend the node

	double transformedX, transformedY;

	theModel.getScreenCoords(x, y, transformedX, transformedY);

	glVertex2f(transformedX - size, transformedY);
	glVertex2f(transformedX, transformedY + size);
	glVertex2f(transformedX + size, transformedY);
	glVertex2f(transformedX, transformedY - size);

	glEnd();


	// put the label
	if (showLabel) {
		glRasterPos2i(transformedX + 3 * size, transformedY + 4 * size); // position
		YsGlDrawFontBitmap16x20(label.c_str()); // size and contains
	}
}
