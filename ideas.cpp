int sizes[3] = [3,4,5];
int orient[2] = [1,2];
int lastShot[2] = [-1,-1];
//horizontal top vertical left



Message offMissOrKill() { 
	boardCounter[n][n];
	for(int i=0; i<cols; i++) {
		for(int j=0; j<row; j++) {
			if(board[i][j] == '~') {
				for(int k=3; k<6; k++) {
					for(int l=1; l<3; l++) {
						bool possible = true;
						for(int m=1; m<k; m++) {
							if(board[i + ((l == 1) ? m : 0)][j + ((l == 2) ? m : 0)] != '~') {
								possible = false;
							}
						}
						if(possible) {
							boardCounter[i][j]++;
						}
					}
				}
			}
		}
	}

	int maxSoFar[2] = [0,0];
	for(int i=1; i<cols; i++) {
		for(int j=0; j<row; j++) {
			if(board[i][j] > board[maxSoFar[0]][maxSoFar[1]]) {
				maxSoFar = [i,j];
			}
		}
	}

	Message result(SHOT,maxSoFar[0],maxSoFar[1],"Die!");
	return result; 
}


Message myplayer::offHit(lastRow,lastCol) {
	int top = 0, left = 0, right = 0, down = 0;
	int increment = 1;
		//n = size of board
		//has to be 2 open at least, if not not possible
	while(lastRow+increment < n && board[lastRow+increment][lastCol] == '~') {
		down++;
		increment++;
	}
	increment=1;
	while(lastRow-increment >= 0 && board[lastRow-increment][lastCol] == '~') {
		top++;
		increment++;
	}
	increment=1;
	while(lastCol+increment < n && board[lastRow][lastCol+increment] == '~') {
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
	return result; 
	}
	else if(top>left && top>right){
	Message result(SHOT,lastRow-1,lastCol,"Die!");
	return result; 
	}
	else if(left>right){
	Message result(SHOT,lastRow,lastCol-1,"Die!");
	return result; 
	}
	else{
	Message result(SHOT,lastRow,lastCol+1,"Die!");
	return result; 
	}
}


//function check if open hit, if so offHit for that position
