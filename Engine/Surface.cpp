#include "Surface.h"
#include <assert.h>
Surface::Surface(const std::string& filename,unsigned int width_s,unsigned int height_s)
{

        std::vector<unsigned char> image; //the raw pixels
      
        //decode
        unsigned error = lodepng::decode(image, width_s, height_s, filename);
        width = static_cast<int>(width_s);
        height = static_cast<int>(height_s);
        pixels = new Color[width * height];

        //if there's an error, display it
        if (error) { std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl; }
        else {
          int size=image.size()/4;
          int i = 0;
          for (int y =0; y <height; y++) {
              for (int x = 0; x < width; x++) {
                  PutPixel(x, y, Colors::MakeRGB(image[i], image[i + 1], image[i + 2]));
                  i = i + 4;
              }
          }
        }

        //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
   }

Surface::Surface()
{
    pixels = new Color[0];    
}


void Surface::PutPixel(int x, int y, Color c)
{
    assert(x >= 0);
    assert(x < width);
    assert(y >= 0); 
    assert(y < height);
    pixels[y *  width + x] = c;
}

Color  Surface::GetPixel(int x, int y) const
{
    assert(x >= 0);
    assert(x < (int)width);
    assert(y >= 0);
    assert(y < (int) height);
    return  pixels[y * width + x];
}

int Surface::GetWidth() const
{
    return (int)width;
}

int Surface::GetHeight() const
{
    return (int) height;
}

Surface::~Surface()
{
    delete [] pixels;
   
}

void  Surface::AssignPixels(Surface & surface,int right, int top, int left, int bottom)
{
    int sizeW = right - left;
    int sizeH = bottom - top;
    surface.pixels= new Color[sizeW * sizeH];
    surface.width = sizeW;
    surface.height = sizeH;
    for (int y = 0; y < sizeH; y++) {
        for (int x = 0; x < sizeW; x++) {
           surface.pixels[y * sizeW + x] = this->pixels[(top + y) * sizeW + (left + x)];
        }
    }
   
}
