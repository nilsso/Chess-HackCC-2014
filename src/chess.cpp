#include "chess.h"
#include<iostream>

typedef Piece::PieceType PType;
typedef Piece::PieceColor PColor;

Piece::Piece(Board *board, PieceType type, PieceColor color, int x, int y):
    board_(board),
    type_(type),
    x_(x),
    y_(y),
    color_(color)
{
}

Piece::~Piece()
{
}

bool Piece::canMove(Piece *piece, int x, int y)
{
    //piece->y_ += (piece->color_ == PColor::BLACK ? 1 : -1) * y;

    switch (piece->type_) {
        // Pawn "is move valid" logic
        case (PType::PAWN):
        {
            // Deltas
            int dx = abs(x - piece->x_);
            int dy = abs(y - piece->y_);

            // If move request delta-y is 2
            if ((dy == 2) && (dx == 0)) {
                // Return if pawn is on initial space
                return ((piece->y_ == 1 && piece->color_ == PColor::BLACK) ||
                        (piece->y_ == 6 && piece->color_ == PColor::WHITE));
            }
            // If move request delta-y is 1 and delta-x is 0 or 1
            return (dy == 1 && dx < 2);
        }

        // Rook "is move valid" logic
        case (PType::ROOK):
        {
            // If rook is moving in only one axis
            return (!((x - piece-> x_) == 0) != !((y - piece->y_) == 0));
        }

        // Knight "is move valid" logic
        case (PType::KNIGHT):
        {
            int dx = abs(x - piece->x_);
            int dy = abs(y - piece->y_);
            return ((dx == 2 && dy == 1) || (dx == 1 && dy == 2));
        }

        // Bishop "is move valid" logic
        case (PType::BISHOP):
        {
            return ((x - piece->x_) == (y - piece->y_));
            break;
        }

        // Queen "is move valid" logic
        case (PType::QUEEN):
        {
            return (
                !((x - piece-> x_) == 0) != !((y - piece->y_) == 0) ||
                (x - piece->x_) == (y - piece->y_));
            break;
        }

        // King "is move valid" logic
        case (PType::KING):
        {
            int dx = abs(x - piece->x_);
            int dy = abs(y - piece->y_);

            return ((dx < 2) && (dy < 2));
        }
    }

    return false;
}

Board::Board()
{
    for (int y = 0; y < Board::MAX_Y; y++) {
        for (int x = 0; x < Board::MAX_X; x++) {
            board[y][x] = nullptr;
        }
    }
}

