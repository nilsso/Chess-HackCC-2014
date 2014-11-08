#include "chess.h"
#include<iostream>

Board::Board()
{
   Board::setup();
}

void Board::setup()
{
   for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
         board[i][j] = new Piece;
         board[i][j]->type_ = EMPTY;
      }
   }

   board[0][0]->type_ = ROOK;
   board[0][0]->color_ = WHITE;
   board[0][1]->type_ = KNIGHT;
   board[0][1]->color_ = WHITE;
   board[0][2]->type_ = BISHOP;
   board[0][2]->color_ = WHITE;
   board[0][3]->type_ = QUEEN;
   board[0][3]->color_ = WHITE;
   board[0][4]->type_ = KING;
   board[0][4]->color_ = WHITE;
   board[0][7]->type_ = ROOK;
   board[0][7]->color_ = WHITE;
   board[0][6]->type_ = KNIGHT;
   board[0][6]->color_ = WHITE;
   board[0][5]->type_ = BISHOP;
   board[0][5]->color_ = WHITE;

   board[7][0]->type_ = ROOK;
   board[7][0]->color_ = BLACK;
   
   board[7][1]->type_ = KNIGHT;
   board[7][1]->color_ = BLACK;

   board[7][2]->type_ = BISHOP;
   board[7][2]->color_ = BLACK;

   board[7][3]->type_ = KING;
   board[7][3]->color_ = BLACK;

   board[7][4]->type_ = QUEEN;
   board[7][4]->color_ = BLACK;

   board[7][5]->type_ = BISHOP;
   board[7][5]->color_ = BLACK;

   board[7][6]->type_ = KNIGHT;
   board[7][6]->color_ = BLACK;

   board[7][7]->type_ = ROOK;
   board[7][7]->color_ = BLACK;

   for(int i = 0; i < 8; i++){
      board[1][i]->type_ = PAWN;
      board[1][i]->color_ = WHITE;
      board[6][i]->type_ = PAWN;
      board[6][i]->color_ = BLACK;
   }
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

