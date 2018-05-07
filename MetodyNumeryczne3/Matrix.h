#pragma once
#include<string>
#include<iostream>

using namespace std;

struct Dimention {
	int x = 0;
	int y = 0;
};



typedef string matrixDimensionException;
typedef string matrixAdditionException;

class Matrix
{
private:
	const double EPSILON = 1e-12;

	Dimention matrixDimension;
	double** matrix;

	double** cossOutRowAndColumn(double** m, int y, int x, int i, int j);
	double** copyMatrix();
	void initWithZeros();

	static matrixDimensionException generateMessage(Dimention lM, Dimention rM, int operationType);

public:
	struct LU_Matrices {
		Matrix* L;
		Matrix* U;
	};

	struct LUI_Matrices {
		Matrix* L = nullptr;
		Matrix* U = nullptr;
		Matrix* I = nullptr;
	};

	struct M_DUL {
		Matrix* D = nullptr;
		Matrix* U = nullptr;
		Matrix* L = nullptr;
	};

	enum OperationType {
		ADDITION,
		SUBTRACTION,
		MULTIPLICATION,
		DIVISION,
		INVERSION
	};

	//creates a m*n matrix
	Matrix(int m, int n, double** initTab);
	Matrix(const Matrix &obj);
	Matrix();
	~Matrix();

	
	void transpose();
	double** getTransposed();

	bool transformIntoInvertedMatrix();
	bool transformIntoLU_Matrix();

	double** getLU_ComboMatrix();
	LU_Matrices* getLU_Matrices();
	LUI_Matrices* getLUI_Matrices();
	M_DUL* getDUL_Matrices();
	double** getInvertedMatrix();

	double norm();
	

	void printMatrix();
	int getWidth();
	int getHeight();
	double getElement(int m, int n);
	double** getMatrixCopy();


	static double** createEmptyMatrix(int m, int n);
	static double** createEyeMatrix(int n);
	static void deleteMatrix(double** m, int y);


	Matrix operator=(const Matrix& obj);
	friend Matrix operator+(const Matrix& lM, const Matrix& rM);
	Matrix operator+=(const Matrix& rM);
	friend Matrix operator-(const Matrix& lM, const Matrix& rM);
	Matrix operator-=(const Matrix& rM);
	friend Matrix operator*(const double c, const Matrix& rM);
	Matrix operator*=(const double c);
	friend Matrix operator*(const Matrix& lM, const Matrix& rM);
	Matrix operator*=(const Matrix& rM);
	friend Matrix operator/(const Matrix& lM, const Matrix& rM);
	Matrix operator/=(const Matrix& rM);

	static double abs(double a);

private:

};

