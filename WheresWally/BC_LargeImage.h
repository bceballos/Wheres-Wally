#ifndef largeImage
#define largeImage

#include "BC_Image.h"

class LargeImage : public Image {
public:
	void CreateBorder(int xOffset, int yOffset, int width, int height, int thickness, double color);

	using Image::Image;
	using Image::operator+=;
	using Image::operator-=;
	using Image::operator*=;
	using Image::operator=;

	LargeImage()
	{

	}
	LargeImage(int width, int height, double* matrix);

	~LargeImage()
	{

	}

};

#endif