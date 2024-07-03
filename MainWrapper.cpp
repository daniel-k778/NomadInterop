#include "MainWrapper.hpp"
#include "EvaluatorWrapper.hpp"

MainWrapper::MainWrapper(int argc, char** argv)
{
    this->argc = argc;
    this->argv = argv;
}

MainWrapper::~MainWrapper()
{

}

void MainWrapper::SetVariables(std::vector<double> initialVariables)
{
    numVars = initialVariables.size();
    upperBoundIsGivenVec.resize(numVars, false);
    lowerBoundIsGivenVec.resize(numVars, false);
    upperBoundValueVec.resize(numVars, 0.0);
    lowerBoundValueVec.resize(numVars, 0.0);
    initialVars.resize(numVars, 0.0);
	initialVars = initialVariables;
}

void MainWrapper::SetUpperBounds(std::vector<double> upperBounds)
{
    for (int i = 0; i < upperBounds.size(); i++)
    {
        upperBoundIsGivenVec[i] = true;
        upperBoundValueVec[i] = upperBounds[i];
    }
}

void MainWrapper::SetLowerBounds(std::vector<double> lowerBounds)
{
	for (int i = 0; i < lowerBounds.size(); i++)
	{
		lowerBoundIsGivenVec[i] = true;
		lowerBoundValueVec[i] = lowerBounds[i];
	}
}

void MainWrapper::SetNumberOfIterations(int numIters)
{
	numIterations = numIters;
}

void MainWrapper::SetOutputTypes(vector<const char*> outputTypes)
{
    bbot.resize(outputTypes.size());

    for (int i = 0; i < bbot.size(); i++)
    {
        const char* type = outputTypes[i];

        if (type == "OBJ")
        {
            bbot[i] = NOMAD::OBJ;
        }
        else if (type == "PB")
        {
            bbot[i] = NOMAD::PB;
        }
        else if (type == "EB")
        {
            bbot[i] = NOMAD::EB;
        }
        else
        {
            throw std::invalid_argument("Invalid output type");
        }
    }
}

void MainWrapper::Optimize()
{
    // display:
    NOMAD::Display out(std::cout);
    out.precision(NOMAD::DISPLAY_PRECISION_STD);

    try {

        // NOMAD initializations:
        NOMAD::begin(argc, argv);

        // parameters creation:
        NOMAD::Parameters params(out);

        params.set_DIMENSION(numVars);             // number of variables

        params.set_BB_OUTPUT_TYPE(bbot);

        //    p.set_DISPLAY_ALL_EVAL(true);   // displays all evaluations.
        params.set_DISPLAY_STATS("bbe ( sol ) obj");


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
        params.set_X0(x0);
        params.set_LOWER_BOUND(lb);
        params.set_UPPER_BOUND(ub);


        params.set_MAX_BB_EVAL(numIterations);     // the algorithm terminates after
        // 100 black-box evaluations
        params.set_DISPLAY_DEGREE(2);
        params.set_SOLUTION_FILE("sol.txt");

        // parameters validation:
        params.check();

        // custom evaluator creation:
        My_Evaluator ev(params);

        // algorithm creation and execution:
        NOMAD::Mads mads(params, &ev);
        mads.run();
    }
    catch (exception& e) {
        std::cerr << "\nNOMAD has been interrupted (" << e.what() << ")\n\n";
    }

    NOMAD::Slave::stop_slaves(out);
    NOMAD::end();
}