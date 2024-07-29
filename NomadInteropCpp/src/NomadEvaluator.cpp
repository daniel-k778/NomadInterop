#include "NomadEvaluator.hpp"

NomadSingleObjEvaluator::NomadSingleObjEvaluator( const NOMAD::Parameters& p, BaseSingleObjEvaluator* Evaluator, NomadCore* nomadCore ) : NOMAD::Evaluator( p )
{
	this->m_SingleObjEvaluator = Evaluator;
	this->m_NomadCore = nomadCore;
	this->m_Params = &p;

	// Initialize the evaluator
	static auto numConstraints = m_NomadCore->GetNumberEBConstraints() + m_NomadCore->GetNumberPBConstraints();
	m_SingleObjEvaluator->Initialize(numConstraints);
}

NomadSingleObjEvaluator::~NomadSingleObjEvaluator( void )
{

}

bool NomadSingleObjEvaluator::eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const
{
	// This function is called by NOMAD to evaluate the objective function and constraints
	// The function returns true if the evaluation succeeded, and false otherwise

	static auto numVars = m_NomadCore->GetNumberOfVariables();
	double* paramsPtr = new double[numVars];

	// Copy the variables to a double array
	for (int i = 0; i < numVars; i++)
	{
		paramsPtr[i] = x[i].value();
	}

	// Evaluate the objective function and constraints
	m_SingleObjEvaluator->Evaluate(paramsPtr, numVars);

	// Set the objective function value
	x.set_bb_output(0, m_SingleObjEvaluator->GetObjectiveFunction());

	// Get the constraints array
	auto evalConstraintsArr = m_SingleObjEvaluator->GetConstraints();

	// Set the constraints
	for (int i = 0; i < evalConstraintsArr.size(); i++)
	{
		x.set_bb_output(i + 1, evalConstraintsArr.at(i));
	}

	delete[] paramsPtr;

	// Return the evaluation status
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

	// Initialize the evaluator
	static auto numConstraints = m_NomadCore->GetNumberEBConstraints() + m_NomadCore->GetNumberPBConstraints();
	static auto numObjFunctions = m_NomadCore->GetNumberObjFunctions();
	m_MultiObjEvaluator->Initialize(numConstraints, numObjFunctions);
}

NomadMultiObjEvaluator::~NomadMultiObjEvaluator( void )
{

}

bool NomadMultiObjEvaluator::eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const
{
	// This function is called by NOMAD to evaluate the objective function and constraints
	// The function returns true if the evaluation succeeded, and false otherwise

	static auto numVars = m_NomadCore->GetNumberOfVariables();
	double* paramsPtr = new double[numVars];

	// Copy the variables to a double array
	for (int i = 0; i < numVars; i++)
	{
		paramsPtr[i] = x[i].value();
	}

	// Evaluate the objective function
	m_MultiObjEvaluator->Evaluate(paramsPtr, numVars);

	// Get the objective functions and constraints arrays
	auto evalObjFunctionsArr = m_MultiObjEvaluator->GetObjectiveFunction();
	auto evalConstraintsArr = m_MultiObjEvaluator->GetConstraints();

	// Set the objective functions
	for (int i = 0; i < evalObjFunctionsArr.size(); i++)
	{
		x.set_bb_output(i, evalObjFunctionsArr.at(i));
	}

	// Set the constraints
	for (int i = 0; i < evalConstraintsArr.size(); i++)
	{
		x.set_bb_output(i + evalObjFunctionsArr.size(), evalConstraintsArr.at(i));
	}

	delete[] paramsPtr;

	// Return the evaluation status
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