#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <list>

using namespace std;

// Forward declaration
class Board;

// -----------------------------------------------------------------------------
// Piece structures
// ---------------------------------------------------------------------
// Piece interface
struct Piece
{
    // Piece property enums
    enum class PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
    enum class PieceColor { WHITE, BLACK };

    // Constructor
    Piece(Board *board, PieceType type, PieceColor color, int x, int y);

    // Destructor
    ~Piece();

    // Static functions
    static bool canMove(Piece *piece, int x, int y);

    // Data members
    Board *board_;
    PieceType type_;
    PieceColor color_;
    int x_, y_;
};

// -----------------------------------------------------------------------------
// Board class
// -----------------------------------------------------------------------------
class Board
{
    public:
        // Move return type enums
        enum MoveReturnType { VALID, INVALID, BLOCKED };

        // Piece enumeration names
        enum BoardPiece {
            // Black
            BLACK_PAWN1, BLACK_PAWN2, BLACK_PAWN3, BLACK_PAWN4,
            BLACK_PAWN5, BLACK_PAWN6, BLACK_PAWN7, BLACK_PAWN8,
            BLACK_ROOK1, BLACK_ROOK2, BLACK_KNIGHT1, BLACK_KNIGHT2,
            BLACK_BISHOP1, BLACK_BISHOP2, BLACK_QUEEN, BLACK_KING,

            // White
            WHITE_PAWN1, WHITE_PAWN2, WHITE_PAWN3, WHITE_PAWN4,
            WHITE_PAWN5, WHITE_PAWN6, WHITE_PAWN7, WHITE_PAWN8,
            WHITE_ROOK1, WHITE_ROOK2, WHITE_KNIGHT1, WHITE_KNIGHT2,
            WHITE_BISHOP1, WHITE_BISHOP2, WHITE_QUEEN, WHITE_KING
        };

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

        void printBoard();

    private:
        const unsigned int MAX_X = 8;
        const unsigned int MAX_Y = 8;

        // Board matrix
        Piece *board[8][8];

        // Pieces array
        Piece *pieces[8 * 8];
};

