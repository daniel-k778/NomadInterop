#include "NomadCore.hpp"
#include "NomadEvaluator.hpp"

NomadCore::NomadCore( void )
{

}

NomadCore::~NomadCore( void )
{

}

void NomadCore::SetInitialVariableValue( int index, double value )
{
    if (index >= _NumVars || index < 0)
    {
        throw std::invalid_argument("Index out of bounds");
    }

    _InitialVarsVec[index] = value;
}

void NomadCore::SetNumberVariables( int numberVariables )
{
    // Set the number of variables
    // Resize the vectors to the number of variables

    if (numberVariables <= 0)
    {
        throw std::exception("Number of variables must be greater than 0.");
    }

    _NumVars = numberVariables;
    _UpperBoundIsGivenVec.resize(_NumVars, false);
    _LowerBoundIsGivenVec.resize(_NumVars, false);
    _UpperBoundValueVec.resize(_NumVars, 0.0);
    _LowerBoundValueVec.resize(_NumVars, 0.0);
    _InitialVarsVec.resize(_NumVars, 0.0);
    _FinalVariables.resize(_NumVars, 0.0);
    _ParamaterTypeIsGivenVec.resize(_NumVars, false);
    _ParamaterTypeVec.resize(_NumVars, "");
}

int NomadCore::GetNumberOfVariables( void )
{
    return _NumVars;
}

void NomadCore::SetVariableUpperBound( int index, double value )
{
    if (index >= _NumVars || index < 0)
    {
        throw std::invalid_argument("Index out of bounds");
    }

    // Adds a flag to indicate that the upper bound is given
    _UpperBoundIsGivenVec[index] = true;
    _UpperBoundValueVec[index] = value;
}

void NomadCore::SetVariableLowerBound( int index, double value )
{
    if (index >= _NumVars || index < 0)
    {
        throw std::invalid_argument("Index out of bounds");
    }

    // Adds a flag to indicate that the lower bound is given
    _LowerBoundIsGivenVec[index] = true;
    _LowerBoundValueVec[index] = value;
}

void NomadCore::SetVariableType( int index, const char* type ) {
    if (index >= _NumVars || index < 0)
    {
        throw std::invalid_argument("Index out of bounds");
    }

    // Adds a flag to indicate that the parameter type is given
    _ParamaterTypeIsGivenVec[index] = true;
    _ParamaterTypeVec[index] = type;
}


void NomadCore::SetNumberOfIterations( int numIters )
{
    if (numIters <= 0)
    {
        throw std::exception("Number of iterations must be greater than 0.");
    }
    _NumIterations = numIters;
}

int NomadCore::GetNumberOfIterations( void )
{
    return _NumIterations;
}

void NomadCore::SetOutputPath( const char* outputFilePath )
{
    _OutputPath = outputFilePath;
}

void NomadCore::SetNumberPBConstraints( int numPBConstraints )
{
    if (numPBConstraints < 0)
    {
        throw std::exception("Number of progressive barrier constraints being set must be greater or equal to 0.");
    }
    _NumPBConstraints = numPBConstraints;
}

int NomadCore::GetNumberPBConstraints( void )
{
    return _NumPBConstraints;
}

void NomadCore::SetNumberEBConstraints( int numEBConstraints )
{
    if (numEBConstraints < 0)
    {
        throw std::exception("Number of extreme barrier constraints being set must be greater or equal to 0.");
    }
    _NumEBConstraints = numEBConstraints;
}

int NomadCore::GetNumberEBConstraints( void )
{
    return _NumEBConstraints;
}

void NomadCore::SetEvaluator( BaseSingleObjEvaluator* eval )
{
    _SingleObjEvaluatorPtr = eval;
    _EvaluatorType = EvaluatorType::SINGLE_OBJECTIVE;
    _EvaluatorPointerType = EvaluatorPointerType::RAW;
}

void NomadCore::SetEvaluator( BaseMultiObjEvaluator* eval )
{
    _MultiObjEvaluatorPtr = eval;
    _EvaluatorType = EvaluatorType::MULTI_OBJECTIVE;
    _EvaluatorPointerType = EvaluatorPointerType::RAW;
}

