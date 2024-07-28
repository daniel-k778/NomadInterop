#pragma once
#include "nomad.hpp"
#include "BaseEvaluator.hpp"

class NomadCore
{
private:
	const char* m_OutputPath = nullptr;

	int m_NumVars = 0;
	int m_NumIterations = 100;

	int m_NumPBConstraints = 0;
	int m_NumEBConstraints = 0;

	std::vector<double> m_InitialVarsVec = { };
	std::vector<double> m_UpperBoundValueVec = { };
	std::vector<bool> m_UpperBoundIsGivenVec = { };
	std::vector<double> m_LowerBoundValueVec = { };
	std::vector<bool> m_LowerBoundIsGivenVec = { };

	std::vector<double> m_FinalVariables = { };

	std::vector<bool> m_ParamaterTypeIsGivenVec = { };
	std::vector<std::string> m_ParamaterTypeVec = { };

	BaseEvaluator* m_Evaluator = nullptr;

public:

	NomadCore();
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

	void SetInitialVariableValue(int index, double value);

	void SetNumberPBConstraints(int numPBConstraints);
	int GetNumberPBConstraints();

	void SetNumberEBConstraints(int numEBConstraints);
	int GetNumberEBConstraints();

	void SetVariableUpperBound(int index, double value);
	void SetVariableLowerBound(int index, double value);

	void SetVariableType(int index, const char* type);

	void SetEvaluator(BaseEvaluator* eval);

	void Optimize();

	std::vector<double> GetResults();
};