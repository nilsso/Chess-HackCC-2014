#pragma once

class Board
{
    public:
        enum Piece { PAWN = 1, ROOK, KNIGHT, BISHOP, QUEEN, KING };
        
        Board();

        void move(int x1, int y1, int x2, int y2);

    private:
        int board[8][8];
};
