/**
 \file   BaseEvaluator.hpp
 \brief  Base classes for evaluators (headers)
 \date   2024-07-29
 \see    BaseEvaluator.cpp
 */

#ifndef __BASEEVALUATOR_H__
#define __BASEEVALUATOR_H__

#include "nomad.hpp"

#ifdef NOMADCORE_EXPORTS
#define NOMADCORE_API __declspec( dllexport )
#else
#define NOMADCORE_API __declspec( dllimport )
#endif

/// Base class for single-objective evaluators.
class NOMADCORE_API BaseSingleObjEvaluator
{
public:
    /// Constructor.
    /**
     */
    BaseSingleObjEvaluator( void );

    /// Destructor.
    /**
    */
    ~BaseSingleObjEvaluator( void );

    /// Initialize the evaluator.
    /**
     \param numConstraints Number of constraints  -- \b IN.
     */
    virtual void Initialize( int numConstraints );

    /// Get the objective function.
    /**
     \return Objective function value.
     */
    virtual double GetObjectiveFunction( void );

    /// Get the objective function status.
    /**
     \return Objective function status.
     */
    virtual bool GetObjectiveFunctionStatus( void );

    /// Get the constraints.
    /**
     \return Constraints array.
     */
    virtual std::vector<double> GetConstraints( void );

    /// Evaluate the objective function and constraints.
    /**
     \param x Array of variables  -- \b IN.
     \param numVars Number of variables  -- \b IN.
     */
    virtual void Evaluate( double* x, int numVars );
};

/// Base class for multi-objective evaluators.
class NOMADCORE_API BaseMultiObjEvaluator
{
public:
    /// Constructor.
    /**
    */
    BaseMultiObjEvaluator( void );

    /// Destructor.
    /**
    */
    ~BaseMultiObjEvaluator( void );

    /// Initialize the evaluator.
    /**
     \param numConstraints Number of constraints  -- \b IN.
     \param numObjFunctions Number of objective functions  -- \b IN.
     */
    virtual void Initialize( int numConstraints, int numObjFunctions );

    /// Get the objective function.
    /**
     \return Objective function value.
     */
    virtual std::vector<double> GetObjectiveFunction( void );

    /// Get the objective function status.
    /**
     \return Objective function status.
     */
    virtual bool GetObjectiveFunctionStatus( void );

    /// Get the constraints.
    /**
     \return Constraints array.
     */
    virtual std::vector<double> GetConstraints( void );

    /// Evaluate the objective function and constraints.
    /**
     \param x Array of variables  -- \b IN.
     \param numVars Number of variables  -- \b IN.
     */
    virtual void Evaluate( double* x, int numVars );
};

#endif // __BASEEVALUATOR_H__
