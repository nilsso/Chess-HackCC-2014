#pragma once

#include <string>
#include <list>

using namespace std;

// -----------------------------------------------------------------------------
// Piece structures
// ---------------------------------------------------------------------
// Piece interface
struct Piece
{
    // Piece property enums
    enum PieceColor { WHITE, BLACK };

    // Constructor
    Piece(int x, int y, PieceColor color);

    // Functions
    virtual bool canMove(int x, int y) = 0;

    // Data members
    int x_, y_;
    PieceColor color_;
};

struct Pawn: public Piece
{
    // Constructor
    Pawn(int x, int y, PieceColor color);

    // Functions
    bool canMove(int x, int y);
};

struct Rook: public Piece
{
    // Constructor
    Rook(int x, int y, PieceColor color):
        Piece(x, y, color) {}

    // Functions
    bool canMove(int x, int y);
};

struct Knight: public Piece
{
    // Constructor
    Knight(int x, int y, PieceColor color):
        Piece(x, y, color) {}


    // Functions
    bool canMove(int x, int y);
};

struct Bishop: public Piece
{
    // Constructor
    Bishop(int x, int y, PieceColor color):
        Piece(x, y, color) {}


    // Functions
    bool canMove(int x, int y);
};

struct Queen: public Piece
{
    // Constructor
    Queen(int x, int y, PieceColor color):
        Piece(x, y, color) {}


    // Functions
    bool canMove(int x, int y);
};

struct King: public Piece
{
    // Constructor
    King(int x, int y, PieceColor color):
        Piece(x, y, color) {}

    // Functions
    bool canMove(int x, int y);
};

// -----------------------------------------------------------------------------
// Board class
// -----------------------------------------------------------------------------
class Board
{
    public:
        // Move return type enums
        enum MoveReturnType { VALID, INVALID, BLOCKED };
        // Board constructor
        Board();

        // Setup function
        /*
         * Sets up the board with new pieces.
         */
        void setup();

        // Cleanup function
        /*
         * Cleans up the remaining pieces.
         */
        void cleanup();

        // Move function
        /*
         * Attempts to move a piece from position 1 to position 2. Checks to
         * see if the piece can move to the destination based on piece move
         * rulesets (bishop only moves diagonally, pawn forward except for
         * attacking, etc.), if the piece is blocked from moving to that
         * position, and lastly if the resulting move wouldn't result in self
         * check. Returns false if any of those conditions fail.
         *
         * move a piece.
         * @param x1 Origin x-coordinate.
         * @param y1 Origin y-coordinate.
         * @param x2 Destination x-coordinate.
         * @param y2 Destination y-coordinate.
         */
        bool canMove(int x1, int y1, int x2, int y2);

        void printBoardArray();

    private:
        const unsigned int MAX_X = 8;
        const unsigned int MAX_Y = 8;

        // Board grid
        Piece* board[8][8];

        // Black pieces
        Pawn   * blackPawn1;
        Pawn   * blackPawn2;
        Pawn   * blackPawn3;
        Pawn   * blackPawn4;
        Pawn   * blackPawn5;
        Pawn   * blackPawn6;
        Pawn   * blackPawn7;
        Pawn   * blackPawn8;
        Rook   * blackRook1;
        Rook   * blackRook2;
        Knight * blackKnight1;
        Knight * blackKnight2;
        Bishop * blackBishop1;
        Bishop * blackBishop2;
        Queen  * blackQueen;
        King   * blackKing;

        // White pieces
        Pawn   * whitePawn1;
        Pawn   * whitePawn2;
        Pawn   * whitePawn3;
        Pawn   * whitePawn4;
        Pawn   * whitePawn5;
        Pawn   * whitePawn6;
        Pawn   * whitePawn7;
        Pawn   * whitePawn8;
        Rook   * whiteRook1;
        Rook   * whiteRook2;
        Knight * whiteKnight1;
        Knight * whiteKnight2;
        Bishop * whiteBishop1;
        Bishop * whiteBishop2;
        Queen  * whiteQueen;
        King   * whiteKing;

        // List of live pieces
        list<Piece *> pieces;
};

