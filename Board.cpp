#include "Board.h"

void Board::initBoard() {
    for (int i = 0; i < BOARD_WIDTH; i++){
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            mBoard[i][j] = POS_FREE;
        }
    }
};

void Board::storePiece(int pX, int pY, int pPiece, int pRotation) {
    for (int i1 = pX, i2 = pX; i1 < PIECE_BLOCKS; i1++, i2++) {
        for (int j1 = pY, j2 = pY; j1 < PIECE_BLOCKS; j1++, j2++) {
            if (mPieces -> getBlockType(pPiece, pRotation, j2, i2) != 0) {
                mBoard[i1][j1] = POS_FULL;
            }
        }
    }
}

bool Board::isGameOver() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mBoard[i][0] == POS_FULL) {
            return true;
        }
    }
    return false;
}

void Board::deleteLine(int pY) {
    for (int i = pY; i > 0; i--) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            mBoard[i][j] = mBoard[i][j - 1];
        }
    }
}

void Board::deletePossibleLines() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        while(int j = 0 < BOARD_WIDTH) {
            if (mBoard[i][j] != POS_FULL) {
                break;
                i++;
            }
            if (i == POS_FULL) {
                deleteLine(j);
            }
        }
    }
}

bool Board::isFreeBlock(int pX, int pY) {
    if (mBoard[pX][pY] != POS_FULL) {
        return true;
    }
    else {
        return false;
    }
}

int Board::getXPosInPixels(int pPos) {
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}

int Board::getYPosInPixels(int pPos) {
    return ((mScreenHeight - (BLOCK_SIZE * (BOARD_WIDTH))) + (pPos * BLOCK_SIZE));
}

bool Board::isPossibleMove(int pX, int pY, int pPiece, int pRotation) {
    for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++) {
        for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++) {
            if (i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1) {
                if (mPieces -> getBlockType(pPiece, pRotation, j2, i2) != 0) {
                    return 0;
                }
            }
            if (j1 >= 0) {
                if ((mPieces -> getBlockType(pPiece, pRotation, j2, i2)) != 0 && (!isFreeBlock(i1, j1))) {
                    return false;
                }
            }
        }
    }
    return true;
}