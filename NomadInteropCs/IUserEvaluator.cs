using System.Runtime.InteropServices;

namespace NomadLibrary
{
    public interface IUserEvaluator
    {
        void Evaluate(IntPtr x, int numVars, int numConstraints);
        double GetObjectiveFunction();
        void GetConstraints(IntPtr constraintsPtr);
    }
}

