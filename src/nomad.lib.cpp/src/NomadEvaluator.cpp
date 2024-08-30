#include "NomadEvaluator.hpp"

NomadSingleObjEvaluator::NomadSingleObjEvaluator( const NOMAD::Parameters& p, BaseSingleObjEvaluator* evaluator, NomadCore* nomadCore ) : NOMAD::Evaluator( p )
{
    this->_SingleObjEvaluatorPtr = evaluator;
    this->_NomadCore = nomadCore;
    this->_Params = &p;

    // Initialize the evaluator
    static auto numConstraints = _NomadCore->GetNumberEBConstraints() + _NomadCore->GetNumberPBConstraints();
    _SingleObjEvaluatorPtr->Initialize(numConstraints);
}

NomadSingleObjEvaluator::NomadSingleObjEvaluator( const NOMAD::Parameters& p, std::shared_ptr<BaseSingleObjEvaluator> evaluator, NomadCore* nomadCore ) : NOMAD::Evaluator( p )
{
    this->_SingleObjEvaluatorSmrtPtr = evaluator;
    this->_NomadCore = nomadCore;
    this->_Params = &p;

    // Initialize the evaluator
    static auto numConstraints = _NomadCore->GetNumberEBConstraints() + _NomadCore->GetNumberPBConstraints();

    EvaluatorPointerType evalPtrType = _NomadCore->GetEvaluatorPointerType();

    if (evalPtrType == EvaluatorPointerType::RAW)
    {
        _SingleObjEvaluatorPtr->Initialize(numConstraints);
    }
    else if (evalPtrType == EvaluatorPointerType::SMART)
    {
        _SingleObjEvaluatorSmrtPtr->Initialize(numConstraints);
    }
    else
    {
        throw std::runtime_error("Invalid evaluator pointer type.");
    }
}

NomadSingleObjEvaluator::~NomadSingleObjEvaluator( void )
{

}

bool NomadSingleObjEvaluator::eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const
{
    // This function is called by NOMAD to evaluate the objective function and constraints
    // The function returns true if the evaluation succeeded, and false otherwise

    EvaluatorPointerType evalPtrType = _NomadCore->GetEvaluatorPointerType();

    static auto numVars = _NomadCore->GetNumberOfVariables();
    double* paramsPtr = new double[numVars];

    // Copy the variables to a double array
    for (int i = 0; i < numVars; i++)
    {
        paramsPtr[i] = x[i].value();
    }

    // Evaluate the objective function and constraints
    double objFuncValue;
    if (evalPtrType == EvaluatorPointerType::RAW)
    {
        _SingleObjEvaluatorPtr->Evaluate(paramsPtr, numVars);
        objFuncValue = _SingleObjEvaluatorPtr->GetObjectiveFunction();
    }
    else if (evalPtrType == EvaluatorPointerType::SMART)
    {
        _SingleObjEvaluatorSmrtPtr->Evaluate(paramsPtr, numVars);
        objFuncValue = _SingleObjEvaluatorSmrtPtr->GetObjectiveFunction();
    }
    else
    {
        throw std::runtime_error("Invalid evaluator pointer type.");
    }

    // Set the objective function value
    x.set_bb_output(0, objFuncValue);

    // Get the constraints array
    std::vector<double> evalConstraintsArr;
    if (evalPtrType == EvaluatorPointerType::RAW)
    {
        evalConstraintsArr = _SingleObjEvaluatorPtr->GetConstraints();
    }
    else if (evalPtrType == EvaluatorPointerType::SMART)
    {
        evalConstraintsArr = _SingleObjEvaluatorSmrtPtr->GetConstraints();
    }
    else
    {
        throw std::runtime_error("Invalid evaluator pointer type.");
    }

    static auto numConstraints = _NomadCore->GetNumberEBConstraints() + _NomadCore->GetNumberPBConstraints();

    if (evalConstraintsArr.size() == numConstraints)
    {
        // Set the constraints
        for (int i = 0; i < evalConstraintsArr.size(); i++)
        {
            x.set_bb_output(i + 1, evalConstraintsArr.at(i));
        }
    }
    else
    {
        throw std::runtime_error("The number of constraints does not match the number of constraints in the evaluator.");
    }

    delete[] paramsPtr;

    // Return the evaluation status
    if (evalPtrType == EvaluatorPointerType::RAW)
    {
        count_eval = _SingleObjEvaluatorPtr->GetObjectiveFunctionStatus();
    }
    else if (evalPtrType == EvaluatorPointerType::SMART)
    {
        count_eval = _SingleObjEvaluatorSmrtPtr->GetObjectiveFunctionStatus();
    }
    else
    {
        throw std::runtime_error("Invalid evaluator pointer type.");
    }

    return true;
}

