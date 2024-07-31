/**
 \file   NomadEvaluator.hpp
 \brief  Class definitions derived from NOMAD evaluators (headers)
 \author
 \date   2024-07-29
 \see    NomadEvaluator.cpp
 */

#ifndef __NOMADEVALUATOR_H__
#define __NOMADEVALUATOR_H__

#include "nomad.hpp"
#include "NomadCore.hpp"
#include "BaseEvaluator.hpp"


/// NOMAD single-objective evaluator.
class NomadSingleObjEvaluator : public NOMAD::Evaluator
{
private:
    BaseSingleObjEvaluator*        _SingleObjEvaluator = nullptr;  ///< Single-objective evaluator.
    NomadCore*                     _NomadCore = nullptr;           ///< NOMAD core.
    const NOMAD::Parameters*       _Params = nullptr;              ///< Parameters.

public:
    /// Constructor.
    /**
     \param p NOMAD parameters  -- \b IN.
     \param Evaluator Single-objective evaluator  -- \b IN.
     \param nomadCore NOMAD core  -- \b IN.
     */
    NomadSingleObjEvaluator( const NOMAD::Parameters& p, BaseSingleObjEvaluator* Evaluator, NomadCore* nomadCore );

    /// Destructor.
    /**
    */
    ~NomadSingleObjEvaluator( void );

    /// Evaluate the objective function and constraints.
    /**
     \param x Evaluated point  -- \b IN.
     \param h_max Maximum constraint violation  -- \b IN.
     \param count_eval Flag for counting evaluations  -- \b IN.
     \return Evaluation status.
     */
    bool eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const;
};

/// NOMAD multi-objective evaluator.
class NomadMultiObjEvaluator : public NOMAD::Multi_Obj_Evaluator
{
private:
    BaseMultiObjEvaluator*        _MultiObjEvaluator = nullptr;     ///< Multi-objective evaluator.
    NomadCore*                    _NomadCore = nullptr;             ///< NOMAD core.
    const NOMAD::Parameters*      _Params = nullptr;                ///< Parameters.

public:
    /// Constructor.
    /**
     \param p NOMAD parameters  -- \b IN.
     \param Evaluator Multi-objective evaluator  -- \b IN.
     \param nomadCore NOMAD core  -- \b IN.
     */
    NomadMultiObjEvaluator( const NOMAD::Parameters& p, BaseMultiObjEvaluator* Evaluator, NomadCore* nomadCore );

    /// Destructor.
    /**
    */
    ~NomadMultiObjEvaluator( void );

    /// Evaluate the objective function and constraints.
    /**
     \param x Evaluated point  -- \b IN.
     \param h_max Maximum constraint violation  -- \b IN.
     \param count_eval Flag for counting evaluations  -- \b IN.
     \return Evaluation status.
     */
    bool eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const;
};

#endif // __NOMADEVALUATOR_H__
