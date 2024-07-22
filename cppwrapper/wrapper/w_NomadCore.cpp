#include "w_NomadCore.h"

extern "C" {

    NomadCore* CreateNomadCore()
    {
        return new NomadCore();
    }

    void SetOutputPath(NomadCore* nomadCore, const char* path)
    {
        nomadCore->SetOutputPath(path);
    }

    void SetNumberVariables(NomadCore* nomadCore, int numVars)
    {
        nomadCore->SetNumberVariables(numVars);
    }

    void SetInitialVariable(NomadCore* nomadCore, int index, double value)
    {
        nomadCore->SetInitialVariable(index, value);
    }

    void SetUpperBound(NomadCore* nomadCore, int index, double value)
    {
        nomadCore->SetUpperBound(index, value);
    }

    void SetLowerBound(NomadCore* nomadCore, int index, double value)
    {
        nomadCore->SetLowerBound(index, value);
    }

    void SetNumberOfIterations(NomadCore* nomadCore, int numIterations)
    {
        nomadCore->SetNumberOfIterations(numIterations);
    }

    void SetNumberEBConstraints(NomadCore* nomadCore, int numEBConstraints)
    {
        nomadCore->SetNumberEBConstraints(numEBConstraints);
    }

    void SetNumberPBConstraints(NomadCore* nomadCore, int numPBConstraints)
    {
        nomadCore->SetNumberPBConstraints(numPBConstraints);
    }

    void SetEvaluator(NomadCore* nomadCore, BaseEvaluator* evaluator)
    {
        nomadCore->SetEvaluator(evaluator);
    }

    void Optimize(NomadCore* nomadCore)
    {
        nomadCore->Optimize();
    }
}
