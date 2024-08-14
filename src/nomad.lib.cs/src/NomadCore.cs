using System;
using System.Runtime.InteropServices;

namespace NomadInteropCS
{
    /// <summary>
    /// Provides methods for interacting with the NOMAD Core library via P/Invoke.
    /// This class defines delegates and imports functions from the NOMAD Core DLL.
    /// It also includes methods for setting evaluators and retrieving results.
    /// </summary>
    public class NomadCore
    {
        private const string PATH = "nomadlibx64cpp.dll";

        /*--------------------------------------------------------------------------*/
        /*  Delegate declarations for function pointers used in the NOMAD Core DLL. */
        /*--------------------------------------------------------------------------*/

        /// <summary>
        /// Delegate for the Evaluate function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void EvaluateDelegate(nint x, int numVars);

        /// <summary>
        /// Delegate for the GetSingleObjFunction function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate double GetSingleObjFunctionDelegate();

        /// <summary>
        /// Delegate for the GetMultiObjFunction function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GetMultiObjFunctionDelegate(nint objFunctions);
         
        /// <summary>
        /// Delegate for the GetObjectiveFunctionStatus function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate bool GetObjectiveFunctionStatusDelegate();

        /// <summary>
        /// Delegate for the GetConstraints function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GetConstraintsDelegate(nint constraints);

        /// <summary>
        /// Delegate for the SingleObjInit function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SingleObjInitDelegate(int numConstraints);

        /// <summary>
        /// Delegate for the MultiObjInit function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void MultiObjInitDelegate(int numConstraints, int numObjFunctions);


        /*--------------------------------------------------------------------------*/
        /*             DLL Import declarations for NOMAD Core functions.            */
        /*--------------------------------------------------------------------------*/

        /// <summary>
        /// Creates an instance of the NOMAD Core object.
        /// </summary>
        /// <returns>A pointer to the created NOMAD Core instance.</returns>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern nint CreateNomadCore();

        /// <summary>
        /// Deletes an instance of the NOMAD Core object.
        /// </summary>
        /// <param name="nomadCore">A pointer to the created NOMAD Core instance.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void DestroyNomadCore(nint nomadCore);

        /// <summary>
        /// Sets the output path for the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="path">The output path as a string.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetOutputPath(nint nomadCore, string path);

        /// <summary>
        /// Sets the number of variables in the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="numVars">Number of variables.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberVariables(nint nomadCore, int numVars);

        /// <summary>
        /// Sets the initial value of a specific variable.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="index">Index of the variable.</param>
        /// <param name="value">Initial value of the variable.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetInitialVariableValue(nint nomadCore, int index, double value);

        /// <summary>
        /// Sets the upper bound of a specific variable.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="index">Index of the variable.</param>
        /// <param name="value">Upper bound of the variable.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetVariableUpperBound(nint nomadCore, int index, double value);

        /// <summary>
        /// Sets the lower bound of a specific variable.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="index">Index of the variable.</param>
        /// <param name="value">Lower bound of the variable.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetVariableLowerBound(nint nomadCore, int index, double value);

        /// <summary>
        /// Sets the type of a specific variable.
        /// - "CONTINUOUS"
        /// - "INTEGER"
        /// - "BINARY"
        /// - "CATEGORICAL"
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="index">Index of the variable.</param>
        /// <param name="type">Type of the variable (e.g., "CONTINUOUS", "INTEGER").</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetVariableType(nint nomadCore, int index, string type);

        /// <summary>
        /// Sets the number of iterations for optimization.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="numIterations">Number of iterations.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberOfIterations(nint nomadCore, int numIterations);

        /// <summary>
        /// Sets the number of extreme barrier constraints.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="numEBConstraints">Number of extreme barrier constraints.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberEBConstraints(nint nomadCore, int numEBConstraints);

        /// <summary>
        /// Sets the number of progressive barrier constraints.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="numPBConstraints">Number of progressive barrier constraints.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberPBConstraints(nint nomadCore, int numPBConstraints);

        /// <summary>
        /// Optimizes a single-objective problem using the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void OptimizeSingleObj(nint nomadCore);

        /// <summary>
        /// Optimizes a multi-objective problem using the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void OptimizeMultiObj(nint nomadCore);

        /// <summary>
        /// Sets the number of objective functions for the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="numObjFunctions">Number of objective functions.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberObjFunctions(nint nomadCore, int numObjFunctions);

        /*--------------------------------------------------------------------------*/
        /*                        Implementations for NOMAD Core                    */
        /*--------------------------------------------------------------------------*/

        /// <summary>
        /// Sets the single-objective evaluator for the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="evaluator">The evaluator implementing the `ISingleObjEvaluator` interface.</param>
        public static void SetSingleObjEvaluator(nint nomadCore, ISingleObjEvaluator evaluator)
        {
            // Create delegates for each required function pointer.
            EvaluateDelegate evalDelegate = new EvaluateDelegate(evaluator.Evaluate);
            GetSingleObjFunctionDelegate getObjFuncDelegate = new GetSingleObjFunctionDelegate(evaluator.GetObjectiveFunction);
            GetObjectiveFunctionStatusDelegate getObjectiveFunctionStatusDelegate = new GetObjectiveFunctionStatusDelegate(evaluator.GetObjectiveFunctionStatus);
            GetConstraintsDelegate getConstraintsDelegate = new GetConstraintsDelegate(evaluator.GetConstraints);
            SingleObjInitDelegate initDelegate = new SingleObjInitDelegate(evaluator.Initialize);

            // Convert delegates to function pointers and call the native function to set the evaluator.
            nint evalPtr = Marshal.GetFunctionPointerForDelegate(evalDelegate);
            nint getObjFuncPtr = Marshal.GetFunctionPointerForDelegate(getObjFuncDelegate);
            nint getObjectiveFunctionStatusPtr = Marshal.GetFunctionPointerForDelegate(getObjectiveFunctionStatusDelegate);
            nint getConstraintsPtr = Marshal.GetFunctionPointerForDelegate(getConstraintsDelegate);
            nint initPtr = Marshal.GetFunctionPointerForDelegate(initDelegate);

            SetSingleObjEvaluator(nomadCore, evalPtr, getObjFuncPtr, getConstraintsPtr, initPtr, getObjectiveFunctionStatusPtr);
        }

