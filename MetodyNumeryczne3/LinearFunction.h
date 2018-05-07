/*
 * Author: Dominikus Noah Preugszas
 * 
 * Linear function.cpp - declares a class responsible for preparing and 
 * calculating interpolated function values. There are two calculation methods
 * to choose from, while constructing the object: Lagrange'e and Spline
 * 
 * Methods are defined across the files:
 *		LinearFunction.cpp, Lagrange.cpp and Sklejane.cpp
 */
#pragma once

class LinearFunction
{
public:
	enum Mode
	{
		LAGRANGE,
		SKLEJANE
	};
	
	double* allocateAndCopy(const double* original);

	LinearFunction(const double* functionArguments, const double* functionValues, 
		unsigned int size, Mode mode);
	~LinearFunction();


	void changeAccessMode(Mode mode);
	double F(double x);

private:
	unsigned size;
	double* initialFunctionArguments;
	double* initialFunctionValues;

	Mode accessMode;
	
	double currentX;

	double getValueFromInitialValues();

	double getValueUsingLagrangeMethod();
	double calculateW();
	double calculateCurrentDenominator(int i);
	double calculateSumOfComponents();

	double* h_j_;
	double* M_;	

	double getValueUsingSklejaneMethod();
	int getCurrentIndex();
	
	void prepareSklejaneMethod();
	double* getH_Values();
	double* getU_Values(double* h_j);
	double* getDeltaValues(double* h_j);
	double* getLambdaValues(double* h_j);
	double** allocateInputTab();
	void setUpInputTab(double* u_j, double* lambda_j, double** inputTab);
	double** createEmptyVector();
	void deleteAllVectorsAndMatrices(double* u_j, double* delta_j, double* lambda_j, double** deltaMatrix, double** inputTab, double** emptyVector, double** M_Matrix);
	void copySolutionsToThisObject(double** M_Matrix);
	double** calculateM_Values_CSI_Algorithm(double** inputTab, double** emptyVector);

	static double potega(double a, int x);
};
