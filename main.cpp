#include"raylib.h"
#include <vector>
#include <random>

//visual bubble sort using Raylib

using namespace std;
int vecMax(std::vector<int> &v, int size);
bool bubblesort(std::vector<int>& v, int size, int maxSize);
void sleep();
Color chooseColor(int curr, int toSwap, int stopSwap, int size);


enum screenSize : int {width = 800,  height = 600, recWid = 10};

int main()
{
	int size = 40, maxSize, k = 0;
	bool exit = false;
	std::vector<int> v(size);
	auto func = []() {
		return rand() % 150;
	};
	std::generate(v.begin(), v.end(), func);		//put random values in the vector
	
	maxSize = vecMax(v, size);			//cheack for max value in vector
	
	InitWindow(screenSize::width, screenSize::height, "sortArray");
	SetTargetFPS(80);

	while (!WindowShouldClose() && !exit)
	{
		BeginDrawing();
		ClearBackground(BLACK);
		if (IsKeyPressed(KEY_SPACE))
		{
			exit = bubblesort(v, size, maxSize);
			std::generate(v.begin(), v.end(), func);	//put random values in the vector
		}

		for(k = 0; k < size; ++k)
			DrawRectangle((screenSize::width - 20) / size * (k + 1), screenSize::height - v[k] * (screenSize::height / maxSize), screenSize::recWid, v[k] * (screenSize::height / maxSize), WHITE);

		DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
//make a delay
void sleep()
{
	double time = GetTime() + 3;
	while (time > GetTime()) {}
}

bool bubblesort(std::vector<int> &v, int size, int maxSize)
{
	int i, j, k;
	Color color = WHITE;
	for (i = 0; i < size - 1; ++i)
		for (j = 0; j < size - i - 1; ++j)
		{
			if (v[j] > v[j + 1])
				swap(v[j], v[j + 1]);
			
			if (WindowShouldClose())	//to exit the program
				return true;

			BeginDrawing();
			ClearBackground(BLACK);
			for (k = 0; k < size ; ++k)	//draw change
			{
				DrawFPS(10, 10);
				color = chooseColor(k, j, i, size);
				DrawRectangle((screenSize::width - 20) / size * (k + 1), screenSize::height - v[k] * (screenSize::height / maxSize), screenSize::recWid, v[k] * (screenSize::height / maxSize), color);
			}
			EndDrawing();
		}
	sleep();
	return false;
}
//return a diffrent color for the rectangles
Color chooseColor(int curr, int toSwap, int stopSwap, int size)
{
	if (curr == toSwap || curr == toSwap + 1)		//rectangles that are currently compared
		return RED;
	else if (curr > size - stopSwap - 1)		//rectangles that are than with the sort
		return GREEN;
	return WHITE;
}
//return the max value in a vector
int vecMax(std::vector<int> &v, int size)
{
	int max = v[0];

	for (int i = 1; i < size; ++i)
	{
		if (v[i] > max)
			max = v[i];
	}
	return max;
}