#include "NomadCoreAPI.hpp"

extern "C" {

    void SingleObjEvaluatorWrapper::Initialize( int numConstraints ) {
		m_Constraints.resize(numConstraints);
		m_Init(numConstraints);
	}

    void SingleObjEvaluatorWrapper::Evaluate( double* x, int numVars ) {
		m_Evaluate(x, numVars);
		m_Obj = m_GetObjectiveFunction();
		m_GetConstraints(m_Constraints.data());
	}

    double SingleObjEvaluatorWrapper::GetObjectiveFunction( void ) {
        return m_Obj;
    }

    std::vector<double> SingleObjEvaluatorWrapper::GetConstraints( void ) {
		return m_Constraints;
	}

    void MultiObjEvaluatorWrapper::Initialize( int numConstraints, int numObjFunctions ) {
        m_Constraints.resize(numConstraints);
        m_Obj.resize(numObjFunctions);
        m_Init(numConstraints, numObjFunctions);
    }

    void MultiObjEvaluatorWrapper::Evaluate( double* x, int m_NumVars ) {
		m_Evaluate(x, m_NumVars);
		m_GetObjectiveFunction(m_Obj.data());
		m_GetConstraints(m_Constraints.data());
	}

    std::vector<double> MultiObjEvaluatorWrapper::GetObjectiveFunction( void ) {
		return m_Obj;
	}

    std::vector<double> MultiObjEvaluatorWrapper::GetConstraints( void ) {
        return m_Constraints;
    }

    NomadCore* CreateNomadCore( void ) {
        return new NomadCore();
    }

    void SetOutputPath( NomadCore* nomadCore, const char* path ) {
        nomadCore->SetOutputPath(path);
    }

    void SetNumberVariables( NomadCore* nomadCore, int numVars ) {
        nomadCore->SetNumberVariables(numVars);
    }

    void SetInitialVariableValue( NomadCore* nomadCore, int index, double value ) {
        nomadCore->SetInitialVariableValue(index, value);
    }

    void SetVariableUpperBound( NomadCore* nomadCore, int index, double value ) {
        nomadCore->SetVariableUpperBound(index, value);
    }

    void SetVariableLowerBound( NomadCore* nomadCore, int index, double value ) {
        nomadCore->SetVariableLowerBound(index, value);
    }

    void SetVariableType( NomadCore* nomadCore, int index, const char* type ) {
		nomadCore->SetVariableType(index, type);
	}

    void SetNumberOfIterations( NomadCore* nomadCore, int numIterations ) {
        nomadCore->SetNumberOfIterations(numIterations);
    }

    void SetNumberEBConstraints( NomadCore* nomadCore, int numEBConstraints ) {
        nomadCore->SetNumberEBConstraints(numEBConstraints);
    }

    void SetNumberPBConstraints( NomadCore* nomadCore, int numPBConstraints ) {
        nomadCore->SetNumberPBConstraints(numPBConstraints);
    }

    void SetSingleObjEvaluator( NomadCore* nomadCore, EvaluateDelegate evaluator, GetSingleObjFunctionDelegate m_GetObjectiveFunction, GetConstraintsDelegate m_GetConstraints, SingleObjInitDelegate m_Init ) {
        SingleObjEvaluatorWrapper* wrapper = new SingleObjEvaluatorWrapper();
        wrapper->m_Evaluate = evaluator;
        wrapper->m_GetObjectiveFunction = m_GetObjectiveFunction;
        wrapper->m_GetConstraints = m_GetConstraints;
        wrapper->m_Init = m_Init;
        nomadCore->SetSingleObjEvaluator(wrapper);
    }

    void SetMultiObjEvaluator( NomadCore* nomadCore, EvaluateDelegate evaluator, GetMultiObjFunctionDelegate m_GetObjectiveFunction, GetConstraintsDelegate m_GetConstraints, MultiObjInitDelegate m_Init ) {
		MultiObjEvaluatorWrapper* wrapper = new MultiObjEvaluatorWrapper();
		wrapper->m_Evaluate = evaluator;
		wrapper->m_GetObjectiveFunction = m_GetObjectiveFunction;
		wrapper->m_GetConstraints = m_GetConstraints;
		wrapper->m_Init = m_Init;
		nomadCore->SetMultiObjEvaluator(wrapper);
	}

    void SetNumberObjFunctions( NomadCore* nomadCore, int numObjFunctions ) {
		nomadCore->SetNumberObjFunctions(numObjFunctions);
	}

    void OptimizeSingleObj( NomadCore* nomadCore ) {
        nomadCore->OptimizeSingleObj();
    }

    void OptimizeMultiObj( NomadCore* nomadCore ) {
		nomadCore->OptimizeMultiObj();
	}

    double* GetResults( NomadCore* nomadCore, int* size ) {
        static std::vector<double> results = nomadCore->GetResults();
        *size = static_cast<int>(results.size());
        return results.data();
    }
}
