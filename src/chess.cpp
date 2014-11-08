#include "chess.h"
#include<iostream>

typedef Piece::PieceType PType;
typedef Piece::PieceColor PColor;

Piece::Piece(Board *board, PieceType type, PieceColor color, int x, int y):
    board_(board),
    x_(x),
    y_(y),
    color_(color)
{

}

bool Piece::canMove(Piece *piece, int x, int y)
{
    //piece->y_ += (piece->color_ == PColor::BLACK ? 1 : -1) * y;

    switch (piece->type_) {
        case (PType::PAWN):
        {

            break;
        }
        case (PType::ROOK):
        {
            // If rook is moving in only one axis
            return !(((piece->x_+ x) != 0) && ((piece->y_ + y) != 0));
        }
        case (PType::KNIGHT):
        {

            break;
        }
        case (PType::BISHOP):
        {

            break;
        }
        case (PType::QUEEN):
        {

            break;
        }
        case (PType::KING):
        {

            break;
        }
    }

    return false;
}

Board::Board()
{
   Board::setup();
}

void Board::setup()
{
    // Create new piece instances
    pieces[BLACK_ROOK1]   = new Piece(PType::ROOK, PColor::BLACK, 0, 0);
    pieces[BLACK_ROOK1]   = new Piece(PType::ROOK, PColor::BLACK, 1, 0);
    pieces[BLACK_KNIGHT2] = new Piece(PType::KNIGHT, PColor::BLACK, 2, 0);
    pieces[BLACK_KNIGHT2] = new Piece(PType::KNIGHT, PColor::BLACK, 3, 0);
    pieces[BLACK_BISHOP2] = new Piece(PType::BISHOP, PColor::BLACK, 4, 0);
    pieces[BLACK_BISHOP2] = new Piece(PType::BISHOP, PColor::BLACK, 5, 0);
    pieces[BLACK_QUEEN]   = new Piece(PType::QUEEN, PColor::BLACK, 6, 0);
    pieces[BLACK_KING]    = new Piece(PType::KING, PColor::BLACK, 7, 0);

    pieces[BLACK_PAWN1]   = new Piece(PType::PAWN, PColor::BLACK, 0, 1);
    pieces[BLACK_PAWN2]   = new Piece(PType::PAWN, PColor::BLACK, 1, 1);
    pieces[BLACK_PAWN3]   = new Piece(PType::PAWN, PColor::BLACK, 2, 1);
    pieces[BLACK_PAWN4]   = new Piece(PType::PAWN, PColor::BLACK, 3, 1);
    pieces[BLACK_PAWN5]   = new Piece(PType::PAWN, PColor::BLACK, 4, 1);
    pieces[BLACK_PAWN6]   = new Piece(PType::PAWN, PColor::BLACK, 5, 1);
    pieces[BLACK_PAWN7]   = new Piece(PType::PAWN, PColor::BLACK, 6, 1);
    pieces[BLACK_PAWN8]   = new Piece(PType::PAWN, PColor::BLACK, 7, 1);

    pieces[WHITE_PAWN1]   = new Piece(PType::PAWN, PColor::WHITE, 0, 6);
    pieces[WHITE_PAWN2]   = new Piece(PType::PAWN, PColor::WHITE, 1, 6);
    pieces[WHITE_PAWN3]   = new Piece(PType::PAWN, PColor::WHITE, 2, 6);
    pieces[WHITE_PAWN4]   = new Piece(PType::PAWN, PColor::WHITE, 3, 6);
    pieces[WHITE_PAWN5]   = new Piece(PType::PAWN, PColor::WHITE, 4, 6);
    pieces[WHITE_PAWN6]   = new Piece(PType::PAWN, PColor::WHITE, 5, 6);
    pieces[WHITE_PAWN7]   = new Piece(PType::PAWN, PColor::WHITE, 6, 6);
    pieces[WHITE_PAWN8]   = new Piece(PType::PAWN, PColor::WHITE, 7, 6);

    pieces[WHITE_ROOK1]   = new Piece(PType::ROOK, PColor::WHITE, 0, 7);
    pieces[WHITE_ROOK1]   = new Piece(PType::ROOK, PColor::WHITE, 1, 7);
    pieces[WHITE_KNIGHT2] = new Piece(PType::KNIGHT, PColor::WHITE, 2, 7);
    pieces[WHITE_KNIGHT2] = new Piece(PType::KNIGHT, PColor::WHITE, 3, 7);
    pieces[WHITE_BISHOP2] = new Piece(PType::BISHOP, PColor::WHITE, 4, 7);
    pieces[WHITE_BISHOP2] = new Piece(PType::BISHOP, PColor::WHITE, 5, 7);
    pieces[WHITE_QUEEN]   = new Piece(PType::QUEEN, PColor::WHITE, 6, 7);
    pieces[WHITE_KING]    = new Piece(PType::KING, PColor::WHITE, 7, 7);

    // Populate board matrix
    board[0][0] = pieces[BLACK_ROOK1];
    board[0][1] = pieces[BLACK_ROOK2];
    board[0][2] = pieces[BLACK_KNIGHT1];
    board[0][3] = pieces[BLACK_KNIGHT2];
    board[0][4] = pieces[BLACK_BISHOP1];
    board[0][5] = pieces[BLACK_BISHOP2];
    board[0][6] = pieces[BLACK_QUEEN];
    board[0][7] = pieces[BLACK_KING];

    board[1][0] = pieces[BLACK_PAWN1];
    board[1][1] = pieces[BLACK_PAWN2];
    board[1][2] = pieces[BLACK_PAWN3];
    board[1][3] = pieces[BLACK_PAWN4];
    board[1][4] = pieces[BLACK_PAWN5];
    board[1][5] = pieces[BLACK_PAWN6];
    board[1][6] = pieces[BLACK_PAWN7];
    board[1][7] = pieces[BLACK_PAWN8];

    board[6][0] = pieces[WHITE_PAWN1];
    board[6][1] = pieces[WHITE_PAWN2];
    board[6][2] = pieces[WHITE_PAWN3];
    board[6][3] = pieces[WHITE_PAWN4];
    board[6][4] = pieces[WHITE_PAWN5];
    board[6][5] = pieces[WHITE_PAWN6];
    board[6][6] = pieces[WHITE_PAWN7];
    board[6][7] = pieces[WHITE_PAWN8];

    board[7][0] = pieces[WHITE_ROOK1];
    board[7][1] = pieces[WHITE_ROOK2];
    board[7][2] = pieces[WHITE_KNIGHT1];
    board[7][3] = pieces[WHITE_KNIGHT2];
    board[7][4] = pieces[WHITE_BISHOP1];
    board[7][5] = pieces[WHITE_BISHOP2];
    board[7][6] = pieces[WHITE_QUEEN];
    board[7][7] = pieces[WHITE_KING];

    // Add pieces to live pieces list
    live_pieces.push_back(pieces[BLACK_PAWN1]);
    live_pieces.push_back(pieces[BLACK_PAWN2]);
    live_pieces.push_back(pieces[BLACK_PAWN3]);
    live_pieces.push_back(pieces[BLACK_PAWN4]);
    live_pieces.push_back(pieces[BLACK_PAWN5]);
    live_pieces.push_back(pieces[BLACK_PAWN6]);
    live_pieces.push_back(pieces[BLACK_PAWN7]);
    live_pieces.push_back(pieces[BLACK_PAWN8]);

    live_pieces.push_back(pieces[BLACK_ROOK1]);
    live_pieces.push_back(pieces[BLACK_ROOK2]);
    live_pieces.push_back(pieces[BLACK_KNIGHT1]);
    live_pieces.push_back(pieces[BLACK_KNIGHT2]);
    live_pieces.push_back(pieces[BLACK_BISHOP1]);
    live_pieces.push_back(pieces[BLACK_BISHOP2]);
    live_pieces.push_back(pieces[BLACK_QUEEN]);
    live_pieces.push_back(pieces[BLACK_KING]);

    live_pieces.push_back(pieces[WHITE_PAWN1]);
    live_pieces.push_back(pieces[WHITE_PAWN2]);
    live_pieces.push_back(pieces[WHITE_PAWN3]);
    live_pieces.push_back(pieces[WHITE_PAWN4]);
    live_pieces.push_back(pieces[WHITE_PAWN5]);
    live_pieces.push_back(pieces[WHITE_PAWN6]);
    live_pieces.push_back(pieces[WHITE_PAWN7]);
    live_pieces.push_back(pieces[WHITE_PAWN8]);

    live_pieces.push_back(pieces[WHITE_ROOK1]);
    live_pieces.push_back(pieces[WHITE_ROOK2]);
    live_pieces.push_back(pieces[WHITE_KNIGHT1]);
    live_pieces.push_back(pieces[WHITE_KNIGHT2]);
    live_pieces.push_back(pieces[WHITE_BISHOP1]);
    live_pieces.push_back(pieces[WHITE_BISHOP2]);
    live_pieces.push_back(pieces[WHITE_QUEEN]);
    live_pieces.push_back(pieces[WHITE_KING]);
}

void Board::cleanup()
{
    auto it = live_pieces.begin();
    while (it != live_pieces.end()) {
        it = live_pieces.erase(it);
        it++;
    }
}

bool Board::canMove(int x1, int y1, int x2, int y2)
{
    // If new coordinates are outside limits
    if (x2 < 0 || x2 > MAX_X || y2 < 0 || y2 > MAX_Y)
        return false;

    // If piece can move to position
    return Piece::canMove(board[y1][x1], x2, y2);
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