void Board::setup()
{
    // Create new piece instances
    pieces[BLACK_ROOK1]   = new Piece(this, PType::ROOK, PColor::BLACK, 0, 0);
    pieces[BLACK_ROOK2]   = new Piece(this, PType::ROOK, PColor::BLACK, 1, 0);
    pieces[BLACK_KNIGHT1] = new Piece(this, PType::KNIGHT, PColor::BLACK, 2, 0);
    pieces[BLACK_KNIGHT2] = new Piece(this, PType::KNIGHT, PColor::BLACK, 3, 0);
    pieces[BLACK_BISHOP1] = new Piece(this, PType::BISHOP, PColor::BLACK, 4, 0);
    pieces[BLACK_BISHOP2] = new Piece(this, PType::BISHOP, PColor::BLACK, 5, 0);
    pieces[BLACK_QUEEN]   = new Piece(this, PType::QUEEN, PColor::BLACK, 6, 0);
    pieces[BLACK_KING]    = new Piece(this, PType::KING, PColor::BLACK, 7, 0);

    pieces[BLACK_PAWN1]   = new Piece(this, PType::PAWN, PColor::BLACK, 0, 1);
    pieces[BLACK_PAWN2]   = new Piece(this, PType::PAWN, PColor::BLACK, 1, 1);
    pieces[BLACK_PAWN3]   = new Piece(this, PType::PAWN, PColor::BLACK, 2, 1);
    pieces[BLACK_PAWN4]   = new Piece(this, PType::PAWN, PColor::BLACK, 3, 1);
    pieces[BLACK_PAWN5]   = new Piece(this, PType::PAWN, PColor::BLACK, 4, 1);
    pieces[BLACK_PAWN6]   = new Piece(this, PType::PAWN, PColor::BLACK, 5, 1);
    pieces[BLACK_PAWN7]   = new Piece(this, PType::PAWN, PColor::BLACK, 6, 1);
    pieces[BLACK_PAWN8]   = new Piece(this, PType::PAWN, PColor::BLACK, 7, 1);

    pieces[WHITE_PAWN1]   = new Piece(this, PType::PAWN, PColor::WHITE, 0, 6);
    pieces[WHITE_PAWN2]   = new Piece(this, PType::PAWN, PColor::WHITE, 1, 6);
    pieces[WHITE_PAWN3]   = new Piece(this, PType::PAWN, PColor::WHITE, 2, 6);
    pieces[WHITE_PAWN4]   = new Piece(this, PType::PAWN, PColor::WHITE, 3, 6);
    pieces[WHITE_PAWN5]   = new Piece(this, PType::PAWN, PColor::WHITE, 4, 6);
    pieces[WHITE_PAWN6]   = new Piece(this, PType::PAWN, PColor::WHITE, 5, 6);
    pieces[WHITE_PAWN7]   = new Piece(this, PType::PAWN, PColor::WHITE, 6, 6);
    pieces[WHITE_PAWN8]   = new Piece(this, PType::PAWN, PColor::WHITE, 7, 6);

    pieces[WHITE_ROOK1]   = new Piece(this, PType::ROOK, PColor::WHITE, 0, 7);
    pieces[WHITE_ROOK2]   = new Piece(this, PType::ROOK, PColor::WHITE, 1, 7);
    pieces[WHITE_KNIGHT1] = new Piece(this, PType::KNIGHT, PColor::WHITE, 2, 7);
    pieces[WHITE_KNIGHT2] = new Piece(this, PType::KNIGHT, PColor::WHITE, 3, 7);
    pieces[WHITE_BISHOP1] = new Piece(this, PType::BISHOP, PColor::WHITE, 4, 7);
    pieces[WHITE_BISHOP2] = new Piece(this, PType::BISHOP, PColor::WHITE, 5, 7);
    pieces[WHITE_QUEEN]   = new Piece(this, PType::QUEEN, PColor::WHITE, 6, 7);
    pieces[WHITE_KING]    = new Piece(this, PType::KING, PColor::WHITE, 7, 7);

    // Populate board matrix
    board[0][0] = pieces[BLACK_ROOK1];
    board[0][1] = pieces[BLACK_KNIGHT1];
    board[0][2] = pieces[BLACK_BISHOP1];
    board[0][3] = pieces[BLACK_QUEEN];
    board[0][4] = pieces[BLACK_KING];
    board[0][5] = pieces[BLACK_BISHOP2];
    board[0][6] = pieces[BLACK_KNIGHT2];
    board[0][7] = pieces[BLACK_ROOK2];

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
    board[7][1] = pieces[WHITE_KNIGHT1];
    board[7][2] = pieces[WHITE_BISHOP1];
    board[7][3] = pieces[WHITE_QUEEN];
    board[7][4] = pieces[WHITE_KING];
    board[7][5] = pieces[WHITE_BISHOP2];
    board[7][6] = pieces[WHITE_KNIGHT2];
    board[7][7] = pieces[WHITE_ROOK2];
}

void Board::cleanup()
{
    for (Piece *p : pieces) {
        if (p != nullptr) {
            delete p;
        }
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

PType Board::GetTypeAtPosition(int x, int y)
{
    // By grace
    //if ((x < 0) || (x > MAX_X) || (y < 0) || (y > MAX_Y))

    return board[y][x]->type_;
}

PColor Board::GetColorAtPosition(int x, int y)
{
    // By grace
    return board[y][x]->color_;
}

void Board::printBoard(){
   for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 8; x++) {
         if (board[y][x] != nullptr) {
             switch (board[y][x]->type_) {
                 case (Piece::PieceType::PAWN):
                     cout << ((board[y][x]->color_ == PColor::BLACK) ? 'P' : 'p');
                     break;
                 case (Piece::PieceType::ROOK):
                     cout << (board[y][x]->color_ == PColor::BLACK ? 'R' : 'r');
                     break;
                 case (PType::KNIGHT):
                     cout << (board[y][x]->color_ == PColor::BLACK ? 'G' : 'g');
                     break;
                 case (PType::BISHOP):
                     cout << (board[y][x]->color_ == PColor::BLACK ? 'B' : 'b');
                     break;
                 case (PType::QUEEN):
                     cout << (board[y][x]->color_ == PColor::BLACK ? 'Q' : 'q');
                     break;
                 case (PType::KING):
                     cout << (board[y][x]->color_ == PColor::BLACK ? 'K' : 'k');
                     break;
                 //default:
                     //cout << 'x';
                     //break;
             }
         }
      }
      cout << endl;
   }
   cout << endl;
}

int main(){
   //string email = "test@test.com";

   Board b;

   b.setup();

   b.printBoard();

   //b.move(email,0,4,4,4);

   //b.printBoardArray();

   //b.move(email,1,3,5,5);

   //b.printBoardArray();

   //cin.ignore();

   return EXIT_SUCCESS;
}


