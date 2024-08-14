#include "NomadCore.hpp"
#include "BaseEvaluator.hpp"

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
    int counter = 1; // counter for demonstrating the failure of the objective function

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

        if (counter % 2 == 0) { // Fail the objective function every other iteration
            objstatus = false; // set the objective function status(failure)
        }
        else {
            objstatus = true; // set the objective function status(success)
        }
        counter++;
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
        nomadCore->SetVariableType(i, NomadVariableType::CONTINUOUS);
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
    delete myEval;
}
