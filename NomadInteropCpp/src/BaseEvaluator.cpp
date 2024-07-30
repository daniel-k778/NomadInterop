#include "BaseEvaluator.hpp"

BaseSingleObjEvaluator::BaseSingleObjEvaluator( void )
{

}

BaseSingleObjEvaluator::~BaseSingleObjEvaluator( void )
{

}

void BaseSingleObjEvaluator::Initialize( int numConstraints )
{
    throw std::exception("Initialize function not provided.");
}

double BaseSingleObjEvaluator::GetObjectiveFunction( void )
{
    throw std::exception("Objective function not provided.");
}

bool BaseSingleObjEvaluator::GetObjectiveFunctionStatus( void )
{
    throw std::exception("Objective function status not provided.");
}

std::vector<double> BaseSingleObjEvaluator::GetConstraints( void )
{
    throw std::exception("Constraints function not provided.");
}

void BaseSingleObjEvaluator::Evaluate( double* x, int _NumVars )
{
    throw std::exception("Evaluate function not provided.");
}

BaseMultiObjEvaluator::BaseMultiObjEvaluator( void )
{

}

BaseMultiObjEvaluator::~BaseMultiObjEvaluator( void )
{

}

void BaseMultiObjEvaluator::Initialize( int numConstraints, int numObjFunctions )
{
    throw std::exception("Initialize function not provided.");
}

std::vector<double> BaseMultiObjEvaluator::GetObjectiveFunction( void )
{
    throw std::exception("Objective function not provided.");
}

bool BaseMultiObjEvaluator::GetObjectiveFunctionStatus( void )
{
    throw std::exception("Objective function status not provided.");
}

std::vector<double> BaseMultiObjEvaluator::GetConstraints( void )
{
    throw std::exception("Constraints function not provided.");
}

void BaseMultiObjEvaluator::Evaluate( double* x, int _NumVars )
{
    throw std::exception("Evaluate function not provided.");
}
