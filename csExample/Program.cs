using NomadLibrary;
using System.Runtime.InteropServices;
using System.Transactions;


namespace csExample
{
    class Program
    {
        static void Main()
        {
            IntPtr nomadCore = NomadCore.CreateNomadCore();

            NomadCore.SetNumberVariables(nomadCore, 3);
            for (int i = 0; i < 3; i++)
            {
                
                //NomadCore.SetVariableUpperBound(nomadCore, i, 20.0);
                NomadCore.SetVariableType(nomadCore, i, "CONTINUOUS");
            }
            NomadCore.SetInitialVariableValue(nomadCore, 0, 4.0);
            NomadCore.SetInitialVariableValue(nomadCore, 1, 0.7);
            NomadCore.SetInitialVariableValue(nomadCore, 2, 11.5);

            NomadCore.SetVariableLowerBound(nomadCore, 0, 4);
            NomadCore.SetVariableUpperBound(nomadCore, 0, 6);
            NomadCore.SetVariableLowerBound(nomadCore, 1, 0.4);
            NomadCore.SetVariableUpperBound(nomadCore, 1, 1);
            NomadCore.SetVariableLowerBound(nomadCore, 2, 11);
            NomadCore.SetVariableUpperBound(nomadCore, 2, 12);



            NomadCore.SetNumberOfIterations(nomadCore, 500);

            //NomadCore.SetNumberEBConstraints(nomadCore, 2);
            //NomadCore.SetNumberPBConstraints(nomadCore, 3);

            myEvaluator2 myEval = new myEvaluator2();

            NomadCore.SetEvaluator(nomadCore, myEval);
            NomadCore.Optimize(nomadCore);

            double[] results = NomadCore.GetResults(nomadCore);

            foreach (double r in results)
            {
                Console.WriteLine(r);
            }

        }
    }

    public class myEvaluator : IUserEvaluator
    {
        private double obj;
        private double[] constraints;

        public myEvaluator()
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
            if (constraintsPtr != IntPtr.Zero)
            {
                Marshal.Copy(constraints, 0, constraintsPtr, constraints.Length);
            }
        }
    }

    public class myEvaluator2 : IUserEvaluator
    {
        private double obj = 0;
        private double[] constraints;

        public myEvaluator2()
        {
            obj = 0.0;
            constraints = new double[0]; // Assuming 2 constraints for simplicity
        }

        public void Evaluate(IntPtr x, int m_NumVars, int numConstraints)
        {
            double[] xArray = new double[m_NumVars];
            Marshal.Copy(x, xArray, 0, m_NumVars);

            double[] excelXValues = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
            double[] excelYValues = { 11.3, 12.12912391, 12.6141303, 12.95824781, 13.22516609, 
                13.44325421, 13.62764508, 13.78737172, 13.9282606, 14.05429, 
                14.16829746, 14.27237811, 14.36812304 };


            obj = 0.0;

            for (int i = 0; i < excelXValues.Length; i++)
            {
                obj += Math.Abs(excelYValues[i] - (xArray[0] * Math.Log10(Math.Pow(excelXValues[i], xArray[1])) + xArray[2]));
            }
        }

        public double GetObjectiveFunction()
        {
            return obj;
        }

        public void GetConstraints(IntPtr constraintsPtr)
        {
            if (constraintsPtr != IntPtr.Zero)
            {
                Marshal.Copy(constraints, 0, constraintsPtr, constraints.Length);
            }
        }
    }
}
