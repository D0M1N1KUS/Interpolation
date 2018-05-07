#pragma once
#include<fstream>
#include<string>
#include<random>
#include "MyArrayList.h"

using namespace std;

class DataReader
{
public:
	enum DocumentType
	{
		CSV,
		TXT_SPREADSHEET
	};

	DataReader(const char* path, DocumentType documentType);
	~DataReader();

	double** getDataFromFile();
	void grabDoubles(MyArrayList<double>* Arguments, MyArrayList<double>* Values);
	void copyListElementsToMemory(MyArrayList<double>* Arguments, MyArrayList<double>* Values);
	
	int getNrOfElementsPerDataSet();
	void printInfo();

private:
	ifstream InputFile;

	string TempFileName;

	double** data;
	int valuesPerDataSet;

	string generateTempFileName();

};
