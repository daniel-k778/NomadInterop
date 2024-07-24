using System.Runtime.InteropServices;

namespace cswrapper
{
    public class UserEvaluator
    {
        private double obj;
        private double[] constraints;

        public UserEvaluator()
        {
            obj = 0.0;
            constraints = new double[2]; // Assuming 2 constraints for simplicity
        }

        public void Evaluate(IntPtr x, int m_NumVars, int numConstraints)
        {
            double[] xArray = new double[m_NumVars];
            Marshal.Copy(x, xArray, 0, m_NumVars);

            double c1 = 0.0, c2 = 0.0;
            for (int i = 0; i < m_NumVars; i++)
            {
                c1 += Math.Pow((xArray[i] - 1.0), 2);
                c2 += Math.Pow((xArray[i] + 1), 2);
            }

            obj = xArray[4];
            constraints[0] = c1 - 25;
            constraints[1] = 25 - c2;
        }

        public double GetObjectiveFunction()
        {
            return obj;
        }

        public void GetConstraints(IntPtr constraintsPtr)
        {
            Marshal.Copy(constraints, 0, constraintsPtr, constraints.Length);
        }
    }
}

