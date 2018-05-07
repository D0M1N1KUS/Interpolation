#include "Report.h"

void testAndReport(const char * inputFilePath, const char * outputFilePath, 
	LinearFunction::Mode calculationMethod, int partOfData, int nrOfValuesToCalculate)
{
	ofstream OutputFile;
	OutputFile.open(outputFilePath);

	DataReader reader(inputFilePath, DataReader::DocumentType::CSV);
	double** data = reader.getDataFromFile();

	double** halfTheData = new double*[2];
	halfTheData[0] = copyHalfTab(data[0], reader.getNrOfElementsPerDataSet(), partOfData);
	halfTheData[1] = copyHalfTab(data[1], reader.getNrOfElementsPerDataSet(), partOfData);

	LinearFunction ReportFunction = LinearFunction(halfTheData[0], halfTheData[1],
		reader.getNrOfElementsPerDataSet() / partOfData, calculationMethod);

	double min = data[0][0];
	double max = data[0][reader.getNrOfElementsPerDataSet() - 1];
	double increment = (max - min) / nrOfValuesToCalculate;

	double currentArgument = min;

	cout << setprecision(PRECISION) << fixed;

	cout << "Generating report... [";
	OutputFile << "X\tY" << endl;
	double i = 0;
	double percentage = 0.1;
	while(currentArgument < max)
	{
		if(i++/nrOfValuesToCalculate >= percentage)
		{
			cout << "-";
			percentage += 0.1;
		}
		OutputFile << currentArgument << "\t" << ReportFunction.F(currentArgument) << endl;
		currentArgument += increment;
	}
	cout << "] Done." << endl;


	delete[] halfTheData[0];
	delete[] halfTheData[1];
	delete[] halfTheData;
}

void testExistingValues(const char * inputFilePath, const char * outputFilePath, LinearFunction::Mode calculationMethod, 
	int partOfData)
{
	ofstream OutputFile;
	OutputFile.open(outputFilePath);

	DataReader reader(inputFilePath, DataReader::DocumentType::CSV);
	double** data = reader.getDataFromFile();

	double** halfTheData = new double*[2];
	halfTheData[0] = copyHalfOFTab(data[0], reader.getNrOfElementsPerDataSet());
	halfTheData[1] = copyHalfOFTab(data[1], reader.getNrOfElementsPerDataSet());

	LinearFunction ReportFunction = LinearFunction(halfTheData[0], halfTheData[1],
		reader.getNrOfElementsPerDataSet()/2 + 1, calculationMethod);

	double maxIndex = reader.getNrOfElementsPerDataSet();

	cout << setprecision(PRECISION) << fixed;

	cout << "Generating report... [";
	OutputFile << "X\tY" << endl;
	double percentage = 0.1;
	for(auto i = 0; i < reader.getNrOfElementsPerDataSet(); i++)
	{
		if (i / maxIndex >= percentage)
		{
			cout << "-";
			percentage += 0.1;
		}
		OutputFile << data[0][i] << "\t" << ReportFunction.F(data[0][i]) << endl;
	}
	cout << "] Done. Generated " << maxIndex << " values." << endl;

	delete[] halfTheData[0];
	delete[] halfTheData[1];
	delete[] halfTheData;

}
