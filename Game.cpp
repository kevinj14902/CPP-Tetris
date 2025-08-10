#ifndef LINUX
#include <windows.h>
#endif
#include "Game.h"

int Game::GetRand(int pA, int pB) {
    return rand() % (pB - pA + 1) + pA;
}

void Game::InitGame() {
    srand((unsigned int)time(NULL));

    mPiece = GetRand(0 ,6);
    mRotation = GetRand(0, 3);
    mPosX = (BOARD_WIDTH / 2) + mPieces -> getXInitialPos(mPiece, mRotation);
    mPosY = mPieces -> getYInitialPos(mPiece, mRotation);

    mNextPiece = GetRand (0, 6);
    mNextRotation = GetRand (0, 3);
    mNextPosX = BOARD_WIDTH + 5;
    mNextPosY = 5;
}

void Game::CreateNewPiece() {
    mPiece = mNextPiece;
    mRotation = mNextRotation;
    mPosX = (BOARD_WIDTH / 2) + mPieces -> getXInitialPos (mPiece, mRotation);
    mPosY = mPieces -> getYInitialPos (mPiece, mRotation);

    mNextPiece = GetRand (0, 6);
    mNextRotation = GetRand (0, 3);
}

void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation) {
    color mColor;

    int mPixelsX = mBoard -> getXPosInPixels(pX);
    int mPixelsY = mBoard -> getYPosInPixels(pY);

    for (int i = 0; i < PIECE_BLOCKS; i++) {
        for (int j = 0; j < PIECE_BLOCKS; j++) {
            switch(mPieces -> getBlockType(pPiece, pRotation, i, j)) {
                case 1: mColor = GREEN;
                break;
                case 2: mColor = BLUE;
                break;
            }
            if (mPieces -> getBlockType(pPiece, pRotation, i, j) != 0) {
                mIO -> DrawRectangle(mPixelsX + i * BLOCK_SIZE, mPixelsY + j * BLOCK_SIZE, (mPixelsX + i * BLOCK_SIZE) + BLOCK_SIZE - 1, (mPixelsY + j * BLOCK_SIZE) + BLOCK_SIZE - 1, mColor);
            }
        }
    }
}

void Game::DrawBoard() {
    int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    mIO -> DrawRectangle(mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);
    mIO -> DrawRectangle(mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);

    mX1 += 1;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            if(!mBoard -> isFreeBlock(i, j)) {
                mIO -> DrawRectangle(mX1 + i * BLOCK_SIZE, mY + j * BLOCK_SIZE, (mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1, (mX2 + j * BLOCK_SIZE) + BLOCK_SIZE - 1, RED);
            }
        }
    }
}

void Game::DrawScene() {
    DrawBoard();
    DrawPiece(mPosX, mPosY, mPiece, mRotation);
    DrawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);
}