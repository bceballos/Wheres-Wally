#include "BC_RefImage.h"
#include <algorithm>

RefImage::RefImage() {

}

double RefImage::Compare(LargeImage* largeTemp, int offsetX, int offsetY) { //Comparison
	double ssd = 0.0;
	
	for (int y = 0; y < this->getHeight(); y++) { //Iterate through the size of the reference image
		for (int x = 0; x < this->getWidth(); x++) {
			double largeValue = largeTemp->getValue(x + offsetX, y + offsetY); //Get value of pixel from the largeImage matrix
			double refValue = this->getValue(x, y); //Get value of pixel from refimage matrix
	
			if (refValue != 255) {
				ssd += pow((largeValue - refValue), 2.0); //calculate Sum of Square difference
			}
		}
	}
	
	return ssd; //return Sum of Square difference
}