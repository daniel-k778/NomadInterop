#include <iostream>
#include "NomadCore.hpp"
#include "BaseEvaluator.hpp"
#include <cmath>
#include <vector>

class UserEvaluator : public BaseMultiObjEvaluator
{
private:
    std::vector<double> obj;
    std::vector<double> constraints;
    bool objStatus = true;

    int numObjFunctions = 0;
    int numConstraints = 0;

public:

    void Initialize(int numConstraints, int numObjFunctions) {
        this->numObjFunctions = numObjFunctions;
        this->numConstraints = numConstraints;

        obj.resize(numObjFunctions);
        constraints.resize(numConstraints);
    }

    bool GetObjectiveFunctionStatus()
    {
        return objStatus;
    }

    std::vector<double> GetObjectiveFunction()
    {
        return obj;
    }

    std::vector<double> GetConstraints()
    {
        return constraints;
    }

    void Evaluate(double* x, int _NumVars)
    {

        double c1 = 0.0, c2 = 0.0;
        for (int i = 0; i < _NumVars; i++)
        {
            c1 += std::pow((x[i] - 1.0), 2);
            c2 += std::pow((x[i] + 1), 2);
        }

        obj[0] = x[4];
        obj[1] = c1 - 25;
        constraints[0] = 25 - c2;

        objStatus = true;
    }
};


auto main() -> int {
    NomadCore* myMainWrapper = new NomadCore();
    myMainWrapper->SetOutputPath("sol.txt");

    int _NumVars = 5;
    myMainWrapper->SetNumberVariables(_NumVars);
    for (int i = 0; i < _NumVars; i++) {
        myMainWrapper->SetInitialVariableValue(i, 1.0);
        myMainWrapper->SetVariableType(i, "CONTINUOUS");
    }

    myMainWrapper->SetNumberOfIterations(100);
    myMainWrapper->SetNumberEBConstraints(2);
    myMainWrapper->SetNumberPBConstraints(3);

    UserEvaluator* myEval = new UserEvaluator();

    myMainWrapper->SetNumberObjFunctions(2);
    myMainWrapper->SetMultiObjEvaluator(myEval);
    myMainWrapper->OptimizeMultiObj();
}
