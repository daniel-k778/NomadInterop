using NomadInterop;
using System.Runtime.InteropServices;
using System.Transactions;


namespace csExample
{
    class Program
    {
        static void Main()
        {
            IntPtr nomadCore = NomadCore.CreateNomadCore();

            NomadCore.SetNumberVariables(nomadCore, 5);
            for (int i = 0; i < 3; i++)
            {
                
                //NomadCore.SetVariableUpperBound(nomadCore, i, 20.0);
                NomadCore.SetVariableType(nomadCore, i, "CONTINUOUS");
            }

            NomadCore.SetNumberOfIterations(nomadCore, 500);

            NomadCore.SetNumberEBConstraints(nomadCore, 2);
            NomadCore.SetNumberPBConstraints(nomadCore, 3);

            myEvaluator myEval = new myEvaluator();

            //NomadCore.SetSingleObjEvaluator(nomadCore, myEval);
            //NomadCore.OptimizeSingleObj(nomadCore);

            NomadCore.SetNumberObjFunctions(nomadCore, 2);
            NomadCore.SetMultiObjEvaluator(nomadCore, myEval);
            NomadCore.OptimizeMultiObj(nomadCore);

            double[] results = NomadCore.GetResults(nomadCore);

            foreach (double r in results)
            {
                Console.WriteLine(r);
            }

        }
    }

    public class myEvaluator : IMultiObjEvaluator
    {
        private double[] obj;
        private double[] constraints;

        private bool objStatus;

        public void Initialize(int numConstraints, int numObjFunctions)
        {
            constraints = new double[numConstraints];
            obj = new double[numObjFunctions];
        }

        public void Evaluate(IntPtr x, int m_NumVars)
        {
            double[] xArray = new double[m_NumVars];
            Marshal.Copy(x, xArray, 0, m_NumVars);

            double c1 = 0.0, c2 = 0.0;
            for (int i = 0; i < m_NumVars; i++)
            {
                c1 += Math.Pow((xArray[i] - 1.0), 2);
                c2 += Math.Pow((xArray[i] + 1), 2);
            }

            obj[0] = xArray[4];
            obj[1] = c1 - 25;
            constraints[0] = 25 - c2;

            objStatus = true;
        }

        public void GetObjectiveFunction(IntPtr objFunctionsPtr)
        {
            if (objFunctionsPtr != IntPtr.Zero)
            {
                Marshal.Copy(obj, 0, objFunctionsPtr, obj.Length);
            }
        }

        public bool GetObjectiveFunctionStatus()
        {
            return objStatus;
        }

        public void GetConstraints(IntPtr constraintsPtr)
        {
            if (constraintsPtr != IntPtr.Zero)
            {
                Marshal.Copy(constraints, 0, constraintsPtr, constraints.Length);
            }
        }
    }

    public class myEvaluator2 : ISingleObjEvaluator
    {
        private double obj = 0;
        private double[] constraints;

        private bool objStatus;

        public myEvaluator2()
        {

        }

        public void Initialize(int numConstraints)
        {
            constraints = new double[numConstraints];
            obj = 0.0;
        }

        public void Evaluate(IntPtr x, int m_NumVars)
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

            objStatus = true;
        }

        public double GetObjectiveFunction()
        {
            return obj;
        }

        public bool GetObjectiveFunctionStatus()
        {
            return objStatus;
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
