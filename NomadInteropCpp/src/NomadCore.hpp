/**
 \file   NomadCore.hpp
 \brief  NOMAD Core Functions (headers)
 \author
 \date   2024-07-29
 \see    NomadCore.cpp
 */

#ifndef NOMADCORE_H
#define NOMADCORE_H

#include "nomad.hpp"
#include "BaseEvaluator.hpp"

class NomadCore
{
private:
	const char*  m_OutputPath = nullptr;		///< Output path.
	int		     m_NumVars = 0;				    ///< Number of variables.
	int			 m_NumIterations = 100;		    ///< Number of iterations.
	int			 m_NumPBConstraints = 0;		///< Number of progressive barrier constraints.
	int			 m_NumEBConstraints = 0;		///< Number of extreme barrier constraints.
	int			 m_NumObjFunctions = 1;		 	///< Number of objective functions.

	std::vector<double>		 m_InitialVarsVec = { };			///< Initial variables. Stores the initial values of the variables.
	std::vector<double>		 m_FinalVariables = { };			///< Final variables. Stores the optimizer results.
	std::vector<double>		 m_UpperBoundValueVec = { };		///< Upper bound values of the variables.
	std::vector<bool>		 m_UpperBoundIsGivenVec = { };		///< Flag for upper bound values.
	std::vector<double>		 m_LowerBoundValueVec = { };		///< Lower bound values of the variables.
	std::vector<bool>		 m_LowerBoundIsGivenVec = { };		///< Flag for lower bound values.
	std::vector<bool>		 m_ParamaterTypeIsGivenVec = { };	///< Flag for parameter types.
	std::vector<std::string> m_ParamaterTypeVec = { };

	BaseSingleObjEvaluator*  m_SingleObjEvaluator = nullptr; ///< Single-objective evaluator.
	BaseMultiObjEvaluator*   m_MultiObjEvaluator = nullptr;  ///< Multi-objective evaluator.

public:
	/// Constructor.
	/**
	*/
	NomadCore();

	/// Destructor.
	/**
	*/
	~NomadCore();

	/// Set the output path.
	/**
	 \param outputPath Path for output file  -- \b IN.
	 */
	void SetOutputPath( const char* outputPath );

	/// Set the number of iterations.
	/**
	 \param numIters Number of iterations  -- \b IN.
	 */
	void SetNumberOfIterations( int numIters );

	/// Get the number of iterations.
	/**
	 \return Number of iterations.
	 */
	int GetNumberOfIterations( void );

	/// Set the number of variables.
	/**
	 \param numVariables Number of variables  -- \b IN.
	 */
	void SetNumberVariables( int numVariables );

	/// Get the number of variables.
	/**
	 \return Number of variables.
	 */
	int GetNumberOfVariables( void );

	/// Set the initial value of a variable.
	/**
	 \param index Index of the variable  -- \b IN.
	 \param value Initial value of the variable  -- \b IN.
	 */
	void SetInitialVariableValue( int index, double value );

	/// Set the number of progressive barrier constraints.
	/**
	 \param numPBConstraints Number of progressive barrier constraints  -- \b IN.
	 */
	void SetNumberPBConstraints( int numPBConstraints );

	/// Get the number of progressive barrier constraints.
	/**
	 \return Number of progressive barrier constraints.
	 */
	int GetNumberPBConstraints( void );

	/// Set the number of extreme barrier constraints.
	/**
	 \param numEBConstraints Number of extreme barrier constraints  -- \b IN.
	 */
	void SetNumberEBConstraints( int numEBConstraints );

	/// Get the number of extreme barrier constraints.
	/**
	 \return Number of extreme barrier constraints.
	 */
	int GetNumberEBConstraints( void );

	/// Set the upper bound of a variable.
	/**
	 \param index Index of the variable  -- \b IN.
	 \param value Upper bound of the variable  -- \b IN.
	 */
	void SetVariableUpperBound( int index, double value );

	/// Set the lower bound of a variable.
	/**
	 \param index Index of the variable  -- \b IN.
	 \param value Lower bound of the variable  -- \b IN.
	 */
	void SetVariableLowerBound( int index, double value );

	/// Set the type of a variable.
	/**
	* - "CONTINUOUS"
	* - "INTEGER"
	* - "BINARY"
	* - "CATEGORICAL"
	 \param index Index of the variable  -- \b IN.
	 \param type Type of the variable  -- \b IN.
	 */
	void SetVariableType( int index, const char* type );

	/// Set the number of objective functions.
	/**
	 \param numObjFunctions Number of objective functions  -- \b IN.
	 */
	void SetNumberObjFunctions( int numObjFunctions );

	/// Get the number of objective functions.
	/**
	 \return Number of objective functions.
	 */
	int GetNumberObjFunctions( void );

	/// Set the single-objective evaluator.
	/**
	 \param eval Single-objective evaluator  -- \b IN.
	 */
	void SetSingleObjEvaluator( BaseSingleObjEvaluator* eval );

	/// Set the multi-objective evaluator.
	/**
	 \param eval Multi-objective evaluator  -- \b IN.
	 */
	void SetMultiObjEvaluator( BaseMultiObjEvaluator* eval );

	/// Optimize a single-objective problem.
	/**
	*/
	void OptimizeSingleObj( void );

	/// Optimize a multi-objective problem.
	/**
	*/
	void OptimizeMultiObj( void );

	/// Get the results.
	/**
	 \return Optimizer results.
	 */
	std::vector<double> GetResults( void );
};

#endif // NOMADCORE_H