using System;
using System.Runtime.InteropServices;

namespace cswrapper
{
    class NomaddotNET
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void EvaluateDelegate(IntPtr x, int m_NumVars, int numConstraints);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate double GetObjectiveFunctionDelegate();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GetConstraintsDelegate(IntPtr constraints);

        // Import the CreateNomadCore function from the DLL
        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CreateNomadCore();

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetOutputPath(IntPtr nomadCore, string path);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberVariables(IntPtr nomadCore, int numVars);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetInitialVariable(IntPtr nomadCore, int index, double value);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetUpperBound(IntPtr nomadCore, int index, double value);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetLowerBound(IntPtr nomadCore, int index, double value);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetVariableType(IntPtr nomadCore, int index, string type);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberOfIterations(IntPtr nomadCore, int numIterations);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberEBConstraints(IntPtr nomadCore, int numEBConstraints);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberPBConstraints(IntPtr nomadCore, int numPBConstraints);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetEvaluator(IntPtr nomadCore, IntPtr evaluator, IntPtr getObjectiveFunction, IntPtr getConstraints);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Optimize(IntPtr nomadCore);

        static void Main()
        {
            IntPtr nomadCore = CreateNomadCore();
            //SetOutputPath(nomadCore, "sol.txt");
            SetNumberVariables(nomadCore, 5);
            for (int i = 0; i < 5; i++)
            {
                SetInitialVariable(nomadCore, i, 1.0);
                SetUpperBound(nomadCore, i, 5.0);
                SetLowerBound(nomadCore, i, -6.0);
                SetVariableType(nomadCore, i, "CONTINUOUS");
            }

            SetNumberOfIterations(nomadCore, 100);
            SetNumberEBConstraints(nomadCore, 2);
            SetNumberPBConstraints(nomadCore, 3);

            UserEvaluator userEvaluator = new UserEvaluator();

            EvaluateDelegate evalDelegate = new EvaluateDelegate(userEvaluator.Evaluate);
            GetObjectiveFunctionDelegate getObjFuncDelegate = new GetObjectiveFunctionDelegate(userEvaluator.GetObjectiveFunction);
            GetConstraintsDelegate getConstraintsDelegate = new GetConstraintsDelegate(userEvaluator.GetConstraints);

            IntPtr evalPtr = Marshal.GetFunctionPointerForDelegate(evalDelegate);
            IntPtr getObjFuncPtr = Marshal.GetFunctionPointerForDelegate(getObjFuncDelegate);
            IntPtr getConstraintsPtr = Marshal.GetFunctionPointerForDelegate(getConstraintsDelegate);

            SetEvaluator(nomadCore, evalPtr, getObjFuncPtr, getConstraintsPtr);
            Optimize(nomadCore);
        }
    }
}
