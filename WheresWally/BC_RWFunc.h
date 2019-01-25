#ifndef rwFunc
#define rwFunc

#include <string>
#include "BC_RWFunc.h"

class RWFunc {
public:
	double* readText(std::string fileName, int height, int width);
	void writePgm(std::string fileName, double *data, int height, int width, int Q);
};

#endif
