#include"Matrix.h"

void Matrix::transpose()
{
	double** newMatrix = getTransposed();
	deleteMatrix(matrix, matrixDimension.y);
	matrix = newMatrix;
}

double ** Matrix::getTransposed()
{
	double** newMatrix = createEmptyMatrix(matrixDimension.y, matrixDimension.x);

	for (int i = 0; i < matrixDimension.y; i++) {
		for (int j = 0; j < matrixDimension.x; j++) {
			newMatrix[j][i] = matrix[i][j];
		}
	}

	return newMatrix;
}
