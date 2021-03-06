#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <chrono>
#include "Pong.h"

using namespace cv;

const int screenWidth = 800;
const int screenHeight = 600;
const int wallSize = 20;
const int ballSize = 20;
const int playerSize = 80;
const int ballSpeed = 4;
const int playerSpeed = 30;
const Scalar wallColor = Scalar(150, 150, 150);
const Scalar ballColor = Scalar(0, 255, 0);
const Scalar backgroundColor = Scalar(0, 0, 0);
const Scalar playerColor = Scalar(0, 211, 255);
const int fillShape = -1;
const bool playarIsCircle = false;

Mat image;
int sx, sy, playerX, playerY = 0;
bool start = false;

Ball ball(0,0);

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
		ball.draw(image);
	}
	fieldDraw();
	player();
	imshow("Display window", image);
}

void MouseCallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		ball.place(x, y);
		start = true;
		redraw();
	}

}

int main(int argc, char** argv)
{
	image = Mat::zeros(screenHeight, screenWidth, CV_8UC3);
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
		
		if (duratation.count() > 17)
		{
			startTime = Time::now();

			if (start) {
				ball.move(sx, sy);
			}

			if (ball.getX() < wallSize + ballSize / 2 || ball.getX() > screenWidth - wallSize - ballSize / 2) {
				sx *= -1;
			}

			if (ball.getY() < wallSize + ballSize / 2) {
				sy *= -1;
			}

			if (ball.getY() > screenHeight - wallSize - ballSize / 2 &&
				ball.getX() > playerX && ball.getX() < playerX + playerSize) {
				sy *= -1;
			}

			if (ball.getY() > screenHeight) start = false;

			key = cvWaitKey(1);
			//std::cout << key << std::endl;
			if(key == 27) break;
			if(key == 65 || key == 97) playerX -= playerSpeed;
			if(key == 68 || key == 100) playerX += playerSpeed;

			redraw();
		}
	}

	return 0;
}
