#pragma once
#include "nomad.hpp"

class BaseEvaluator
{
private:


public:
    BaseEvaluator()
    {

    }

    ~BaseEvaluator(void)
    {

    }

    virtual double GetObjectiveFunction() {
        throw std::exception("Objective function not provided.");
    }

    virtual std::vector<double> GetConstraints() {
		throw std::exception("Constraints not provided.");
	}

	virtual void Evaluate(double* x, int m_NumVars, int numConstraints)
	{
		throw std::exception("Evaluate function not provided.");
	}
};