#include "w_NomadCore.h"

extern "C" {

    class EvaluatorWrapper : public BaseEvaluator {
    public:
        EvaluateDelegate evaluate;
        GetObjectiveFunctionDelegate getObjectiveFunction;
        GetConstraintsDelegate getConstraints;

        double m_obj = 0.0;
        std::vector<double> m_constraints;

        void Evaluate(double* x, int m_NumVars, int numConstraints) override {
            evaluate(x, m_NumVars, numConstraints);
            m_obj = getObjectiveFunction();
            m_constraints.resize(numConstraints);
            getConstraints(m_constraints.data());
        }

        double GetObjectiveFunction() override {
            return m_obj;
        }

        std::vector<double> GetConstraints() override {
            return m_constraints;
        }
    };

    NomadCore* CreateNomadCore() {
        return new NomadCore();
    }

    void SetOutputPath(NomadCore* nomadCore, const char* path) {
        nomadCore->SetOutputPath(path);
    }

    void SetNumberVariables(NomadCore* nomadCore, int numVars) {
        nomadCore->SetNumberVariables(numVars);
    }

    void SetInitialVariable(NomadCore* nomadCore, int index, double value) {
        nomadCore->SetInitialVariable(index, value);
    }

    void SetUpperBound(NomadCore* nomadCore, int index, double value) {
        nomadCore->SetUpperBound(index, value);
    }

    void SetLowerBound(NomadCore* nomadCore, int index, double value) {
        nomadCore->SetLowerBound(index, value);
    }

    void SetVariableType(NomadCore* nomadCore, int index, const char* type) {
		nomadCore->SetVariableType(index, type);
	}

    void SetNumberOfIterations(NomadCore* nomadCore, int numIterations) {
        nomadCore->SetNumberOfIterations(numIterations);
    }

    void SetNumberEBConstraints(NomadCore* nomadCore, int numEBConstraints) {
        nomadCore->SetNumberEBConstraints(numEBConstraints);
    }

    void SetNumberPBConstraints(NomadCore* nomadCore, int numPBConstraints) {
        nomadCore->SetNumberPBConstraints(numPBConstraints);
    }

    void SetEvaluator(NomadCore* nomadCore, EvaluateDelegate evaluator, GetObjectiveFunctionDelegate getObjectiveFunction, GetConstraintsDelegate getConstraints) {
        EvaluatorWrapper* wrapper = new EvaluatorWrapper();
        wrapper->evaluate = evaluator;
        wrapper->getObjectiveFunction = getObjectiveFunction;
        wrapper->getConstraints = getConstraints;
        nomadCore->SetEvaluator(wrapper);
    }

    void Optimize(NomadCore* nomadCore) {
        nomadCore->Optimize();
    }
}
