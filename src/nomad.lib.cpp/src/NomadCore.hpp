/**
 \file   NomadCore.hpp
 \brief  DLL exports for NOMAD core functions and class definitions (headers)
 \date   2024-07-29
 \see    NomadCore.cpp
 */

#ifndef __NOMADCORE_H__
#define __NOMADCORE_H__

#include "nomad.hpp"
#include "BaseEvaluator.hpp"
#include "Defines.hpp"

#ifdef NOMADCORE_EXPORTS
#define NOMADCORE_API __declspec( dllexport )
#else
#define NOMADCORE_API __declspec( dllimport )
#endif

/// NOMAD core class.
class NOMADCORE_API NomadCore
{
private:
    const char*     _OutputPath = nullptr;            ///< Output path.
    int             _NumVars = 0;                     ///< Number of variables.
    int             _NumIterations = 100;             ///< Number of iterations.
    int             _NumPBConstraints = 0;            ///< Number of progressive barrier constraints.
    int             _NumEBConstraints = 0;            ///< Number of extreme barrier constraints.
    int             _NumObjFunctions = 1;             ///< Number of objective functions.

    std::vector<double>         _InitialVarsVec = { };              ///< Initial variables. Stores the initial values of the variables.
    std::vector<double>         _FinalVariables = { };              ///< Final variables. Stores the optimizer results.
    std::vector<double>         _UpperBoundValueVec = { };          ///< Upper bound values of the variables.
    std::vector<bool>           _UpperBoundIsGivenVec = { };        ///< Flag for upper bound values.
    std::vector<double>         _LowerBoundValueVec = { };          ///< Lower bound values of the variables.
    std::vector<bool>           _LowerBoundIsGivenVec = { };        ///< Flag for lower bound values.
    std::vector<bool>           _ParamaterTypeIsGivenVec = { };     ///< Flag for parameter types.
    std::vector<std::string>    _ParamaterTypeVec = { };

    BaseSingleObjEvaluator*                 _SingleObjEvaluatorPtr = nullptr;        ///< Raw pointer for single-objective evaluator.
    BaseMultiObjEvaluator*                  _MultiObjEvaluatorPtr = nullptr;         ///< Raw pointer for multi-objective evaluator.
    std::shared_ptr<BaseSingleObjEvaluator> _SingleObjEvaluatorSmrtPtr = nullptr;    ///< Smart pointer for single-objective evaluator.
    std::shared_ptr<BaseMultiObjEvaluator>  _MultiObjEvaluatorSmrtPtr = nullptr;     ///< Smart pointer for multi-objective evaluator.

    EvaluatorType                           _EvaluatorType = EvaluatorType::NONE;                ///< Evaluator type.
    EvaluatorPointerType                    _EvaluatorPointerType = EvaluatorPointerType::NONE;  ///< Evaluator pointer type.

public:
    /// Constructor.
    /**
    */
    NomadCore();

    /// Destructor.
    /**
    */
    ~NomadCore();

    /// Set the output path.
    /**
     \param outputPath Path for output file  -- \b IN.
     */
    void SetOutputPath( const char* outputPath );

    /// Set the number of iterations.
    /**
     \param numIters Number of iterations  -- \b IN.
     */
    void SetNumberOfIterations( int numIters );

    /// Get the number of iterations.
    /**
     \return Number of iterations.
     */
    int GetNumberOfIterations( void );

    /// Set the number of variables.
    /**
     \param numVariables Number of variables  -- \b IN.
     */
    void SetNumberVariables( int numVariables );

    /// Get the number of variables.
    /**
     \return Number of variables.
     */
    int GetNumberOfVariables( void );

    /// Set the initial value of a variable.
    /**
     \param index Index of the variable  -- \b IN.
     \param value Initial value of the variable  -- \b IN.
     */
    void SetInitialVariableValue( int index, double value );

    /// Set the number of progressive barrier constraints.
    /**
     \param numPBConstraints Number of progressive barrier constraints  -- \b IN.
     */
    void SetNumberPBConstraints( int numPBConstraints );

    /// Get the number of progressive barrier constraints.
    /**
     \return Number of progressive barrier constraints.
     */
    int GetNumberPBConstraints( void );

    /// Set the number of extreme barrier constraints.
    /**
     \param numEBConstraints Number of extreme barrier constraints  -- \b IN.
     */
    void SetNumberEBConstraints( int numEBConstraints );

    /// Get the number of extreme barrier constraints.
    /**
     \return Number of extreme barrier constraints.
     */
    int GetNumberEBConstraints( void );

    /// Set the upper bound of a variable.
    /**
     \param index Index of the variable  -- \b IN.
     \param value Upper bound of the variable  -- \b IN.
     */
    void SetVariableUpperBound( int index, double value );

    /// Set the lower bound of a variable.
    /**
     \param index Index of the variable  -- \b IN.
     \param value Lower bound of the variable  -- \b IN.
     */
    void SetVariableLowerBound( int index, double value );

    /// Set the type of a variable.
    /**
    * - "CONTINUOUS"
    * - "INTEGER"
    * - "BINARY"
    * - "CATEGORICAL"
     \param index Index of the variable  -- \b IN.
     \param type Type of the variable  -- \b IN.
     */
    void SetVariableType( int index, const char* type );

    /// Set the number of objective functions.
    /**
     \param numObjFunctions Number of objective functions  -- \b IN.
     */
    void SetNumberObjFunctions( int numObjFunctions );

    /// Get the number of objective functions.
    /**
     \return Number of objective functions.
     */
    int GetNumberObjFunctions( void );

    /// Get the type of the evaluator.
    /**
     \return Evaluator type.
     */
    EvaluatorType GetEvaluatorType( void );

    /// Get the type of the evaluator pointer.
    /**
     \return Evaluator pointer type.
     */
    EvaluatorPointerType GetEvaluatorPointerType(void);

    /// Set the single-objective evaluator using raw pointer.
    /**
     \param eval Single-objective evaluator  -- \b IN.
     */
    void SetEvaluator( BaseSingleObjEvaluator* eval );

    /// Set the single-objective evaluator using smart pointer.
    /**
     \param eval Single-objective evaluator  -- \b IN.
     */
    void SetEvaluator( std::shared_ptr<BaseSingleObjEvaluator> eval );

    /// Set the multi-objective evaluator using raw pointer.
    /**
     \param eval Multi-objective evaluator  -- \b IN.
     */
    void SetEvaluator( BaseMultiObjEvaluator* eval );

    /// Set the single-objective evaluator using smart pointer.
    /**
     \param eval Single-objective evaluator  -- \b IN.
     */
    void SetEvaluator( std::shared_ptr<BaseMultiObjEvaluator> eval );

    /// Optimize a single-objective problem.
    /**
    */
    void Optimize( void );

    /// Get the results.
    /**
     \return Optimizer results.
     */
    std::vector<double> GetResults( void );
};

#endif // __NOMADCORE_H__
