/*
 * Author: Dominikus Noah Preugszas 160752
 * Project: Metody numeryczne: projekt 3 aproksymacja interpolacyjna
 * 
 * main.cpp - generates reports and catches exceptions
 */

#include<iostream>
#include<iomanip>

#include "LinearFunction.h"
#include "DataReader.h"
#include "Matrix.h"
#include "Report.h"

using namespace std;

int main()
{
	try {
		testExistingValues("trasaAlpyIn.txt", "Reports3\\AlpyLagrFirstHalf.txt", LinearFunction::Mode::LAGRANGE, 32);
		testExistingValues("trasaAlpyIn.txt", "Reports3\\AlpySklejFirstHalf.txt", LinearFunction::Mode::SKLEJANE, 32);	
	}
	catch (exception e)
	{
		cout << endl << e.what() << endl;
		system("pause");
		exit(1);
	}
	catch(matrixDimensionException e)
	{
		cout << e << endl;
		system("pause");
		exit(1);
	}
	system("pause");
	return 0;
}


