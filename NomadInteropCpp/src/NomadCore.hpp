#pragma once
#include "nomad.hpp"
#include "BaseEvaluator.hpp"

class NomadCore
{
private:
	const char*  m_OutputPath = nullptr;
	int		     m_NumVars = 0;
	int			 m_NumIterations = 100;
	int			 m_NumPBConstraints = 0;
	int			 m_NumEBConstraints = 0;
	int			 m_NumObjFunctions = 1;

	std::vector<double>		 m_InitialVarsVec = { };
	std::vector<double>		 m_FinalVariables = { };
	std::vector<double>		 m_UpperBoundValueVec = { };
	std::vector<bool>		 m_UpperBoundIsGivenVec = { };
	std::vector<double>		 m_LowerBoundValueVec = { };
	std::vector<bool>		 m_LowerBoundIsGivenVec = { };
	std::vector<bool>		 m_ParamaterTypeIsGivenVec = { };
	std::vector<std::string> m_ParamaterTypeVec = { };

	BaseSingleObjEvaluator*  m_SingleObjEvaluator = nullptr;
	BaseMultiObjEvaluator*   m_MultiObjEvaluator = nullptr;

public:

	NomadCore();
	~NomadCore();

	/**
	 * @brief Set the output file path.
	 * @param outputPath Path to the output file.
	 */
	void SetOutputPath( const char* outputFilePath );

	void SetNumberOfIterations( int numIters );
	int GetNumberOfIterations( void );

	void SetNumberVariables( int numberVariables );
	int GetNumberOfVariables( void );

	void SetInitialVariableValue( int index, double value );

	void SetNumberPBConstraints( int numPBConstraints );
	int GetNumberPBConstraints( void );

	void SetNumberEBConstraints( int numEBConstraints );
	int GetNumberEBConstraints( void );

	void SetVariableUpperBound( int index, double value );
	void SetVariableLowerBound( int index, double value );

	void SetVariableType( int index, const char* type );

	void SetNumberObjFunctions( int numObjFunctions );
	int GetNumberObjFunctions( void );

	void SetSingleObjEvaluator( BaseSingleObjEvaluator* eval );
	void SetMultiObjEvaluator( BaseMultiObjEvaluator* eval );

	void OptimizeSingleObj( void );
	void OptimizeMultiObj( void );

	std::vector<double> GetResults( void );
};