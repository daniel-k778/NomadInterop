#pragma once
#include "nomad.hpp"

class BaseSingleObjEvaluator
{
private:


public:
    BaseSingleObjEvaluator( void )
    {

    }

    ~BaseSingleObjEvaluator( void )
    {

    }

    virtual void Initialize(int numConstraints) {
        throw std::exception("Initialize function not provided.");
    }
    virtual double GetObjectiveFunction() {
        throw std::exception("Objective function not provided.");
    }

    virtual std::vector<double> GetConstraints() {
		throw std::exception("Constraints not provided.");
	}

	virtual void Evaluate(double* x, int m_NumVars)
	{
		throw std::exception("Evaluate function not provided.");
	}
};

class BaseMultiObjEvaluator
{
private:

public:
    BaseMultiObjEvaluator( void )
    {

    }

    ~BaseMultiObjEvaluator( void )
    {

    }

    virtual void Initialize(int numConstraints, int numObjFunctions) {
		throw std::exception("Initialize function not provided.");
	}

    virtual std::vector<double> GetObjectiveFunction() {
        throw std::exception("Objective function not provided.");
    }

    virtual std::vector<double> GetConstraints() {
        throw std::exception("Constraints not provided.");
    }

    virtual void Evaluate(double* x, int m_NumVars)
    {
        throw std::exception("Evaluate function not provided.");
    }
};