/**
 * @author Stefan Brandle, Jonathan Geisler
 * @date September, 2004
 *
 * Please type in your name[s] here:
 * Ben Duggan, Brandon Hoeksema
 */

#include <iostream>
#include "thewhiteperl.h"

using namespace std;

thewhiteperl::thewhiteperl( int boardSize ):
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
Message thewhiteperl::getMove() {
	for(int x=0;x<boardSize;x++){
		for(int y=0;y<boardSize;y++){
			if(board[x][y]=='X'){
				return offHit(x,y); //if there is a hit on the board
			}
		}
	}
	return offMissOrKill();
}

Message thewhiteperl::offMissOrKill() { 
	int boardCounter[boardSize][boardSize];
	for(int x=0;x<boardSize;x++){
		for(int y=0;y<boardSize;y++){
			boardCounter[x][y] = 0;
		}
	}
	for(int i=0; i<boardSize; i++) { //for every row
		for(int j=0; j<boardSize; j++) { // for ever col
			if(board[i][j] == '~') { // if its water
				for(int k=3; k<6; k++) { //for every size of ship
					for(int l=1; l<3; l++) { // for every orientation
						bool possible = true;
						for(int m=1; m<k; m++) { 
							//if not on board or not water
							if(!(i + ((l == 1) ? m : 0) >= 0 && i + ((l == 1) ? m : 0)<boardSize && j + ((l == 2) ? m : 0) >= 0 &&  j + ((l == 2) ? m : 0)<boardSize) || board[i + ((l == 1) ? m : 0)][j + ((l == 2) ? m : 0)] != '~') {
								possible = false;
							}

						}
						if(possible) {
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

	int maxSoFar[2]; //the most probable shot
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

bool thewhiteperl::search(int row, int col, int rowDelta, int colDelta, int rangeLeft,int shot[2]) //recursive search 
{
	shot[0]=row;
	shot[1]=col;
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
		shot[0]=row+rowDelta;
		shot[1]=col+colDelta;
		return search(row+rowDelta, col+colDelta, rowDelta, colDelta, rangeLeft-1, shot);
	}
	return false;

}

Message thewhiteperl::offHit(int lastRow,int lastCol) {
	int shot[2];
	shot[0]=lastRow, shot[1]=lastCol;
	int blah;

	//iterate through the board logging locations of hits
	//if they are next to eachother by col,set horiz to true
	//if they are next to eachother by row, set vert to true

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
			if(lastCol+inc < boardSize && lastCol+inc >= 0 && board[lastRow][lastCol+inc] == '~' && stillRight) {
				right++;
			} else {
				if(lastCol+inc < boardSize && lastCol+inc >= 0 && board[lastRow][lastCol+inc] != 'X' && stillRight) {
					stillRight = false;
				}
			}
			if(lastCol-inc < boardSize && lastCol-inc >= 0 && board[lastRow][lastCol-inc] == '~' && stillLeft) {
				left++;
			} else {
				if(lastCol-inc < boardSize && lastCol-inc >= 0 && board[lastRow][lastCol-inc] != 'X' && stillLeft) {
					stillLeft = false;
				}
			}
			inc++;
		}
		//cout << "Left: " << left << " Right: " << right << endl;
		//cin >> blah;
		if(right > left) {
			for(int i=1; i<5; i++) {
				if(lastCol+i < boardSize && lastCol+i >= 0 && board[lastRow][lastCol+i] == '~') {
					Message result(SHOT,lastRow,lastCol+i,"Die!");
					return result;
				}
			}
		} else if(left > 0) {
			for(int i=1; i<5; i++) {
				if(lastCol-i < boardSize && lastCol-i >= 0 && board[lastRow][lastCol-i] == '~') {
					Message result(SHOT,lastRow,lastCol-i,"Die!");
					return result;
				}
			}		
		}
	}
	if(vert) {
		//same code just some minor alterations
		int top = 0, bottom = 0, inc = 1;
		bool stillTop = true, stillBottom = true;
		while(inc < 5) {
			if(lastRow+inc < boardSize && lastRow+inc >= 0 && board[lastRow+inc][lastCol] == '~' && stillTop) {
				top++;
			} else {
				if(lastRow+inc < boardSize && lastRow+inc >= 0 && board[lastRow+inc][lastCol] != 'X' && stillTop) {
					stillTop = false;
				}
			}
			if(lastRow-inc < boardSize && lastRow-inc >= 0 && board[lastRow-inc][lastCol] == '~' && stillBottom) {
				bottom++;
			} else {
				if(lastRow-inc < boardSize && lastRow-inc >= 0 && board[lastRow-inc][lastCol] != 'X' && stillBottom) {
					stillBottom = false;
				}
			}
			inc++;
		}
		//cout << "Top: " << top << " Bottom: " << bottom << endl;
		//cin >> blah;
		if(top > bottom) {
			for(int i=1; i<5; i++) {
				if(lastRow+i < boardSize && lastRow+i >= 0 && board[lastRow+i][lastCol] == '~') {
					Message result(SHOT,lastRow+i,lastCol,"Die!");
					return result;
				}
			}
		} else if(bottom > 0) {
			for(int i=1; i<5; i++) {
				if(lastRow-i < boardSize && lastRow-i >= 0 && board[lastRow-i][lastCol] == '~') {
					Message result(SHOT,lastRow-i,lastCol,"Die!");
					return result;
				}
			}		
		}
	}

	int top1, left1, right1, down1;
	int increment1 = 1;
	top1 = 0;
	left1 = 0;
	right1 = 0;
	down1 = 0;
	while(lastRow+increment1 < boardSize && board[lastRow+increment1][lastCol] == '~') {
		down1++;
		increment1++;
	}
	increment1=1;
	while(lastRow-increment1 >= 0 && board[lastRow-increment1][lastCol] == '~') {
		top1++;
		increment1++;
	}
	increment1=1;
	while(lastCol+increment1 < boardSize && board[lastRow][lastCol+increment1] == '~') {
		right1++;
		increment1++;
	}
	increment1=1;
	while(lastCol-increment1 >= 0 && board[lastRow][lastCol-increment1] == '~') {
		left1++;
		increment1++;
	}

	//cout << "Top: " << top1 << " Bottom: " << down1 << " Left: " << left1 << " Right: " << right1 << endl;
	//cin >> blah;

	if( down1>top1 && down1>left1 && down1>right1){
		if ( search( lastRow+1, lastCol, 1, 0, 4, shot ) == true ) { //down1
			Message result(SHOT,shot[0],shot[1],"Die!");
			return result;
		}
	}
	if(top1>left1 && top1>right1){
		if( search( lastRow-1, lastCol, -1, 0, 4, shot ) == true ) {	//top
			Message result(SHOT,shot[0],shot[1],"Die!");
			return result;
		}
	}
	if(left1>right1){
		if ( search( lastRow, lastCol-1, 0, -1, 4, shot ) == true ) {  //left
			Message result(SHOT,shot[0],shot[1],"Die!");
			return result;
		} 
	}
	else{
		if ( search( lastRow, lastCol+1, 0, 1, 4, shot ) == true ) { //right
			Message result(SHOT,shot[0],shot[1],"Die!");
			return result;
		} 
	}
}
