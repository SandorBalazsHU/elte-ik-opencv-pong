#ifndef PONG_H
#define PONG_H
class Ball 
{
	public:
		Ball();
	private:
		int x = 0;
		int y = 0;
		int size = 20;
		bool fill = true;
		bool circle = true;
};
#endif