void NomadCore::SetEvaluator( std::shared_ptr<BaseSingleObjEvaluator> eval )
{
    _SingleObjEvaluatorSmrtPtr = eval;
    _EvaluatorType = EvaluatorType::SINGLE_OBJECTIVE;
    _EvaluatorPointerType = EvaluatorPointerType::SMART;
}

void NomadCore::SetEvaluator( std::shared_ptr<BaseMultiObjEvaluator> eval )
{
    _MultiObjEvaluatorSmrtPtr = eval;
    _EvaluatorType = EvaluatorType::MULTI_OBJECTIVE;
    _EvaluatorPointerType = EvaluatorPointerType::SMART;
}

void NomadCore::SetNumberObjFunctions( int numObjFunctions )
{
    if (_EvaluatorType == EvaluatorType::SINGLE_OBJECTIVE && numObjFunctions != 1)
    {
        throw std::exception("Single objective evaluator is set. Number of objective functions must be 1.");
    }
    if (_EvaluatorType == EvaluatorType::NONE)
    {
        throw std::exception("Evaluator is not set.");
    }
    if (numObjFunctions <= 1)
    {
        throw std::exception("Number of objective functions must be greater than 1.");
    }
    _NumObjFunctions = numObjFunctions;
}

int NomadCore::GetNumberObjFunctions( void )
{
    return _NumObjFunctions;
}

