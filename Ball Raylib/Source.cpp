#include"raylib.h"
#include<cstdlib>
#include<time.h>
using namespace std;

class Ball {
private:
	float x, y, speedX, speedY, radius;
	Color color;
public:
	Ball();
	Ball(float x, float y, float speedX, float speedY, float radius, Color color);

	void setX(float x);
	void setY(float y);
	void setSpeedX(float speedX);
	void setSpeedY(float speedY);
	float getX();
	float getY();
	float getSpeedX();
	float getSpeedY();

	void SetBall(float x, float y, float speedX, float speedY, float radius, Color color);
	void Draw();
};

Ball::Ball() { };

Ball::Ball(float x, float y, float speedX, float speedY, float radius, Color color)
	: x(x), y(y), speedX(speedX), speedY(speedY), radius(radius), color(color) { }

void Ball::setX(float x) { this->x = x; }
void Ball::setY(float y){	this->y = y; }
void Ball::setSpeedX(float speedX) { this->speedX = speedX; }
void Ball::setSpeedY(float speedY){ this->speedY = speedY; }
float Ball::getX() { return x; }
float Ball::getY() { return y; }
float Ball::getSpeedX() { return speedX; }
float Ball::getSpeedY() { return speedY; }

void Ball::SetBall(float x, float y, float speedX, float speedY, float radius, Color color)
{
	this->x = x;
	this->y = y;
	this->speedX = speedX;
	this->speedY = speedY;
	this->radius = radius;
	this->color = color;
}

void Ball::Draw() { DrawCircle(x, y, radius, color); }


//Global Const Variables
//-----------------------------------------
const int numBalls = 1000;
Ball balls[numBalls];

const int screenWidth = 1200;
const int screenHeight = 800;
//-----------------------------------------

void SetUp()
{
	InitWindow(screenWidth, screenHeight, "Random Ball");
	SetWindowState(FLAG_VSYNC_HINT);
	srand(time(0));
	for (int i = 0; i < numBalls; i++)
	{
		Color color{ (int)(rand() % 255), (int)(rand() % 255), (int)(rand() % 255), (int)(rand() % 255) };
		balls[i].SetBall(rand() % GetScreenWidth(), rand() % GetScreenHeight(), rand() % 300 + 100, rand() % 300 + 100, rand() % 10 + 5, color);
		int poss = rand() % 4;
		if (poss == 0)
			balls[i].setSpeedX(balls[i].getSpeedX() * -1);
		else if (poss == 1)
			balls[i].setSpeedY(balls[i].getSpeedY() * -1);
	}
}

void Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	for (int i = 0; i < numBalls; i++)
	{
		balls[i].Draw();
	}
	EndDrawing();
}

void Input()
{

}

void Logic()
{
	for (int i = 0; i < numBalls; i++)
	{
		balls[i].setX(balls[i].getX() + balls[i].getSpeedX() * GetFrameTime());
		balls[i].setY(balls[i].getY() + balls[i].getSpeedY() * GetFrameTime());
	}
	for (int i = 0; i < numBalls; i++)
	{
		if (balls[i].getX() > GetScreenWidth())
		{
			balls[i].setX(GetScreenWidth());
			balls[i].setSpeedX(balls[i].getSpeedX() * -1);
		}
		else if (balls[i].getX() < 0)
		{
			balls[i].setX(0);
			balls[i].setSpeedX(balls[i].getSpeedX() * -1);
		}

		if (balls[i].getY() > GetScreenHeight())
		{
			balls[i].setY(GetScreenHeight());
			balls[i].setSpeedY(balls[i].getSpeedY() * -1);
		}
		else if (balls[i].getY() < 0)
		{
			balls[i].setY(0);
			balls[i].setSpeedY(balls[i].getSpeedY() * -1);
		}
	}
}

int main()
{
	SetUp();
	while (!WindowShouldClose())
	{
		Draw();
		Input();
		Logic();
	}
	CloseWindow();

	return 0;
}