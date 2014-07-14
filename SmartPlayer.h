/**
 * @author Stefan Brandle
 * @date April, 2004
 * Lab 15: SmartPlayer AI
 *
 * Please type in your name[s] here:
 */

#ifndef SMARTPLAYER_H		// Double inclusion protection
#define SMARTPLAYER_H

#include "PlayerV1.h"

using namespace std;

class SmartPlayer: public PlayerV1 {
    public:
	SmartPlayer( int boardSize );
	virtual Message getMove( );

    private:
	// Local functions
	void getFollowUpShot( int lastRow, int lastCol, int shot[] );
	bool search( int row, int col, int rowDelta, int colDelta, int shot[], int rangeLeft);
	void getNextProbe( int shot[] );

	// Local data
        int lastRow;
        int lastCol;
        int StepSize;
        int cellCount;
        int shot[2];

};	// end of class SmartPlayer

#endif

