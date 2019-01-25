#ifndef image
#define image

class Image {
public:
	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	double** getMatrix();
	double getValue(int x, int y);
	virtual void setValue(int x, int y, double value); //Set to virtual so that other classes may override it such as LargeImage class if passed a 1D array with no conversion

	Image& operator+=(const Image& temp);
	Image& operator-=(const Image& temp);
	Image& operator*=(const Image& temp);
	Image* operator=(const Image& temp);
	friend Image operator+(Image first, const Image& second);
	friend Image operator-(Image first, const Image& second);
	friend Image operator*(Image first, const Image& second);

	Image();
	Image(int width, int height);
	Image(int width, int height, double** matrix);


protected:
	double** matrix;

private:
	int width, height;

};

#endif