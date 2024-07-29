#include "NomadCoreAPI.hpp"

extern "C"
{

    void SingleObjEvaluatorWrapper::Initialize( int numConstraints )
    {
		m_Constraints.resize(numConstraints);
		m_Inititialize(numConstraints);
	}

    void SingleObjEvaluatorWrapper::Evaluate( double* x, int numVars )
    {
		m_Evaluate(x, numVars);
		m_Obj = m_GetObjectiveFunction();
		m_GetConstraints(m_Constraints.data());
	}

    double SingleObjEvaluatorWrapper::GetObjectiveFunction( void )
    {
        return m_Obj;
    }

    bool SingleObjEvaluatorWrapper::GetObjectiveFunctionStatus( void )
    {
        return m_ObjStatus;
    }

    std::vector<double> SingleObjEvaluatorWrapper::GetConstraints( void )
    {
		return m_Constraints;
	}

    void MultiObjEvaluatorWrapper::Initialize( int numConstraints, int numObjFunctions )
    {
        m_Constraints.resize(numConstraints);
        m_Obj.resize(numObjFunctions);
        m_Inititialize(numConstraints, numObjFunctions);
    }

    void MultiObjEvaluatorWrapper::Evaluate( double* x, int m_NumVars )
    {
		m_Evaluate(x, m_NumVars);
		m_GetObjectiveFunction(m_Obj.data());
		m_GetConstraints(m_Constraints.data());
	}

    std::vector<double> MultiObjEvaluatorWrapper::GetObjectiveFunction( void )
    {
		return m_Obj;
	}

    bool MultiObjEvaluatorWrapper::GetObjectiveFunctionStatus( void )
    {
		return m_ObjStatus;
	}

    std::vector<double> MultiObjEvaluatorWrapper::GetConstraints( void )
    {
        return m_Constraints;
    }

    NomadCore* CreateNomadCore( void )
    {
        return new NomadCore();
    }

    void SetOutputPath( NomadCore* nomadCore, const char* path )
    {
        nomadCore->SetOutputPath(path);
    }

    void SetNumberVariables( NomadCore* nomadCore, int numVars )
    {
        nomadCore->SetNumberVariables(numVars);
    }

    void SetInitialVariableValue( NomadCore* nomadCore, int index, double value )
    {
        nomadCore->SetInitialVariableValue(index, value);
    }

    void SetVariableUpperBound( NomadCore* nomadCore, int index, double value )
    {
        nomadCore->SetVariableUpperBound(index, value);
    }

    void SetVariableLowerBound( NomadCore* nomadCore, int index, double value )
    {
        nomadCore->SetVariableLowerBound(index, value);
    }

    void SetVariableType( NomadCore* nomadCore, int index, const char* type )
    {
		nomadCore->SetVariableType(index, type);
	}

    void SetNumberOfIterations( NomadCore* nomadCore, int numIterations )
    {
        nomadCore->SetNumberOfIterations(numIterations);
    }

    void SetNumberEBConstraints( NomadCore* nomadCore, int numEBConstraints )
    {
        nomadCore->SetNumberEBConstraints(numEBConstraints);
    }

    void SetNumberPBConstraints( NomadCore* nomadCore, int numPBConstraints )
    {
        nomadCore->SetNumberPBConstraints(numPBConstraints);
    }

    void SetSingleObjEvaluator( NomadCore* nomadCore, EvaluateDelegate evaluator, GetSingleObjFunctionDelegate m_GetObjectiveFunction, GetConstraintsDelegate m_GetConstraints, SingleObjInitDelegate m_Inititialize, GetObjectiveFunctionStatusDelegate m_GetObjectiveFunctionStatus )
    {
        SingleObjEvaluatorWrapper* w = new SingleObjEvaluatorWrapper();
        w->m_Evaluate = evaluator;
        w->m_GetObjectiveFunction = m_GetObjectiveFunction;
        w->m_GetObjectiveFunctionStatus = m_GetObjectiveFunctionStatus;
        w->m_GetConstraints = m_GetConstraints;
        w->m_Inititialize = m_Inititialize;
        nomadCore->SetSingleObjEvaluator(w);
    }

    void SetMultiObjEvaluator( NomadCore* nomadCore, EvaluateDelegate evaluator, GetMultiObjFunctionDelegate m_GetObjectiveFunction, GetConstraintsDelegate m_GetConstraints, MultiObjInitDelegate m_Inititialize, GetObjectiveFunctionStatusDelegate m_GetObjectiveFunctionStatus )
    {
		MultiObjEvaluatorWrapper* w = new MultiObjEvaluatorWrapper();
		w->m_Evaluate = evaluator;
		w->m_GetObjectiveFunction = m_GetObjectiveFunction;
        w->m_GetObjectiveFunctionStatus = m_GetObjectiveFunctionStatus;
		w->m_GetConstraints = m_GetConstraints;
		w->m_Inititialize = m_Inititialize;
		nomadCore->SetMultiObjEvaluator(w);
	}

    void SetNumberObjFunctions( NomadCore* nomadCore, int numObjFunctions )
    {
		nomadCore->SetNumberObjFunctions(numObjFunctions);
	}

    void OptimizeSingleObj( NomadCore* nomadCore )
    {
        nomadCore->OptimizeSingleObj();
    }

    void OptimizeMultiObj( NomadCore* nomadCore )
    {
		nomadCore->OptimizeMultiObj();
	}

    double* GetResults(NomadCore* nomadCore, int* size)
    {
        // This is a workaround to avoid copying the vector to a C array.
        // We use a static vector to hold the results so that we can return a pointer to the internal data.
        // Note: The use of static here means the results are not thread-safe and will persist across function calls.
        // Ensure that the NomadCore object is valid and the results are not modified elsewhere.
        static std::vector<double> results = nomadCore->GetResults();
        *size = static_cast<int>(results.size());
        return results.data();
    }
}
