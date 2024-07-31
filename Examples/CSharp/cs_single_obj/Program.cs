using NomadInteropCS;
using System.Runtime.InteropServices;
using System.Transactions;


namespace cs_single_obj
{
    /*----------------------------------------*/
    /*           evaluator creation           */
    /*----------------------------------------*/
    public class myEvaluator : ISingleObjEvaluator
    {
        private double obj = 0; // Objective function
        private double[] constraints; // Array of constraints
        private bool objStatus; // Objective function status (success/failure)

        private double[] xVals = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 }; // x values from excel
        private double[] yVals = { 11.3, 12.12912391, 12.6141303, 12.95824781, 13.22516609,
                    13.44325421, 13.62764508, 13.78737172, 13.9282606, 14.05429,
                    14.16829746, 14.27237811, 14.36812304 }; // y values from excel

        public void Initialize(int numConstraints)
        {
            // Required method for implementing the ISingleObjEvaluator interface.
            // Initializes the arrays for constraints and objective functions.

            objStatus = false;
            constraints = new double[numConstraints];
            obj = 0.0;
        }

        public void Evaluate(IntPtr x, int numVars)
        {
            // Required method for implementing the IMultiObjEvaluator interface.
            // Evaluates the objective functions and constraints

            double[] xArray = new double[numVars];
            Marshal.Copy(x, xArray, 0, numVars);

            obj = 0.0;

            for (int i = 0; i < xVals.Length; i++)
            {
                // Model the equation and solve for the error
                // y = a * log10(x^b) + c
                // obj += |y - (a * log10(x^b) + c)|

                obj += Math.Abs(yVals[i] - (xArray[0] * Math.Log10(Math.Pow(xVals[i], xArray[1])) + xArray[2]));
            }

            objStatus = true; // Set the status of the objective function (success)
        }

        public double GetObjectiveFunction()
        {
            // Required method for implementing the ISingleObjEvaluator interface.
            // Returns the objective function value

            return obj;
        }

        public bool GetObjectiveFunctionStatus()
        {
            // Required method for implementing the ISingleObjEvaluator interface.
            // Returns the status of the objective function

            return objStatus;
        }

        public void GetConstraints(IntPtr constraintsPtr)
        {
            // Required method for implementing the ISingleObjEvaluator interface.
            // Copies the constraints from the array to the pointer.

            if (constraintsPtr != IntPtr.Zero)
            {
                Marshal.Copy(constraints, 0, constraintsPtr, constraints.Length);
            }
        }
    }

    /*----------------------------------------*/
    /*               main program             */
    /*----------------------------------------*/
    class Program
    {
        static void Main()
        {
            // Create a NomadCore instance
            IntPtr nomadCore = NomadCore.CreateNomadCore();

            // Set the number of variables
            int numVars = 3;
            NomadCore.SetNumberVariables(nomadCore, numVars);

            // Set the initial variable values, upper and lower bounds, and type
            for (int i = 0; i < numVars; i++)
            {
                NomadCore.SetInitialVariableValue(nomadCore, i, 15.0);
                NomadCore.SetVariableUpperBound(nomadCore, i, 20.0);
                NomadCore.SetVariableLowerBound(nomadCore, i, -50);
                NomadCore.SetVariableType(nomadCore, i, "CONTINUOUS");
            }

            // Set the number of iterations
            NomadCore.SetNumberOfIterations(nomadCore, 500);


            // Set the evaluator
            myEvaluator myEval = new myEvaluator();
            NomadCore.SetSingleObjEvaluator(nomadCore, myEval);

            // Optimize the multi-objective function
            NomadCore.OptimizeSingleObj(nomadCore);

            // Get the results
            double[] results = NomadCore.GetResults(nomadCore);

            Console.Write("Results: ");
            foreach (double r in results)
            {
                Console.Write($"{r} ");
            }

            NomadCore.DestroyNomadCore(nomadCore);
        }
    }
}
