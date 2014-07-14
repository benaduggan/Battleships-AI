/**
 * @author Stefan Brandle, Jonathan Geisler
 * @date September, 2004
 *
 * Please type in your name[s] here:
 * Benjamin Duggan, Brandon Hoeksema
 */
#ifndef THEWHITEPERL_H		// Double inclusion protection
#define THEWHITEPERL_H
#include "PlayerV1.h"

using namespace std;

class thewhiteperl: public PlayerV1 {
    public:
	thewhiteperl( int boardSize );
	Message getMove();
	Message offHit(int lastRow,int lastCol);
	bool search(int row, int col, int rowDelta, int colDelta, int rangeLeft,int shot[2]);
	int side(int lastRow, int lastCol, int direction);
	Message offMissOrKill();

    private:
        int lastRow;
        int lastCol;
};
#endif