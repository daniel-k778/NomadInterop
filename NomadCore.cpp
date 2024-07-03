#include "NomadCore.hpp"
#include "Evaluator.hpp"

NomadCore::NomadCore(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;
}

NomadCore::~NomadCore()
{

}

void NomadCore::SetInitialVariable(int index, double value)
{
    if (index >= numVars || index < 0)
	{
		throw std::invalid_argument("Index out of bounds");
	}
	initialVars[index] = value;
}

void NomadCore::SetNumberVariables(int numberVariables)
{
    numVars = numberVariables;
    upperBoundIsGivenVec.resize(numVars, false);
    lowerBoundIsGivenVec.resize(numVars, false);
    upperBoundValueVec.resize(numVars, 0.0);
    lowerBoundValueVec.resize(numVars, 0.0);
    initialVars.resize(numVars, 0.0);
    m_FinalVariables.resize(numVars, 0.0);
}

void NomadCore::SetUpperBound(int index, double value)
{
    if (index >= numVars || index < 0)
    {
        throw std::invalid_argument("Index out of bounds");
    }
    upperBoundIsGivenVec[index] = true;
    upperBoundValueVec[index] = value;
}

void NomadCore::SetLowerBound(int index, double value)
{
    if (index >= numVars || index < 0)
    {
        throw std::invalid_argument("Index out of bounds");
    }
	lowerBoundIsGivenVec[index] = true;
	lowerBoundValueVec[index] = value;
}

void NomadCore::SetNumberOfIterations(int numIters)
{
	numIterations = numIters;
}

void NomadCore::SetOutputPath(const char* outputFilePath)
{
	outputPath = outputFilePath;
}

void NomadCore::SetNumberPBConstraints(int numPBConstraints)
{
	numberPBConstraints = numPBConstraints;
}

void NomadCore::SetNumberEBConstraints(int numEBConstraints)
{
	numberEBConstraints = numEBConstraints;
}

void NomadCore::Optimize()
{
    NOMAD::Display* out = new NOMAD::Display(std::cout);

    try {
        out->precision(NOMAD::DISPLAY_PRECISION_STD);

        NOMAD::begin(argc, argv);
        //NOMAD::Parameters params(out);

        NOMAD::Parameters* params = new NOMAD::Parameters(*out);
        params->set_DIMENSION(numVars);

        vector<NOMAD::bb_output_type> bbot;
        bbot.resize(numberPBConstraints + numberEBConstraints + 1);
        bbot[0] = NOMAD::OBJ; // 0 always obj

        for (int i = 1; i < numberPBConstraints + 1; i++)
        {
            bbot[i] = NOMAD::PB;
        }

        for (int i = numberPBConstraints + 1; i < numberPBConstraints + numberEBConstraints + 1; i++)
        {
            bbot[i] = NOMAD::EB;
        }

        params->set_BB_OUTPUT_TYPE(bbot);

        //    p.set_DISPLAY_ALL_EVAL(true);   // displays all evaluations.
        params->set_DISPLAY_STATS("bbe ( sol ) obj");


        NOMAD::Point x0(numVars);
        NOMAD::Point lb(numVars);
        NOMAD::Point ub(numVars);
        for (int i = 0; i < numVars; i++)
        {
            x0[i] = initialVars[i];

            if (lowerBoundIsGivenVec[i])
            {
                lb[i] = lowerBoundValueVec[i];
            }

            if (upperBoundIsGivenVec[i])
            {
                ub[i] = upperBoundValueVec[i];
            }
        }
        params->set_X0(x0);
        params->set_LOWER_BOUND(lb);
        params->set_UPPER_BOUND(ub);

        params->set_MAX_BB_EVAL(numIterations);
        params->set_DISPLAY_DEGREE(2);
        params->set_SOLUTION_FILE(outputPath);

        // parameters validation:
        params->check();

        // custom evaluator creation:
        Evaluator* evaluatorPtr = new Evaluator(*params);

        // algorithm creation and execution:
        NOMAD::Mads* mads = new NOMAD::Mads(*params, evaluatorPtr);
        mads->run();

        double vals = mads->get_best_feasible()->value(0);
    }
    catch (exception& e) {
		std::cerr << "\nNOMAD has been interrupted (" << e.what() << ")\n\n";
	}

    NOMAD::Slave::stop_slaves(*out);
    NOMAD::end();
}