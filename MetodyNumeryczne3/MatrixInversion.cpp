#include"Matrix.h"

bool Matrix::transformIntoInvertedMatrix()
{
	double** invertedMatrix = getInvertedMatrix();
	if (invertedMatrix == nullptr)
		return false;
	deleteMatrix(this->matrix, matrixDimension.y);
	this->matrix = invertedMatrix;
	return true;
}



bool Matrix::transformIntoLU_Matrix()
{
	double** newMatrix = getLU_ComboMatrix();
	if (newMatrix == nullptr)
		return false;
	deleteMatrix(this->matrix, matrixDimension.y);
	this->matrix = newMatrix;
	return true;
}



double** Matrix::getLU_ComboMatrix()
{
	if (matrixDimension.x != matrixDimension.y) {
		matrixDimensionException ex = std::string("The LU transformation works only for square matrices!\n");
		throw ex;
	}
	double** newMatrix = copyMatrix();
	double sum;
	for (int j = 0; j < matrixDimension.x; j++) {
		if (abs(newMatrix[j][j]) < EPSILON) {
			deleteMatrix(newMatrix, matrixDimension.y);
			return nullptr;
		}
		for (int i = 0; i <= j; i++) {
			sum = 0;
			for (int k = 0; k < i; k++) {
				sum += newMatrix[i][k] * newMatrix[k][j];
			}
			newMatrix[i][j] -= sum;
		}
		for (int i = j + 1; i < matrixDimension.x; i++) {
			sum = 0;
			for (int k = 0; k < j; k++) {
				sum += newMatrix[i][k] * newMatrix[k][j];
			}
			newMatrix[i][j] = (newMatrix[i][j] - sum) / newMatrix[j][j];
		}
	}
	return newMatrix;
}



Matrix::LU_Matrices * Matrix::getLU_Matrices()
{
	double** LU_ComboMatrix = getLU_ComboMatrix();
	if (LU_ComboMatrix == nullptr)
		return nullptr;

	LU_Matrices* LUs = new LU_Matrices;
	double** tempL = createEmptyMatrix(matrixDimension.y, matrixDimension.x);
	double** tempU = createEmptyMatrix(matrixDimension.y, matrixDimension.x);

	for (int i = 0; i < matrixDimension.y; i++) {
		for (int j = 0; j < matrixDimension.x; j++) {
			if (j >= i) {
				tempU[i][j] = LU_ComboMatrix[i][j];
				tempL[i][j] = 0;
			}
			if (i > j) {
				tempL[i][j] = LU_ComboMatrix[i][j];
				tempU[i][j] = 0;
			}
		}
		tempL[i][i] = 1;
	}

	LUs->L = new Matrix(matrixDimension.y, matrixDimension.x, tempL);
	LUs->U = new Matrix(matrixDimension.y, matrixDimension.x, tempU);

	deleteMatrix(tempL, matrixDimension.y);
	deleteMatrix(tempU, matrixDimension.y);
	return LUs;
}



Matrix::LUI_Matrices * Matrix::getLUI_Matrices()
{
	double** LU_ComboMatrix = getLU_ComboMatrix();
	if (LU_ComboMatrix == nullptr)
		return nullptr;

	LUI_Matrices* LUIs = new LUI_Matrices;
	double** tempL = createEmptyMatrix(matrixDimension.y, matrixDimension.x);
	double** tempU = createEmptyMatrix(matrixDimension.y, matrixDimension.x);
	double** tempI = createEmptyMatrix(matrixDimension.y, matrixDimension.x);

	for (int i = 0; i < matrixDimension.y; i++) {
		for (int j = 0; j < matrixDimension.x; j++) {
			if (i < j) {
				tempU[i][j] = LU_ComboMatrix[i][j];
				tempL[i][j] = 0;
			}
			if (i > j) {
				tempL[i][j] = LU_ComboMatrix[i][j];
				tempU[i][j] = 0;
			}
			tempI[i][j] = 0;
		}
		tempI[i][i] = 1;
	}

	LUIs->L = new Matrix(matrixDimension.y, matrixDimension.x, tempL);
	LUIs->U = new Matrix(matrixDimension.y, matrixDimension.x, tempU);
	LUIs->I = new Matrix(matrixDimension.y, matrixDimension.x, tempI);

	deleteMatrix(tempL, matrixDimension.y);
	deleteMatrix(tempU, matrixDimension.y);
	deleteMatrix(tempI, matrixDimension.y);
	return LUIs;
}



Matrix::M_DUL* Matrix::getDUL_Matrices()
{
	if (matrixDimension.y != matrixDimension.x) {
		matrixDimensionException ex = std::string("Can\'t get DUL matrices out of given one!");
		throw ex;
	}

	double** D = createEmptyMatrix(matrixDimension.y, matrixDimension.x);
	double** U = createEmptyMatrix(matrixDimension.y, matrixDimension.x);
	double** L = createEmptyMatrix(matrixDimension.y, matrixDimension.x);

	for (int i = 0; i < matrixDimension.y; i++) {
		for (int j = 0; j < matrixDimension.x; j++) {
			if (i == j) {
				D[i][j] = matrix[i][j];

				U[i][j] = 0;
				L[i][j] = 0;
			}
			if (i < j) {
				U[i][j] = matrix[i][j];

				D[i][j] = 0;
				L[i][j] = 0;
			}
			if (i > j) {
				L[i][j] = matrix[i][j];

				D[i][j] = 0;
				U[i][j] = 0;
			}
		}
	}

	Matrix* newD = new Matrix(matrixDimension.y, matrixDimension.x, D);
	Matrix* newU = new Matrix(matrixDimension.y, matrixDimension.x, U);
	Matrix* newL = new Matrix(matrixDimension.y, matrixDimension.x, L);

	deleteMatrix(D, matrixDimension.y);
	deleteMatrix(U, matrixDimension.y);
	deleteMatrix(L, matrixDimension.y);

	M_DUL* Matrices = new M_DUL;
	Matrices->D = newD;
	Matrices->U = newU;
	Matrices->L = newL;
	
	return Matrices;
}



double** Matrix::getInvertedMatrix()
{
	double** LU_cMatrix = getLU_ComboMatrix();
	if (LU_cMatrix == nullptr)
		return nullptr;

	double** X = createEyeMatrix(matrixDimension.y);
	int n = matrixDimension.y;

	double sum;
	for (int k = 0; k < matrixDimension.y; k++) {
		for (int i = 1; i < n; i++) {
			sum = 0;
			for (int j = 0; j < i; j++) {
				sum += LU_cMatrix[i][j] * X[j][k];
			}
			X[i][k] -= sum;
		}

		if (fabs(LU_cMatrix[n - 1][n - 1]) < EPSILON)
			return nullptr;
		X[n - 1][k] /= LU_cMatrix[n - 1][n - 1];
		for (int i = n - 2; i >= 0; i--) {
			sum = 0;
			for (int j = i + 1; j < n; j++) {
				sum += LU_cMatrix[i][j] * X[j][k];
			}
			if (fabs(LU_cMatrix[i][i]) < EPSILON)
				return nullptr;
			X[i][k] = (X[i][k] - sum) / LU_cMatrix[i][i];
		}
	}
	return X;
}