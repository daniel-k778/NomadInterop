#pragma once
#include "nomad.hpp"

class MainWrapper
{
private:

	int argc;
	char** argv;

	int numVars = 0;
	int numIterations;

	std::vector<double> initialVars;
	std::vector<double> upperBoundValueVec;
	std::vector<bool> upperBoundIsGivenVec;
	std::vector<double> lowerBoundValueVec;
	std::vector<bool> lowerBoundIsGivenVec;

	vector<NOMAD::bb_output_type> bbot;

	NOMAD::Evaluator* interimEvaluator;


public:

	MainWrapper(int argc, char** argv);
	~MainWrapper();

	/**
	 * @brief Set the number of iterations.
	 * @param numIters Number of iterations.
	 */
	void SetNumberOfIterations(int numIters);

	/**
	 * @brief Set the values for the initial variables.
	 * @param initialVariables vector of initial variables values.
	 */
	void SetVariables(std::vector<double> initialVariables);

	/**
	 * @brief Set the upper bounds.
	 * 
	 * Not all variables need to have upper bounds.
	 * 
	 * @param upperBounds vector of upper bound for each variable
	 */
	void SetUpperBounds(std::vector<double> upperBounds);

	/**
	 * @brief Set the lower bounds.
	 * 
	 * Not all variables need to have lower bounds.
	 * 
	 * @param lowerBounds vector of lower bound for each variable.
	 */
	void SetLowerBounds(std::vector<double> lowerBounds);

	/**
	 * @brief Set the output types.
	 * 
	 * OBJ: objective value.
	 * EB: extreme barrier.
	 * PB: progressive barrier.
	 * 
	 * @param outputTypes vector of output types.
	 */
	void SetOutputTypes(vector<const char*> outputTypes);

	void Optimize();
	
};