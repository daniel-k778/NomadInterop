#include "NomadEvaluator.hpp"

NomadSingleObjEvaluator::NomadSingleObjEvaluator( const NOMAD::Parameters& p, BaseSingleObjEvaluator* Evaluator, NomadCore* nomadCore ) : NOMAD::Evaluator( p )
{
	this->m_SingleObjEvaluator = Evaluator;
	this->m_NomadCore = nomadCore;
	this->m_Params = &p;

	static auto numConstraints = m_NomadCore->GetNumberEBConstraints() + m_NomadCore->GetNumberPBConstraints();
	m_SingleObjEvaluator->Initialize(numConstraints);
}

NomadSingleObjEvaluator::~NomadSingleObjEvaluator( void )
{

}

bool NomadSingleObjEvaluator::eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const
{
	static auto numVars = m_NomadCore->GetNumberOfVariables();
	double* paramsPtr = new double[numVars];

	for (int i = 0; i < numVars; i++)
	{
		paramsPtr[i] = x[i].value();
	}

	m_SingleObjEvaluator->Evaluate(paramsPtr, numVars);
	x.set_bb_output(0, m_SingleObjEvaluator->GetObjectiveFunction()); // objective value

	auto evalConstraintsArr = m_SingleObjEvaluator->GetConstraints();

	for (int i = 0; i < evalConstraintsArr.size(); i++)
	{
		x.set_bb_output(i + 1, evalConstraintsArr.at(i)); // add each constraint
	}

	delete[] paramsPtr;

	if (m_SingleObjEvaluator->GetObjectiveFunctionStatus())
	{
		count_eval = true;
		return true;       // the evaluation succeeded
	}
	else
	{
		count_eval = false;
		return false;       // the evaluation failed
	}
}

NomadMultiObjEvaluator::NomadMultiObjEvaluator( const NOMAD::Parameters& p, BaseMultiObjEvaluator* Evaluator, NomadCore* nomadCore ) : NOMAD::Multi_Obj_Evaluator( p )
{
	this->m_MultiObjEvaluator = Evaluator;
	this->m_NomadCore = nomadCore;
	this->m_Params = &p;

	static auto numConstraints = m_NomadCore->GetNumberEBConstraints() + m_NomadCore->GetNumberPBConstraints();
	static auto numObjFunctions = m_NomadCore->GetNumberObjFunctions();
	m_MultiObjEvaluator->Initialize(numConstraints, numObjFunctions);
}

NomadMultiObjEvaluator::~NomadMultiObjEvaluator( void )
{

}

bool NomadMultiObjEvaluator::eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const
{
	static auto numVars = m_NomadCore->GetNumberOfVariables();
	double* paramsPtr = new double[numVars];

	for (int i = 0; i < numVars; i++)
	{
		paramsPtr[i] = x[i].value();
	}

	m_MultiObjEvaluator->Evaluate(paramsPtr, numVars);
	auto evalObjFunctionsArr = m_MultiObjEvaluator->GetObjectiveFunction();
	auto evalConstraintsArr = m_MultiObjEvaluator->GetConstraints();

	for (int i = 0; i < evalObjFunctionsArr.size(); i++)
	{
		x.set_bb_output(i, evalObjFunctionsArr.at(i)); // add each objective function
	}

	for (int i = 0; i < evalConstraintsArr.size(); i++)
	{
		x.set_bb_output(i + evalObjFunctionsArr.size(), evalConstraintsArr.at(i)); // add each constraint
	}

	delete[] paramsPtr;

	if (m_MultiObjEvaluator->GetObjectiveFunctionStatus())
	{
		count_eval = true;
		return true;       // the evaluation succeeded
	}
	else
	{
		count_eval = false;
		return false;       // the evaluation failed
	}
}