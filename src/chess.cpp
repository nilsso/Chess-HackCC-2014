#include "chess.h"
#include<iostream>

Board::Board()
{
   Board::setup();
}

void Board::setup()
{
    // White pieces
    Pawn   * whitePawn1   = new Pawn(0, 6, WHITE);
    Pawn   * whitePawn2   = new Pawn(1, 6, WHITE);
    Pawn   * whitePawn3   = new Pawn(2, 6, WHITE);
    Pawn   * whitePawn4   = new Pawn(2, 6, WHITE);
    Pawn   * whitePawn5   = new Pawn(2, 6, WHITE);
    Pawn   * whitePawn6   = new Pawn(2, 6, WHITE);
    Pawn   * whitePawn7   = new Pawn(2, 6, WHITE);
    Pawn   * whitePawn8   = new Pawn(2, 6, WHITE);
    Rook   * whiteRook1   = new Rook(2, 6, WHITE);
    Rook   * whiteRook2   = new Rook(2, 6, WHITE);
    Knight * whiteKnight1 = new Knight(2, 6, WHITE);
    Knight * whiteKnight2 = new Knight(2, 6, WHITE);
    Bishop * whiteBishop1 = new Bishop(2, 6, WHITE);
    Bishop * whiteBishop2 = new Bishop(2, 6, WHITE);
    Queen  * whiteQueen   = new Queen(2, 6, WHITE);
    King   * whiteKing    = new King(2, 6, WHITE);

    // White pieces
    Pawn   * blackPawn1   = new Pawn(0, 6, WHITE);
    Pawn   * blackPawn2   = new Pawn(1, 6, WHITE);
    Pawn   * blackPawn3   = new Pawn(2, 6, WHITE);
    Pawn   * blackPawn4   = new Pawn(2, 6, WHITE);
    Pawn   * blackPawn5   = new Pawn(2, 6, WHITE);
    Pawn   * blackPawn6   = new Pawn(2, 6, WHITE);
    Pawn   * blackPawn7   = new Pawn(2, 6, WHITE);
    Pawn   * blackPawn8   = new Pawn(2, 6, WHITE);
    Rook   * blackRook1   = new Rook(2, 6, WHITE);
    Rook   * blackRook2   = new Rook(2, 6, WHITE);
    Knight * blackKnight1 = new Knight(2, 6, WHITE);
    Knight * blackKnight2 = new Knight(2, 6, WHITE);
    Bishop * blackBishop1 = new Bishop(2, 6, WHITE);
    Bishop * blackBishop2 = new Bishop(2, 6, WHITE);
    Queen  * blackQueen   = new Queen(2, 6, WHITE);
    King   * blackKing    = new King(2, 6, WHITE);

    // Populate board grid
    board[0][0] = blackRook1;
    board[1][0] = blackKnight1;
    board[2][0] = blackBishop1;
    board[3][0] = blackQueen;
    board[4][0] = blackKing;
    board[5][0] = blackBishop2;
    board[6][0] = blackKnight2;
    board[7][0] = blackRook2;

    board[0][1] = blackPawn1;
    board[1][1] = blackPawn2;
    board[2][1] = blackPawn3;
    board[3][1] = blackPawn4;
    board[4][1] = blackPawn5;
    board[5][1] = blackPawn6;
    board[6][1] = blackPawn7;
    board[7][1] = blackPawn8;

    board[0][6] = whitePawn1;
    board[1][6] = whitePawn2;
    board[2][6] = whitePawn3;
    board[3][6] = whitePawn4;
    board[4][6] = whitePawn5;
    board[5][6] = whitePawn6;
    board[6][6] = whitePawn7;
    board[7][6] = whitePawn8;

    board[0][7] = whiteRook1;
    board[1][7] = whiteKnight1;
    board[2][7] = whiteBishop1;
    board[3][7] = whiteQueen;
    board[4][7] = whiteKing;
    board[5][7] = whiteBishop2;
    board[6][7] = whiteKnight2;
    board[7][7] = whiteRook2;
}

void Board::move(string email_address, int row1, int col1, int row2, int col2)
{
   bool success = true;

   if(board[row2][col2]->type_ == EMPTY){
      *(board[row2][col2]) = *(board[row1][col1]);
      board[row1][col1]->type_ = EMPTY;
   }
   else 
      success = false;

}

void Board::printBoardArray(){
   for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
         if(board[i][j]->type_ == EMPTY){
            cout << "x  ";
         }
         else{
            cout << board[i][j]->type_ << "  ";
         }
      }
      cout << endl;
   }
   cout << endl;

}

int main(){
   
   string email = "test@test.com";

   Board b;
   
   b.printBoardArray();
   
   b.move(email,0,4,4,4);
   
   b.printBoardArray();

   b.move(email,1,3,5,5);

   b.printBoardArray();

   cin.ignore();
   
   return 0;

}


