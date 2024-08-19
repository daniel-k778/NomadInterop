#include "NomadCore.hpp"
#include "BaseEvaluator.hpp"

/*--------------------------------------------*/
/*             evaluator creation             */
/*--------------------------------------------*/
class UserEvaluator : public BaseMultiObjEvaluator
{
private:
    vector<double> obj; // Objective function values
    vector<double> constraints; // Constraint values
    bool objStatus = true; // Objective function status (success/failure)
    int numObjFunctions = 0; // Number of objective functions
    int numConstraints = 0; // Number of constraints

public:

    void Initialize(int numConstraints, int numObjFunctions) {
        // Required method for implementing the derived BaseMultiObjEvaluator class.
        // Note: this function can be used to initialize any part of the evaluator.

        this->numObjFunctions = numObjFunctions;
        this->numConstraints = numConstraints;

        obj.resize(numObjFunctions);
        constraints.resize(numConstraints);
    }

    bool GetObjectiveFunctionStatus()
    {
        // Required method for implementing the derived BaseMultiObjEvaluator class.
        // This function is used to return the status of the objective function evaluation.

        return objStatus;
    }

    vector<double> GetObjectiveFunction()
    {
        // Required method for implementing the derived BaseMultiObjEvaluator class.
        // This function is used to return a vector of objective function values.

        return obj;
    }

    vector<double> GetConstraints()
    {
        // Required method for implementing the derived BaseMultiObjEvaluator class.
        // This function is used to return the constraint values.

        return constraints;
    }

    void Evaluate(double* x, int numVars)
    {
        // Required method for implementing the derived BaseMultiObjEvaluator class.
        // This function is used to evaluate the objective function and constraints.

        double c1 = 0.0, c2 = 0.0;
        for (int i = 0; i < numVars; i++)
        {
            c1 += std::pow((x[i] - 1.0), 2);
            c2 += std::pow((x[i] + 1), 2);
        }

        obj[0] = x[4]; // Set the first objective function
        obj[1] = c1 - 25; // Set the second objective function
        constraints[0] = 25 - c2; // Set the first constraint

        objStatus = true; // Set the objective function status(success)
    }
};

/*--------------------------------------------*/
/*                main program                */
/*--------------------------------------------*/
auto main() -> int {

    // Create an instance of the NomadCore class
    NomadCore* nomadCore = new NomadCore();

    // Set the output path(optional)
    nomadCore->SetOutputPath("sol.txt");

    // Set the number of variables, initial values, and types
    int numVars = 5;
    nomadCore->SetNumberVariables(numVars);
    for (int i = 0; i < numVars; i++) {
        nomadCore->SetInitialVariableValue(i, 1.0);
        nomadCore->SetVariableType(i, NOMAD_VARIABLE_TYPE_CONTINUOUS);
    }

    // Set the number of iterations
    nomadCore->SetNumberOfIterations(100);

    // Set the number of extreme and progressive barrier constraints
    nomadCore->SetNumberEBConstraints(2);
    nomadCore->SetNumberPBConstraints(3);

    // Set the number of objective functions
    nomadCore->SetNumberObjFunctions(2);

    // Set the evaluator
    UserEvaluator* myEval = new UserEvaluator();
    nomadCore->SetMultiObjEvaluator(myEval);

    // Run the optimization
    nomadCore->OptimizeMultiObj();

    delete nomadCore;
    delete myEval;
}