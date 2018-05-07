#pragma once
#include<iostream>
#include<iomanip>
#include<conio.h>
#include<fstream>

#include "LinearFunction.h"
#include "DataReader.h"

#define PRECISION 15

void testAndReport(const char* inputFilePath, const char* outputFilePath,
	LinearFunction::Mode calculationMethod, int partOfData, int nrOfValuesToCalculate);

void testExistingValues(const char* inputFilePath, const char* outputFilePath,
	LinearFunction::Mode calculationMethod, int partOfData);

template<typename T>
T* copyTab(T* tab, int size)
{
	T* newTab = new T[size];
	for (auto i = 0; i < size; i++)
	{
		newTab[i] = tab[i];
	}
	return newTab;
}

template<typename T>
T* copyHalfTab(T* tab, int size, int part)
{
	T* newTab = new T[(size / part) + 1];
	auto j = 0;
	auto i = 0;
	while (i < size)
	{
		newTab[j] = tab[i];
		j++;
		i += part;
	}
	newTab[j] = tab[511];
	return newTab;
}

template<typename T>
T* copyHalfOFTab(T* tab, int size)
{
	T* newTab = new T[(size / 2) + 1];
	auto i = 0;
	for (; i < size/2 + 1; i++)
	{
		newTab[i] = tab[i];
	}
	newTab[i] = tab[size - 1];
	newTab[++i] = tab[size - 1];
	return newTab;
}
