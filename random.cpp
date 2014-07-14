/**
 * @author Stefan Brandle, Jonathan Geisler
 * @date September, 2004
 *
 * Please type in your name[s] here:
 */

#include <iostream>

using namespace std;

#include "myplayer.h"

myplayer::myplayer( int boardSize ):
	PlayerV1(boardSize)
{
	//this->boardSize = boardSize;
	lastRow = 0;
	lastCol = 0;
}

/**
 * Gets the computer's shot choice. This is then returned to the caller.
 * @return Message The most important parts of the returned message are 
 * the row and column values. 
 * Position 0 of the int array should hold the row, position 1 the column.
 */
Message myplayer::getMove() {
	for(int x=0;x<boardSize;x++){
		for(int y=0;y<boardSize;y++){
			if(board[x][y]=='X'){
				return offHit(x,y);
			}
		}
	}
	return offMissOrKill();
}

Message myplayer::offMissOrKill() { 
	int boardCounter[boardSize][boardSize];
	for(int x=0;x<boardSize;x++){
		for(int y=0;y<boardSize;y++){
			boardCounter[x][y] = 0;
		}
	}
	for(int i=0; i<boardSize; i++) {
		for(int j=0; j<boardSize; j++) {
			if(board[i][j] == '~') {
				for(int k=3; k<6; k++) {
					for(int l=1; l<3; l++) {
						bool possible = true;
						for(int m=1; m<k; m++) {
							//if not on board or not water
							if(!(i + ((l == 1) ? m : 0) >= 0 && i + ((l == 1) ? m : 0)<boardSize && j + ((l == 2) ? m : 0) >= 0 &&  j + ((l == 2) ? m : 0)<boardSize) || board[i + ((l == 1) ? m : 0)][j + ((l == 2) ? m : 0)] != '~') {
								possible = false;
							}

						}
						if(possible) {
							//inside here need to add 1 for each of the positions not just the i j
							for(int m=0; m<k; m++) {
								boardCounter[i + ((l == 1) ? m : 0)][j + ((l == 2) ? m : 0)]++;
							}
							//boardCounter[i][j]++;
						}
					}
				}
			}
		}
	}

	int maxSoFar[2];
	maxSoFar[0]=0;
	maxSoFar[1]=0;
	for(int i=0; i<boardSize; i++) {
		for(int j=0; j<boardSize; j++) {
			//boardCounter not board
			if(boardCounter[i][j] > boardCounter[maxSoFar[0]][maxSoFar[1]]) {
				maxSoFar[0] = i;
				maxSoFar[1] = j;
			}
		}
	}
	lastRow=maxSoFar[0];
	lastCol=maxSoFar[1];
	Message result(SHOT,maxSoFar[0],maxSoFar[1],"Die!");
	return result; 
}

bool myplayer::search( int row, int col, int rowDelta, int colDelta, int rangeLeft) 
{
    cout<<"search"<<row<< "  " << col << endl;
    if( rangeLeft < 1 ) return false;	// Out of jumps
    if( row<0 || col<0 || row>=boardSize || col>=boardSize ) return false;	// Off board

    if( board[row][col] == '*' ) {	// Nobody out here -- stop
	return false;
    }
    else if( board[row][col] == '~' ) {	// Not shot at yet
	//shot[0] = row; shot[1] = col;
	return true;
    }
    else if ( board[row][col] == 'X' ) {
	lastRow+=rowDelta;
	lastCol+=colDelta;
        return search(row+rowDelta, col+colDelta, rowDelta, colDelta, rangeLeft-1);
    }
    return false;

}

