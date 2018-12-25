#include <iostream>
#include "nets.h"

using namespace std;


int main(){


	int numberofinputs = 2;
	int numberofoutputs = 2;
	int numberofhiddens = 3;


	int inputdatadismensions[] = {3,2};

	Nets * netsinstance;
	netsinstance = new Nets();

	netsinstance->initparams(numberofhiddens, numberofinputs, numberofoutputs);
	netsinstance->initnetwork();

	/*cout<<"dumping hidden weights"<<endl;
	netsinstance->getHiddenWeights()->dump();
	cout<<"dumping output weights"<<endl;
	netsinstance->getOutputWeights()->dump();*/


	/* ----- Dumping Weights before traning ----- */
	netsinstance->dump();

	Matrix<int> inputdata(2,1);
	int bufferforinput[2][1] = {{1},{2}};
	inputdata.populateFromArray(bufferforinput[0]);

	Matrix<int> targetdata(2,1);
	int bufferfortarget[2][1] = {{0},{0}};
	targetdata.populateFromArray(bufferfortarget[0]);

	netsinstance->tr(inputdata, targetdata, 1);

	/* ---- Dumping Weights after traning --- */
	netsinstance->dump();

	return 0;


}


