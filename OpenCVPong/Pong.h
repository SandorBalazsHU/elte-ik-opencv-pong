#ifndef PONG_H
#define PONG_H

#include <opencv2/core/core.hpp>

class Shape
{
	public:
		Shape(int x, int y);
		void move(int sx, int sy);
		virtual void draw(cv::Mat image);
		int getX();
		int getY();

	protected:
		int x = 0;
		int y = 0;
		int border = 1;
};

class Ball : public Shape
{
	public:
		Ball(int x, int y, int size = 20, bool fill = true, bool circle = true);
		void draw(cv::Mat image);
		void place(int x, int y);

	private:
		int size = 20;
		bool circle = true;
		bool fill = true;
		cv::Scalar color = cv::Scalar(0, 255, 0);
};

/*class Wall : public Shape
{
	public:
		Ball(int x, int y, int size = 20, cv::Scalar color = cv::Scalar(0, 255, 0),
		bool fill = true, bool circle = true);
		void draw(cv::Mat image);

	private:
};*/
#endif