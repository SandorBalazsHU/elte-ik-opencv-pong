#include "pch.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;

#define WIDTH 800
#define HEIGHT 600
#define WALL 20
#define BALL 20
#define PLAYER 80
#define SPEED 10
#define PLAYERSPEED 30

Mat image;
int iksz, ipszilon, sx, sy, playerX, playerY;
bool start = false;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

void fieldDraw() {
	rectangle(image, Point(0, 0), Point(WALL, HEIGHT-1), Scalar(150, 150, 150), -1);
	rectangle(image, Point(0, 0), Point(WIDTH - 1, WALL), Scalar(150, 150, 150), -1);
	rectangle(image, Point(WIDTH - WALL - 1, 0), Point(WIDTH-1, HEIGHT - 1), Scalar(150, 150, 150), -1);
}

void player() {
	rectangle(image, Point(playerX, HEIGHT - WALL - 1 + playerY), Point(playerX + PLAYER, HEIGHT - 1 + playerY), Scalar(0, 211, 255), -1);
}

void redraw() {
	rectangle(image, Point(0, 0), Point(WIDTH, HEIGHT), Scalar(0, 0, 0), CV_FILLED);
	if(start) rectangle(image, Point(iksz, ipszilon), Point(iksz + BALL, ipszilon + BALL), Scalar(0, 255, 0), -1);
	fieldDraw();
	player();
	imshow("Display window", image);
}

void MouseCallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		iksz = x;
		ipszilon = y;
		start = true;
		redraw();
	}

}

int main(int argc, char** argv)
{
	image = Mat::zeros(HEIGHT, WIDTH, CV_8UC3);
	iksz = 50;
	ipszilon = 50;
	sx = SPEED;
	sy = SPEED;
	playerX = (WIDTH / 2) - (PLAYER / 2);
	playerY = 0;

	namedWindow("Display window", WINDOW_AUTOSIZE);
	setMouseCallback("Display window", MouseCallBackFunc, NULL);
	imshow("Display window", image);

	auto startTime = Time::now();

	int key = 0;
	while (true) {
		auto currentTime = Time::now();
		fsec fs = currentTime - startTime;
		ms duratation = std::chrono::duration_cast<ms>(fs);
		
		if (duratation.count() > 60)
		{
			startTime = Time::now();

			key = cvWaitKey(1);

			if (start) {
				iksz += sx;
				ipszilon += sy;
			}

			if (iksz<WALL || iksz > WIDTH - WALL * 2) {
				sx *= -1;
			}

			if (ipszilon < WALL) {
				sy *= -1;
			}

			if (ipszilon > HEIGHT - WALL - BALL - 1 && iksz > playerX && iksz < playerX + PLAYER) {
				sy *= -1;
			}


			if (key == 27) break;
			switch (key) {
			case 'a':
				playerX -= PLAYERSPEED;
				break;
			case 'd':
				playerX += PLAYERSPEED;
				break;
			}
			redraw();
		}
	}

	return 0;
}
