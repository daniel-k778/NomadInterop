#include "NomadCore.hpp"
#include "BaseEvaluator.hpp"

class UserEvaluator : public BaseMultiObjEvaluator
{
private:
    vector<double> m_obj;
    vector<double> m_constraints;
    bool m_objStatus = true;

    int m_NumObjFunctions = 0;
    int m_NumConstraints = 0;

public:
    UserEvaluator()
    {

    }

    ~UserEvaluator()
    {

    }

    void Initialize(int numConstraints, int numObjFunctions) {
        this->m_NumObjFunctions = numObjFunctions;
        this->m_NumConstraints = numConstraints;

        m_obj.resize(numObjFunctions);
        m_constraints.resize(numConstraints);
    }

    bool GetObjectiveFunctionStatus()
	{
		return m_objStatus;
	}

    vector<double> GetObjectiveFunction()
    {
        return m_obj;
    }

    vector<double> GetConstraints()
    {
		return m_constraints;
	}

    void Evaluate(double* x, int m_NumVars)
    {

        double c1 = 0.0, c2 = 0.0;
        for (int i = 0; i < m_NumVars; i++)
        {
            c1 += std::pow((x[i] - 1.0), 2);
            c2 += std::pow((x[i] + 1), 2);
        }

        m_obj[0] = x[4];
        m_obj[1] = c1 - 25;
        m_constraints[0] = 25 - c2;

        m_objStatus = true;
    }
};


auto main() -> int {
	NomadCore* myMainWrapper = new NomadCore();
	myMainWrapper->SetOutputPath("sol.txt");

	int m_NumVars = 5;
	myMainWrapper->SetNumberVariables(m_NumVars);
	for (int i = 0; i < m_NumVars; i++) {
		myMainWrapper->SetInitialVariableValue(i, 1.0);
        myMainWrapper->SetVariableType(i, "CONTINUOUS");
	}

	myMainWrapper->SetNumberOfIterations(100);
	myMainWrapper->SetNumberEBConstraints(2);
	myMainWrapper->SetNumberPBConstraints(3);

	UserEvaluator* myEval = new UserEvaluator();

    myMainWrapper->SetNumberObjFunctions(2);
	myMainWrapper->SetMultiObjEvaluator(myEval);
    myMainWrapper->OptimizeMultiObj();
}