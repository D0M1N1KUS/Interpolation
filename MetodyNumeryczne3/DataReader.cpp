#include "DataReader.h"
#include "MyArrayList.h"

/*
 *Data reader object to read data from csv files and other types of files
 *
 * This is actually a little bit messy. I planned to do a modifier function,
 * that converts a csv file. But that would be to timeconsuming, since I'm a 
 * newbie at file operations and writing interpreters :/
 */

DataReader::DataReader(const char* path, DocumentType documentType) {
	this->valuesPerDataSet = 0;
	this->data = nullptr;
	this->InputFile.open(path, ofstream::in);
	if(!InputFile.is_open())
	{
		exception FailedToOpenfileException = exception("DataReader: Failed to open input file!");
		throw FailedToOpenfileException;
	}
}

DataReader::~DataReader()
{
	if (InputFile.is_open()) 
	{
		this->InputFile.close();
	}
	delete[] this->data[0];
	delete[] this->data[1];
	delete[] this->data;
}

double** DataReader::getDataFromFile()
{
	if(this->data != nullptr)
	{
		return data;
	}

	MyArrayList<double> Arguments = MyArrayList<double>();
	MyArrayList<double> Values = MyArrayList<double>();
	
	grabDoubles(&Arguments, &Values);

	if(Arguments.size() != Values.size())
	{
		std::exception ValueNumberNotEqualException = std::exception("The number of values and agruments must be the same");
	}

	copyListElementsToMemory(&Arguments, &Values);
	this->valuesPerDataSet = Arguments.size();
	return this->data;
}

void DataReader::grabDoubles(MyArrayList<double>* Arguments, MyArrayList<double>* Values)
{
	while (!this->InputFile.eof())
	{
		double temp;
		InputFile >> temp;
		Arguments->pushBack(temp);
		InputFile >> temp;
		Values->pushBack(temp);
	}
}

void DataReader::copyListElementsToMemory(MyArrayList<double>* Arguments, MyArrayList<double>* Values)
{
	double** data = new double*[2];
	data[0] = new double[Arguments->size()];
	data[1] = new double[Values->size()];

	for (auto i = 0; i < Arguments->size(); i++)
	{
		data[0][i] = Arguments->at(i);
		data[1][i] = Values->at(i);
	}
	this->data = data;
}

int DataReader::getNrOfElementsPerDataSet()
{
	return this->valuesPerDataSet;
}

string DataReader::generateTempFileName()
{
	string randomTempFileName;
	while (true)
	{
		randomTempFileName = string(to_string(rand()));
		ifstream file(randomTempFileName);
		if (!file.good())
			break;
	}
	randomTempFileName += ".temp";
	this->TempFileName = randomTempFileName;
	return randomTempFileName;
}
