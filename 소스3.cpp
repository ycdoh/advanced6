#include <GLFW/glfw3.h>
#include<iostream>
#include <cstring>
#include <stdlib.h>    // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include<vector>
using namespace std;
#pragma once

class mypainter2D
{
public:
	GLFWwindow* window;
	float *pixels;
	const int width;// = 640;
	const int height;// = 480;



	mypainter2D() :width(640), height(480)//window(nullptr),pixels(nullptr)
	{
		//printf("asd");
		//printf("%d %d", width, height);
		pixels = new float[width*height * 3];

	}
	~mypainter2D() { if (pixels != nullptr)delete[] pixels; }
	void initalize()
	{	//init canvas	
		if (!glfwInit())
		{
			std::cout << "glfw warning<" << std::endl;
			exit(1);
		}

		window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			std::cout << "window warning" << std::endl;
			exit(1);
		}
		glfwMakeContextCurrent(window);
		//float* pixels = new float[width*height * 3];


		/*for(int i=0;i<width*height * 3;i++)
		pixels[i] = 1;*/


	}


	void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
	{
		pixels[(i + width* j) * 3 + 0] = red;
		pixels[(i + width* j) * 3 + 1] = green;
		pixels[(i + width* j) * 3 + 2] = blue;
	}
	void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
	{
		if (i0 == i1 && j1 != j0)
		{
			for (int j = j0; j <= j1; j++)
			{
				const int i = (i1 - i0)*(j - j0) / (j1 - j0) + i0;

				drawPixel(i, j, red, green, blue);
			}

		}


		else if (j1 == j0 && i0 != i1)
		{
			for (int i = i0; i <= i1; i++)
			{
				const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

				drawPixel(i, j, red, green, blue);
			}
		}

		else
		{
			for (int i = i0; i <= i1; i++)
			{
				const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

				drawPixel(i, j, red, green, blue);
			}

		}
	}



};
mypainter2D my_painter;
void drawOnPixelBuffer()
{
	std::fill_n(my_painter.pixels, my_painter.width*my_painter.height * 3, 1.0f);
}


class GeometricObjectinterface
{
public:
	virtual void draw() {}//= 0;
};



class circle//class circle
{


public:
	int mid_x, mid_y, r_size;
	float red, green, blue;


	circle() {}
	circle(int _mid_x, int _mid_y, int _r_size, float _red, float _green, float _blue) :
	mid_x(_mid_x),mid_y(_mid_y),r_size(_r_size),red(_red),green(_green),blue(_blue)
	{}
public:
	void draw()
	{
		mid_x = 300; mid_y = 300; r_size = 50; red = 0; green = 0; blue = 255;
		int num_segments = 360;
		for (int ii = 0; ii < num_segments; ii++)
		{
			float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

			float x = r_size * cosf(theta);//calculate the x component
			float y = r_size * sinf(theta);//calculate the y component

			my_painter.drawPixel(x + mid_x, y + mid_y, red, green, blue);//output vertex

		}
	}
};


class Box
{

public:
	int start_x, start_y;
	int end_x, end_y;
	float red, green, blue;

	Box() {}
	Box(int _start_x, int _start_y, int _end_x, int _end_y, float _red, float _green, float _blue)
	:start_x(_start_x), start_y(_start_y), end_x(_end_x), end_y(_end_y), red(_red), green(_green), blue(_blue) {}

	void draw()
	{
		start_x = 100; start_y = 100; end_x = 200; end_y = 200; red = 255; green = blue = 0;
		for (int i = start_y; i < end_y; i++)
			my_painter.drawLine(start_x, i, end_x, i, red, green, blue);
	}
};


template<class T>
class GeometricObjectcolor :public GeometricObjectinterface
{
public:
	virtual void draw()
	{
		T draw_circle_box;
		draw_circle_box.draw();
	}
};


int main(void)
{
	int i, j;
	my_painter.initalize();

	std::vector<GeometricObjectinterface*> obj_list;
	obj_list.push_back(new GeometricObjectcolor<Box>);
	obj_list.push_back(new GeometricObjectcolor<circle>);






	//return 0;
	/*for(i=0;i<my_painter.height;i++)
	for (j = 0; j<my_painter.width; j++)
	printf("%lf",my_painter.pixels[i+j*my_painter.width]);*/



	while (!glfwWindowShouldClose(my_painter.window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		drawOnPixelBuffer();


		for (auto itr : obj_list)
			itr->draw();


		/*for (i = 0; i < 2; i++)
		obj_list[i]->draw();*/
		glDrawPixels(my_painter.width, my_painter.height, GL_RGB, GL_FLOAT, my_painter.pixels);
		glfwSwapBuffers(my_painter.window);
		glfwPollEvents();

		//glfwGetCursorPos(my_painter.window, &xpos, &ypos);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
	glfwTerminate();

	return 0;
}
