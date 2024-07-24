#pragma once
#include "nomad.hpp"
#include "BaseEvaluator.hpp"


class NomadEvaluator : public NOMAD::Evaluator
{
private:
	BaseEvaluator* m_Evaluator = nullptr;
	NomadCore* m_NomadCore = nullptr;
	const NOMAD::Parameters* m_Params;
public:
	NomadEvaluator(const NOMAD::Parameters& p, BaseEvaluator* Evaluator, NomadCore* nomadCore) :
		NOMAD::Evaluator(p)
	{
		this->m_Evaluator = Evaluator;
		this->m_NomadCore = nomadCore;
		this->m_Params = &p;
	}

	~NomadEvaluator(void)
	{

	}

	bool eval_x(NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval) const
	{
		double* paramsPtr = new double[m_NomadCore->GetNumberOfVariables()];
		for (int i = 0; i < m_NomadCore->GetNumberOfVariables(); i++)
		{
			paramsPtr[i] = x[i].value();
		}

		m_Evaluator->Evaluate(paramsPtr, m_NomadCore->GetNumberOfVariables(), m_NomadCore->GetNumberEBConstraints() + m_NomadCore->GetNumberPBConstraints());
		x.set_bb_output(0, m_Evaluator->GetObjectiveFunction()); // objective value

		auto constraints = m_Evaluator->GetConstraints();

		for (int i = 0; i < constraints.size(); i++) {
			x.set_bb_output(i + 1, constraints.at(i)); // add each constraint
			}

		count_eval = true; // count a black-box evaluation
		delete[] paramsPtr;

		return true;       // the evaluation succeeded
	}
};