#include "NomadCoreAPI.hpp"

extern "C"
{

    void SingleObjEvaluatorWrapper::Initialize( int numConstraints )
    {
		_Constraints.resize(numConstraints);
		_Inititialize(numConstraints);
	}

    void SingleObjEvaluatorWrapper::Evaluate( double* x, int numVars )
    {
		_Evaluate(x, numVars);
		_Obj = _GetObjectiveFunction();
		_GetConstraints(_Constraints.data());
	}

    double SingleObjEvaluatorWrapper::GetObjectiveFunction( void )
    {
        return _Obj;
    }

    bool SingleObjEvaluatorWrapper::GetObjectiveFunctionStatus( void )
    {
        return _ObjStatus;
    }

    std::vector<double> SingleObjEvaluatorWrapper::GetConstraints( void )
    {
		return _Constraints;
	}

    void MultiObjEvaluatorWrapper::Initialize( int numConstraints, int numObjFunctions )
    {
        _Constraints.resize(numConstraints);
        _Obj.resize(numObjFunctions);
        _Inititialize(numConstraints, numObjFunctions);
    }

    void MultiObjEvaluatorWrapper::Evaluate( double* x, int _NumVars )
    {
		_Evaluate(x, _NumVars);
		_GetObjectiveFunction(_Obj.data());
		_GetConstraints(_Constraints.data());
	}

    std::vector<double> MultiObjEvaluatorWrapper::GetObjectiveFunction( void )
    {
		return _Obj;
	}

    bool MultiObjEvaluatorWrapper::GetObjectiveFunctionStatus( void )
    {
		return _ObjStatus;
	}

    std::vector<double> MultiObjEvaluatorWrapper::GetConstraints( void )
    {
        return _Constraints;
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

    void SetSingleObjEvaluator( NomadCore* nomadCore, EvaluateDelegate evaluator, GetSingleObjFunctionDelegate _GetObjectiveFunction, GetConstraintsDelegate _GetConstraints, SingleObjInitDelegate _Inititialize, GetObjectiveFunctionStatusDelegate _GetObjectiveFunctionStatus )
    {
        SingleObjEvaluatorWrapper* w = new SingleObjEvaluatorWrapper();
        w->_Evaluate = evaluator;
        w->_GetObjectiveFunction = _GetObjectiveFunction;
        w->_GetObjectiveFunctionStatus = _GetObjectiveFunctionStatus;
        w->_GetConstraints = _GetConstraints;
        w->_Inititialize = _Inititialize;
        nomadCore->SetSingleObjEvaluator(w);
    }

    void SetMultiObjEvaluator( NomadCore* nomadCore, EvaluateDelegate evaluator, GetMultiObjFunctionDelegate _GetObjectiveFunction, GetConstraintsDelegate _GetConstraints, MultiObjInitDelegate _Inititialize, GetObjectiveFunctionStatusDelegate _GetObjectiveFunctionStatus )
    {
		MultiObjEvaluatorWrapper* w = new MultiObjEvaluatorWrapper();
		w->_Evaluate = evaluator;
		w->_GetObjectiveFunction = _GetObjectiveFunction;
        w->_GetObjectiveFunctionStatus = _GetObjectiveFunctionStatus;
		w->_GetConstraints = _GetConstraints;
		w->_Inititialize = _Inititialize;
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
