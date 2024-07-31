#include "NomadCore.hpp"
#include "BaseEvaluator.hpp"

//class UserEvaluator : public BaseMultiObjEvaluator
//{
//private:
//    vector<double> _obj;
//    vector<double> _constraints;
//    bool _objStatus = true;
//
//    int _NumObjFunctions = 0;
//    int _NumConstraints = 0;
//
//public:
//    UserEvaluator()
//    {
//
//    }
//
//    ~UserEvaluator()
//    {
//
//    }
//
//    void Initialize(int numConstraints, int numObjFunctions) {
//        this->_NumObjFunctions = numObjFunctions;
//        this->_NumConstraints = numConstraints;
//
//        _obj.resize(numObjFunctions);
//        _constraints.resize(numConstraints);
//    }
//
//    bool GetObjectiveFunctionStatus()
//    {
//        return _objStatus;
//    }
//
//    vector<double> GetObjectiveFunction()
//    {
//        return _obj;
//    }
//
//    vector<double> GetConstraints()
//    {
//        return _constraints;
//    }
//
//    void Evaluate(double* x, int _NumVars)
//    {
//
//        double c1 = 0.0, c2 = 0.0;
//        for (int i = 0; i < _NumVars; i++)
//        {
//            c1 += std::pow((x[i] - 1.0), 2);
//            c2 += std::pow((x[i] + 1), 2);
//        }
//
//        _obj[0] = x[4];
//        _obj[1] = c1 - 25;
//        _constraints[0] = 25 - c2;
//
//        _objStatus = true;
//    }
//};
//
//
//auto main() -> int {
//    NomadCore* myMainWrapper = new NomadCore();
//    myMainWrapper->SetOutputPath("sol.txt");
//
//    int _NumVars = 5;
//    myMainWrapper->SetNumberVariables(_NumVars);
//    for (int i = 0; i < _NumVars; i++) {
//        myMainWrapper->SetInitialVariableValue(i, 1.0);
//        myMainWrapper->SetVariableType(i, "CONTINUOUS");
//    }
//
//    myMainWrapper->SetNumberOfIterations(100);
//    myMainWrapper->SetNumberEBConstraints(2);
//    myMainWrapper->SetNumberPBConstraints(3);
//
//    UserEvaluator* myEval = new UserEvaluator();
//
//    myMainWrapper->SetNumberObjFunctions(2);
//    myMainWrapper->SetMultiObjEvaluator(myEval);
//    myMainWrapper->OptimizeMultiObj();
//}

/*--------------------------------------------*/
/*             evaluator creation             */
/*--------------------------------------------*/
class myEvaluator : public BaseSingleObjEvaluator
{
private:
    double obj = 0.0; // objective function value
    vector<double> constraints; // constraint values
    bool objstatus = true; // objective function status (success/failure)
    int numConstraints = 0; // number of constraints

public:
    void Initialize(int numConstraints) {
        // Required method for implementing the derived BaseSingleObjEvaluator class.
        // Note: this function can be used to initialize any part of the evaluator.

        this->numConstraints = numConstraints;
        constraints.resize(numConstraints);
    }

    bool GetObjectiveFunctionStatus()
    {
        // Required method for implementing the derived BaseSingleObjEvaluator class.
        // This function is used to return the status of the objective function evaluation.

        return objstatus;
    }

    double GetObjectiveFunction()
    {
        // Required method for implementing the derived BaseSingleObjEvaluator class.
        // This function is used to return the objective function value.

        return obj;
    }

    vector<double> GetConstraints()
    {
        // Required method for implementing the derived BaseSingleObjEvaluator class.
        // This function is used to return the constraint values.

        return constraints;
    }

    void Evaluate(double* x, int numVars)
    {
        // Required method for implementing the derived BaseSingleObjEvaluator class.
        // This function is used to evaluate the objective function and constraints.

        double c1 = 0.0, c2 = 0.0;
        for (int i = 0; i < numVars; i++)
        {
            c1 += std::pow((x[i] - 1.0), 2);
            c2 += std::pow((x[i] + 1), 2);
        }

        obj = x[4]; // set the objective function
        constraints[0] = c1 - 25; // set the first constraint
        constraints[1] = 25 - c2; // set the second constraint

        objstatus = true; // set the objective function status
    }
};

/*--------------------------------------------*/
/*                main program                */
/*--------------------------------------------*/
auto main() -> int {

    // Create an instance of the NomadCore class
    NomadCore* nomadCore = new NomadCore();

    // Set the number of variables, initial values, and types
    int numVars = 5;
    nomadCore->SetNumberVariables(numVars);
    for (int i = 0; i < numVars; i++) {
        nomadCore->SetInitialVariableValue(i, 1.0);
        nomadCore->SetVariableType(i, "CONTINUOUS");
    }

    // Set the number of iterations
    nomadCore->SetNumberOfIterations(100);

    // Set the number of extreme and progressive barrier constraints
    nomadCore->SetNumberEBConstraints(2);
    nomadCore->SetNumberPBConstraints(3);

    // Set the evaluator
    myEvaluator* myEval = new myEvaluator();
    nomadCore->SetSingleObjEvaluator(myEval);

    // Optimize the problem
    nomadCore->OptimizeSingleObj();

    delete nomadCore;
}
