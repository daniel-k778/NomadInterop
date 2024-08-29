using System;
using System.Runtime.InteropServices;
using System.Runtime.Versioning;

namespace NomadInteropCS
{
    /// <summary>
    /// Provides methods for interacting with the NOMAD Core library via P/Invoke.
    /// This class defines delegates and imports functions from the NOMAD Core DLL.
    /// It also includes methods for setting evaluators and retrieving results.
    /// </summary>
    public abstract class NomadCore
    {
        /// <summary>
        /// Delegate for the Evaluate function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        protected delegate void EvaluateDelegate(nint x, int numVars);

        /// <summary>
        /// Delegate for the GetSingleObjFunction function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        protected delegate double GetSingleObjFunctionDelegate();

        /// <summary>
        /// Delegate for the GetMultiObjFunction function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        protected delegate void GetMultiObjFunctionDelegate(nint objFunctions);
         
        /// <summary>
        /// Delegate for the GetObjectiveFunctionStatus function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        protected delegate bool GetObjectiveFunctionStatusDelegate();

        /// <summary>
        /// Delegate for the GetConstraints function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        protected delegate void GetConstraintsDelegate(nint constraints);

        /// <summary>
        /// Delegate for the SingleObjInit function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        protected delegate void SingleObjInitDelegate(int numConstraints);

        /// <summary>
        /// Delegate for the MultiObjInit function in the NOMAD Core DLL.
        /// </summary>
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        protected delegate void MultiObjInitDelegate(int numConstraints, int numObjFunctions);

        /// <summary>
        /// Creates an instance of the NOMAD Core object.
        /// </summary>
        /// <returns>A pointer to the created NOMAD Core instance.</returns>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern nint CreateNomadCore();

        /// <summary>
        /// Deletes an instance of the NOMAD Core object.
        /// </summary>
        /// <param name="nomadCore">A pointer to the created NOMAD Core instance.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void DestroyNomadCore(nint nomadCore);

        /// <summary>
        /// Sets the output path for the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="path">The output path as a string.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetOutputPath(nint nomadCore, string path);

        /// <summary>
        /// Sets the number of variables in the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="numVars">Number of variables.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetNumberVariables(nint nomadCore, int numVars);

        /// <summary>
        /// Sets the initial value of a specific variable.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="index">Index of the variable.</param>
        /// <param name="value">Initial value of the variable.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetInitialVariableValue(nint nomadCore, int index, double value);

        /// <summary>
        /// Sets the upper bound of a specific variable.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="index">Index of the variable.</param>
        /// <param name="value">Upper bound of the variable.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetVariableUpperBound(nint nomadCore, int index, double value);

        /// <summary>
        /// Sets the lower bound of a specific variable.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="index">Index of the variable.</param>
        /// <param name="value">Lower bound of the variable.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetVariableLowerBound(nint nomadCore, int index, double value);

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
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetVariableType(nint nomadCore, int index, string type);

        /// <summary>
        /// Sets the number of iterations for optimization.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="numIterations">Number of iterations.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetNumberOfIterations(nint nomadCore, int numIterations);

        /// <summary>
        /// Sets the number of extreme barrier constraints.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="numEBConstraints">Number of extreme barrier constraints.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetNumberEBConstraints(nint nomadCore, int numEBConstraints);

        /// <summary>
        /// Sets the number of progressive barrier constraints.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="numPBConstraints">Number of progressive barrier constraints.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetNumberPBConstraints(nint nomadCore, int numPBConstraints);

        /// <summary>
        /// Optimizes the problem using the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void Optimize(nint nomadCore);

        /// <summary>
        /// Sets the number of objective functions for the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="numObjFunctions">Number of objective functions.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetNumberObjFunctions(nint nomadCore, int numObjFunctions);

        /// <summary>
        /// Sets the single-objective evaluator for the NOMAD Core instance.
        /// </summary>
        /// <param name="nomadCore">Pointer to the NOMAD Core instance.</param>
        /// <param name="evaluator">Function pointer to evaluator delegate.</param>
        /// <param name="getObjectiveFunction">Function pointer to the getobjectivefunction delegate.</param>
        /// <param name="getConstraints">Function pointer to getConstraints delegate.</param>
        /// <param name="getObjectiveFunctionStatus">Function pointer to getobjectivefunctionstatus delegate.</param>
        /// <param name="init">Function pointer to initialize delegate.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetSingleObjEvaluator(nint nomadCore, nint evaluator, nint getObjectiveFunction, nint getConstraints, nint init, nint getObjectiveFunctionStatus);

        /// <summary>
        /// Sets the multi-objective evaluator for the NOMAD Core instance.
        /// <param name="nomadCore"/>Pointer to the NOMAD Core instance.</param>
        /// <param name="evaluator">Function pointer to evaluator delegate.</param>
        /// <param name="getConstraints">Function pointer to getConstraints delegate.</param>
        /// <param name="getObjectiveFunction">Function pointer to the getobjectivefunction delegate.</param>
        /// <param name="getObjectiveFunctionStatus">Function pointer to getobjectivefunctionstatus delegate.</param>
        /// <param name="init">Function pointer to initialize delegate.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern void SetMultiObjEvaluator(nint nomadCore, nint evaluator, nint getObjectiveFunction, nint getConstraints, nint init, nint getObjectiveFunctionStatus);

        /// <summary>
        /// Gets the results from the NOMAD Core instance.
        /// <param name="nomadCore"/>Pointer to the NOMAD Core instance.</param>"
        /// <param name="size">Size of the results array.</param>
        [DllImport("nomadlibx64cpp.dll", CallingConvention = CallingConvention.Cdecl)]
        protected static extern nint GetResults(nint nomadCore, ref int size);
    }
}
