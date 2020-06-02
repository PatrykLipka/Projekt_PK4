#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Vec2D.h"

class Font
{
public:
	Font(const std::string& filename, unsigned int width, unsigned int height, Color chroma = Colors::White);
	void DrawTexts(const std::string& text, const Vec2D& pos, Color color, Graphics& gfx) const;
private:
	Rect MapGlyphRect(char c) const;
private:
	Surface surface;
	int glyphWidth;
	int glyphHeight;
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	Color chroma;
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};