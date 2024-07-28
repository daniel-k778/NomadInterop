#pragma once
#include "nomad.hpp"
#include "BaseEvaluator.hpp"


class NomadEvaluator : public NOMAD::Evaluator
{
private:
	BaseEvaluator* m_Evaluator = nullptr;
	NomadCore* m_NomadCore = nullptr;
	const NOMAD::Parameters* m_Params = nullptr;
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
		static auto numVars = m_NomadCore->GetNumberOfVariables();
		double* paramsPtr = new double[numVars];
		for (int i = 0; i < numVars; i++)
		{
			paramsPtr[i] = x[i].value();
		}

		static auto numConstraints = m_NomadCore->GetNumberEBConstraints() + m_NomadCore->GetNumberPBConstraints();
		m_Evaluator->Evaluate(paramsPtr, numVars, numConstraints);
		x.set_bb_output(0, m_Evaluator->GetObjectiveFunction()); // objective value

		auto evalConstraintsArr = m_Evaluator->GetConstraints();

		for (int i = 0; i < evalConstraintsArr.size(); i++) {
			x.set_bb_output(i + 1, evalConstraintsArr.at(i)); // add each constraint
		}


		count_eval = true; // count a black-box evaluation
		delete[] paramsPtr;

		return true;       // the evaluation succeeded
	}
};