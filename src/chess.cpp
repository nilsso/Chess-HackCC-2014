#include "chess.h"
#include<iostream>

Piece::Piece(int x, int y, PieceColor color):
    x_(x),
    y_(y),
    color_(color)
{

}

Board::Board()
{
   Board::setup();
}

void Board::setup()
{
    // White pieces
    Pawn   * whitePawn1   = new Pawn(0, 6, Piece::BLACK);
    Pawn   * whitePawn2   = new Pawn(1, 6, Piece::BLACK);
    Pawn   * whitePawn3   = new Pawn(2, 6, Piece::BLACK);
    Pawn   * whitePawn4   = new Pawn(2, 6, Piece::BLACK);
    Pawn   * whitePawn5   = new Pawn(2, 6, Piece::BLACK);
    Pawn   * whitePawn6   = new Pawn(2, 6, Piece::BLACK);
    Pawn   * whitePawn7   = new Pawn(2, 6, Piece::BLACK);
    Pawn   * whitePawn8   = new Pawn(2, 6, Piece::BLACK);
    Rook   * whiteRook1   = new Rook(2, 6, Piece::BLACK);
    Rook   * whiteRook2   = new Rook(2, 6, Piece::BLACK);
    Knight * whiteKnight1 = new Knight(2, 6, Piece::BLACK);
    Knight * whiteKnight2 = new Knight(2, 6, Piece::BLACK);
    Bishop * whiteBishop1 = new Bishop(2, 6, Piece::BLACK);
    Bishop * whiteBishop2 = new Bishop(2, 6, Piece::BLACK);
    Queen  * whiteQueen   = new Queen(2, 6, Piece::BLACK);
    King   * whiteKing    = new King(2, 6, Piece::BLACK);

    // White pieces
    Pawn   * blackPawn1   = new Pawn(0, 6, Piece::WHITE);
    Pawn   * blackPawn2   = new Pawn(1, 6, Piece::WHITE);
    Pawn   * blackPawn3   = new Pawn(2, 6, Piece::WHITE);
    Pawn   * blackPawn4   = new Pawn(2, 6, Piece::WHITE);
    Pawn   * blackPawn5   = new Pawn(2, 6, Piece::WHITE);
    Pawn   * blackPawn6   = new Pawn(2, 6, Piece::WHITE);
    Pawn   * blackPawn7   = new Pawn(2, 6, Piece::WHITE);
    Pawn   * blackPawn8   = new Pawn(2, 6, Piece::WHITE);
    Rook   * blackRook1   = new Rook(2, 6, Piece::WHITE);
    Rook   * blackRook2   = new Rook(2, 6, Piece::WHITE);
    Knight * blackKnight1 = new Knight(2, 6, Piece::WHITE);
    Knight * blackKnight2 = new Knight(2, 6, Piece::WHITE);
    Bishop * blackBishop1 = new Bishop(2, 6, Piece::WHITE);
    Bishop * blackBishop2 = new Bishop(2, 6, Piece::WHITE);
    Queen  * blackQueen   = new Queen(2, 6, Piece::WHITE);
    King   * blackKing    = new King(2, 6, Piece::WHITE);

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

    // Add pieces to live pieces list
    pieces.push_back(blackPawn1);
    pieces.push_back(blackPawn2);
    pieces.push_back(blackPawn3);
    pieces.push_back(blackPawn4);
    pieces.push_back(blackPawn5);
    pieces.push_back(blackPawn6);
    pieces.push_back(blackPawn7);
    pieces.push_back(blackPawn8);

    pieces.push_back(blackRook1);
    pieces.push_back(blackRook2);
    pieces.push_back(blackKnight1);
    pieces.push_back(blackKnight2);
    pieces.push_back(blackBishop1);
    pieces.push_back(blackBishop2);
    pieces.push_back(blackQueen);
    pieces.push_back(blackKing);

    pieces.push_back(whitePawn1);
    pieces.push_back(whitePawn2);
    pieces.push_back(whitePawn3);
    pieces.push_back(whitePawn4);
    pieces.push_back(whitePawn5);
    pieces.push_back(whitePawn6);
    pieces.push_back(whitePawn7);
    pieces.push_back(whitePawn8);

    pieces.push_back(whiteRook1);
    pieces.push_back(whiteRook2);
    pieces.push_back(whiteKnight1);
    pieces.push_back(whiteKnight2);
    pieces.push_back(whiteBishop1);
    pieces.push_back(whiteBishop2);
    pieces.push_back(whiteQueen);
    pieces.push_back(whiteKing);
}

void Board::cleanup()
{
    auto it = pieces.begin();
    while (it != pieces.end()) {
        it = pieces.erase(it);
        it++;
    }
}

bool Board::canMove(int x1, int y1, int x2, int y2)
{
    // If new coordinates are outside limits
    if (x2 < 0 || x2 > MAX_X || y2 < 0 || y2 > MAX_Y)
        return false;

    return board[x1][y1]->canMove(x2, y2);
}

void Board::printBoardArray(){
   //for(int i = 0; i < 8; i++){
      //for(int j = 0; j < 8; j++){
         //if(board[i][j]){
            //cout << "x  ";
         //}
         //else{
            //cout << board[i][j]->type_ << "  ";
         //}
      //}
      //cout << endl;
   //}
   //cout << endl;
}

int main(){
   //string email = "test@test.com";

   //Board b;

   //b.printBoardArray();

   //b.move(email,0,4,4,4);

   //b.printBoardArray();

   //b.move(email,1,3,5,5);

   //b.printBoardArray();

   //cin.ignore();

   return 0;
}


