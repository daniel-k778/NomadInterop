#pragma once
#include "NomadCore.hpp"
#include <iostream>

#ifdef NOMADCORE_EXPORTS
#define NOMADCORE_API __declspec(dllexport)
#else
#define NOMADCORE_API __declspec(dllimport)
#endif

extern "C" {

    NOMADCORE_API NomadCore* CreateNomadCore();

    NOMADCORE_API void SetOutputPath(NomadCore* nomadCore, const char* path);

    NOMADCORE_API void SetNumberVariables(NomadCore* nomadCore, int numVars);

    NOMADCORE_API void SetInitialVariable(NomadCore* nomadCore, int index, double value);

    NOMADCORE_API void SetUpperBound(NomadCore* nomadCore, int index, double value);

    NOMADCORE_API void SetLowerBound(NomadCore* nomadCore, int index, double value);

    NOMADCORE_API void SetNumberOfIterations(NomadCore* nomadCore, int numIterations);

    NOMADCORE_API void SetNumberEBConstraints(NomadCore* nomadCore, int numEBConstraints);

    NOMADCORE_API void SetNumberPBConstraints(NomadCore* nomadCore, int numPBConstraints);

    NOMADCORE_API void SetEvaluator(NomadCore* nomadCore, BaseEvaluator* evaluator);

    NOMADCORE_API void Optimize(NomadCore* nomadCore);

}