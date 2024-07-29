#pragma once
#include "nomad.hpp"
#include "BaseEvaluator.hpp"


class NomadSingleObjEvaluator : public NOMAD::Evaluator
{
private:
	BaseSingleObjEvaluator* m_SingleObjEvaluator = nullptr;
	NomadCore* m_NomadCore = nullptr;
	const NOMAD::Parameters* m_Params = nullptr;
public:
	NomadSingleObjEvaluator(const NOMAD::Parameters& p, BaseSingleObjEvaluator* Evaluator, NomadCore* nomadCore) :
		NOMAD::Evaluator(p)
	{
		this->m_SingleObjEvaluator = Evaluator;
		this->m_NomadCore = nomadCore;
		this->m_Params = &p;

		static auto numConstraints = m_NomadCore->GetNumberEBConstraints() + m_NomadCore->GetNumberPBConstraints();
		m_SingleObjEvaluator->Initialize(numConstraints);
	}

	~NomadSingleObjEvaluator(void)
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

		m_SingleObjEvaluator->Evaluate(paramsPtr, numVars);
		x.set_bb_output(0, m_SingleObjEvaluator->GetObjectiveFunction()); // objective value

		auto evalConstraintsArr = m_SingleObjEvaluator->GetConstraints();

		for (int i = 0; i < evalConstraintsArr.size(); i++) {
			x.set_bb_output(i + 1, evalConstraintsArr.at(i)); // add each constraint
		}


		count_eval = true; // count a black-box evaluation
		delete[] paramsPtr;

		return true;       // the evaluation succeeded
	}
};

class NomadMultiObjEvaluator : public NOMAD::Multi_Obj_Evaluator
{
private:
	BaseMultiObjEvaluator* m_MultiObjEvaluator = nullptr;
	NomadCore* m_NomadCore = nullptr;
	const NOMAD::Parameters* m_Params = nullptr;
public:
	NomadMultiObjEvaluator(const NOMAD::Parameters& p, BaseMultiObjEvaluator* Evaluator, NomadCore* nomadCore) :
		NOMAD::Multi_Obj_Evaluator(p)
	{
		this->m_MultiObjEvaluator = Evaluator;
		this->m_NomadCore = nomadCore;
		this->m_Params = &p;

		static auto numConstraints = m_NomadCore->GetNumberEBConstraints() + m_NomadCore->GetNumberPBConstraints();
		static auto numObjFunctions = m_NomadCore->GetNumberObjFunctions();
		m_MultiObjEvaluator->Initialize(numConstraints, numObjFunctions);
	}

	~NomadMultiObjEvaluator(void)
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

		m_MultiObjEvaluator->Evaluate(paramsPtr, numVars);

		static auto numObjFuncs = m_NomadCore->GetNumberObjFunctions();
		for (int i = 0; i < numObjFuncs; i++) {
			x.set_bb_output(i, m_MultiObjEvaluator->GetObjectiveFunction().at(i)); // objective value
		}

		auto evalConstraintsArr = m_MultiObjEvaluator->GetConstraints();

		for (int i = 0; i < evalConstraintsArr.size(); i++) {
			x.set_bb_output(i + numObjFuncs, evalConstraintsArr.at(i)); // add each constraint
		}

		count_eval = true; // count a black-box evaluation
		delete[] paramsPtr;

		return true;       // the evaluation succeeded
	}
};