        /// <summary>
        /// Sets the multi-objective evaluator for the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="evaluator">The evaluator implementing the `IMultiObjEvaluator` interface.</param>
        public static void SetMultiObjEvaluator(nint nomadCore, IMultiObjEvaluator evaluator)
        {
            // Create delegates for each required function pointer.
            EvaluateDelegate evalDelegate = new EvaluateDelegate(evaluator.Evaluate);
            GetMultiObjFunctionDelegate getObjFuncDelegate = new GetMultiObjFunctionDelegate(evaluator.GetObjectiveFunction);
            GetObjectiveFunctionStatusDelegate getObjectiveFunctionStatusDelegate = new GetObjectiveFunctionStatusDelegate(evaluator.GetObjectiveFunctionStatus);
            GetConstraintsDelegate getConstraintsDelegate = new GetConstraintsDelegate(evaluator.GetConstraints);
            MultiObjInitDelegate initDelegate = new MultiObjInitDelegate(evaluator.Initialize);

            // Convert delegates to function pointers and call the native function to set the evaluator.
            nint evalPtr = Marshal.GetFunctionPointerForDelegate(evalDelegate);
            nint getObjFuncPtr = Marshal.GetFunctionPointerForDelegate(getObjFuncDelegate);
            nint getObjectiveFunctionStatusPtr = Marshal.GetFunctionPointerForDelegate(getObjectiveFunctionStatusDelegate);
            nint getConstraintsPtr = Marshal.GetFunctionPointerForDelegate(getConstraintsDelegate);
            nint initPtr = Marshal.GetFunctionPointerForDelegate(initDelegate);

            SetMultiObjEvaluator(nomadCore, evalPtr, getObjFuncPtr, getConstraintsPtr, initPtr, getObjectiveFunctionStatusPtr);
        }

        /// <summary>
        /// Retrieves the results from the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <returns>An array of double values representing the results.</returns>
        public static double[] GetResults(nint nomadCore)
        {
            // Get the size of the results array from the native function.
            int size = 0;
            nint resultPtr = GetResults(nomadCore, ref size);

            // Allocate managed array and copy results from native memory.
            double[] results = new double[size];
            Marshal.Copy(resultPtr, results, 0, size);

            return results;
        }

        /*--------------------------------------------------------------------------*/
        /*                        Constants for NOMAD Core                          */
        /*--------------------------------------------------------------------------*/

        /// <summary>
        /// Variable types supported by NOMAD Core.
        /// </summary>
        public static class VariableType
        {
            public const string Continuous = "CONTINUOUS";
            public const string Integer = "INTEGER";
            public const string Binary = "BINARY";
            public const string Categorical = "CATEGORICAL";
        }


        /*--------------------------------------------------------------------------*/
        /*    Private DLL imports for internal use. Do not expose these directly    */
        /*--------------------------------------------------------------------------*/

        /// <summary>
        /// Sets the single-objective evaluator for the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="evaluator">Function pointer to evaluator delegate.</param>
        /// <param name="getObjectiveFunction">Function pointer to the getobjectivefunction delegate.</param>
        /// <param name="getConstraints">Function pointer to getConstraints delegate.</param>
        /// <param name="getObjectiveFunctionStatus">Function pointer to getobjectivefunctionstatus delegate.</param>
        /// <param name="init">Function pointer to initialize delegate.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        private static extern void SetSingleObjEvaluator(nint nomadCore, nint evaluator, nint getObjectiveFunction, nint getConstraints, nint init, nint getObjectiveFunctionStatus);

        /// <summary>
        /// Sets the multi-objective evaluator for the NOMAD Core instance.
        /// <param name="nomadCore"/>Pointer to the NOMAD Core instance.</param>
        /// <param name="evaluator">Function pointer to evaluator delegate.</param>
        /// <param name="getConstraints">Function pointer to getConstraints delegate.</param>
        /// <param name="getObjectiveFunction">Function pointer to the getobjectivefunction delegate.</param>
        /// <param name="getObjectiveFunctionStatus">Function pointer to getobjectivefunctionstatus delegate.</param>
        /// <param name="init">Function pointer to initialize delegate.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        private static extern void SetMultiObjEvaluator(nint nomadCore, nint evaluator, nint getObjectiveFunction, nint getConstraints, nint init, nint getObjectiveFunctionStatus);

        /// <summary>
        /// Gets the results from the NOMAD Core instance.
        /// <param name="nomadCore"/>Pointer to the NOMAD Core instance.</param>"
        /// <param name="size">Size of the results array.</param>
        [DllImport(PATH, CallingConvention = CallingConvention.Cdecl)]
        private static extern nint GetResults(nint nomadCore, ref int size);
    }
}
