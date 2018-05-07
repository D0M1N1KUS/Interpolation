#include "CalculationMethods.h"
#include<ctime>

Matrix* Metoda_Gaussa_Seidela(Matrix* Xin, Matrix* A, Matrix* b, double errorLimit, int iterationLimit, 
	int* iterations, double* error, double* elapsedSecs)
{
	int nrOfIterations = 0;
	double Err = errorLimit + 1;

	Matrix Xout(*Xin);
	Matrix Res;
	
	Matrix::M_DUL* M = A->getDUL_Matrices();

	int heightA = A->getHeight();
	int widthA = A->getWidth();

	clock_t begin, end;
	begin = clock();
	
	double** temp = (*M->D + *M->L).getMatrixCopy();
	Matrix d_plus_l(heightA, widthA, temp);
	Matrix inv_d_plus_l(heightA, widthA, temp);
	inv_d_plus_l.transformIntoInvertedMatrix();
	double** temp2 = (inv_d_plus_l * *M->U).getMatrixCopy();
	Matrix inv_d_plus_l_times_U(heightA, widthA, temp2);

	while (Err > errorLimit) {
		nrOfIterations++;
		Xout =  inv_d_plus_l * *b - inv_d_plus_l_times_U * Xout;
		Res = ((*A * Xout) - *b);
		Err = Res.norm();
		if (nrOfIterations == iterationLimit)
			break;
	}

	end = clock();
	if (elapsedSecs != nullptr)
		*elapsedSecs = double(end - begin) / CLOCKS_PER_SEC;

	Matrix* Outcome = new Matrix(Xout);

	if (iterations != nullptr)
		*iterations = nrOfIterations;
	if (error != nullptr)
		*error = Err;

	Matrix::deleteMatrix(temp, heightA);
	Matrix::deleteMatrix(temp2, heightA);

	return Outcome;
}

Matrix* Metoda_Jacobiego(Matrix* Xin, Matrix* A, Matrix* b, double errorLimit, int iterationLimit, int* iterations, 
	double* error, double* elapsedSecs)
{
	int nrOfIterations = 0;
	double Err = errorLimit + 1;

	Matrix Xout(*Xin);
	Matrix Res;

	Matrix::M_DUL* M = A->getDUL_Matrices();

	int heightA = A->getHeight();
	int widthA = A->getWidth();

	

	double** temp = (*M->L + *M->U).getMatrixCopy();

	

	Matrix l_plus_u(heightA, widthA, temp);
	Matrix inv_d(*M->D);

	clock_t begin, end;
	begin = clock();

	inv_d.transformIntoInvertedMatrix();

	double** temp2 = (inv_d*l_plus_u).getMatrixCopy();
	Matrix inv_d_times_l_plus_u(heightA, widthA, temp2);

	while (Err > errorLimit) {
		nrOfIterations++;
		Xout = inv_d * *b - inv_d_times_l_plus_u*Xout;
		Res = ((*A * Xout) - *b);
		Err = Res.norm();
		if (nrOfIterations == iterationLimit)
			break;
	}

	end = clock();
	if (elapsedSecs != nullptr)
		*elapsedSecs = double(end - begin) / CLOCKS_PER_SEC;

	Matrix* Outcome = new Matrix(Xout);

	*iterations = nrOfIterations;
	*error = Err;

	Matrix::deleteMatrix(temp, heightA);
	Matrix::deleteMatrix(temp2, heightA);

	return Outcome;
}