NomadMultiObjEvaluator::NomadMultiObjEvaluator( const NOMAD::Parameters& p, BaseMultiObjEvaluator* evaluator, NomadCore* nomadCore ) : NOMAD::Multi_Obj_Evaluator( p )
{
    this->_MultiObjEvaluatorPtr = evaluator;
    this->_NomadCore = nomadCore;
    this->_Params = &p;

    // Initialize the evaluator
    static auto numConstraints = _NomadCore->GetNumberEBConstraints() + _NomadCore->GetNumberPBConstraints();
    static auto numObjFunctions = _NomadCore->GetNumberObjFunctions();
    _MultiObjEvaluatorPtr->Initialize(numConstraints, numObjFunctions);
}

NomadMultiObjEvaluator::NomadMultiObjEvaluator( const NOMAD::Parameters& p, std::shared_ptr<BaseMultiObjEvaluator> evaluator, NomadCore* nomadCore ) : NOMAD::Multi_Obj_Evaluator( p )
{
    this->_MultiObjEvaluatorSmrtPtr = evaluator;
    this->_NomadCore = nomadCore;
    this->_Params = &p;

    // Initialize the evaluator
    static auto numConstraints = _NomadCore->GetNumberEBConstraints() + _NomadCore->GetNumberPBConstraints();
    static auto numObjFunctions = _NomadCore->GetNumberObjFunctions();

    EvaluatorPointerType evalPtrType = _NomadCore->GetEvaluatorPointerType();
    if (evalPtrType == EvaluatorPointerType::RAW)
    {
        _MultiObjEvaluatorPtr->Initialize(numConstraints, numObjFunctions);
    }
    else if (evalPtrType == EvaluatorPointerType::SMART)
    {
        _MultiObjEvaluatorSmrtPtr->Initialize(numConstraints, numObjFunctions);
    }
    else
    {
        throw std::runtime_error("Invalid evaluator pointer type.");
    }
}

NomadMultiObjEvaluator::~NomadMultiObjEvaluator( void )
{

}

bool NomadMultiObjEvaluator::eval_x( NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval ) const
{
    // This function is called by NOMAD to evaluate the objective function and constraints
    // The function returns true if the evaluation succeeded, and false otherwise

    auto evalPtrType = _NomadCore->GetEvaluatorPointerType();

    static auto numVars = _NomadCore->GetNumberOfVariables();
    double* paramsPtr = new double[numVars];

    // Copy the variables to a double array
    for (int i = 0; i < numVars; i++)
    {
        paramsPtr[i] = x[i].value();
    }

    // Evaluate the objective function
    if (evalPtrType == EvaluatorPointerType::RAW)
    {
        _MultiObjEvaluatorPtr->Evaluate(paramsPtr, numVars);
    }
    else if (evalPtrType == EvaluatorPointerType::SMART)
    {
        _MultiObjEvaluatorSmrtPtr->Evaluate(paramsPtr, numVars);
    }
    else
    {
        throw std::runtime_error("Invalid evaluator pointer type.");
    }

    // Get the objective functions and constraints arrays
    std::vector<double> evalObjFunctionsArr;
    std::vector<double> evalConstraintsArr;
    if (evalPtrType == EvaluatorPointerType::RAW)
    {
        evalObjFunctionsArr = _MultiObjEvaluatorPtr->GetObjectiveFunction();
        evalConstraintsArr = _MultiObjEvaluatorPtr->GetConstraints();
    }
    else if (evalPtrType == EvaluatorPointerType::SMART)
    {
        evalObjFunctionsArr = _MultiObjEvaluatorSmrtPtr->GetObjectiveFunction();
        evalConstraintsArr = _MultiObjEvaluatorSmrtPtr->GetConstraints();
    }
    else
    {
        throw std::runtime_error("Invalid evaluator pointer type.");
    }
    static auto numConstraints = _NomadCore->GetNumberEBConstraints() + _NomadCore->GetNumberPBConstraints();
    static auto numObjFunctions = _NomadCore->GetNumberObjFunctions();

    if (evalObjFunctionsArr.size() == numObjFunctions)
    {
        // Set the objective functions
        for (int i = 0; i < evalObjFunctionsArr.size(); i++)
        {
            x.set_bb_output(i, evalObjFunctionsArr.at(i));
        }
    }
    else
    {
        throw std::runtime_error("The number of objective functions does not match the number of objective functions in the evaluator.");
    }

    if (evalConstraintsArr.size() == numConstraints)
    {
        // Set the constraints
        for (int i = 0; i < evalConstraintsArr.size(); i++)
        {
            x.set_bb_output(i + evalObjFunctionsArr.size(), evalConstraintsArr.at(i));
        }
    }
    else
    {
        throw std::runtime_error("The number of constraints does not match the number of constraints in the evaluator.");
    }

    delete[] paramsPtr;

    // Return the evaluation status
    if (evalPtrType == EvaluatorPointerType::RAW)
    {
        count_eval = _MultiObjEvaluatorPtr->GetObjectiveFunctionStatus();
    }
    else if (evalPtrType == EvaluatorPointerType::SMART)
    {
        count_eval = _MultiObjEvaluatorSmrtPtr->GetObjectiveFunctionStatus();
    }
    else
    {
        throw std::runtime_error("Invalid evaluator pointer type.");
    }

    return true;
}
