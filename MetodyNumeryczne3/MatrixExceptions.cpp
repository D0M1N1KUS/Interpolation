#include<string>
#include"Matrix.h"


matrixDimensionException Matrix::generateMessage(Dimention lM, Dimention rM, int operationType)
{
	string leftSize, rightSize;
	leftSize = "Left: " + lM.y + 'x' + lM.x;
	rightSize = " Right: " + rM.y + 'x' + rM.x;

	matrixDimensionException ex;
	if (operationType == OperationType::MULTIPLICATION) {
		 ex = "Invalid matrix dimentions for multiplication! " + 
			leftSize + rightSize;
	}
	else if (operationType == OperationType::DIVISION) {
		ex = "Invalid matrix dimentions for division! " +
			leftSize + rightSize;
	}
	else if (operationType == OperationType::INVERSION) {
		ex = "When there\'s actually no such exception thrown anywhere, but you\'ll get this here anyway... well, you\'re screwed :'(";
	}
	else if (operationType == OperationType::ADDITION) {
		ex = "Dimentions of matrices must be identical during addition! " +
			leftSize + rightSize;
	}
	else if (operationType == OperationType::SUBTRACTION) {
		ex = "Dimentions of matrices must be identical during subtraction! " +
			leftSize + rightSize;
	}

	return ex;
}