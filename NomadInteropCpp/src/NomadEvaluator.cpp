#include "NomadEvaluator.hpp"

NomadSingleObjEvaluator::NomadSingleObjEvaluator( const NOMAD::Parameters& p, BaseSingleObjEvaluator* Evaluator, NomadCore* nomadCore ) : NOMAD::Evaluator( p )
{
	this->_SingleObjEvaluator = Evaluator;
	this->_NomadCore = nomadCore;
	this->_Params = &p;

	// Initialize the evaluator
	static auto numConstraints = _NomadCore->GetNumberEBConstraints() + _NomadCore->GetNumberPBConstraints();
	_SingleObjEvaluator->Initialize(numConstraints);
}

NomadSingleObjEvaluator::~NomadSingleObjEvaluator( void )
{

}

bool NomadSingleObjEvaluator::eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const
{
	// This function is called by NOMAD to evaluate the objective function and constraints
	// The function returns true if the evaluation succeeded, and false otherwise

	static auto numVars = _NomadCore->GetNumberOfVariables();
	double* paramsPtr = new double[numVars];

	// Copy the variables to a double array
	for (int i = 0; i < numVars; i++)
	{
		paramsPtr[i] = x[i].value();
	}

	// Evaluate the objective function and constraints
	_SingleObjEvaluator->Evaluate(paramsPtr, numVars);

	// Set the objective function value
	x.set_bb_output(0, _SingleObjEvaluator->GetObjectiveFunction());

	// Get the constraints array
	auto evalConstraintsArr = _SingleObjEvaluator->GetConstraints();

	// Set the constraints
	for (int i = 0; i < evalConstraintsArr.size(); i++)
	{
		x.set_bb_output(i + 1, evalConstraintsArr.at(i));
	}

	delete[] paramsPtr;

	// Return the evaluation status
	if (_SingleObjEvaluator->GetObjectiveFunctionStatus())
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
	this->_MultiObjEvaluator = Evaluator;
	this->_NomadCore = nomadCore;
	this->_Params = &p;

	// Initialize the evaluator
	static auto numConstraints = _NomadCore->GetNumberEBConstraints() + _NomadCore->GetNumberPBConstraints();
	static auto numObjFunctions = _NomadCore->GetNumberObjFunctions();
	_MultiObjEvaluator->Initialize(numConstraints, numObjFunctions);
}

NomadMultiObjEvaluator::~NomadMultiObjEvaluator( void )
{

}

bool NomadMultiObjEvaluator::eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const
{
	// This function is called by NOMAD to evaluate the objective function and constraints
	// The function returns true if the evaluation succeeded, and false otherwise

	static auto numVars = _NomadCore->GetNumberOfVariables();
	double* paramsPtr = new double[numVars];

	// Copy the variables to a double array
	for (int i = 0; i < numVars; i++)
	{
		paramsPtr[i] = x[i].value();
	}

	// Evaluate the objective function
	_MultiObjEvaluator->Evaluate(paramsPtr, numVars);

	// Get the objective functions and constraints arrays
	auto evalObjFunctionsArr = _MultiObjEvaluator->GetObjectiveFunction();
	auto evalConstraintsArr = _MultiObjEvaluator->GetConstraints();

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
	if (_MultiObjEvaluator->GetObjectiveFunctionStatus())
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