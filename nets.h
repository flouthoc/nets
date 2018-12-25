#ifndef NETS_H
#define NETS_H

#include <iostream>
#include "matrix.h"
#include "netsmath.h"

using namespace std;

class Nets{

	int hiddensNumber;
	int inputsNumber;
	int outputsNumber;
	Matrix<int> * hiddenWeights;
	Matrix<int> * outputWeights;
	Matrix<int> * inputs;

public:


		void dump();
		Matrix<int> * getHiddenWeights();
		Matrix<int> * getOutputWeights();
		void initparams(int, int, int);
		void initnetwork();
		Matrix<int> pr(Matrix<int> inputs);
		void tr(Matrix<int> inputs, Matrix<int> targets, int learningrate); /*backward propogation of errors*/
};


inline void Nets::dump(){

	cout<<"--------Dumping weights---------"<<endl;
	cout<<"********HiddenWeights********"<<endl;
	this->getHiddenWeights()->dump();
	cout<<"********OutputsWeights********"<<endl;
	this->getOutputWeights()->dump();	
}

inline Matrix<int> Nets::pr(Matrix<int> inputs){

	/*
		|----- Forward Propogation -----|
	*/

	/*
		To-do : Prepare sigmod function
	*/

	Matrix<int> hiddenInputs = hiddenWeights->dot(inputs);
	Matrix<int> hiddenOutputs = hiddenInputs.apply(Netsmath<int>::sigmod);
	Matrix<int> finalInput = outputWeights->dot(hiddenOutputs);
	Matrix<int> finalOutput = finalInput.apply(Netsmath<int>::sigmod);

	return finalOutput;

}


inline void Nets::tr(Matrix<int> inputs, Matrix<int> targets, int learningrate){

	/*
		|----- Backward Propogation ----|
	*/


	cout<<"Printing Input Dimensions"<<endl;
	cout<<inputs.getRowSize()<<" X "<<inputs.getColoumnSize()<<endl;


	cout<<"Printing Hidden Dimensions"<<endl;
	cout<<hiddenWeights->getRowSize()<<" X "<<hiddenWeights->getColoumnSize()<<endl;


	cout<<"Starting forward propogation"<<endl;


	// step 1 forward propogation
	Matrix<int> hiddenInputs = hiddenWeights->dot(inputs);
	Matrix<int> hiddenOutputs = hiddenInputs.apply(Netsmath<int>::sigmod);
	Matrix<int> finalInput = outputWeights->dot(hiddenInputs);
	Matrix<int> finalOutput = finalInput.apply(Netsmath<int>::sigmod);


	cout<<"Calculating Errors";
	//calculate errors
	Matrix<int> outputError = targets.subtract(finalOutput);
	Matrix<int> hiddenError = outputWeights->dot(outputError);


	cout<<"Starting Backpropogation";
	//backpropogate
	
	//change in outputWeights
	Matrix<int> sigmodprimematrix = finalOutput.apply(Netsmath<int>::sigmod);
	Matrix<int> tempmultiply = outputError.multiply(sigmodprimematrix);
	Matrix<int> hiddenOutputsTranspose = hiddenOutputs.transpose();
	Matrix<int> tempdot = tempmultiply.dot(hiddenOutputsTranspose);
	Matrix<int> tempScale = tempdot.scale(learningrate);
	(*outputWeights) = outputWeights->add(tempScale);

	//change in hiddenWeights
	Matrix<int> sigmodprimematrix2 = Netsmath<int>::sigmodprime(hiddenOutputs);//hiddenOutputs.apply(sigmodprime);
	Matrix<int> tempmultiply2 = hiddenError.multiply(sigmodprimematrix2);
	Matrix<int> inputTranspose = inputs.transpose();
	Matrix<int> tempdot2 = tempmultiply2.dot(inputTranspose);
	Matrix<int> tempScale2 = tempdot2.scale(learningrate);
	(*hiddenWeights) = hiddenWeights->add(tempScale2);

}


inline Matrix<int> * Nets::getHiddenWeights(){
	return this->hiddenWeights;
}

inline Matrix<int> * Nets::getOutputWeights(){
	return this->outputWeights;
}

inline void Nets::initparams(int hiddensNumber, int inputsNumber, int outputsNumber){

	this->hiddensNumber = hiddensNumber;
	this->inputsNumber = inputsNumber;
	this->outputsNumber = outputsNumber;
}


inline void Nets::initnetwork(){
	//hiddenWeights = new Matrix(hiddensNumber, inputsNumber);
	//outputsNumber = new Matrix(outputsNumber, hiddensNumber);
	hiddenWeights = Matrix<int>::generateRandom(hiddensNumber, inputsNumber);
	cout<<"initnetwork::Hidden Weights"<<hiddenWeights->getColoumnSize()<<endl;
	outputWeights = Matrix<int>::generateRandom(outputsNumber, hiddensNumber);
}

#endif




