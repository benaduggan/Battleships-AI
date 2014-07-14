/**
 * @author Stefan Brandle
 * @date April, 2004
 * Lab 15: SmartPlayer AI
 *
 * Please type in your name[s] here:
 */

#include "PlayerV1.h"
#include "SmartPlayer.h"

using namespace std;

SmartPlayer::SmartPlayer( int boardSize ):
    PlayerV1(boardSize)
{
    lastRow = 0;
    lastCol = 1;
    cellCount = boardSize * boardSize;
    StepSize = 3;
}

/**
 * Gets the computer's shot choice. This is then returned to the caller.
 * @return int[] shot
 *  Position 0 of the int array should hold the row, position 1 the column.
 */
Message SmartPlayer::getMove( ) {
    if( board[lastRow][lastCol] == HIT ) {
	getFollowUpShot( lastRow, lastCol, shot );
    } else {
	getNextProbe( shot );
    }
    Message move( SHOT, shot[0], shot[1], "Take that!" );
    return move;
}

void SmartPlayer::getFollowUpShot( int lastRow, int lastCol, int shot[] ) {
    if( search( lastRow, lastCol, -1, 0, shot, 4 ) == true ) {	
	return;
    } else if ( search( lastRow, lastCol, 0, 1, shot, 4 ) == true ) {
	return;
    } else if ( search( lastRow, lastCol, 1, 0, shot, 4 ) == true ) {
	return;
    } else if ( search( lastRow, lastCol, 0, -1, shot, 4 ) == true ) {
	return;
    } else {
	getNextProbe( shot );
    }
}

bool SmartPlayer::search( int row, int col, int rowDelta, int colDelta, 
                             int shot[], int rangeLeft) 
{
    if( rangeLeft < 0 ) return false;	// Out of jumps
    if( row<0 || col<0 || row>=boardSize || col>=boardSize ) return false;	// Off board

    if( board[row][col] == MISS ) {	// Nobody out here -- stop
	return false;
    }
    else if( board[row][col] == WATER ) {	// Not shot at yet
	shot[0] = row; shot[1] = col;
	return true;
    } else if( search(row+rowDelta, col+colDelta, rowDelta, colDelta, shot, rangeLeft-1) ) {
	return true;
    }
    return false;
}

void SmartPlayer::getNextProbe( int shot[] ) {
    int loopCount = 0;
    while( board[lastRow][lastCol] != WATER && loopCount < cellCount ) {
	lastCol = lastCol + StepSize;
	if( lastCol >= boardSize ) {
	    lastCol = lastCol % boardSize;
	    // if boardSize is multiple of column, could get caught going down columns. 
	    // Adjust if needed.
	    if( boardSize % StepSize == 0 ) {	
		if( lastCol + 1 == StepSize ) {
		    lastCol = 0;
		} else {
		    lastCol++;
		}
	    }
	    lastRow++;
	}
	if( lastRow >= boardSize ) {
	    lastRow = 0;
	}
	loopCount++;
	if( loopCount >= cellCount ) {
	    StepSize = 1;
	    loopCount = 0;
	}
    }

    shot[0] = lastRow;
    shot[1] = lastCol;
}


/*
SmartPlayer.cpp:51: syntax error before `::' token
SmartPlayer.cpp:61: ISO C++ forbids declaration of `shot' with no type
SmartPlayer.cpp:61: `col' was not declared in this scope
SmartPlayer.cpp:62: syntax error before `return'
SmartPlayer.cpp: In member function `void SmartPlayer::getNextProbe(int*)':
SmartPlayer.cpp:91: assignment of read-only variable `SmartPlayer::StepSize'

*/
