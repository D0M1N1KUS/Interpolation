#include "LinearFunction.h"
#include "MyArrayList.h"


double LinearFunction::getValueUsingLagrangeMethod()
{
	MyArrayList<double> List_li = MyArrayList<double>();
	MyArrayList<double> List_L_x = MyArrayList<double>();
	
	for(auto i = 0; i < this->size; i++)
	{
		double f_xi = this->initialFunctionValues[i];
		List_li.emptyList();
		for(auto j = 0; j < this->size; j++)
		{
			if (j != i)
			{
				double li = (this->currentX - this->initialFunctionArguments[j]) /
					(this->initialFunctionArguments[i] - this->initialFunctionArguments[j]);
				List_li.sortInsert(li);
			}
		}
		double l = List_li.multiplyAllFromFirst();
		List_L_x.sortInsert(f_xi * l);
	}
	return List_L_x.sumAllFromFirst();
}

double LinearFunction::calculateW()
{
	MyArrayList<double> PolymonialW = MyArrayList<double>();
	for(auto i = 0; i < this->size; i++)
	{
		PolymonialW.sortInsert(this->currentX - this->initialFunctionArguments[i]);
	}
	return PolymonialW.multiplyAllFromFirst();
}

double LinearFunction::calculateSumOfComponents()
{
	MyArrayList<double> Components = MyArrayList<double>();
	for (auto i = 0; i < this->size; i++)
	{
		double denominator = calculateCurrentDenominator(i);

		double currentValue = this->initialFunctionValues[i];
		double fraction = currentValue / denominator;
		double fraction2 = 1 / (currentX - this->initialFunctionArguments[i]);
		Components.sortInsert(fraction*fraction2);
	}
	return Components.sumAllFromFirst();
}

double LinearFunction::calculateCurrentDenominator(int i)
{
	MyArrayList<double> Denominator = MyArrayList<double>();
	double currentValue = this->initialFunctionArguments[i];

	for (auto j = 0; j < this->size; j++) {
		if (this->initialFunctionArguments[j] - currentValue != 0)
		{
			Denominator.sortInsert(currentValue - initialFunctionArguments[j]);
		}
	}
	return Denominator.multiplyAllFromFirst();
}