/*
offhit
check if two X's in a row
if so, search both ends for water
if water, choose whicheve side has more open water first
if not two X's in a row, look around the current X and shoot whichever side has more open water
*/
Message myplayer::offHit(int lastRow,int lastCol) {
    if( search( lastRow-1, lastCol, -1, 0, 4 ) == true ) {	
	Message result(SHOT,lastRow-1,lastCol,"Die!");
    	cout<<"offhit"<<lastRow<< "  " << lastCol << endl;
	return result;
    } else if ( search( lastRow, lastCol+1, 0, 1, 4 ) == true ) {
    	cout<<"offhit"<<lastRow<< "  " << lastCol << endl;
	Message result(SHOT,lastRow,lastCol+1,"Die!");
	return result;
    } else if ( search( lastRow+1, lastCol, 1, 0, 4 ) == true ) {
    	cout<<"offhit"<<lastRow<< "  " << lastCol << endl;
	Message result(SHOT,lastRow+1,lastCol,"Die!");
	return result;
    } else if ( search( lastRow, lastCol-1, 0, -1, 4 ) == true ) {
    	cout<<"offhit"<<lastRow<< "  " << lastCol << endl;
	Message result(SHOT,lastRow,lastCol-1,"Die!");
	return result;
    } else {
	return offHit(lastCol,lastRow);
    }



	/*
	   if there is an X adjacent to this X make that the direction
	   then with that direction, determine which side is best (if either) to choose.
	   if neither are possible, do what you would have done if no adjacent X

	   bool horiz = false, vert = false;
	   for(int i=-1; i<2; i+=2) {
	   if(board[lastRow][lastCol+i] == 'X') { 
	   horiz = true;
	   }
	   if(board[lastRow+i][lastCol] == 'X') { 
	   vert = true;
	   }
	   }

	   if(horiz) {
		int right = 0, left = 0, inc = 1;
		bool stillRight = true, stillLeft = true;
		while(inc < 5) {
			if(board[lastRow][lastCol+inc] == '~' && stillRight) {
				right++;
			} else {
				stillRight = false;
			}
			if(board[lastRow][lastCol-inc] == '~' && stillLeft) {
				left++;
			} else {
				stillLeft = false;
			}
			inc++;
		}
		if(right > left) {
			for(int i=1; i<5; i++) {
				if(board[lastRow][lastCol+i] == '~') {
					Message result(SHOT,lastRow,lastCol+i,"Die!");
					return result;
				}
			}
		} else if(!(left == 0 && right == 0)) {
			for(int i=1; i<5; i++) {
				if(board[lastRow][lastCol-i] == '~') {
					Message result(SHOT,lastRow,lastCol-i,"Die!");
					return result;
				}
			}		
		}
	   } else if(vert) {
		//same code just some minor alterations
	   }

	   run other code

	int top = 0, left = 0, right = 0, down = 0;
	int increment = 1;
	//n = size of board
	//has to be 2 open at least, if not not possible

	//if it finds a hit next to hit, extend that path



	while(lastRow+increment < boardSize && board[lastRow+increment][lastCol] == '~') {
		down++;
		increment++;
	}
	increment=1;
	while(lastRow-increment >= 0 && board[lastRow-increment][lastCol] == '~') {
		top++;
		increment++;
	}
	increment=1;
	while(lastCol+increment < boardSize && board[lastRow][lastCol+increment] == '~') {
		right++;
		increment++;
	}
	increment=1;
	while(lastCol-increment >= 0 && board[lastRow][lastCol-increment] == '~') {
		left++;
		increment++;
	}
	if(down>top && down>left && down>right){
		Message result(SHOT,lastRow+1,lastCol,"Die!");
		lastRow++;
		if(board[lastRow][lastCol] == 'X') {
			return offHit(lastRow,lastCol);
		}
		if(board[lastRow][lastCol] != '~') {
		}
		return result; 
	}
	else if(top>left && top>right){
		Message result(SHOT,lastRow-1,lastCol,"Die!");
		lastRow--;
		if(board[lastRow][lastCol] == 'X') {
			return offHit(lastRow,lastCol);
		}
		return result; 
	}
	else if(left>right){
		Message result(SHOT,lastRow,lastCol-1,"Die!");
		lastCol--;
		if(board[lastRow][lastCol] == 'X') {
			return offHit(lastRow,lastCol);
		}
		return result; 
	}
	else{
		Message result(SHOT,lastRow,lastCol+1,"Die!");
		lastCol++;
		if(board[lastRow][lastCol] == 'X') {
			return offHit(lastRow,lastCol);
		}
		return result; 
	}
*/
}
