//#include "NomadCore.hpp"
//#include "BaseEvaluator.hpp"
//
//class UserEvaluator : public BaseEvaluator
//{
//private:
//    double m_obj = 0.0;
//    vector<double> m_constraints;
//public:
//    UserEvaluator()
//    {
//
//    }
//
//    ~UserEvaluator()
//    {
//
//    }
//
//    double GetObjectiveFunction()
//    {
//        return m_obj;
//    }
//
//    vector<double> GetConstraints()
//    {
//		return m_constraints;
//	}
//
//    void Evaluate(double* x, int m_NumVars, int numConstraints)
//    {
//        double c1 = 0.0, c2 = 0.0;
//        for (int i = 0; i < m_NumVars; i++)
//        {
//            c1 += std::pow((x[i] - 1.0), 2);
//            c2 += std::pow((x[i] + 1), 2);
//        }
//        m_obj = x[4];
//
//        m_constraints.resize(numConstraints);
//        m_constraints[0] = c1 - 25;
//        m_constraints[1] = 25 - c2;
//    }
//};
//
//
//auto main() -> int {
//	NomadCore* myMainWrapper = new NomadCore();
//	myMainWrapper->SetOutputPath("sol.txt");
//
//	int m_NumVars = 5;
//	myMainWrapper->SetNumberVariables(m_NumVars);
//	for (int i = 0; i < m_NumVars; i++) {
//		myMainWrapper->SetInitialVariable(i, 1.0);
//		myMainWrapper->SetUpperBound(i, 5.0);
//		myMainWrapper->SetLowerBound(i, -6.0);
//        myMainWrapper->SetVariableType(i, "CONTINUOUS");
//	}
//
//	myMainWrapper->SetNumberOfIterations(100);
//	myMainWrapper->SetNumberEBConstraints(2);
//	myMainWrapper->SetNumberPBConstraints(3);
//
//	UserEvaluator* myEval = new UserEvaluator();
//
//	myMainWrapper->SetEvaluator(myEval);
//    myMainWrapper->Optimize();
//}