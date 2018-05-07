#include "LinearFunction.h"
#include <exception>

LinearFunction::LinearFunction(const double* functionArguments, const double* functionValues,
	unsigned int size, Mode mode)
{
	this->size = size;
	this->initialFunctionArguments = this->allocateAndCopy(functionArguments);
	this->initialFunctionValues = this->allocateAndCopy(functionValues);
	this->accessMode = mode;
	this->h_j_ = nullptr;
	this->M_ = nullptr;

	if (mode == SKLEJANE)
		prepareSklejaneMethod();
}

double* LinearFunction::allocateAndCopy(const double* original)
{
	auto newTab = new double[this->size];

	for(auto i=0; i<this->size; i++)
	{
		newTab[i] = original[i];
	}
	return newTab;
}



LinearFunction::~LinearFunction()
{
	delete this->initialFunctionArguments;
	delete this->initialFunctionValues;
}

void LinearFunction::changeAccessMode(Mode mode)
{
	this->accessMode = mode;
}

double LinearFunction::F(double x)
{
	this->currentX = x;

	try { return getValueFromInitialValues(); }
	catch (std::exception e) {/*Argument not in initial arguments collection*/};

	if(this->accessMode == LAGRANGE)
	{
		return getValueUsingLagrangeMethod();
	}
	if(this->accessMode == SKLEJANE)
	{
		return getValueUsingSklejaneMethod();
	}
	typedef std::exception MethodNotImplemented;
	auto ex = new std::exception("LinearFunction::F(x) Method is not implemented.");
	throw ex;
}

double LinearFunction::getValueFromInitialValues()
{
	for(auto i = 0; i < this->size; i++)
	{
		if (currentX == initialFunctionArguments[i])
			return initialFunctionValues[i];
	}
	std::exception ArgumentNotFoundException = std::exception();
	throw ArgumentNotFoundException;
}


