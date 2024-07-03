#include "NomadCore.hpp"


auto main(int argc, char** argv) -> int {
	NomadCore* myMainWrapper = new NomadCore(argc, argv);
	myMainWrapper->SetOutputPath("sol.txt");

	int numVars = 5;
	myMainWrapper->SetNumberVariables(numVars);
	for (int i = 0; i < numVars; i++) {
		myMainWrapper->SetInitialVariable(i, 1.0);
		myMainWrapper->SetUpperBound(i, 5.0);
		myMainWrapper->SetLowerBound(i, -6.0);
	}

	myMainWrapper->SetNumberOfIterations(100);
	myMainWrapper->SetNumberEBConstraints(2);
	myMainWrapper->SetNumberPBConstraints(3);

	myMainWrapper->Optimize();
}