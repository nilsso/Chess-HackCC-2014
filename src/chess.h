#pragma once

#include <string>

using namespace std;

class Board
{
    public:
        // Move return type enums
        enum MoveReturnType { VALID, INVALID, BLOCKED };
        // Board constructor
        Board();

        // Setup function
        /*
         * Sets up a brand new chess board.
         */
        void setup();

        // Move function
        /*
         * Attempts to move a piece from position 1 to position 2. Checks to
         * see if the piece can move to the destination based on piece move
         * rulesets (bishop only moves diagonally, pawn forward except for
         * attacking, etc.), and then if it the piece is blocked from moving
         * to that position. If move is valid, move the piece and process the
         * resulting board state (was a piece killed?). Lastly return the
         * return type (valid, invalid, etc.).
         *
         * @param email The email of the player attempting to move a piece.
         * @param x1 Origin x-coordinate.
         * @param y1 Origin y-coordinate.
         * @param x2 Destination x-coordinate.
         * @param y2 Destination y-coordinate.
         */
        void move(string email, int x1, int y1, int x2, int y2);

    private:
        // Piece property enums
        enum PieceType { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
        enum PieceColor { WHITE, BLACK };

        // Piece struct
        struct Piece
        {
            PieceType type_;
            PieceColor color_;
        };
        
        Piece* board[8][8];
};
