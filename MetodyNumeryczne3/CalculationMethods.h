#pragma once

#include"Matrix.h"

Matrix* Metoda_Gaussa_Seidela(Matrix* Xin, Matrix* A, Matrix* b, double errorLimit, int iterationLimit, 
	int* iterations, double* error, double* elapsedSecs);

Matrix* Metoda_Jacobiego(Matrix* Xin, Matrix* A, Matrix* b, double errorLimit, int iterationLimit, 
	int* iterations, double* error, double* elapsedSecs);

Matrix* Eliminacja_Gaussa(Matrix* A, Matrix* b, double* error, double* elapsedSecs);