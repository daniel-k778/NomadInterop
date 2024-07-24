#include "NomadCoreAPI.hpp"

extern "C" {

    class EvaluatorWrapper : public BaseEvaluator {
    public:
        EvaluateDelegate m_Evaluate;
        GetObjectiveFunctionDelegate m_GetObjectiveFunction;
        GetConstraintsDelegate m_GetConstraints;

        double m_Obj = 0.0;
        std::vector<double> m_Constraints;

        void Evaluate(double* x, int m_NumVars, int numConstraints) override {
            m_Evaluate(x, m_NumVars, numConstraints);
            m_Obj = m_GetObjectiveFunction();
            m_Constraints.resize(numConstraints);
            m_GetConstraints(m_Constraints.data());
        }

        double GetObjectiveFunction() override {
            return m_Obj;
        }

        std::vector<double> GetConstraints() override {
            return m_Constraints;
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

    void SetEvaluator(NomadCore* nomadCore, EvaluateDelegate evaluator, GetObjectiveFunctionDelegate m_GetObjectiveFunction, GetConstraintsDelegate m_GetConstraints) {
        EvaluatorWrapper* wrapper = new EvaluatorWrapper();
        wrapper->m_Evaluate = evaluator;
        wrapper->m_GetObjectiveFunction = m_GetObjectiveFunction;
        wrapper->m_GetConstraints = m_GetConstraints;
        nomadCore->SetEvaluator(wrapper);
    }

    void Optimize(NomadCore* nomadCore) {
        nomadCore->Optimize();
    }

    double* GetResults(NomadCore* nomadCore, int* size) {
        static std::vector<double> results = nomadCore->GetResults();
        *size = static_cast<int>(results.size());
        return results.data();
    }
}
