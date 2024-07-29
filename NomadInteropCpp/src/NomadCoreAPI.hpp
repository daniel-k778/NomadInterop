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

typedef void(__stdcall* SingleObjInitDelegate)(int numConstraints);
typedef void (__stdcall* MultiObjInitDelegate)(int numConstraints, int numObjFunctions);

typedef void(__stdcall* EvaluateDelegate)(double* x, int numVars);
typedef void(__stdcall* GetConstraintsDelegate)(double* constraints);

typedef double(__stdcall* GetSingleObjFunctionDelegate)();
typedef void(__stdcall* GetMultiObjFunctionDelegate)(double* objFunctions);

extern "C" {
    class SingleObjEvaluatorWrapper : public BaseSingleObjEvaluator {
    public:
        EvaluateDelegate m_Evaluate;
        GetSingleObjFunctionDelegate m_GetObjectiveFunction;
        GetConstraintsDelegate m_GetConstraints;
        SingleObjInitDelegate m_Init;

        double m_Obj = 0.0;
        std::vector<double> m_Constraints;

        void Initialize( int numConstraints ) override;

        void Evaluate( double* x, int numVars ) override;

        double GetObjectiveFunction( void ) override;

        std::vector<double> GetConstraints( void ) override;
    };

    class MultiObjEvaluatorWrapper : public BaseMultiObjEvaluator {
    public:
        EvaluateDelegate m_Evaluate;
        GetMultiObjFunctionDelegate m_GetObjectiveFunction;
        GetConstraintsDelegate m_GetConstraints;
        MultiObjInitDelegate m_Init;

        std::vector<double> m_Obj;
        std::vector<double> m_Constraints;

        void Initialize( int numConstraints, int numObjFunctions ) override;

        void Evaluate( double* x, int m_NumVars ) override;

        std::vector<double> GetObjectiveFunction( void ) override;

        std::vector<double> GetConstraints( void ) override;
    };


    NOMADCORE_API NomadCore* CreateNomadCore( void );

    NOMADCORE_API void SetOutputPath( NomadCore* nomadCore, const char* path );

    NOMADCORE_API void SetNumberVariables( NomadCore* nomadCore, int numVars );

    NOMADCORE_API void SetInitialVariableValue( NomadCore* nomadCore, int index, double value );

    NOMADCORE_API void SetVariableUpperBound( NomadCore* nomadCore, int index, double value );

    NOMADCORE_API void SetVariableLowerBound( NomadCore* nomadCore, int index, double value );

    NOMADCORE_API void SetVariableType( NomadCore* nomadCore, int index, const char* type );

    NOMADCORE_API void SetNumberOfIterations( NomadCore* nomadCore, int numIterations );

    NOMADCORE_API void SetNumberEBConstraints( NomadCore* nomadCore, int numEBConstraints );

    NOMADCORE_API void SetNumberPBConstraints( NomadCore* nomadCore, int numPBConstraints );

    NOMADCORE_API void SetSingleObjEvaluator( NomadCore* nomadCore, EvaluateDelegate evaluator, GetSingleObjFunctionDelegate m_GetObjectiveFunction, GetConstraintsDelegate m_GetConstraints, SingleObjInitDelegate m_init );

    NOMADCORE_API void SetMultiObjEvaluator( NomadCore* nomadCore, EvaluateDelegate evaluator, GetMultiObjFunctionDelegate m_GetObjectiveFunction, GetConstraintsDelegate m_GetConstraints, MultiObjInitDelegate m_init );

    NOMADCORE_API void SetNumberObjFunctions( NomadCore* nomadCore, int numObjFunctions );

    NOMADCORE_API void OptimizeSingleObj( NomadCore* nomadCore );

    NOMADCORE_API void OptimizeMultiObj( NomadCore* nomadCore );

    NOMADCORE_API double* GetResults( NomadCore* nomadCore, int* size );
}
