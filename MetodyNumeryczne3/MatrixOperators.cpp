#include"Matrix.h"


Matrix Matrix::operator=(const Matrix & obj)
{
	if (matrix != nullptr)
		deleteMatrix(matrix, matrixDimension.y);
	matrix = createEmptyMatrix(obj.matrixDimension.y, obj.matrixDimension.x);
	matrixDimension.x = obj.matrixDimension.x;
	matrixDimension.y = obj.matrixDimension.y;
	for (int i = 0; i < obj.matrixDimension.y; i++) {
		for (int j = 0; j < obj.matrixDimension.x; j++) {
			matrix[i][j] = obj.matrix[i][j];
		}
	}
	return *this;
}



Matrix Matrix::operator+=(const Matrix & rM)
{
	for (int i = 0; i < rM.matrixDimension.y; i++) {
		for (int j = 0; j < rM.matrixDimension.x; j++) {
			matrix[i][j] += rM.matrix[i][j];
		}
	}
	return *this;
}



Matrix Matrix::operator-=(const Matrix & rM)
{
	for (int i = 0; i < rM.matrixDimension.y; i++) {
		for (int j = 0; j < rM.matrixDimension.x; j++) {
			matrix[i][j] -= rM.matrix[i][j];
		}
	}
	return *this;
}



Matrix Matrix::operator*=(const double c)
{
	for (int i = 0; i < this->matrixDimension.y; i++) {
		for (int j = 0; j < this->matrixDimension.x; j++) {
			matrix[i][j] *= c;
		}
	}
	return *this;
}



Matrix Matrix::operator*=(const Matrix & rM)
{
	double** newEmptyMatrix = Matrix::createEmptyMatrix(this->matrixDimension.y, rM.matrixDimension.x);
	double* rowL = new double[this->matrixDimension.x];
	double* colR = new double[rM.matrixDimension.y];
	double add;

	if (this->matrixDimension.x == rM.matrixDimension.y)
	{
		for (int i = 0; i < this->matrixDimension.y; i++)
		{
			for (int j = 0; j < rM.matrixDimension.x; j++)
			{
				add = 0;

				for (int k = 0; k < this->matrixDimension.x; k++) {
					rowL[k] = this->matrix[i][k];
				}
				for (int k = 0; k < rM.matrixDimension.y; k++) {
					colR[k] = rM.matrix[k][j];
				}

				for (int k = 0; k < this->matrixDimension.x; k++) {
					add += rowL[k] * colR[k];
				}

				newEmptyMatrix[i][j] = add;
			}
		}
	}
	else
	{
		matrixDimensionException ex = string("Invalid matrix dimentions for multiplication!");
		throw ex;
	}

	deleteMatrix(matrix, matrixDimension.y);

	this->matrix = newEmptyMatrix;
	this->matrixDimension.x = rM.matrixDimension.x;

	delete[] rowL;
	delete[] colR;

	return *this;
}



Matrix Matrix::operator/=(const Matrix & rM)
{
	Matrix Mat(rM);
	Matrix Temp(*this);
	Mat.transformIntoInvertedMatrix();
	Temp = Temp * Mat;
	double** newMatrix = Temp.getMatrixCopy();
	deleteMatrix(this->matrix, this->matrixDimension.y);
	this->matrix = newMatrix;
	return *this;
}



Matrix operator+(const Matrix & lM, const Matrix & rM)
{
	double** newEmptyMatrix = Matrix::createEmptyMatrix(lM.matrixDimension.y, lM.matrixDimension.x);

	if (lM.matrixDimension.x == rM.matrixDimension.x &&
		lM.matrixDimension.y == rM.matrixDimension.y) {

		for (int i = 0; i < lM.matrixDimension.y; i++) {
			for (int j = 0; j < lM.matrixDimension.x; j++) {
				newEmptyMatrix[i][j] = lM.matrix[i][j] + rM.matrix[i][j];
			}
		}
	}
	else
	{
		throw Matrix::generateMessage(lM.matrixDimension, rM.matrixDimension, Matrix::ADDITION);
	}

	Matrix temp(lM.matrixDimension.y, lM.matrixDimension.x, newEmptyMatrix);
	Matrix::deleteMatrix(newEmptyMatrix, lM.matrixDimension.y);
	return temp;
}



Matrix operator-(const Matrix & lM, const Matrix & rM)
{
	double** newEmptyMatrix = Matrix::createEmptyMatrix(lM.matrixDimension.y, lM.matrixDimension.x);

	if (lM.matrixDimension.x == rM.matrixDimension.x &&
		lM.matrixDimension.y == rM.matrixDimension.y) {

		for (int i = 0; i < lM.matrixDimension.y; i++) {
			for (int j = 0; j < lM.matrixDimension.x; j++) {
				newEmptyMatrix[i][j] = lM.matrix[i][j] - rM.matrix[i][j];
			}
		}
	}
	else
	{
		throw Matrix::generateMessage(lM.matrixDimension, rM.matrixDimension, Matrix::SUBTRACTION);
	}
	Matrix temp(lM.matrixDimension.y, lM.matrixDimension.x, newEmptyMatrix);
	Matrix::deleteMatrix(newEmptyMatrix, lM.matrixDimension.y);
	return temp;
}



Matrix operator*(const double c, const Matrix & rM)
{
	double** newEmptyMatrix = Matrix::createEmptyMatrix(rM.matrixDimension.x, rM.matrixDimension.y);

	for (int i = 0; i < rM.matrixDimension.y; i++) {
		for (int j = 0; j < rM.matrixDimension.x; j++) {
			newEmptyMatrix[i][j] *= c;
		}
	}

	return Matrix(rM.matrixDimension.y, rM.matrixDimension.x, newEmptyMatrix);
}



Matrix operator*(const Matrix & lM, const Matrix & rM)
{
	double** newEmptyMatrix = Matrix::createEmptyMatrix(lM.matrixDimension.y, rM.matrixDimension.x);
	double* rowL = new double[lM.matrixDimension.x];
	double* colR = new double[rM.matrixDimension.y];
	double add;

	if (lM.matrixDimension.x == rM.matrixDimension.y)
	{
		for (int i = 0; i < lM.matrixDimension.y; i++)
		{
			for (int j = 0; j < rM.matrixDimension.x; j++)
			{
				add = 0;

				for (int k = 0; k < lM.matrixDimension.x; k++) {
					rowL[k] = lM.matrix[i][k];
				}
				for (int k = 0; k < rM.matrixDimension.y; k++) {
					colR[k] = rM.matrix[k][j];
				}

				for (int k = 0; k < lM.matrixDimension.x; k++) {
					add += rowL[k] * colR[k];
				}

				newEmptyMatrix[i][j] = add;
			}
		}
	}
	else
	{
		throw  Matrix::generateMessage(lM.matrixDimension, rM.matrixDimension, Matrix::MULTIPLICATION);
	}

	delete[] rowL;
	delete[] colR;

	return Matrix(lM.matrixDimension.y, rM.matrixDimension.x, newEmptyMatrix);
}



Matrix operator/(const Matrix & lM, const Matrix & rM)
{
	if (lM.matrixDimension.x == rM.matrixDimension.y)
	{
		Matrix Mat(rM);
		Mat.transformIntoInvertedMatrix();
		Mat = lM * Mat;
		return Mat;
	}
	else
	{
		throw Matrix::generateMessage(lM.matrixDimension, rM.matrixDimension, Matrix::DIVISION);
	}
}
