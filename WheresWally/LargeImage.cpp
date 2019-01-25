#include "BC_LargeImage.h"

void LargeImage::CreateBorder(int xOffset, int yOffset, int width, int height, int thickness, double color) {
	for (int x = 0; x < width; x++) { //Iterate around the border
		for (int y = 0; y < height; y++) {
			if (x < thickness || y < thickness || y + thickness >= height || x + thickness >= width) { //If it's within the thickness boundary - 3px inwards set the value of the cell to 0 for black border
				setValue(x + xOffset, y + yOffset, color);
			}
		}
	}
}