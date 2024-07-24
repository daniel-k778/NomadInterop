#pragma once
#include "NomadCore.hpp"
#include "BaseEvaluator.hpp"
#include <iostream>
#include <vector>

#ifdef NOMADCORE_EXPORTS
#define NOMADCORE_API __declspec(dllexport)
#else
#define NOMADCORE_API __declspec(dllimport)
#endif

typedef void(__stdcall* EvaluateDelegate)(double* x, int m_NumVars, int numConstraints);
typedef void(__stdcall* GetConstraintsDelegate)(double* constraints);
typedef double(__stdcall* GetObjectiveFunctionDelegate)();

extern "C" {

    NOMADCORE_API NomadCore* CreateNomadCore();

    NOMADCORE_API void SetOutputPath(NomadCore* nomadCore, const char* path);

    NOMADCORE_API void SetNumberVariables(NomadCore* nomadCore, int numVars);

    NOMADCORE_API void SetInitialVariable(NomadCore* nomadCore, int index, double value);

    NOMADCORE_API void SetUpperBound(NomadCore* nomadCore, int index, double value);

    NOMADCORE_API void SetLowerBound(NomadCore* nomadCore, int index, double value);

    NOMADCORE_API void SetVariableType(NomadCore* nomadCore, int index, const char* type);

    NOMADCORE_API void SetNumberOfIterations(NomadCore* nomadCore, int numIterations);

    NOMADCORE_API void SetNumberEBConstraints(NomadCore* nomadCore, int numEBConstraints);

    NOMADCORE_API void SetNumberPBConstraints(NomadCore* nomadCore, int numPBConstraints);

    NOMADCORE_API void SetEvaluator(NomadCore* nomadCore, EvaluateDelegate evaluator, GetObjectiveFunctionDelegate m_GetObjectiveFunction, GetConstraintsDelegate m_GetConstraints);

    NOMADCORE_API void Optimize(NomadCore* nomadCore);

    NOMADCORE_API double* GetResults(NomadCore* nomadCore, int* size);
}
