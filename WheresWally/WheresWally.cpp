#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <time.h>

//To Do:
/*	Main:
	Search - Search the large image matrix by using the reference image matrix ontop
		   - Take Large Image, Reference Image, number of matches
		   - Create a vector of matches
		   - loop through the large image - width of reference
		   - Compare images
		   - Add the item to the match list
		   - Sort the match list
		   - Push out the last match
		   - Loop through match list and add a black border to the edge
	Compare - Compare submatrix to reference matrix
			- Loop through get the value from large matrix, get the value from reference matrix
			- If matrix value is less than 255 calculate the variance using square sum difference
			- Return the variance
	Sort - Sort the matrix
		 - Merge sor the match list
	Convert - array to matrix
			- matrix to array
	Read Image
	Write Image
*/

/*	Image:
	width, height, length (width*height)
	Get Matrix by index, and x and y position
	Set Matrix by index, and x and y position

	constructors - take width, height, double* []

	operator overloads

	deconstructor - delete matrix

	protected - double matrix


*/

/*	Match:
	contains offsets of the match
	contains value of accuracy
*/

/*	Reference Image:
	inherit Image:
	offeset from main matrix x, y
	user operator overloads

	inherits: constructors, deconstructors and operator overloads

*/

/*	Large Image:

	Create Sub Matrix - takes offsets, width and height

	inherits: constructors, deconstructors and operator overloads

*/


#include "BC_Image.h" //Includes of header files
#include "BC_LargeImage.h"
#include "BC_RefImage.h"
#include "BC_RWFunc.h"
#include "BC_MatchPos.h"

//Sizes of the images
#define LARGE_IMG_WIDTH 1024 
#define LARGE_IMG_HEIGHT 768
#define REF_IMG_WIDTH 36
#define REF_IMG_HEIGHT 49
//File paths
#define INPUT_LARGE_PATH "input/Cluttered_scene.txt" 
#define INPUT_REF_PATH "input/Wally_grey.txt"
#define OUTPUT_IMG_PATH "output/Wally_found.pgm"

double** ConvertToMatrix(double* file, int width, int height) {
	double** tempMatrix = new double*[height]; //Create array of pointers

	int length = width * height; 
	for (int i = 0; i < height; i++) { //For each array element defined by the height create an array inside of that element with size width
		tempMatrix[i] = new double[width];
	}

	for (int y = 0; y < height; y++) { //Convert the 1D array to the 2D array by setting each element of the 1D array to a cell in the matrix
		for (int x = 0; x < width; x++) {
			tempMatrix[y][x] = file[((width * y) + x)];
		}
	}

	return tempMatrix; // Return the matrix
}

double* ConvertToFile(double** matrix) {
	double* tempFile = new double[LARGE_IMG_WIDTH * LARGE_IMG_HEIGHT]; //Create a 1D array of size equal to width * length of the large iamge
	for (int y = 0; y < LARGE_IMG_HEIGHT; y++) { //Iterate through the matrix
		for (int x = 0; x < LARGE_IMG_WIDTH; x++) {
			tempFile[(LARGE_IMG_WIDTH * y) + x] = matrix[y][x]; //Put matrix elements into 1D array in order
		}
	}

	return tempFile; //Return 1D array
}

void Sort(std::vector<MatchPos>& matchList) {
	int i, j; //Create i and j
	MatchPos item; //Create MatchPos item

	for (i = 1; i < matchList.size(); i++) { //Foreach element in the match list
		item = matchList.at(i); //Set temp element equal to second element
		j = i - 1; //J is previous element

		while (j >= 0 && matchList.at(j).ssd > item.ssd) { //Move element back until it's in order
			matchList.at(j + 1) = matchList.at(j);
			j = j - 1;
		}

		matchList.at(j + 1) = item;
	}
}

