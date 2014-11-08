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
        void canMove(int x1, int y1, int x2, int y2);

    private:
        // Piece property enums
        enum PieceColor { WHITE, BLACK };

        // ---------------------------------------------------------------------
        // Piece structures
        // ---------------------------------------------------------------------
        // Piece interface
        struct Piece
        {
            Piece(int x, int y, PieceColor color);
            int x_, y_;
            PieceColor color_;
            virtual bool canMove(int x, int y) = 0;
        };

        struct Pawn: public Piece
        {
            Pawn(int x, int y, PieceColor color);
            bool canMove(int x, int y);
        };

        struct Rook: public Piece
        {
            Rook(int x, int y, PieceColor color);
            bool canMove(int x, int y);
        };

        struct Knight: public Piece
        {
            Knight(int x, int y, PieceColor color);
            bool canMove(int x, int y);
        };

        struct Bishop: public Piece
        {
            Bishop(int x, int y, PieceColor color);
            bool canMove(int x, int y);
        };

        struct Queen: public Piece
        {
            Queen(int x, int y, PieceColor color);
            bool canMove(int x, int y);
        };

        struct King: public Piece
        {
            King(int x, int y, PieceColor color);
            bool canMove(int x, int y);
        };

        // Board grid
        Piece* board[8][8];

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
};

