#include "BC_Image.h"
#include <iostream>
/*

	int width, height, length;
	void getValue(int x, int y);
	void getValue(int x, int y);

	Image operator+=(const Image image);
	Image operator-=(const Image image);
	Image operator*=(const Image image);
	Image operator=(const Image image);
	friend Image operator+(Image first, const Image second);
	friend Image operator-(Image first, const Image second);
	friend Image operator*(Image first, const Image second);

	Image(int width, int height, double* matrix);
	~Image();

*/

double** Image::getMatrix() { //Return the matrix
	return matrix;
}

double Image::getValue(int x, int y) { //Return value from the matrix
	return matrix[y][x];
}

void Image::setValue(int x, int y, double value) { //Set value in the matrix
	matrix[y][x] = value;
}

Image::Image() {
}

Image::Image(int width, int height, double** matrix) { //Constructor from given width, height and matrix
	this->width = width;
	this->height = height;
	this->matrix = matrix;
}

Image::Image(int width, int height) { //Constructor from given width and height
	this->width = width;
	this->height = height;
	this->matrix = new double*[this->height];
	for (int i = 0; i < this->height; i++)
		matrix[i] = new double[width];
}

Image operator+(Image first, const Image& second) { //Operator overloads
	first += second; 
	return first;
}

Image operator-(Image first, const Image& second) {
	first -= second;
	return first;
}

Image operator*(Image first, const Image& second) {
	first *= second;
	return first;
}

Image & Image::operator+=(const Image& temp)
{
	Image holder = Image(this->width + temp.width, temp.height); //Create temporary holder

	for (int i = 0; i < this->height; i++) { //Iterate through the height and width of the matrix
		for (int j = 0; j < this->width; j++) { 
			holder.setValue(i, j, this->matrix[i][j]); //Set value at i j of holder equal to i j of this matrix
		}
		for (int j = 0; j < temp.width; j++) { //Set value at i j + offset amount equal to i j of other matrix
			holder.setValue(i, j+this->width, temp.matrix[i][j]);
		}
	}

	return holder; //Returns concatenated matrix
}

Image & Image::operator-=(const Image & temp) //Subtract values between matricies
{
	Image holder = Image(temp.width, temp.height); //Create holder

	for (int i = 0; i < temp.height; i++) {
		for (int j = 0; j < temp.width; j++) {
			holder.setValue(j, i, this->matrix[i][j] - temp.matrix[i][j]); //Set the values equal to subtraction of two matricies
		}
	}

	return holder; //Return subtracted matrix
}

Image & Image::operator*=(const Image & temp) //Multiplies the matricies
{
	double matrixValue = 0;

	Image holder = Image(temp.width, this->height); //Set matrix equal to opposites

	for (int i = 0; i < temp.width; i++) { //Iterate through the other matrix
		for (int j = 0; j < temp.height; j++) {
			matrixValue = 0;

			for (int k = 0; k < this->width; k++) {
				matrixValue += this->matrix[j][k] + temp.matrix[k][i]; //The value is the addition of all the values
			}

			holder.setValue(i, j, matrixValue); //Set the value
		}
	}

	return holder;
}

Image* Image::operator=(const Image & temp) { //Set one matrix equal to the other one
	this->width = temp.width;
	this->height = temp.height;
	this->matrix = temp.matrix;

	return this;
}
