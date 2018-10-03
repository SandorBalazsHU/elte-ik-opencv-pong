#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "pong.h"

Shape::Shape(int x, int y) : x(x), y(y)
{

}

void Shape::move(int sx, int sy)
{
	this->x += sx;
	this->y += sy;
}

void Shape::draw(cv::Mat image)
{

}

int Shape::getX()
{
	return this->x;
}

int Shape::getY()
{
	return this->y;
}

Ball::Ball(int x, int y, int size, bool fill, bool circle) :
Shape(x, y), size(size), fill(fill), circle(circle)
{

}

void Ball::place(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Ball::draw(cv::Mat image)
{
	int border = this->fill ? -1 : this->border;
	if (!this->circle)
	{
		cv::rectangle(image, cv::Point(this->x, this->y), cv::Point(this->x + this->size, this->size), this->color, border);
	}
	else
	{
		cv::circle(image, cv::Point(this->x, this->y), this->size / 2, this->color, border);
	}
}