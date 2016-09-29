void vCopyMatrix(Matrix mSource, Matrix mDestination);
void vTransposeMatrix(Matrix mSrcDst);
void vRightMultiply(Matrix mMat1, Matrix mMat2);
void vTranslate(float fTrans, char cAxis, Matrix mMat);

void vCalcRotVec(float fNewX, float fNewY,
                 float fOldX, float fOldY,
                 float fDiameter,
                 float *fVecX, float *fVecY, float *fVecZ);

void vAxisRotMatrix(float fVecX, float fVecY, float fVecZ, Matrix mNewMat);
