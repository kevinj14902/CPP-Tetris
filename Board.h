#ifndef _BOARD_
#define _BOARD_
#include "Pieces.h"
#define BOARD_LINE_WIDTH 6
#define BLOCK_SIZE 16
#define BOARD_POSITION 320
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define MIN_VERTICAL_MARGIN 20
#define MIN_HORIZONTAL_MARGIN 20
#define PIECE_BLOCKS 5

class Board {
    public:
        Board(Pieces *pPieces, int pScreenHeight);

        int getXPosInPixels(int pPos);
        int getYPosInPixels(int pPos);
        bool isFreeBlock(int pX, int pY);
        bool isPossibleMove(int pX, int pY, int pPiece, int pRotation);
        void storePiece(int pX, int pY, int pPiece, int pRotation);
        void deletePossibleLines();
        bool isGameOver();

        private:
            enum{POS_FREE, POS_FULL};
            int mBoard[BOARD_WIDTH][BOARD_HEIGHT];
            Pieces *mPieces;
            int mScreenHeight;

            void initBoard();
            void deleteLine(int pY);
};

#endif