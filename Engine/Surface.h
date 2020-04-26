#pragma once
#include "Colors.h"
#include <string>
#include <vector>
#include "lodepng.h"
#include <iostream>


class Surface
{
public:
	Surface(const std::string& filename, unsigned int width, unsigned int height);
	Surface();
	void PutPixel(int x, int y, Color c);
	Color GetPixel(int x, int y) const;
	int GetWidth() const;
	int GetHeight() const;
	~Surface();
	void AssignPixels(Surface& surface,int right, int top, int left, int bottom);
	
private:
	 Color * pixels=nullptr;
	 int width = 0;
	 int height = 0;
	 
};
