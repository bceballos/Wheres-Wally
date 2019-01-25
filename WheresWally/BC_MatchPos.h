#ifndef matchPosition
#define matchPosition

#include "BC_Image.h"

class MatchPos {
public:
	int x, y;
	double ssd;

	MatchPos();
	MatchPos(int x, int y, double ssd);
	~MatchPos()
	{

	}

	bool operator == (MatchPos& temp) {
		return this->ssd == temp.ssd;
	}
};

#endif // !matchPosition

