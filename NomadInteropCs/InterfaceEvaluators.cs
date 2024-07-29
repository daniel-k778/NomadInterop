using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace NomadInterop
{
    public interface ISingleObjEvaluator
    {
        void Initialize(int numConstraints);
        void Evaluate(IntPtr x, int numVars);
        double GetObjectiveFunction();

        bool GetObjectiveFunctionStatus();
        void GetConstraints(IntPtr constraintsPtr);
    }

    public interface IMultiObjEvaluator
    {
        void Initialize(int numConstraints, int numObjFunctions);
        void Evaluate(IntPtr x, int numVars);
        void GetObjectiveFunction(IntPtr objFunctionPtr);

        bool GetObjectiveFunctionStatus();
        void GetConstraints(IntPtr constraintsPtr);
    }
}

