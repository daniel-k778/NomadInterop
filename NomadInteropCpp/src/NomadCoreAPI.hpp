/**
 \file   NomadCoreAPI.hpp
 \brief  NOMAD core functions (headers)
 \author
 \date   2024-07-29
 \see    NomadCoreAPI.cpp
 */

#ifndef NOMADCOREAPI_H
#define NOMADCOREAPI_H

#include "NomadCore.hpp"
#include "BaseEvaluator.hpp"
#include <iostream>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifdef NOMADCORE_EXPORTS
#define NOMADCORE_API __declspec( dllexport )
#else
#define NOMADCORE_API __declspec( dllimport )
#endif

 /// Delegate for initializing a single-objective evaluator.
 /**
  \param numConstraints Number of constraints -- \b IN.
  */
typedef void( __stdcall* SingleObjInitDelegate )( int numConstraints );

/// Delegate for initializing a multi-objective evaluator.
/**
 \param numConstraints Number of constraints -- \b IN.
 \param numObjFunctions Number of objective functions -- \b IN.
 */
typedef void( __stdcall* MultiObjInitDelegate )( int numConstraints, int numObjFunctions );

/// Delegate for evaluating the objective function.
/**
 \param x Array of variables -- \b IN.
 \param numVars Number of variables -- \b IN.
 */
typedef void( __stdcall* EvaluateDelegate )( double* x, int numVars );

/// Delegate for retrieving constraint values.
/**
 \param constraints Array to store constraint values -- \b OUT.
 */
typedef void( __stdcall* GetConstraintsDelegate )( double* constraints );

/// Delegate for retrieving the status of the objective function.
/**
 \return Status of the objective function.
 */
typedef bool( __stdcall* GetObjectiveFunctionStatusDelegate )( void );

/// Delegate for retrieving the value of a single objective function.
/**
 \return Value of the single objective function.
 */
typedef double( __stdcall* GetSingleObjFunctionDelegate )( void );

/// Delegate for retrieving values of multiple objective functions.
/**
 \param objFunctions Array to store objective function values -- \b OUT.
 */
typedef void( __stdcall* GetMultiObjFunctionDelegate )( double* objFunctions );


