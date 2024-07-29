using System;
using System.Runtime.InteropServices;

namespace NomadLibrary
{
    public class NomadCore
    {
        private const string dllpath = "C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadInterop\\x64\\Debug\\NomadInteropCpp.dll";
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void EvaluateDelegate(IntPtr x, int m_NumVars, int numConstraints);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate double GetObjectiveFunctionDelegate();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GetConstraintsDelegate(IntPtr constraints);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CreateNomadCore();

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetOutputPath(IntPtr nomadCore, string path);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberVariables(IntPtr nomadCore, int numVars);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetInitialVariableValue(IntPtr nomadCore, int index, double value);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetVariableUpperBound(IntPtr nomadCore, int index, double value);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetVariableLowerBound(IntPtr nomadCore, int index, double value);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetVariableType(IntPtr nomadCore, int index, string type);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberOfIterations(IntPtr nomadCore, int numIterations);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberEBConstraints(IntPtr nomadCore, int numEBConstraints);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberPBConstraints(IntPtr nomadCore, int numPBConstraints);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        private static extern void SetEvaluator(IntPtr nomadCore, IntPtr evaluator, IntPtr getObjectiveFunction, IntPtr getConstraints);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Optimize(IntPtr nomadCore);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetResults(IntPtr nomadCore, ref int size);

        public static void SetEvaluator(IntPtr nomadCore, IUserEvaluator evaluator)
        {
            EvaluateDelegate evalDelegate = new EvaluateDelegate(evaluator.Evaluate);
            GetObjectiveFunctionDelegate getObjFuncDelegate = new GetObjectiveFunctionDelegate(evaluator.GetObjectiveFunction);
            GetConstraintsDelegate getConstraintsDelegate = new GetConstraintsDelegate(evaluator.GetConstraints);

            IntPtr evalPtr = Marshal.GetFunctionPointerForDelegate(evalDelegate);
            IntPtr getObjFuncPtr = Marshal.GetFunctionPointerForDelegate(getObjFuncDelegate);
            IntPtr getConstraintsPtr = Marshal.GetFunctionPointerForDelegate(getConstraintsDelegate);

            SetEvaluator(nomadCore, evalPtr, getObjFuncPtr, getConstraintsPtr);
        }

        public static double[] GetResults(IntPtr nomadCore)
        {
            int size = 0;
            IntPtr resultPtr = GetResults(nomadCore, ref size);

            double[] results = new double[size];
            Marshal.Copy(resultPtr, results, 0, size);

            return results;
        }
    }
}