void NomadCore::Optimize(void)
{
    if (_NumVars <= 0)
    {
        throw std::exception("Number of variables must be greater than 0.");
    }
    if (_NumIterations <= 0)
    {
        throw std::exception("Number of iterations must be greater than 0.");
    }
    if (_EvaluatorType == EvaluatorType::NONE)
    {
        throw std::exception("Evaluator is not set.");
    }
    if (_EvaluatorType == EvaluatorType::SINGLE_OBJECTIVE && _NumObjFunctions != 1)
    {
        throw std::exception("Number of objective functions must be equal to 1 for single-objective optimization.");
    }
    else if (_EvaluatorType == EvaluatorType::MULTI_OBJECTIVE && _NumObjFunctions <= 1)
    {
        throw std::exception("Number of objective functions must be greater than 1 for multi-objective optimization.");
    }

    // Display
    NOMAD::Display out(std::cout);
    out.precision(NOMAD::DISPLAY_PRECISION_STD);
    try
    {
        // NOMAD initialisations
        NOMAD::begin(0, NULL);

        // Paramater creation
        NOMAD::Parameters params(out);

        // Set the number of variables
        params.set_DIMENSION(_NumVars);

        // Definition of output types
        vector<NOMAD::bb_output_type> bbot;
        bbot.resize(_NumPBConstraints + _NumEBConstraints + _NumObjFunctions);

        // Set the number of objective functions
        for (int i = 0; i < _NumObjFunctions; i++)
        {
            bbot[i] = NOMAD::OBJ;
        }

        // Set the number of PB constraints
        for (int i = _NumObjFunctions; i < _NumPBConstraints + _NumObjFunctions; i++)
        {
            bbot[i] = NOMAD::PB;
        }

        // Set the number of EB constraints
        for (int i = _NumPBConstraints + _NumObjFunctions; i < _NumPBConstraints + _NumEBConstraints + _NumObjFunctions; i++)
        {
            bbot[i] = NOMAD::EB;
        }

        params.set_BB_OUTPUT_TYPE(bbot);

        // Set the parameter types
        for (int i = 0; i < _NumVars; i++)
        {
            if (_ParamaterTypeIsGivenVec[i])
            {
                if (_ParamaterTypeVec[i] == NOMAD_VARIABLE_TYPE_CATEGORICAL)
                {
                    params.set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::CATEGORICAL);
                }
                else if (_ParamaterTypeVec[i] == NOMAD_VARIABLE_TYPE_INTEGER)
                {
                    params.set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::INTEGER);
                }
                else if (_ParamaterTypeVec[i] == NOMAD_VARIABLE_TYPE_CONTINUOUS)
                {
                    params.set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::CONTINUOUS);
                }
                else if (_ParamaterTypeVec[i] == NOMAD_VARIABLE_TYPE_BINARY)
                {
                    params.set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::BINARY);
                }
                else
                {
                    throw std::invalid_argument("Invalid parameter type");
                }
            }
        }

        // Display
        params.set_DISPLAY_STATS("bbe ( sol ) obj");

        // Set the bounds and initial values of variables
        NOMAD::Point x0(_NumVars);
        NOMAD::Point lb(_NumVars);
        NOMAD::Point ub(_NumVars);

        for (int i = 0; i < _NumVars; i++)
        {
            x0[i] = _InitialVarsVec[i];

            if (_LowerBoundIsGivenVec[i])
            {
                lb[i] = _LowerBoundValueVec[i];
            }

            if (_UpperBoundIsGivenVec[i])
            {
                ub[i] = _UpperBoundValueVec[i];
            }
        }

        params.set_X0(x0);
        params.set_LOWER_BOUND(lb);
        params.set_UPPER_BOUND(ub);

        // Set max iterations
        if (_EvaluatorType == EvaluatorType::SINGLE_OBJECTIVE)
        {
            params.set_MAX_BB_EVAL(_NumIterations);
        }
        else if (_EvaluatorType == EvaluatorType::MULTI_OBJECTIVE)
        {
            params.set_MULTI_OVERALL_BB_EVAL(_NumIterations);
        }

        // Display
        params.set_DISPLAY_DEGREE(2);
        if (_OutputPath)
        {
            params.set_SOLUTION_FILE(_OutputPath);
        }

        // Parameters validation
        params.check();

        // Custom evaluator creation
        NOMAD::Evaluator* evaluator = nullptr;
        if (_EvaluatorType == EvaluatorType::SINGLE_OBJECTIVE)
        {
            if (_EvaluatorPointerType == EvaluatorPointerType::RAW)
            {
                evaluator = new NomadSingleObjEvaluator(params, _SingleObjEvaluatorPtr, this);
            }
            else if (_EvaluatorPointerType == EvaluatorPointerType::SMART)
            {
                evaluator = new NomadSingleObjEvaluator(params, _SingleObjEvaluatorSmrtPtr, this);
            }
            else
            {
                throw std::exception("Invalid evaluator pointer type.");
            }
        }
        else if (_EvaluatorType == EvaluatorType::MULTI_OBJECTIVE)
        {
            if (_EvaluatorPointerType == EvaluatorPointerType::RAW)
            {
                evaluator = new NomadMultiObjEvaluator(params, _MultiObjEvaluatorPtr, this);
            }
            else if (_EvaluatorPointerType == EvaluatorPointerType::SMART)
            {
                evaluator = new NomadMultiObjEvaluator(params, _MultiObjEvaluatorSmrtPtr, this);
            }
            else
            {
                throw std::exception("Invalid evaluator pointer type.");
            }
        }

        // Algorithm creation and execution
        NOMAD::Mads mads(params, evaluator);

        if (_EvaluatorType == EvaluatorType::SINGLE_OBJECTIVE)
        {
            mads.run();
        }
        else if (_EvaluatorType == EvaluatorType::MULTI_OBJECTIVE)
        {
            mads.multi_run();
        }

        delete evaluator;

        // Get the best feasible solution
        for (int i = 0; i < _NumVars; i++)
        {
            auto bestFeasible = mads.get_best_feasible();

            if (bestFeasible)
            {
                _FinalVariables[i] = bestFeasible->value(i);
            }
        }


    }
    catch (exception& e)
    {
        std::cerr << "\nNOMAD has been interrupted (" << e.what() << ")\n\n";
    }

    NOMAD::Slave::stop_slaves(out);
    NOMAD::end();

}

std::vector<double> NomadCore::GetResults( void )
{
    return _FinalVariables;
}

EvaluatorType NomadCore::GetEvaluatorType( void )
{
    return _EvaluatorType;
}

EvaluatorPointerType NomadCore::GetEvaluatorPointerType( void )
{
    return _EvaluatorPointerType;
}