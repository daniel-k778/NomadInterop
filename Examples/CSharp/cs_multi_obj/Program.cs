using NomadInteropCS;
using System.Runtime.InteropServices;
using System.Transactions;


namespace cs_multi_obj
{
    /*----------------------------------------*/
    /*           evaluator creation           */
    /*----------------------------------------*/
    public class myEvaluator : IMultiObjEvaluator
    {
        private double[] objArr; // Array of objective functions
        private double[] constraints; // Array of constraints
        private bool objStatus; // Objective function status (success/failure)

        public void Initialize(int numConstraints, int numObjFunctions)
        {
            // Required method for implementing the IMultiObjEvaluator interface.
            // Initializes the arrays for constraints and objective functions.

            objStatus = false;
            constraints = new double[numConstraints];
            objArr = new double[numObjFunctions];
        }

        public void Evaluate(IntPtr x, int numVars)
        {
            // Required method for implementing the IMultiObjEvaluator interface.
            // Evaluates the objective functions and constraints

            double[] xArray = new double[numVars];
            Marshal.Copy(x, xArray, 0, numVars);

            double c1 = 0.0, c2 = 0.0;
            for (int i = 0; i < numVars; i++)
            {
                c1 += Math.Pow((xArray[i] - 1.0), 2);
                c2 += Math.Pow((xArray[i] + 1), 2);
            }

            objArr[0] = xArray[4]; // Set objective function 1
            objArr[1] = c1 - 25; // Set objective function 2
            constraints[0] = 25 - c2; // Set constraint 1

            objStatus = true; // Set the status of the objective function (success)
        }

        public void GetObjectiveFunction(IntPtr objFunctionsPtr)
        {
            // Required method for implementing the IMultiObjEvaluator interface.
            // Copies the objective functions from the array to the pointer.

            if (objFunctionsPtr != IntPtr.Zero)
            {
                Marshal.Copy(objArr, 0, objFunctionsPtr, objArr.Length);
            }
        }

        public bool GetObjectiveFunctionStatus()
        {
            // Required method for implementing the IMultiObjEvaluator interface.
            // Returns the status of the objective function.

            return objStatus;
        }

        public void GetConstraints(IntPtr constraintsPtr)
        {
            // Required method for implementing the IMultiObjEvaluator interface.
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
            int numVars = 5;
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

            // Set the number of extreme and progressive barrier constraints
            NomadCore.SetNumberEBConstraints(nomadCore, 2);
            NomadCore.SetNumberPBConstraints(nomadCore, 3);

            // Set the number of objective functions
            NomadCore.SetNumberObjFunctions(nomadCore, 2);

            // Set the evaluator
            myEvaluator myEval = new myEvaluator();
            NomadCore.SetMultiObjEvaluator(nomadCore, myEval);

            // Optimize the multi-objective function
            NomadCore.OptimizeMultiObj(nomadCore);

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
