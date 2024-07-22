using System;
using System.Runtime.InteropServices;

namespace dllmain
{
    class Program
    {
        // Define the structure for NomadCore
        [StructLayout(LayoutKind.Sequential)]
        public struct NomadCore { }

        // Define the structure for BaseEvaluator (if needed)
        [StructLayout(LayoutKind.Sequential)]
        public struct BaseEvaluator { }

        // Import the CreateNomadCore function from the DLL
        [DllImport("C:\\Users\\Daniel\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr CreateNomadCore();

        [DllImport("C:\\Users\\Daniel\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetOutputPath(IntPtr nomadCore, string path);

        [DllImport("C:\\Users\\Daniel\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberVariables(IntPtr nomadCore, int numVars);

        [DllImport("C:\\Users\\Daniel\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetInitialVariable(IntPtr nomadCore, int index, double value);

        [DllImport("C:\\Users\\Daniel\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetUpperBound(IntPtr nomadCore, int index, double value);

        [DllImport("C:\\Users\\Daniel\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetLowerBound(IntPtr nomadCore, int index, double value);

        [DllImport("C:\\Users\\Daniel\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberOfIterations(IntPtr nomadCore, int numIterations);

        [DllImport("C:\\Users\\Daniel\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberEBConstraints(IntPtr nomadCore, int numEBConstraints);

        [DllImport("C:\\Users\\Daniel\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetNumberPBConstraints(IntPtr nomadCore, int numPBConstraints);

        [DllImport("C:\\Users\\Daniel\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void SetEvaluator(IntPtr nomadCore, IntPtr evaluator);

        [DllImport("C:\\Users\\Daniel\\Desktop\\Nomad\\NomadOpt\\x64\\Debug\\cppwrapper.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Optimize(IntPtr nomadCore);

        static void Main()
        {
            // Create an instance of NomadCore
            IntPtr nomadCore = CreateNomadCore();

            // Set various properties of the NomadCore instance
            SetOutputPath(nomadCore, "C:\\output\\path");
            SetNumberVariables(nomadCore, 10);
            SetInitialVariable(nomadCore, 0, 1.0);
            SetUpperBound(nomadCore, 0, 5.0);
            SetLowerBound(nomadCore, 0, -5.0);
            SetNumberOfIterations(nomadCore, 100);
            SetNumberEBConstraints(nomadCore, 2);
            SetNumberPBConstraints(nomadCore, 2);

            // Assuming evaluator is an IntPtr to a BaseEvaluator object
            IntPtr evaluator = IntPtr.Zero; // Replace with actual evaluator pointer
            SetEvaluator(nomadCore, evaluator);

            // Perform optimization
            Optimize(nomadCore);

            Console.WriteLine("Optimization complete.");
        }
    }
}
