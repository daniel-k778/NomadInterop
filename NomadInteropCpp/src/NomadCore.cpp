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
    if (index >= m_NumVars || index < 0)
	{
		throw std::invalid_argument("Index out of bounds");
	}

	m_InitialVarsVec[index] = value;
}

void NomadCore::SetNumberVariables( int numberVariables )
{
    m_NumVars = numberVariables;
    m_UpperBoundIsGivenVec.resize(m_NumVars, false);
    m_LowerBoundIsGivenVec.resize(m_NumVars, false);
    m_UpperBoundValueVec.resize(m_NumVars, 0.0);
    m_LowerBoundValueVec.resize(m_NumVars, 0.0);
    m_InitialVarsVec.resize(m_NumVars, 0.0);
    m_FinalVariables.resize(m_NumVars, 0.0);
    m_ParamaterTypeIsGivenVec.resize(m_NumVars, false);
    m_ParamaterTypeVec.resize(m_NumVars, "");
}

int NomadCore::GetNumberOfVariables( void )
{
	return m_NumVars;
}

void NomadCore::SetVariableUpperBound( int index, double value )
{
    if (index >= m_NumVars || index < 0)
    {
        throw std::invalid_argument("Index out of bounds");
    }

    m_UpperBoundIsGivenVec[index] = true;
    m_UpperBoundValueVec[index] = value;
}

void NomadCore::SetVariableLowerBound( int index, double value )
{
    if (index >= m_NumVars || index < 0)
    {
        throw std::invalid_argument("Index out of bounds");
    }

	m_LowerBoundIsGivenVec[index] = true;
	m_LowerBoundValueVec[index] = value;
}

void NomadCore::SetVariableType( int index, const char* type ) {
    if (index >= m_NumVars || index < 0)
    {
        throw std::invalid_argument("Index out of bounds");
    }

    m_ParamaterTypeIsGivenVec[index] = true;
    m_ParamaterTypeVec[index] = type;
}


void NomadCore::SetNumberOfIterations( int numIters )
{
	m_NumIterations = numIters;
}

int NomadCore::GetNumberOfIterations( void )
{
	return m_NumIterations;
}

void NomadCore::SetOutputPath( const char* outputFilePath )
{
	m_OutputPath = outputFilePath;
}

void NomadCore::SetNumberPBConstraints( int numPBConstraints )
{
	m_NumPBConstraints = numPBConstraints;
}

int NomadCore::GetNumberPBConstraints( void )
{
	return m_NumPBConstraints;
}

void NomadCore::SetNumberEBConstraints( int numEBConstraints )
{
	m_NumEBConstraints = numEBConstraints;
}

int NomadCore::GetNumberEBConstraints(void )
{
	return m_NumEBConstraints;
}

void NomadCore::SetSingleObjEvaluator( BaseSingleObjEvaluator* eval )
{
    m_SingleObjEvaluator = eval;
}

void NomadCore::SetMultiObjEvaluator( BaseMultiObjEvaluator* eval )
{
    m_MultiObjEvaluator = eval;
}

void NomadCore::SetNumberObjFunctions( int numObjFunctions )
{
	m_NumObjFunctions = numObjFunctions;
}

int NomadCore::GetNumberObjFunctions( void )
{
	return m_NumObjFunctions;
}

void NomadCore::OptimizeSingleObj( void )
{
    if (m_NumVars <= 0)
    {
        throw std::exception("Number of variables must be greater than 0.");
    }

    if (m_NumObjFunctions != 1)
    {
        throw std::exception("Only one objective function can be optimized.");
    }

    NOMAD::Display* out = new NOMAD::Display(std::cout);

    try
    {
        out->precision(NOMAD::DISPLAY_PRECISION_STD);

        NOMAD::begin(0, NULL);

        NOMAD::Parameters* params = new NOMAD::Parameters(*out);
        params->set_DIMENSION(m_NumVars);

        vector<NOMAD::bb_output_type> bbot;
        bbot.resize(m_NumPBConstraints + m_NumEBConstraints + 1);
        bbot[0] = NOMAD::OBJ; // 0 always obj

        for (int i = 1; i < m_NumPBConstraints + 1; i++)
        {
            bbot[i] = NOMAD::PB;
        }

        for (int i = m_NumPBConstraints + 1; i < m_NumPBConstraints + m_NumEBConstraints + 1; i++)
        {
            bbot[i] = NOMAD::EB;
        }

        params->set_BB_OUTPUT_TYPE(bbot);

        for (int i = 0; i < m_NumVars; i++)
		{
            if (m_ParamaterTypeIsGivenVec[i])
            {
                if (m_ParamaterTypeVec[i] == "CATEGORICAL")
                {
                    params->set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::CATEGORICAL);
                }
                else if (m_ParamaterTypeVec[i] == "INTEGER")
                {
                    params->set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::INTEGER);
                }
                else if (m_ParamaterTypeVec[i] == "CONTINUOUS")
                {
                    params->set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::CONTINUOUS);
                }
                else if (m_ParamaterTypeVec[i] == "BINARY")
                {
					params->set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::BINARY);
				}
                else
                {
                    throw std::invalid_argument("Invalid parameter type");
                }
			}
		}

        //    p.set_DISPLAY_ALL_EVAL(true);   // displays all evaluations.
        params->set_DISPLAY_STATS("bbe ( sol ) obj");


        NOMAD::Point x0(m_NumVars);
        NOMAD::Point lb(m_NumVars);
        NOMAD::Point ub(m_NumVars);

        for (int i = 0; i < m_NumVars; i++)
        {
            x0[i] = m_InitialVarsVec[i];

            if (m_LowerBoundIsGivenVec[i])
            {
                lb[i] = m_LowerBoundValueVec[i];
            }

            if (m_UpperBoundIsGivenVec[i])
            {
                ub[i] = m_UpperBoundValueVec[i];
            }
        }

        params->set_X0(x0);
        params->set_LOWER_BOUND(lb);
        params->set_UPPER_BOUND(ub);

        params->set_MAX_BB_EVAL(m_NumIterations);
        params->set_DISPLAY_DEGREE(2);
        if (m_OutputPath)
        {
            params->set_SOLUTION_FILE(m_OutputPath);
        }

        // parameters validation:
        params->check();

        // custom evaluator creation:
        NomadSingleObjEvaluator* evaluatorPtr = new NomadSingleObjEvaluator(*params, m_SingleObjEvaluator, this);

        // algorithm creation and execution:
        NOMAD::Mads* mads = new NOMAD::Mads(*params, evaluatorPtr);
        mads->run();

        for (int i = 0; i < m_NumVars; i++) 
        {
            m_FinalVariables[i] = mads->get_best_feasible()->value(i);
        }


    }
    catch (exception& e)
    {
		std::cerr << "\nNOMAD has been interrupted (" << e.what() << ")\n\n";
	}

    NOMAD::Slave::stop_slaves(*out);
    NOMAD::end();
}

