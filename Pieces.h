#ifndef _PIECES_
#define _PIECES_

class Pieces {
    public:

        int getBlockType(int pPiece, int pRotation, int pX, int pY);
        int getXInitialPos(int pPiece, int pRotation);
        int getYInitialPos(int pPiece, int pRotation);

};

#endif