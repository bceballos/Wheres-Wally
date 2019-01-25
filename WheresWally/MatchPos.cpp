#include "BC_MatchPos.h"

MatchPos::MatchPos() {

}

MatchPos::MatchPos(int x, int y, double ssd) {
	this->x = x;
	this->y = y;
	this->ssd = ssd; //SSD VALUE
}