using System;
using System.Runtime.InteropServices;

namespace NomadInterop
{
    public class NomadCore
    {
        private const string dllpath = "C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadInterop\\x64\\Debug\\NomadInteropCpp.dll";
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void EvaluateDelegate(IntPtr x, int m_NumVars);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate double GetSingleObjFunctionDelegate();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GetMultiObjFunctionDelegate(IntPtr objFunctions);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate bool GetObjectiveFunctionStatusDelegate();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GetConstraintsDelegate(IntPtr constraints);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SingleObjInitDelegate(int numConstraints);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void MultiObjInitDelegate(int numConstraints, int numObjFunctions);

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
        private static extern void SetSingleObjEvaluator(IntPtr nomadCore, IntPtr evaluator, IntPtr getObjectiveFunction, IntPtr getConstraints, IntPtr init, IntPtr getObjectiveFunctionStatus);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        private static extern void SetMultiObjEvaluator(IntPtr nomadCore, IntPtr evaluator, IntPtr getObjectiveFunction, IntPtr getConstraints, IntPtr init, IntPtr getObjectiveFunctionStatus);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void OptimizeSingleObj(IntPtr nomadCore);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void OptimizeMultiObj(IntPtr nomadCore);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberObjFunctions(IntPtr nomadCore, int numObjFunctions);

        [DllImport(dllpath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr GetResults(IntPtr nomadCore, ref int size);

        public static void SetSingleObjEvaluator(IntPtr nomadCore, ISingleObjEvaluator evaluator)
        {
            EvaluateDelegate evalDelegate = new EvaluateDelegate(evaluator.Evaluate);
            GetSingleObjFunctionDelegate getObjFuncDelegate = new GetSingleObjFunctionDelegate(evaluator.GetObjectiveFunction);
            GetObjectiveFunctionStatusDelegate getObjectiveFunctionStatusDelegate = new GetObjectiveFunctionStatusDelegate(evaluator.GetObjectiveFunctionStatus);
            GetConstraintsDelegate getConstraintsDelegate = new GetConstraintsDelegate(evaluator.GetConstraints);
            SingleObjInitDelegate initDelegate = new SingleObjInitDelegate(evaluator.Initialize);

            IntPtr evalPtr = Marshal.GetFunctionPointerForDelegate(evalDelegate);
            IntPtr getObjFuncPtr = Marshal.GetFunctionPointerForDelegate(getObjFuncDelegate);
            IntPtr getObjectiveFunctionStatusPtr = Marshal.GetFunctionPointerForDelegate(getObjectiveFunctionStatusDelegate);
            IntPtr getConstraintsPtr = Marshal.GetFunctionPointerForDelegate(getConstraintsDelegate);
            IntPtr initPtr = Marshal.GetFunctionPointerForDelegate(initDelegate);

            SetSingleObjEvaluator(nomadCore, evalPtr, getObjFuncPtr, getConstraintsPtr, initPtr, getObjectiveFunctionStatusPtr);
        }

        public static void SetMultiObjEvaluator(IntPtr nomadCore, IMultiObjEvaluator evaluator)
        {
            EvaluateDelegate evalDelegate = new EvaluateDelegate(evaluator.Evaluate);
            GetMultiObjFunctionDelegate getObjFuncDelegate = new GetMultiObjFunctionDelegate(evaluator.GetObjectiveFunction);
            GetObjectiveFunctionStatusDelegate getObjectiveFunctionStatusDelegate = new GetObjectiveFunctionStatusDelegate(evaluator.GetObjectiveFunctionStatus);
            GetConstraintsDelegate getConstraintsDelegate = new GetConstraintsDelegate(evaluator.GetConstraints);
            MultiObjInitDelegate initDelegate = new MultiObjInitDelegate(evaluator.Initialize);

            IntPtr evalPtr = Marshal.GetFunctionPointerForDelegate(evalDelegate);
            IntPtr getObjFuncPtr = Marshal.GetFunctionPointerForDelegate(getObjFuncDelegate);
            IntPtr getObjectiveFunctionStatusPtr = Marshal.GetFunctionPointerForDelegate(getObjectiveFunctionStatusDelegate);
            IntPtr getConstraintsPtr = Marshal.GetFunctionPointerForDelegate(getConstraintsDelegate);
            IntPtr initPtr = Marshal.GetFunctionPointerForDelegate(initDelegate);

            SetMultiObjEvaluator(nomadCore, evalPtr, getObjFuncPtr, getConstraintsPtr, initPtr, getObjectiveFunctionStatusPtr);
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
