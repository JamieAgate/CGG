#include <cmath>
#include "CGG_Main.h"
#include <glm.hpp>
#include <iostream>

float lerp(float _a, float _b, float _t)
{
	return ((1.0f - _t)*_a)+(_t*_b);
}

glm::vec2 veclerp(glm::vec2 _a, glm::vec2 _b, float _t)
{
	return ((1.0f - _t)*_a)+(_t*_b);
}

glm::vec2 curvelerp(glm::vec2 _a, glm::vec2 _b, glm::vec2 _c, float _t)
{
	return (pow((1-_t),2)*_a) + (2*_t*_c*(1-_t))+(pow(_t,2)*_b);
}

void curve(glm::vec2 _a, glm::vec2 _b, glm::vec2 _c)
{
	float len = length(_a -_b);
	for(int i = 0; i < len; i++)
	{
		glm::vec2 coord = curvelerp(_a,_b,_c,i/len);

		CGG::DrawPixel(coord.x, coord.y, 255, 0, 0);
	}
}

void line(glm::vec2 _a, glm::vec2 _b)
{
	float dist = length(_a-_b);
	for (int i =0; i < dist; i++)
	{
		float x = lerp(_a.x, _b.x, i/dist);
		float y = lerp(_a.y, _b.y, i/dist);

		CGG::DrawPixel( x, y, 255, 0, 0 );
	}

}

void square(glm::vec2 _a, float _sideLength)
{
	glm::vec2 b(_a.x, _a.y+_sideLength);
	glm::vec2 c(_a.x+_sideLength, _a.y);
	glm::vec2 d(c.x, c.y+_sideLength);

	line(_a,b);
	line(b,d);
	line(d,c);
	line(c,_a);
}

void triangle(glm::vec2 _a, glm::vec2 _b, glm::vec2 _c)
{
	line(_a,_b);
	line(_b,_c);
	line(_c,_a);
}

void circle(glm::vec2& center, float radius)
{
	for(int currentx = center.x - radius; currentx < (center.x + radius); currentx++)
	{
		for(int currenty = center.y- radius; currenty < center.y + radius; currenty++)
		{
			glm::vec2 currentVec(currentx, currenty);
			int dist = length(currentVec - center);
			if (dist < radius)
			{
				
				CGG::DrawPixel(currentx, currenty,255 , 0 , 0);
			}
		}
	}
}

void rotateZ3D(float _theta, glm::vec3 *_nodes[8])
{
	float sint = sin(_theta);
	float cost = cos(_theta);
	int result[2];
	for (int n = 0; n < 8; n++)
	{
		glm::vec3 node = *_nodes[n];
		int x = node.x;
		int y = node.y;
		node.x = x * cost - y * sint;
		node.y = y * cost + x * sint;

		*_nodes[n] = node;
	}
}

void rotateY3D(float _theta, glm::vec3* _nodes[8])
{
	float sint = sin(_theta);
	float cost = cos(_theta);

	for (int n = 0; n < 8; n++)
	{
		glm::vec3 node = *_nodes[n];
		int x = node.x;
		int y = node.z;
		node.x = x * cost - y * sint;
		node.z = y * cost + x * sint;

		*_nodes[n] = node;
	}
}

void rotateX3D(float _theta, glm::vec3* _nodes[8])
{
	float sint = sin(_theta);
	float cost = cos(_theta);

	for (int n = 0; n < 8; n++)
	{
		glm::vec3 node =* _nodes[n];
		int x = node.y;
		int y = node.z;
		node.y = x * cost - y * sint;
		node.z = y * cost + x * sint;

		*_nodes[n] = node;
	}
}