std::vector<MatchPos> Search(LargeImage* largeTemp, RefImage* refTemp, int matches) {
	std::vector<MatchPos> matchList; //Create matchlist
	MatchPos newMatch; //Create temporary match item

	double ssd = 0.0; //Square Sum Difference

	for (int y = 0; y < largeTemp->getHeight() - refTemp->getHeight(); y+=3) { //Loop through the entire image subtracting the reference image size so that it doesn't go over the edge and cause an error
		for (int x = 0; x < largeTemp->getWidth() - refTemp->getWidth(); x+=3) {
			ssd = refTemp->Compare(largeTemp, x, y); //Call compare to calculate Square sum difference
			if ((matchList.size() > 1) && matchList.back().ssd < ssd) { //If the match list has at least 1 element, if the current SSD is less than the ssd of the last element in the match list skip over the rest
				continue;
			}
			newMatch = MatchPos(x, y, ssd); //Create a new match

			matchList.push_back(newMatch); //Push it

			if (matchList.size() > matches) { //If there are more matches than needed, sort the list, erase the worst one
				Sort(matchList);
				matchList.erase(matchList.begin() + matches);
			}
		}
	}

	return matchList; //Return list of matches
}



int main()
{
	int matches = 0; //Quantity of matches
	int thickness = 3; //Thickness of the border of the matches
	RWFunc iofiles;

	double* largeImageData = iofiles.readText(INPUT_LARGE_PATH, LARGE_IMG_HEIGHT, LARGE_IMG_WIDTH); //Read the data from the Cluttered_wally.txt
	double* refImageData = iofiles.readText(INPUT_REF_PATH, REF_IMG_HEIGHT, REF_IMG_WIDTH); //Read the data from the Wally_grey.txt

	std::cout << "Enter the number of matches you would like to find: " << std::endl;  //Get user input for the amount of matches you want, loop if what they have entered isn't an int
	while (!(std::cin >> matches) || matches <= 0) {
		std::cout << "Please enter a valid number of matches: " << std::endl;
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
	}

	LargeImage* largeTemp = new LargeImage(LARGE_IMG_WIDTH, LARGE_IMG_HEIGHT, ConvertToMatrix(largeImageData, LARGE_IMG_WIDTH, LARGE_IMG_HEIGHT)); //Initiate LargeImage class with passed matrix and sizes
	RefImage* refTemp = new RefImage(REF_IMG_WIDTH, REF_IMG_HEIGHT, ConvertToMatrix(refImageData, REF_IMG_WIDTH, REF_IMG_HEIGHT)); //Initiate RefImage class with passed matrix and sizes

	std::chrono::system_clock::time_point start; //Initiate the timer
	start = std::chrono::system_clock::now(); //Set start point
	std::vector<MatchPos> listOMatches = Search(largeTemp, refTemp, matches); //Begin searching through largeTemp using refTemp for matches
	auto end = std::chrono::system_clock::now(); //Set end point

	for (auto match : listOMatches) { //For each match
		largeTemp->CreateBorder(match.x, match.y, REF_IMG_WIDTH, REF_IMG_HEIGHT, thickness, 0.0); //Go into largeTemp and create a border around them
		if (listOMatches[0] == match) { //First element in list of matches is best match due to it's low SSD or "accuracy"
			std::cout << match.x << "," << match.y << " : WALLY " << std::endl;
		}
		else { //Output the rest
			std::cout << match.x << "," << match.y << std::endl;
		}
	}
	std::chrono::duration<float, std::milli> span = end - start; //Calculate how long it's taken to search
	std::cout << "It took: " << span.count() / 1000 << " seconds to find " << matches << " matches" << std::endl; //Output the duration of the search
	iofiles.writePgm(OUTPUT_IMG_PATH, ConvertToFile(largeTemp->getMatrix()), LARGE_IMG_HEIGHT, LARGE_IMG_WIDTH, 255); //Write the pgm

	delete largeTemp; //Delete the pointers which deletes the matrix
	delete refTemp;

}
