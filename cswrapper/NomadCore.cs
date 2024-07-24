using System;
using System.Runtime.InteropServices;

namespace NomadLibrary
{
    public class NomadCore
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void EvaluateDelegate(IntPtr x, int m_NumVars, int numConstraints);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate double GetObjectiveFunctionDelegate();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void GetConstraintsDelegate(IntPtr constraints);

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
        private static extern void SetEvaluator(IntPtr nomadCore, IntPtr evaluator, IntPtr getObjectiveFunction, IntPtr getConstraints);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Optimize(IntPtr nomadCore);

        [DllImport("C:\\Users\\Daniel\\OneDrive\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
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



        //static void Main()
        //{
        //    IntPtr nomadCore = CreateNomadCore();
        //    //SetOutputPath(nomadCore, "sol.txt");
        //    SetNumberVariables(nomadCore, 5);
        //    for (int i = 0; i < 5; i++)
        //    {
        //        SetInitialVariable(nomadCore, i, 1.0);
        //        SetUpperBound(nomadCore, i, 5.0);
        //        SetLowerBound(nomadCore, i, -6.0);
        //        SetVariableType(nomadCore, i, "CONTINUOUS");
        //    }

        //    SetNumberOfIterations(nomadCore, 100);
        //    SetNumberEBConstraints(nomadCore, 2);
        //    SetNumberPBConstraints(nomadCore, 3);

        //    myEvaluator userEvaluator = new myEvaluator();

        //    SetCustomEvaluator(nomadCore, userEvaluator);

        //    Optimize(nomadCore);
        //}
    }

    //public class myEvaluator : IUserEvaluator
    //{
    //    private double obj;
    //    private double[] constraints;

    //    public myEvaluator()
    //    {
    //        obj = 0.0;
    //        constraints = new double[2]; // Assuming 2 constraints for simplicity
    //    }

    //    public void Evaluate(IntPtr x, int m_NumVars, int numConstraints)
    //    {
    //        double[] xArray = new double[m_NumVars];
    //        Marshal.Copy(x, xArray, 0, m_NumVars);

    //        double c1 = 0.0, c2 = 0.0;
    //        for (int i = 0; i < m_NumVars; i++)
    //        {
    //            c1 += Math.Pow((xArray[i] - 1.0), 2);
    //            c2 += Math.Pow((xArray[i] + 1), 2);
    //        }

    //        obj = xArray[4];
    //        constraints[0] = c1 - 25;
    //        constraints[1] = 25 - c2;
    //    }

    //    public double GetObjectiveFunction()
    //    {
    //        return obj;
    //    }

    //    public void GetConstraints(IntPtr constraintsPtr)
    //    {
    //        Marshal.Copy(constraints, 0, constraintsPtr, constraints.Length);
    //    }
    //}
}
