#ifndef NOMADEVALUATOR_H
#define NOMADEVALUATOR_H

#include "nomad.hpp"
#include "NomadCore.hpp"
#include "BaseEvaluator.hpp"

class NomadSingleObjEvaluator : public NOMAD::Evaluator
{
private:
	BaseSingleObjEvaluator*		m_SingleObjEvaluator = nullptr;
	NomadCore*					m_NomadCore = nullptr;
	const NOMAD::Parameters*    m_Params = nullptr;

public:
	NomadSingleObjEvaluator( const NOMAD::Parameters& p, BaseSingleObjEvaluator* Evaluator, NomadCore* nomadCore );

	~NomadSingleObjEvaluator( void );

	bool eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const;
};

class NomadMultiObjEvaluator : public NOMAD::Multi_Obj_Evaluator
{
private:
	BaseMultiObjEvaluator*		m_MultiObjEvaluator = nullptr;
	NomadCore*					m_NomadCore = nullptr;
	const NOMAD::Parameters*    m_Params = nullptr;

public:
	NomadMultiObjEvaluator( const NOMAD::Parameters& p, BaseMultiObjEvaluator* Evaluator, NomadCore* nomadCore );

	~NomadMultiObjEvaluator( void );

	bool eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const;
};

#endif // NOMADEVALUATOR_H