// CheckTheCheck

#include <iostream>
#include <cmath>

using namespace std;

bool checkNoJump( string* board, int i, int j, int ii, int jj ) {
    int incI = 0;
    int incJ = 0;
    if ( i != ii ) incI = ( i - ii ) / abs( i - ii );
    if ( j != jj ) incJ = ( j - jj ) / abs( j - jj );
    int loopI = ii + incI;
    int loopJ = jj + incJ;
    while( loopI != i || loopJ != j ){
        if ( board[loopI][loopJ] != '.' ) return false;
        loopI = loopI + incI;
        loopJ = loopJ + incJ;
    }
    return true;
}

int main()
{
    int gameNum = 1;
    do
    {
        string board[8];
        int whiteKingI = 8;
        int whiteKingJ = 8;
        int blackKingI = 8;
        int blackKingJ = 8;
        bool whiteCheck = false;
        bool blackCheck = false;
        for ( int i = 0; i < 8; i++ ) {
            cin >> board[i];
        }

        // assume the board is empty
        bool isEmpty = true;
        for ( int i = 0; i < 8; i++ ) {
            for ( int j = 0; j < 8; j++ ) {
                if ( board[i][j] != '.' ) isEmpty = false;
                if ( board[i][j] == 'K' ) {
                    whiteKingI = i;
                    whiteKingJ = j;
                }   
                if ( board[i][j] == 'k' ) {
                    blackKingI = i;
                    blackKingJ = j;
                }   
             }
        }

        // if the board is empty then break the loop
        if( isEmpty ) break;
    
        // the board is not empty, implement your code here
        bool getResult = false; 
         
        for ( int i = 0; i < 8 && !getResult; i++ ){
            for ( int j = 0; j < 8 && !getResult; j++ ){
                if ( board[i][j] == '.') continue;
                // For checking Pawn
                if ( ( board[i][j] =='p' ) && ( i + 1 == whiteKingI ) && 
                     ( ( j + 1 == whiteKingJ ) || ( j - 1 == whiteKingJ ) ) ) {
                    whiteCheck = true;
                    getResult = true;
                    continue;
                }
                if ( ( board[i][j] =='P' ) && ( i - 1 == blackKingI ) && 
                     ( ( j + 1 == blackKingJ ) || ( j - 1 == blackKingJ ) ) ) {
                    blackCheck = true;
                    getResult = true;
                    continue;
                }
                // For checking Rook and Queen partially like Rook
                if ( ( board[i][j] == 'r' || board[i][j] == 'q' ) && 
                     ( i == whiteKingI || j == whiteKingJ ) &&
                     checkNoJump( board, i, j, whiteKingI, whiteKingJ ) ) {
                    whiteCheck = true;
                    getResult = true;
                    continue;
                }
                if ( ( board[i][j] == 'R' || board[i][j] == 'Q' ) && 
                     ( i == blackKingI || j == blackKingJ ) &&
                     checkNoJump( board, i, j, blackKingI, blackKingJ ) ) {
                    blackCheck = true;
                    getResult = true;
                    continue;
                }
                // For checking Bishop and Queen partially like Bishop
                if ( ( board[i][j] == 'b' || board[i][j] == 'q' ) && 
                     abs( i - whiteKingI ) == abs( j - whiteKingJ ) &&
                     checkNoJump( board, i, j, whiteKingI, whiteKingJ ) ) {
                    whiteCheck = true;
                    getResult = true;
                    continue;
                }
                if ( ( board[i][j] == 'B' || board[i][j] == 'Q' ) && 
                     abs( i - blackKingI ) == abs( j - blackKingJ ) &&
                     checkNoJump( board, i, j, blackKingI, blackKingJ ) ) {
                    blackCheck = true;
                    getResult = true;
                    continue;
                }
                // For checking Knight
                if ( ( board[i][j] =='n' ) && 
                     ( ( abs( i - whiteKingI ) == 1 && abs( j - whiteKingJ ) == 2 ) || 
                       ( abs( i - whiteKingI ) == 2 && abs( j - whiteKingJ ) == 1 ) ) ) {
                    whiteCheck = true;
                    getResult = true;
                    continue;
                }
                if ( ( board[i][j] =='N' ) && 
                     ( ( abs( i - blackKingI ) == 1 && abs( j - blackKingJ ) == 2 ) || 
                       ( abs( i - blackKingI ) == 2 && abs( j - blackKingJ ) == 1 ) ) ) {
                    blackCheck = true;
                    getResult = true;
                    continue;
                }
            }
        }
        if ( whiteCheck ) {
            cout << "Game #" << gameNum << ": white king is in check.\n";
        } else if ( blackCheck ){
            cout << "Game #" << gameNum << ": black king is in check.\n";
        } else {
            cout << "Game #" << gameNum << ": no king is in check.\n";
        }
        gameNum++;
    }while(1);

    return 0;
}
