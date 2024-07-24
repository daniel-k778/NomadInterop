using System.Runtime.InteropServices;

namespace NomadLibrary
{
    public interface IUserEvaluator
    {
        void Evaluate(IntPtr x, int m_NumVars, int numConstraints);
        double GetObjectiveFunction();
        void GetConstraints(IntPtr constraintsPtr);
    }
}