void NomadCore::OptimizeMultiObj( void )
{
    if (m_NumVars <= 0)
    {
        throw std::exception("Number of variables must be greater than 0.");
    }

    if (m_NumObjFunctions <= 1)
	{
		throw std::exception("Number of objective functions must be greater than 1.");
	}

    NOMAD::Display* out = new NOMAD::Display(std::cout);

    try
    {
        out->precision(NOMAD::DISPLAY_PRECISION_STD);

        NOMAD::begin(0, NULL);

        NOMAD::Parameters* params = new NOMAD::Parameters(*out);
        params->set_DIMENSION(m_NumVars);

        vector<NOMAD::bb_output_type> bbot;
        bbot.resize(m_NumPBConstraints + m_NumEBConstraints + m_NumObjFunctions);

        for (int i = 0; i < m_NumObjFunctions; i++)
        {
            bbot[i] = NOMAD::OBJ;
        }

        for (int i = m_NumObjFunctions; i < m_NumPBConstraints + m_NumObjFunctions; i++)
        {
            bbot[i] = NOMAD::PB;
        }

        for (int i = m_NumPBConstraints + m_NumObjFunctions; i < m_NumPBConstraints + m_NumEBConstraints + m_NumObjFunctions; i++)
        {
            bbot[i] = NOMAD::EB;
        }

        params->set_BB_OUTPUT_TYPE(bbot);

        for (int i = 0; i < m_NumVars; i++)
        {
            if (m_ParamaterTypeIsGivenVec[i])
            {
                if (m_ParamaterTypeVec[i] == "CATEGORICAL")
                {
                    params->set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::CATEGORICAL);
                }
                else if (m_ParamaterTypeVec[i] == "INTEGER")
                {
                    params->set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::INTEGER);
                }
                else if (m_ParamaterTypeVec[i] == "CONTINUOUS")
                {
                    params->set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::CONTINUOUS);
                }
                else if (m_ParamaterTypeVec[i] == "BINARY")
                {
                    params->set_BB_INPUT_TYPE(i, NOMAD::bb_input_type::BINARY);
                }
                else
                {
                    throw std::invalid_argument("Invalid parameter type");
                }
            }
        }

        //    p.set_DISPLAY_ALL_EVAL(true);   // displays all evaluations.
        params->set_DISPLAY_STATS("bbe ( sol ) obj");


        NOMAD::Point x0(m_NumVars);
        NOMAD::Point lb(m_NumVars);
        NOMAD::Point ub(m_NumVars);

        for (int i = 0; i < m_NumVars; i++)
        {
            x0[i] = m_InitialVarsVec[i];

            if (m_LowerBoundIsGivenVec[i])
            {
                lb[i] = m_LowerBoundValueVec[i];
            }

            if (m_UpperBoundIsGivenVec[i])
            {
                ub[i] = m_UpperBoundValueVec[i];
            }
        }

        params->set_X0(x0);
        params->set_LOWER_BOUND(lb);
        params->set_UPPER_BOUND(ub);

        params->set_MULTI_OVERALL_BB_EVAL(m_NumIterations);
        params->set_DISPLAY_DEGREE(2);
        if (m_OutputPath)
        {
            params->set_SOLUTION_FILE(m_OutputPath);
        }

        // parameters validation:
        params->check();

        // custom evaluator creation:
        NomadMultiObjEvaluator* evaluatorPtr = new NomadMultiObjEvaluator(*params, m_MultiObjEvaluator, this);

        // algorithm creation and execution:
        NOMAD::Mads* mads = new NOMAD::Mads(*params, evaluatorPtr);
        mads->multi_run();

        for (int i = 0; i < m_NumVars; i++)
        {
            m_FinalVariables[i] = mads->get_best_feasible()->value(i);
        }


    }
    catch (exception& e)
    {
        std::cerr << "\nNOMAD has been interrupted (" << e.what() << ")\n\n";
    }

    NOMAD::Slave::stop_slaves(*out);
    NOMAD::end();
}

std::vector<double> NomadCore::GetResults( void )
{
    return m_FinalVariables;
}