void cube()
{
	glm::vec3 node0(100, 100, 100);
	glm::vec3 node1(100, 100, 300);
	glm::vec3 node2(100, 300, 100);
	glm::vec3 node3(100, 300, 300);
	glm::vec3 node4(300, 100, 100);
	glm::vec3 node5(300, 100, 300);
	glm::vec3 node6(300, 300, 100);
	glm::vec3 node7(300, 300, 300);
	glm::vec3 nodes[8] = { node0,node1, node2, node3, node4, node5, node6, node7 };

	glm::vec2 edge0(0, 1);
	glm::vec2 edge1(1, 3);
	glm::vec2 edge2(3, 2);
	glm::vec2 edge3(2, 0);
	glm::vec2 edge4(4, 5);
	glm::vec2 edge5(5, 7);
	glm::vec2 edge6(7, 6);
	glm::vec2 edge7(6, 4);
	glm::vec2 edge8(0, 4);
	glm::vec2 edge9(1, 5);
	glm::vec2 edge10(2, 6);
	glm::vec2 edge11(3, 7);
	glm::vec2 edges[12] = { edge0,edge1, edge2, edge3, edge4, edge5, edge6, edge7, edge8, edge9, edge10, edge11 };
	while (CGG::ProcessFrame())
	{
		CGG::SetBackground(0, 0, 0);
		for (int n = 0; n < (sizeof(edges)/8); n++)
		{
			glm::vec2  n0 = edges[n];
			int a = n0.x;
			int b = n0.y;
			glm::vec2 node0 = nodes[a];
			glm::vec2 node1 = nodes[b];
			line(node0, node1);
		}

		float sint = sin(30);
		float cost = cos(30);
	
		for (int n = 0; n < 8; n++)
		{
			glm::vec3 node = nodes[n];
			float y = node.y;
			float z = node.z;
			node.y = y * cost - z * sint;
			node.z = z * cost + y * sint;

			nodes[n] = node;
		}

		for (int n = 0; n < 8; n++)
		{
			glm::vec3 node = nodes[n];
			float x = node.x;
			float z = node.z;
			node.x = x * cost - z * sint;
			node.z = z * cost + x * sint;

			nodes[n] = node;
		}

		for (int n = 0; n < 8; n++)
		{
			glm::vec3 node = nodes[n];
			float x = node.x;
			float y = node.y;
			node.x = x * cost - y * sint;
			node.y = y * cost + x * sint;

			nodes[n] = node;
		}
		//system("PAUSE");
	}
}

int main(int argc, char *argv[])
{
	// Variables for storing window dimensions
	int windowWidth = 640;
	int windowHeight = 480;

	// Call CGG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if( !CGG::Init( windowWidth, windowHeight ) )
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	// Sets every pixel to the same colour
	// parameters are RGBA, numbers are from 0 to 255
	CGG::SetBackground( 0,0,0 );

	// Preparing a position to draw a pixel
	int pixelX = windowWidth / 2;
	int pixelY = windowHeight / 2;

	// Preparing a colour to draw
	int red = 255;
	int green = 0;
	int blue = 0;

	
	// Draws a single pixel at the specified coordinates in the specified colour!
	glm::vec2 a(pixelX,pixelY);
	glm::vec2 b(0,0);
	glm::vec2 c(200,300);
	glm::vec2 d(100, 100);
	glm::vec2 e(500, 300);
	glm::vec2 f(640,480);
	glm::vec2 g(140,180);
	//circle(e,40);
	//line(a,b);
	//square(a, 50);
	//triangle(a,c,d);
	//curve(a,b,e);
	//curve(a,f,g);

	// Do any other DrawPixel calls here
	// ...

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	//return CGG::ShowAndHold();

	
	
	// Advanced access - comment out the above DrawPixel and CGG::ShowAndHold lines, then uncomment the following:

	
	// Variable to keep track of time
	float timer = 0.0f;

	// This is our game loop
	// It will run until the user presses 'escape' or closes the window
	while( CGG::ProcessFrame() )
	{
		// Set every pixel to the same colour
		CGG::SetBackground( 0,0,0 );
		
		// Change our pixel's X coordinate according to time
		//pixelX = (windowWidth / 2) + (int)(sin(timer) * 100.0f);
		// Update our time variable
		//timer += 1.0f / 60.0f;
		cube();
		// Draw the pixel to the screen
		//CGG::DrawPixel( pixelX, pixelY, red, green, blue );

	}
	
	return 0;
	
}