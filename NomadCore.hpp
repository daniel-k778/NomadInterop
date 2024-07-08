#pragma once
#include "nomad.hpp"
#include "BaseEvaluator.hpp"

class NomadCore
{
private:

	int argc;
	char** argv;

	const char* m_OutputPath;

	int m_NumVars = 0;
	int m_NumIterations = 100;

	int m_NumPBConstraints = 0;
	int m_NumEBConstraints = 0;

	std::vector<double> m_InitialVarsVec;
	std::vector<double> m_UpperBoundValueVec;
	std::vector<bool> m_UpperBoundIsGivenVec;
	std::vector<double> m_LowerBoundValueVec;
	std::vector<bool> m_LowerBoundIsGivenVec;

	std::vector<double> m_FinalVariables;

	BaseEvaluator* m_Evaluator = nullptr;


public:

	NomadCore(int argc, char** argv);
	~NomadCore();

	/**
	 * @brief Set the output file path.
	 * @param outputPath Path to the output file.
	 */
	void SetOutputPath(const char* outputFilePath);


	void SetNumberOfIterations(int numIters);
	int GetNumberOfIterations();

	void SetNumberVariables(int numberVariables);
	int GetNumberOfVariables();

	void SetInitialVariable(int index, double value);

	void SetNumberPBConstraints(int numPBConstraints);
	int GetNumberPBConstraints();

	void SetNumberEBConstraints(int numEBConstraints);
	int GetNumberEBConstraints();

	void SetUpperBound(int index, double value);
	void SetLowerBound(int index, double value);

	void SetEvaluator(BaseEvaluator* eval);

	void Optimize();
	
};