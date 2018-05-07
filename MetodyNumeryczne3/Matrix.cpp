#include "Matrix.h"


void Matrix::deleteMatrix(double** m, int y)
{
	for (int i = 0; i < y; i++) {
		delete[] m[i];
	}
	delete[] m;
}

double ** Matrix::cossOutRowAndColumn(double** m, int y, int x, int i, int j)
{
	double** newMatrix = createEmptyMatrix(y - 1, x - 1);
	int a = 0;
	int b = 0;
	for (int k = 0; k < y - 1; k++) {
		if (k != i) {
			for (int l = 0; l < x - 1; l++) {
				if (l != j) {
					newMatrix[a][b] = m[k][l];
					b++;
				}
			}
			a++;
		}
	}
	return newMatrix;
}

double ** Matrix::copyMatrix()
{
	double** newMatrix = createEmptyMatrix(matrixDimension.y, matrixDimension.x);
	for (int i = 0; i < matrixDimension.y; i++) {
		for (int j = 0; j < matrixDimension.x; j++) {
			newMatrix[i][j] = matrix[i][j];
		}
	}
	return newMatrix;
}

void Matrix::initWithZeros()
{
	double** newMatrix = createEmptyMatrix(matrixDimension.y, matrixDimension.x);
	for (int i = 0; i < matrixDimension.y; i++) {
		for (int j = 0; j < matrixDimension.x; j++) {
			newMatrix[i][j] = 0;
		}
	}
}

Matrix::Matrix(int y, int x, double** initTab)
{
	if (y <= 0 || x <= 0) {
		matrixDimensionException ex("Invalid matrix dimentions!");
		throw ex;
	}

	matrixDimension.x = x;
	matrixDimension.y = y;

	this->matrix = createEmptyMatrix(y, x);
	

	if (initTab != nullptr) {
		for (int i = 0; i < y; i++) {
			for (int j = 0; j < x; j++) {
				matrix[i][j] = initTab[i][j];
			}
		}
	}
	else
		initWithZeros();
}

Matrix::Matrix(const Matrix & obj)
{
	matrix = createEmptyMatrix(obj.matrixDimension.y, obj.matrixDimension.x);
	matrixDimension.x = obj.matrixDimension.x;
	matrixDimension.y = obj.matrixDimension.y;
	for (int i = 0; i < obj.matrixDimension.y; i++) {
		for (int j = 0; j < obj.matrixDimension.x; j++) {
			matrix[i][j] = obj.matrix[i][j];
		}
	}
}

Matrix::Matrix()
{
	this->matrix = nullptr;
	this->matrixDimension.y = 0;
	this->matrixDimension.x = 0;
}

Matrix::~Matrix()
{
	deleteMatrix(matrix, matrixDimension.y);
}



int Matrix::getWidth()
{
	return matrixDimension.x;
}

int Matrix::getHeight()
{
	return matrixDimension.y;
}

double Matrix::getElement(int m, int n)
{
	return matrix[m-1][n-1];
}

double** Matrix::getMatrixCopy()
{
	return copyMatrix();
}



double ** Matrix::createEyeMatrix(int n)
{
	double** newEye = createEmptyMatrix(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j == i)
				newEye[i][j] = 1;
			else
				newEye[i][j] = 0;
		}
	}
	return newEye;
}

double ** Matrix::createEmptyMatrix(int y, int x)
{
	double** newMatrix = new double*[y];
	for (int i = 0; i < y; i++) {
		newMatrix[i] = new double[x];
	}
	return newMatrix;
}



void Matrix::printMatrix()
{
	for (int i = 0; i < matrixDimension.y; i++) {
		for (int j = 0; j < matrixDimension.x; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}

}



double Matrix::norm()
{
	if (matrixDimension.y != 1 && matrixDimension.x != 1) {
		matrixDimensionException ex = std::string("This method only calculates the norm of vectors.");
		throw ex;
	}

	double ret = 0;

	for (int k = 0; k < matrixDimension.y; k++) {
		for (int l = 0; l < matrixDimension.x; l++) {
			ret += matrix[k][l] * matrix[k][l];
		}
	}
	return sqrt(ret);
}



double Matrix::abs(double a)
{
	a >= 0 ? a = a : a = -a;
	return a;
}
