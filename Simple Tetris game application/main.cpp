#include <string>
#include <iostream>

#include "yspng.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "DrawingUtilNG.h"
#include "GraphicFont.h"
#include "yssimplesound.h"
#include "Board.h"
#include "Block.h"
#include "Item.h"

using namespace std;
using namespace DrawingUtilNG;

int main() {
	int sizeX = 800;
	int sizeY = 600;
	int blockSize = 25;
	FsOpenWindow(0, 0, sizeX, sizeY, 0);
	TimesNewRomanFont timesnewroman;
	ComicSansFont comicsans;

	YsSoundPlayer player1;
	YsSoundPlayer::SoundData myWav1;
	string fileNames = "tetris-gameboy-02.wav";
	myWav1.LoadWav(fileNames.c_str());
	player1.Start();
	player1.PlayBackground(myWav1);


	YsRawPngDecoder png;
	png.Decode("cover.png");
	GLuint texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D
	(GL_TEXTURE_2D, 0, GL_RGBA, png.wid, png.hei, 0,   
		GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);


	int key;
	while (FSKEY_ENTER != (key = FsInkey())) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		
		glViewport(0, 0, sizeX, sizeY);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, (float)sizeX - 1, (float)sizeY - 1, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glColor4d(1.0, 1.0, 1.0, 1.0); 

		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, texId);

		glBegin(GL_QUADS);
		double scale1 = 1.0; 
		int xSize = png.wid * scale1;
		int ySize = png.hei * scale1;
		glTexCoord2d(0.0, 0.0);  
		glVertex2i(0, 0);

		glTexCoord2d(1.0, 0.0);
		glVertex2i(sizeX, 0);

		glTexCoord2d(1.0, 1.0);
		glVertex2i(sizeX, sizeY);

		glTexCoord2d(0.0, 1.0);
		glVertex2i(0, sizeY);

		glEnd();


		int mouseEvent, leftButton, middleButton, rightButton;
		int locX, locY;
		mouseEvent = FsGetMouseEvent(leftButton, middleButton,
			rightButton, locX, locY);
		if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN && locX <= 455 && locX >= 375
			&& locY <= 400 && locY >= 360) {
			break;
		}

		double red, green, blue;
		DrawingUtilNG::hsv2rgb(200, 1, 1, red, green, blue);
		glColor3f(red, green, blue);
		glBegin(GL_LINE_LOOP);
		glVertex2i(375, 360);
		glVertex2i(375, 400);
		glVertex2i(455, 400);
		glVertex2i(455, 360);
		glEnd();

		timesnewroman.setColorHSV(0, 1, 1);
		timesnewroman.drawText("Start", 388, 400, 0.32, 0);

		glFlush();
		FsSleep(50);
		FsPollDevice();
	}

	bool instruction = true;
	while (instruction) {
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		double red, green, blue;
		DrawingUtilNG::hsv2rgb(200, 1, 1, red, green, blue);
		glColor3f(red, green, blue);
		glBegin(GL_LINE_LOOP);
		glVertex2i(660, 550);
		glVertex2i(780, 550);
		glVertex2i(780, 580);
		glVertex2i(660, 580);
		glEnd();
		timesnewroman.drawText("Continue", 665, 582, 0.32, 0);

		int mouseEvent, leftButton, middleButton, rightButton;
		int locX, locY;
		mouseEvent = FsGetMouseEvent(leftButton, middleButton,
			rightButton, locX, locY);
		if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN && locX <= 780 && locX >= 660
			&& locY <= 580 && locY >= 550) {
			break;
		}

		timesnewroman.setColorHSV(0, 1, 1);
		timesnewroman.drawText("Instruction: ", 0, 60, 0.4, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Use these keys on the screen: ", 0, 120, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Use arrow keys on screen to pan blocks left/right", 80, 150, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Use arrow key up to iterate blocks", 80, 180, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Use arrow key down to accelerate blocks", 80, 210, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Some hints: ", 0, 240, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Use left button of your mouse to change blocks' state", 40, 270, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Press Change Shape button to change blocks' shape", 40, 300, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("These operations will cost 20 scores", 40, 330, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("If you don't have enough scores, you can't do them", 40, 360, 0.3, 0);
		
		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Press Stop button to pause the game", 40, 390, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Press Restart button to restart the game", 40, 420, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Press Exit button to exit the game", 40, 450, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Scores", 0, 480, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Every time you place a block, you get 10 scores", 40, 510, 0.3, 0);

		comicsans.setColorHSV(0, 1, 1);
		comicsans.drawText("Every time you delete a line, you get 100 scores", 40, 540, 0.3, 0);

		glFlush();
		FsSleep(50);
		FsPollDevice();
	}

	bool game = true;
	while (game) {
		Board base = Board(sizeX - 400, sizeY, blockSize);
		Item aliveItem = Item(blockSize, base);
		int times = 0;
		int score = 0;
		int hint = 0;
		int number = 0;
		int loss = 0;
		int clock = 0;
		bool stop = false;
		while (!base.whetherEnd() && FSKEY_ESC != (key = FsInkey())) {
			times += 1;
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			double red, green, blue;
			DrawingUtilNG::hsv2rgb(200, 1, 1, red, green, blue);
			glColor3f(red, green, blue);
			glBegin(GL_QUADS);
			glVertex2i(400, 0);
			glVertex2i(400, 600);
			glVertex2i(405, 600);
			glVertex2i(405, 0);
			glEnd();


			aliveItem.draw();
			base.draw();

			if (!stop) {
				switch (key) {
				case FSKEY_UP:
					aliveItem.rotation(base);
					break;
				case FSKEY_RIGHT:
					aliveItem.horizontalMove(1, base);
					break;
				case FSKEY_LEFT:
					aliveItem.horizontalMove(-1, base);
					break;
				case FSKEY_DOWN:
					aliveItem.goDown(base);
					break;
				}

				if (times % 5 == 0) {
					aliveItem.goDown(base);
				}

				if (!aliveItem.getIsAlive()) {
					aliveItem = Item(blockSize, base);
					score += 10;
				}
				base.update(score, number);
			}


			int mouseEvent, leftButton, middleButton, rightButton;
			int locX, locY;
			mouseEvent = FsGetMouseEvent(leftButton, middleButton,
				rightButton, locX, locY);

			if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
				if (!stop && base.filled(locX, locY, score, hint, loss)) {
					clock = 0;
				}
				else if (!stop) {
					clock = 15;
				}
				if (locX <= 660 && locX >= 460 && locY >= 335 && locY <= 365) {
					if (!stop && aliveItem.changeShape(score, hint, loss)) {
						clock = 0;
					}
					else if (!stop) {
						clock = 15;
					}
				}
				if (locX <= 640 && locX >= 560 && locY >= 520 && locY <= 550) {
					break;
				}
				if (locX <= 540 && locX >= 460 && locY >= 450 && locY <= 480) {
					stop = true;
				}
				if (locX <= 760 && locX >= 660 && locY >= 450 && locY <= 480) {
					stop = false;
				}
			}

			timesnewroman.setColorHSV(0, 1, 1);
			string display = "Your score is: " + to_string(score);
			timesnewroman.drawText(display.c_str(), 410, 70, 0.4, 0);

			display = "Hints you use: " + to_string(hint);
			timesnewroman.setColorHSV(0, 1, 1);
			timesnewroman.drawText(display.c_str(), 410, 140, 0.4, 0);

			display = "Scores you lose: " + to_string(loss);
			timesnewroman.setColorHSV(0, 1, 1);
			timesnewroman.drawText(display.c_str(), 410, 210, 0.4, 0);

			display = "Lines you delete: " + to_string(number);
			timesnewroman.setColorHSV(0, 1, 1);
			timesnewroman.drawText(display.c_str(), 410, 280, 0.4, 0);


			glColor3f(red, green, blue);
			glBegin(GL_LINE_LOOP);
			glVertex2i(460, 335);
			glVertex2i(660, 335);
			glVertex2i(660, 365);
			glVertex2i(460, 365);
			glEnd();
			timesnewroman.drawText("Change Shape", 470, 367, 0.32, 0);

			glColor3f(red, green, blue);
			glBegin(GL_LINE_LOOP);
			glVertex2i(560, 520);
			glVertex2i(640, 520);
			glVertex2i(640, 550);
			glVertex2i(560, 550);
			glEnd();
			timesnewroman.drawText("Exit", 570, 552, 0.32, 0);

			glColor3f(red, green, blue);
			glBegin(GL_LINE_LOOP);
			glVertex2i(460, 450);
			glVertex2i(540, 450);
			glVertex2i(540, 480);
			glVertex2i(460, 480);
			glEnd();
			timesnewroman.drawText("Stop", 470, 482, 0.32, 0);

			glColor3f(red, green, blue);
			glBegin(GL_LINE_LOOP);
			glVertex2i(660, 450);
			glVertex2i(760, 450);
			glVertex2i(760, 480);
			glVertex2i(660, 480);
			glEnd();
			timesnewroman.drawText("Restart", 670, 482, 0.32, 0);



			if (!stop && clock > 0) {
				clock -= 1;
				timesnewroman.setColorHSV(0, 1, 1);
				timesnewroman.drawText("You don't have enough scores", 410, 420, 0.3, 0);
			}

			glFlush();
			FsSleep(50);
			FsPollDevice();
		}

		while (FSKEY_ESC != (key = FsInkey())) {
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

			string display = "Your final score is: " + to_string(score);
			timesnewroman.setColorHSV(0, 1, 1);
			timesnewroman.drawText("Game Over!", sizeX / 2 - 5 * 20, sizeY / 2 - 32 * 2, 0.5, 0);
			timesnewroman.drawText(display.c_str(), sizeX / 2 - 10 * 20, sizeY / 2, 0.5, 0);

			int mouseEvent, leftButton, middleButton, rightButton;
			int locX, locY;
			mouseEvent = FsGetMouseEvent(leftButton, middleButton,
				rightButton, locX, locY);
			
			if (mouseEvent == FSMOUSEEVENT_LBUTTONDOWN) {
				if (locX <= 460 && locX >= 360 && locY >= 335 && locY <= 365) {
					game = true;
					break;
				}
				if (locX <= 440 && locX >= 380 && locY >= 400 && locY <= 430) {
					game = false;
					break;
				}
			}


			double red, green, blue;
			DrawingUtilNG::hsv2rgb(200, 1, 1, red, green, blue);
			glColor3f(red, green, blue);
			glBegin(GL_LINE_LOOP);
			glVertex2i(360, 335);
			glVertex2i(460, 335);
			glVertex2i(460, 365);
			glVertex2i(360, 365);
			glEnd();
			timesnewroman.drawText("Replay", 370, 367, 0.32, 0);

			glColor3f(red, green, blue);
			glBegin(GL_LINE_LOOP);
			glVertex2i(380, 400);
			glVertex2i(440, 400);
			glVertex2i(440, 430);
			glVertex2i(380, 430);
			glEnd();
			timesnewroman.drawText("Exit", 385, 432, 0.32, 0);

			glFlush();
			FsSleep(50);
			FsPollDevice();
		}
	}
	
	player1.End();
	return 0;		
}