extern "C"
{
    /// Class for wrapping a single-objective evaluator.
    class SingleObjEvaluatorWrapper : public BaseSingleObjEvaluator {

    public:
        EvaluateDelegate                     _Evaluate;                    ///< Delegate for evaluating the objective function.
        GetSingleObjFunctionDelegate         _GetObjectiveFunction;        ///< Delegate for retrieving the value of the objective function.
        GetConstraintsDelegate               _GetConstraints;              ///< Delegate for retrieving constraint values.
        SingleObjInitDelegate                _Inititialize;                ///< Delegate for initializing the evaluator.
        GetObjectiveFunctionStatusDelegate   _GetObjectiveFunctionStatus;  ///< Delegate for retrieving the status of the objective function.

        double              _Obj = 0.0;            ///< Value of the objective function.
        bool                _ObjStatus = true;     ///< Status of the objective function.
        std::vector<double> _Constraints;          ///< Array to store constraint values.


        /// Initializes the evaluator.
        /**
         \param numConstraints Number of constraints -- \b IN.
         */
        void Initialize( int numConstraints ) override;

        /// Evaluates the objective function.
        /**
         \param x Array of variables -- \b IN.
         \param numVars Number of variables -- \b IN.
         */
        void Evaluate( double* x, int numVars ) override;

        /// Retrieves the value of the objective function.
        /**
         \return Value of the objective function.
         */
        double GetObjectiveFunction( void ) override;

        /// Retrieves the status of the objective function.
        /**
         \return Status of the objective function.
         */
        bool GetObjectiveFunctionStatus( void ) override;

        /// Retrieves constraint values.
        /**
         \return Array of constraint values.
         */
        std::vector<double> GetConstraints( void ) override;
    };

    /// Class for wrapping a multi-objective evaluator.
    class MultiObjEvaluatorWrapper : public BaseMultiObjEvaluator {
    public:
        EvaluateDelegate                      _Evaluate;                   ///< Delegate for evaluating the objective function.
        GetMultiObjFunctionDelegate           _GetObjectiveFunction;       ///< Delegate for retrieving the value of the objective function.
        GetConstraintsDelegate                _GetConstraints;             ///< Delegate for retrieving constraint values.
        MultiObjInitDelegate                  _Inititialize;               ///< Delegate for initializing the evaluator.
        GetObjectiveFunctionStatusDelegate    _GetObjectiveFunctionStatus; ///< Delegate for retrieving the status of the objective function.

        std::vector<double> _Obj;              ///< Array to store objective function values.
        std::vector<double> _Constraints;      ///< Array to store constraint values.
        bool                _ObjStatus = true; ///< Status of the objective function.

        /// Initializes the evaluator.
        /**
         \param numConstraints Number of constraints -- \b IN.
         \param numObjFunctions Number of objective functions -- \b IN.
         */
        void Initialize( int numConstraints, int numObjFunctions ) override;

        /// Evaluates the objective function.
        /**
         \param x Array of variables -- \b IN.
         \param numVars Number of variables -- \b IN.
         */
        void Evaluate( double* x, int numVars ) override;

        /// Retrieves the value of the objective function.
        /**
         \return Array of objective function values.
         */
        std::vector<double> GetObjectiveFunction( void ) override;

        /// Retrieves the status of the objective function.
        /**
         \return Status of the objective function.
         */
        bool GetObjectiveFunctionStatus( void ) override;

        /// Retrieves constraint values.
        /**
         \return Array of constraint values.
         */
        std::vector<double> GetConstraints( void ) override;
    };

    /// Creates a NomadCore object.
    /**
     \return NomadCore object.
     */
    NOMADCORE_API NomadCore* CreateNomadCore( void );

    /// Sets the output path for results.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \param path Output path -- \b IN.
     */
    NOMADCORE_API void SetOutputPath( NomadCore* nomadCore, const char* path );

    /// Sets the number of variables.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \param numVars Number of variables -- \b IN.
     */
    NOMADCORE_API void SetNumberVariables( NomadCore* nomadCore, int numVars );

    /// Sets the initial value of a variable.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \param index Index of the variable -- \b IN.
     \param value Initial value of the variable -- \b IN.
     */
    NOMADCORE_API void SetInitialVariableValue( NomadCore* nomadCore, int index, double value );

    /// Sets the upper bound of a variable.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \param index Index of the variable -- \b IN.
     \param value Upper bound of the variable -- \b IN.
     */
    NOMADCORE_API void SetVariableUpperBound( NomadCore* nomadCore, int index, double value );

    /// Sets the lower bound of a variable.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \param index Index of the variable -- \b IN.
     \param value Lower bound of the variable -- \b IN.
     */
    NOMADCORE_API void SetVariableLowerBound( NomadCore* nomadCore, int index, double value );

    /// Sets the type of a variable.
    /**
    * - "CONTINUOUS"
    * - "INTEGER"
    * - "BINARY"
    * - "CATEGORICAL"
     \param nomadCore NomadCore object -- \b IN.
     \param index Index of the variable -- \b IN.
     \param type Type of the variable -- \b IN.
     */
    NOMADCORE_API void SetVariableType( NomadCore* nomadCore, int index, const char* type );

    /// Sets the number of iterations.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \param numIterations Number of iterations -- \b IN.
     */
    NOMADCORE_API void SetNumberOfIterations( NomadCore* nomadCore, int numIterations );

    /// Sets the number of EB constraints.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \param numEBConstraints Number of extreme barrier constraints -- \b IN.
     */
    NOMADCORE_API void SetNumberEBConstraints( NomadCore* nomadCore, int numEBConstraints );

    /// Sets the number of PB constraints.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \param numPBConstraints Number of progressive barrier constraints -- \b IN.
     */
    NOMADCORE_API void SetNumberPBConstraints( NomadCore* nomadCore, int numPBConstraints );

    /// Sets the single-objective evaluator.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \param evaluator Delegate for evaluating the objective function -- \b IN.
     \param getObjectiveFunction Delegate for retrieving the value of the objective function -- \b IN.
     \param getConstraints Delegate for retrieving constraint values -- \b IN.
     \param init Delegate for initializing the evaluator -- \b IN.
     \param getObjectiveFunctionStatus Delegate for retrieving the status of the objective function -- \b IN.
     */
    NOMADCORE_API void SetSingleObjEvaluator
    ( NomadCore*                         nomadCore                   , 
      EvaluateDelegate                   evaluator                   , 
      GetSingleObjFunctionDelegate       getObjectiveFunction        ,
      GetConstraintsDelegate             getConstraints              ,
      SingleObjInitDelegate              init                        ,
      GetObjectiveFunctionStatusDelegate getObjectiveFunctionStatus );

    /// Sets the multi-objective evaluator.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \param evaluator Delegate for evaluating the objective function -- \b IN.
     \param getObjectiveFunction Delegate for retrieving the value of the objective function -- \b IN.
     \param getConstraints Delegate for retrieving constraint values -- \b IN.
     \param init Delegate for initializing the evaluator -- \b IN.
     \param getObjectiveFunctionStatus Delegate for retrieving the status of the objective function -- \b IN.
     */
    NOMADCORE_API void SetMultiObjEvaluator
    ( NomadCore*                         nomadCore                   , 
      EvaluateDelegate                   evaluator                   , 
      GetMultiObjFunctionDelegate        getObjectiveFunction        , 
      GetConstraintsDelegate             getConstraints              , 
      MultiObjInitDelegate               init                        , 
      GetObjectiveFunctionStatusDelegate getObjectiveFunctionStatus );

    /// Sets the number of objective functions.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \param numObjFunctions Number of objective functions -- \b IN.
     */
    NOMADCORE_API void SetNumberObjFunctions( NomadCore* nomadCore, int numObjFunctions );

    /// Optimizes a single-objective function.
    /**
     \param nomadCore NomadCore object -- \b IN.
     */
    NOMADCORE_API void OptimizeSingleObj( NomadCore* nomadCore );

    /// Optimizes multiple objective functions.
    /**
     \param nomadCore NomadCore object -- \b IN.
     */
    NOMADCORE_API void OptimizeMultiObj( NomadCore* nomadCore );

    /// Retrieves the optimizer results.
    /**
     \param nomadCore NomadCore object -- \b IN.
     \return Array of results.
     */
    NOMADCORE_API double* GetResults( NomadCore* nomadCore, int* size );
}

#endif // NOMADCOREAPI_H
