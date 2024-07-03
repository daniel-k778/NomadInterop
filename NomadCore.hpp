#pragma once
#include "nomad.hpp"
#include "Evaluator.hpp"

class NomadCore
{
private:

	int argc;
	char** argv;

	const char* outputPath;

	int numVars = 0;
	int numIterations = 100;

	int numberPBConstraints = 0;
	int numberEBConstraints = 0;

	std::vector<double> initialVars;
	std::vector<double> upperBoundValueVec;
	std::vector<bool> upperBoundIsGivenVec;
	std::vector<double> lowerBoundValueVec;
	std::vector<bool> lowerBoundIsGivenVec;

	std::vector<double> m_FinalVariables;


public:

	NomadCore(int argc, char** argv);
	~NomadCore();

	/**
	 * @brief Set the output file path.
	 * @param outputPath Path to the output file.
	 */
	void SetOutputPath(const char* outputFilePath);

	/**
	 * @brief Set the number of iterations.
	 * @param numIters Number of iterations.
	 */
	void SetNumberOfIterations(int numIters);

	/**
	 * @brief Set the values for the initial variables.
	 * @param initialVariables vector of initial variables values.
	 */
	void SetNumberVariables(int numberVariables);
	void SetInitialVariable(int index, double value);

	void SetNumberPBConstraints(int numPBConstraints);
	void SetNumberEBConstraints(int numEBConstraints);

	/**
	 * @brief Set the upper bounds.
	 * 
	 * Not all variables need to have upper bounds.
	 * 
	 * @param upperBounds vector of upper bound for each variable
	 */
	void SetUpperBound(int index, double value);

	/**
	 * @brief Set the lower bounds.
	 * 
	 * Not all variables need to have lower bounds.
	 * 
	 * @param lowerBounds vector of lower bound for each variable.
	 */
	void SetLowerBound(int index, double value);

	/**
	 * @brief Optimize the problem.
	 */
	void Optimize();
	
};