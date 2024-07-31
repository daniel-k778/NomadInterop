#include "NomadCore.hpp"
#include "NomadEvaluator.hpp"

NomadCore::NomadCore( void )
{

}

NomadCore::~NomadCore( void )
{
    if (_MultiObjEvaluator)
    {
        delete _MultiObjEvaluator;
    }

    if (_SingleObjEvaluator)
    {
        delete _SingleObjEvaluator;
    }
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
    _NumPBConstraints = numPBConstraints;
}

int NomadCore::GetNumberPBConstraints( void )
{
    return _NumPBConstraints;
}

void NomadCore::SetNumberEBConstraints( int numEBConstraints )
{
    _NumEBConstraints = numEBConstraints;
}

int NomadCore::GetNumberEBConstraints(void )
{
    return _NumEBConstraints;
}

void NomadCore::SetSingleObjEvaluator( BaseSingleObjEvaluator* eval )
{
    if (_SingleObjEvaluator)
    {
        delete _SingleObjEvaluator;
        _SingleObjEvaluator = nullptr;
    }
    _SingleObjEvaluator = eval;
}

void NomadCore::SetMultiObjEvaluator( BaseMultiObjEvaluator* eval )
{
    if (_MultiObjEvaluator)
    {
        delete _MultiObjEvaluator;
        _MultiObjEvaluator = nullptr;
    }
    _MultiObjEvaluator = eval;
}

void NomadCore::SetNumberObjFunctions( int numObjFunctions )
{
    _NumObjFunctions = numObjFunctions;
}

int NomadCore::GetNumberObjFunctions( void )
{
    return _NumObjFunctions;
}

void NomadCore::OptimizeSingleObj( void )
{
    if (_NumVars <= 0)
    {
        throw std::exception("Number of variables must be greater than 0.");
    }

    if (_NumObjFunctions != 1)
    {
        throw std::exception("Only one objective function can be optimized.");
    }
    // Display
    NOMAD::Display out (std::cout);
    out.precision(NOMAD::DISPLAY_PRECISION_STD);

    try
    {
        // NOMAD initialisations
        NOMAD::begin(0, NULL);

        // Paramater creation
        NOMAD::Parameters params (out);

        // Set the number of variables
        params.set_DIMENSION(_NumVars);

        // Definition of output types
        vector<NOMAD::bb_output_type> bbot;
        bbot.resize(_NumPBConstraints + _NumEBConstraints + 1);
        bbot[0] = NOMAD::OBJ; // 0 always obj for single obj

        // Add the PB constraints
        for (int i = 1; i < _NumPBConstraints + 1; i++)
        {
            bbot[i] = NOMAD::PB;
        }

        // Add the EB constraints
        for (int i = _NumPBConstraints + 1; i < _NumPBConstraints + _NumEBConstraints + 1; i++)
        {
            bbot[i] = NOMAD::EB;
        }

        params.set_BB_OUTPUT_TYPE(bbot);

        // Set the parameter types
        for (int i = 0; i < _NumVars; i++)
        {
            if (_ParamaterTypeIsGivenVec[i])
            {
                if (_ParamaterTypeVec[i] == "CATEGORICAL")
                {
                    params.set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::CATEGORICAL);
                }
                else if (_ParamaterTypeVec[i] == "INTEGER")
                {
                    params.set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::INTEGER);
                }
                else if (_ParamaterTypeVec[i] == "CONTINUOUS")
                {
                    params.set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::CONTINUOUS);
                }
                else if (_ParamaterTypeVec[i] == "BINARY")
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
        params.set_MAX_BB_EVAL(_NumIterations);
        
        // Display
        params.set_DISPLAY_DEGREE(2);

        // Output file
        if (_OutputPath)
        {
            params.set_SOLUTION_FILE(_OutputPath);
        }

        // Parameters validation
        params.check();

        // Custom evaluator creation
        NomadSingleObjEvaluator* evaluatorPtr = new NomadSingleObjEvaluator(params, _SingleObjEvaluator, this);

        // Algorithm creation and execution
        NOMAD::Mads mads (params, evaluatorPtr);
        mads.run();

        delete evaluatorPtr;

        // Get the best feasible solution
        for (int i = 0; i < _NumVars; i++) 
        {
            _FinalVariables[i] = mads.get_best_feasible()->value(i);
        }


    }
    catch (exception& e)
    {
        std::cerr << "\nNOMAD has been interrupted (" << e.what() << ")\n\n";
    }

    NOMAD::Slave::stop_slaves(out);
    NOMAD::end();

}

void NomadCore::OptimizeMultiObj( void )
{
    if (_NumVars <= 0)
    {
        throw std::exception("Number of variables must be greater than 0.");
    }

    if (_NumObjFunctions <= 1)
    {
        throw std::exception("Number of objective functions must be greater than 1.");
    }

    // Display
    NOMAD::Display out (std::cout);
    out.precision(NOMAD::DISPLAY_PRECISION_STD);
    try
    {
        // NOMAD initialisations
        NOMAD::begin(0, NULL);

        // Paramater creation
        NOMAD::Parameters params (out);

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
                if (_ParamaterTypeVec[i] == "CATEGORICAL")
                {
                    params.set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::CATEGORICAL);
                }
                else if (_ParamaterTypeVec[i] == "INTEGER")
                {
                    params.set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::INTEGER);
                }
                else if (_ParamaterTypeVec[i] == "CONTINUOUS")
                {
                    params.set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::CONTINUOUS);
                }
                else if (_ParamaterTypeVec[i] == "BINARY")
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
        params.set_MULTI_OVERALL_BB_EVAL(_NumIterations);

        // Display
        params.set_DISPLAY_DEGREE(2);
        if (_OutputPath)
        {
            params.set_SOLUTION_FILE(_OutputPath);
        }

        // Parameters validation
        params.check();

        // Custom evaluator creation
        NomadMultiObjEvaluator* evaluatorPtr = new NomadMultiObjEvaluator(params, _MultiObjEvaluator, this);

        // Algorithm creation and execution
        NOMAD::Mads mads (params, evaluatorPtr);
        mads.multi_run();

        delete evaluatorPtr;

        // Get the best feasible solution
        for (int i = 0; i < _NumVars; i++)
        {
            _FinalVariables[i] = mads.get_best_feasible()->value(i);
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
