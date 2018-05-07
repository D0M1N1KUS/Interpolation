#include "LinearFunction.h"
#include "Matrix.h"
#include "CalculationMethods.h"
#include <thr/xthrcommon.h>



double LinearFunction::getValueUsingSklejaneMethod()
{
	int currentJ = getCurrentIndex();

	double a_j = this->initialFunctionValues[currentJ];
	double b_j = (this->initialFunctionValues[currentJ + 1] - a_j) / this->h_j_[currentJ + 1];
	double c_j = this->M_[currentJ] / 2;
	double d_j = (this->M_[currentJ + 1] - this->M_[currentJ]) / (6 * this->h_j_[currentJ + 1]);

	double x_jDiff = this->currentX - this->initialFunctionArguments[currentJ];
	
	return (a_j + b_j*(x_jDiff) + c_j*potega(x_jDiff, 2) + d_j*potega(x_jDiff, 3));
}

int LinearFunction::getCurrentIndex()
{
	for (auto i = 0; i <= this->size; i++)
	{
		if (this->currentX >= initialFunctionArguments[i] &&
			this->currentX <= initialFunctionArguments[i + 1] &&
			i < this->size - 1)
		{
			return i;
		}
	}
	exception IndexNotFoundException = exception("LinearFunction::getValueUsingSklejaneMethod: Not able to find matching j-value");
	throw IndexNotFoundException;
}

//This function needs heavy polishing, but I'm not sure if this sorcery-function will work correctly
void LinearFunction::prepareSklejaneMethod()
{
	double* h_j = getH_Values();
	double* u_j = getU_Values(h_j);
	double*delta_j = getDeltaValues(h_j);
	double* lambda_j = getLambdaValues(h_j);

	double** deltaMatrix = new double*;
	deltaMatrix[0] = delta_j;

	double** inputTab = allocateInputTab();
	setUpInputTab(u_j, lambda_j, inputTab);
	double** emptyVector = createEmptyVector();
	double** M_Matrix =	calculateM_Values_CSI_Algorithm(inputTab, emptyVector);

	deleteAllVectorsAndMatrices(u_j, delta_j, lambda_j, deltaMatrix, inputTab, emptyVector, M_Matrix);
}

double* LinearFunction::getH_Values()
{
	double* h_j = new double[this->size - 1];
	for (auto i = 0; i < this->size - 1; i++)
	{
		h_j[i + 1] = initialFunctionArguments[i + 1] - initialFunctionArguments[i];
	}
	this->h_j_ = h_j;
	return h_j;
}

double* LinearFunction::getU_Values(double* h_j)
{
	double* u_j = new double[this->size];
	u_j[this->size - 1] = 0;
	for (auto i = 0; i < this->size - 1; i++)
	{
		u_j[i] = h_j[i] / (h_j[i] + h_j[i + 1]);
	}
	return u_j;
}

double* LinearFunction::getDeltaValues(double* h_j)
{
	double* delta_j = new double[this->size];
	delta_j[0] = 0;
	delta_j[this->size - 1] = 0;
	for (auto i = 1; i < this->size - 1; i++)
	{
		delta_j[i] = (6 / (h_j[i] + h_j[i + 1])) *
			((this->initialFunctionValues[i + 1] - initialFunctionValues[i]) / h_j[i + 1] -
				this->initialFunctionValues[i] - initialFunctionValues[i - 1]);
	}
	return delta_j;
}

double* LinearFunction::getLambdaValues(double* h_j)
{
	double* lambda_j = new double[this->size];
	lambda_j[0] = 0;
	for (auto i = 1; i < this->size - 1; i++)
	{
		lambda_j[i] = h_j[i + 1] / (h_j[i] + h_j[i + 1]);
	}
	return lambda_j;
}

double** LinearFunction::allocateInputTab()
{
	double** inputTab = new double*[this->size];
	for (auto i = 0; i < this->size; i++)
	{
		inputTab[i] = new double[this->size];
	}
	return inputTab;
}

void LinearFunction::setUpInputTab(double* u_j, double* lambda_j, double** inputTab)
{
	for (auto i = 0; i < this->size; i++)
	{
		for (auto j = 0; j < this->size; j++)
		{
			if (i == j)
			{
				inputTab[i][j] = 2;
			}
			else if (j == i + 1)
			{
				inputTab[i][j] = lambda_j[i];
			}
			else if (i == j + 1)
			{
				inputTab[i][j] = u_j[i];
			}
			else
			{
				inputTab[i][j] = 0;
			}
		}
	}
}

double** LinearFunction::createEmptyVector()
{
	double** emptyVector = new double*[this->size];
	for (auto i = 0; i < this->size; i++)
	{
		emptyVector[i] = new double;
		emptyVector[i][1] = 0;
	}
	return emptyVector;
}

void LinearFunction::deleteAllVectorsAndMatrices(double* u_j, double* delta_j, double* lambda_j, double** deltaMatrix, double** inputTab, double** emptyVector, double** M_Matrix)
{
	delete[] emptyVector;

	for (auto i = 0; i < this->size; i++)
	{
		delete[] inputTab[i];
		delete M_Matrix[i];
	}
	delete[] M_Matrix;
	delete[] inputTab;
	delete[] delta_j;
	delete[] lambda_j;
	delete[] u_j;
	delete deltaMatrix;
}

void LinearFunction::copySolutionsToThisObject(double** M_Matrix)
{
	this->M_ = new double[this->size];
	for (auto i = 0; i < this->size; i++)
	{
		this->M_[i] = M_Matrix[i][1];
	}
}

double** LinearFunction::calculateM_Values_CSI_Algorithm(double** inputTab, double** emptyVector)
{
	Matrix CSI_Matrix = Matrix(this->size, this->size, inputTab);
	Matrix Solution = Matrix(this->size, 1, emptyVector);

	Metoda_Gaussa_Seidela(&Solution, &CSI_Matrix, &Solution, 0.000000000000001, 1000, nullptr, nullptr, nullptr);

	double** M_Matrix = Solution.getMatrixCopy();
	copySolutionsToThisObject(M_Matrix);

	return M_Matrix;
}

double LinearFunction::potega(double a, int x)
{
	double result = 1;
	for(auto i = 0; i < x; i++)
	{
		result *= a;
	}
	return result;
}
