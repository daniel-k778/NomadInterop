#include "MainWrapper.hpp"


auto main(int argc, char** argv) -> int {
	MainWrapper* myMainWrapper = new MainWrapper(argc, argv);
	myMainWrapper->SetNumberOfVariables(5);
	myMainWrapper->SetVariables({0, 0, 0, 0, 0 });
	myMainWrapper->SetUpperBounds({ 5.0, 6.0, 7.0 });
	myMainWrapper->SetLowerBounds({ -6.0, -6.0, -6.0, -6.0, -6.0 });
	myMainWrapper->SetNumberOfIterations(100);
	myMainWrapper->Optimize();
	myMainWrapper->SetOutputTypes
}