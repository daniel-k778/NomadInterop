#include "BaseEvaluator.hpp"

BaseSingleObjEvaluator::BaseSingleObjEvaluator( void )
{

}

BaseSingleObjEvaluator::~BaseSingleObjEvaluator( void )
{

}

void BaseSingleObjEvaluator::Initialize( int numConstraints )
{
    throw std::runtime_error("Initialize function not implemented.");
}

double BaseSingleObjEvaluator::GetObjectiveFunction( void )
{
    throw std::runtime_error("GetObjectiveFunction function not implemented.");
}

bool BaseSingleObjEvaluator::GetObjectiveFunctionStatus( void )
{
    throw std::runtime_error("GetObjectiveFunctionStatus function not implemented.");
}

std::vector<double> BaseSingleObjEvaluator::GetConstraints( void )
{
    throw std::runtime_error("GetConstraints function not implemented.");
}

void BaseSingleObjEvaluator::Evaluate( double* x, int _NumVars )
{
    throw std::runtime_error("Evaluate function not implemented.");
}

BaseMultiObjEvaluator::BaseMultiObjEvaluator( void )
{

}

BaseMultiObjEvaluator::~BaseMultiObjEvaluator( void )
{

}

void BaseMultiObjEvaluator::Initialize( int numConstraints, int numObjFunctions )
{
    throw std::runtime_error("Initialize function not implemented.");
}

std::vector<double> BaseMultiObjEvaluator::GetObjectiveFunction( void )
{
    throw std::runtime_error("GetObjectiveFunction function not implemented.");
}

bool BaseMultiObjEvaluator::GetObjectiveFunctionStatus( void )
{
    throw std::runtime_error("GetObjectiveFunctionStatus function not implemented.");
}

std::vector<double> BaseMultiObjEvaluator::GetConstraints( void )
{
    throw std::runtime_error("GetConstraints function not implemented.");
}

void BaseMultiObjEvaluator::Evaluate( double* x, int _NumVars )
{
    throw std::runtime_error("Evaluate function not implemented.");
}
