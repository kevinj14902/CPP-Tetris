#include "Game.h"
#ifndef LINUX
#include <windows.h>
#endif

#ifndef LINUX
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
{
	IO mIO;
	int mScreenHeight = mIO.GetScreenHeight();
	Pieces mPieces;
	Board mBoard(&mPieces, mScreenHeight);
	Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);
	unsigned long mTime1 = SDL_GetTicks();

	while (!mIO.IsKeyDown (SDLK_ESCAPE)) {
		mIO.ClearScreen();
		mGame.DrawScene();
		mIO.UpdateScreen();

		int mKey = mIO.Pollkey();

		switch (mKey) {
			case (SDLK_RIGHT): 
			{
				if (mBoard.isPossibleMove(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX++;
					break;
			}

			case (SDLK_LEFT): 
			{
				if (mBoard.isPossibleMove(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
					mGame.mPosX--;	
				break;
			}

			case (SDLK_DOWN):
			{
				if (mBoard.isPossibleMove(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
					mGame.mPosY++;	
				break;
			}

			case (SDLK_x):
			{
				while(mBoard.isPossibleMove(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { 
                    mGame.mPosY++; 
                }
	
				mBoard.storePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

				mBoard.deletePossibleLines();

				if (mBoard.isGameOver()) {
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();

				break;
			}

			case (SDLK_z):
			{
				if (mBoard.isPossibleMove(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4)) {
					mGame.mRotation = (mGame.mRotation + 1) % 4;
                }
				break;
			}
		}

		// ----- Vertical movement -----

		unsigned long mTime2 = SDL_GetTicks();

		if ((mTime2 - mTime1) > WAIT_TIME) {
			if (mBoard.isPossibleMove(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation)) {
				mGame.mPosY++;
			}
			else {
				mBoard.storePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);

				mBoard.deletePossibleLines();

				if (mBoard.isGameOver()) {
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();
			}

			mTime1 = SDL_GetTicks();
		}
	}

	return 0;
}
