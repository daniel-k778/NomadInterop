#include "NomadCore.hpp"
#include "BaseEvaluator.hpp"

class UserEvaluator : public BaseMultiObjEvaluator
{
private:
    vector<double> _obj;
    vector<double> _constraints;
    bool _objStatus = true;

    int _NumObjFunctions = 0;
    int _NumConstraints = 0;

public:
    UserEvaluator()
    {

    }

    ~UserEvaluator()
    {

    }

    void Initialize(int numConstraints, int numObjFunctions) {
        this->_NumObjFunctions = numObjFunctions;
        this->_NumConstraints = numConstraints;

        _obj.resize(numObjFunctions);
        _constraints.resize(numConstraints);
    }

    bool GetObjectiveFunctionStatus()
    {
        return _objStatus;
    }

    vector<double> GetObjectiveFunction()
    {
        return _obj;
    }

    vector<double> GetConstraints()
    {
        return _constraints;
    }

    void Evaluate(double* x, int _NumVars)
    {

        double c1 = 0.0, c2 = 0.0;
        for (int i = 0; i < _NumVars; i++)
        {
            c1 += std::pow((x[i] - 1.0), 2);
            c2 += std::pow((x[i] + 1), 2);
        }

        _obj[0] = x[4];
        _obj[1] = c1 - 25;
        _constraints[0] = 25 - c2;

        _objStatus = true;
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
