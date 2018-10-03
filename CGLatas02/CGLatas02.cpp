#include "pch.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;

const int screenWidth = 800;
const int screenHeight = 600;
const int wallSize = 20;
const int ballSize = 20;
const int playerSize = 80;
const int ballSpeed = 10;
const int playerSpeed = 30;
const Scalar wallColor = Scalar(150, 150, 150);
const Scalar ballColor = Scalar(0, 255, 0);
const Scalar backgroundColor = Scalar(0, 0, 0);
const Scalar playerColor = Scalar(0, 211, 255);
const int fillShape = 1;
const bool playarIsCircle = false;

Mat image;
int ballX, ballY, sx, sy, playerX, playerY = 0;
bool start = false;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::milliseconds ms;
typedef std::chrono::duration<float> fsec;

void fieldDraw() {
	rectangle(image, Point(0, 0), Point(wallSize, screenHeight), wallColor, fillShape);
	rectangle(image, Point(0, 0), Point(screenWidth, wallSize), wallColor, fillShape);
	rectangle(image, Point(screenWidth - wallSize, 0), Point(screenWidth, screenHeight), wallColor, fillShape);
}

void player() {
	rectangle(image, Point(playerX, screenHeight - wallSize + playerY), Point(playerX + playerSize, screenHeight + playerY), playerColor, fillShape);
}

void redraw() {
	rectangle(image, Point(0, 0), Point(screenWidth, screenHeight), backgroundColor, CV_FILLED);
	if (start)
	{
		if (!playarIsCircle)
		{
			rectangle(image, Point(ballX, ballY), Point(ballX + ballSize, ballY + ballSize), ballColor, fillShape);
		}
		else
		{
			circle(image, Point(ballX, ballY), ballSize/2, ballColor, fillShape);
		}
	}
	fieldDraw();
	player();
	imshow("Display window", image);
}

void MouseCallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		ballX = x;
		ballY = y;
		start = true;
		redraw();
	}

}

int main(int argc, char** argv)
{
	image = Mat::zeros(screenHeight, screenWidth, CV_8UC3);
	ballX = 50;
	ballY = 50;
	sx = ballSpeed;
	sy = ballSpeed;
	playerX = (screenWidth / 2) - (playerSize / 2);
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
				ballX += sx;
				ballY += sy;
			}

			if (ballX<wallSize + ballSize || ballX > screenWidth - wallSize * 2) {
				sx *= -1;
			}

			if (ballY < wallSize) {
				sy *= -1;
			}

			if (ballY > screenHeight - wallSize - ballSize - 1 && ballX > playerX && ballX < playerX + playerSize) {
				sy *= -1;
			}


			if (key == 27) break;
			switch (key) {
			case 'a':
				playerX -= playerSpeed;
				cout << "A" << endl;
				break;
			case 'd':
				playerX += playerSpeed;
				cout << "D" << endl;
				break;
			}
			redraw();
		}
	}

	return 0;
}
