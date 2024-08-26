using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NomadInteropCS
{
    /// <summary>
    /// Provides a container for the NomadCore delegates.
    /// </summary>
    public class NomadProvider : NomadCore
    {
        private IntPtr _NomadCore { get; set; }
        public NomadProvider()
        {
            _NomadCore = NomadCore.CreateNomadCore();
            _EvaluatorSet = false;
            _NumObjFunctionsSet = false;
            _SolveCalled = false;
        }

        ~NomadProvider()
        {
            NomadCore.DestroyNomadCore(_NomadCore);
        }

        public string _OutputPath { get; private set; }
        public int _NumberVariables { get; private set; }
        public int _NumberOfIterations { get; private set; }
        public int _NumberEBConstraints { get; private set; }
        public int _NumberPBConstraints { get; private set; }
        public int _NumberObjFunctions { get; private set; }
        public NomadEvaluatorType _EvaluatorType { get; private set; }
        public bool _EvaluatorSet { get; private set; }
        public bool _NumObjFunctionsSet { get; private set; }
        public bool _SolveCalled { get; private set; }

        public void SetOutputPath(string path)
        {
            _OutputPath = path;
            NomadCore.SetOutputPath(_NomadCore, _OutputPath);
        }

        public void SetNumberVariables(int numVariables)
        {
            _NumberVariables = numVariables;
            NomadCore.SetNumberVariables(_NomadCore, _NumberVariables);
        }

        public void SetInitialVariableValue(int index, double value)
        {
            if (_NumberVariables <= 0)
            {
                throw new InvalidOperationException("Number of variables must be set before setting initial variable values.");
            }
            NomadCore.SetInitialVariableValue(_NomadCore, index, value);
        }

        public void SetVariableUpperBound(int index, double value)
        {
            if (_NumberVariables <= 0)
            {
                throw new InvalidOperationException("Number of variables must be set before setting initial variable values.");
            }
            NomadCore.SetVariableUpperBound(_NomadCore, index, value);
        }

        public void SetVariableLowerBound(int index, double value)
        {
            if (_NumberVariables <= 0)
            {
                throw new InvalidOperationException("Number of variables must be set before setting initial variable values.");
            }
            NomadCore.SetVariableLowerBound(_NomadCore, index, value);
        }

        public void SetVariableType(int index, NomadVariableType type)
        {
            if (_NumberVariables <= 0)
            {
                throw new InvalidOperationException("Number of variables must be set before setting initial variable values.");
            }
            string vType;
            switch (type)
            {
                case NomadVariableType.Continuous:
                    vType = "CONTINUOUS";
                    break;
                case NomadVariableType.Integer:
                    vType = "INTEGER";
                    break;
                case NomadVariableType.Categorical:
                    vType = "CATEGORICAL";
                    break;
                case NomadVariableType.Binary:
                    vType = "BINARY";
                    break;
                default:
                    throw new ArgumentOutOfRangeException(nameof(type), $"Unexpected NomadVariableType value: {type}");
            }

            NomadCore.SetVariableType(_NomadCore, index, vType);
        }

        public void SetNumberOfIterations(int numIterations)
        {
            _NumberOfIterations = numIterations;
            NomadCore.SetNumberOfIterations(_NomadCore, _NumberOfIterations);
        }

        public void SetNumberEBConstraints(int numEBConstraints)
        {
            _NumberEBConstraints = numEBConstraints;
            NomadCore.SetNumberEBConstraints(_NomadCore, _NumberEBConstraints);
        }

        public void SetNumberPBConstraints(int numPBConstraints)
        {
            _NumberPBConstraints = numPBConstraints;
            NomadCore.SetNumberPBConstraints(_NomadCore, _NumberPBConstraints);
        }

        public void Optimize()
        {
            if (!_EvaluatorSet)
            {
                throw new InvalidOperationException("Evaluator must be set before optimization can be performed.");
            }
            if (_EvaluatorType == NomadEvaluatorType.SingleObjective)
            {
                NomadCore.OptimizeSingleObj(_NomadCore);
            }
            else if (_EvaluatorType == NomadEvaluatorType.Multiobjective)
            {
                if (!_NumObjFunctionsSet)
                {
                    throw new InvalidOperationException("Number of objective functions must be set before optimization can be performed.");
                }
                NomadCore.OptimizeMultiObj(_NomadCore);
            }
            _SolveCalled = true;
        }

        public void SetNumberObjFunctions(int numObjFunctions)
        {
            if (!_EvaluatorSet)
            {
                throw new InvalidOperationException("Evaluator must be set before setting the number of objective functions.");
            }
            if (_EvaluatorType == NomadEvaluatorType.SingleObjective)
            {
                throw new InvalidOperationException("Single-objective optimization does not require setting the number of objective functions.");
            }
            _NumberObjFunctions = numObjFunctions;
            NomadCore.SetNumberObjFunctions(_NomadCore, _NumberObjFunctions);
            _NumObjFunctionsSet = true;
        }

        /// <summary>
        /// Retrieves the results from the NOMAD Core instance.
        /// </summary>
        /// <returns>An array of double values representing the results.</returns>
        public double[] GetResults()
        {
            if (!_SolveCalled)
            {
                throw new InvalidOperationException("Optimization must be performed before results can be retrieved.");
            }
            // Get the size of the results array from the native function.
            int size = 0;
            nint resultPtr = NomadCore.GetResults(_NomadCore, ref size);

            // Allocate managed array and copy results from native memory.
            double[] results = new double[size];
            Marshal.Copy(resultPtr, results, 0, size);

            return results;
        }

        private EvaluateDelegate _EvalDelegate { get; set; }
        private GetSingleObjFunctionDelegate _GetSingleObjFuncDelegate { get; set; }
        private GetMultiObjFunctionDelegate _GetMultiObjFuncDelegate { get; set; }
        private GetObjectiveFunctionStatusDelegate _GetObjectiveFunctionStatusDelegate { get; set; }
        private GetConstraintsDelegate _GetConstraintsDelegate { get; set; }
        private SingleObjInitDelegate _InitDelegate { get; set; }
        private MultiObjInitDelegate _MultiObjInitDelegate { get; set; }

        /// <summary>
        /// Function for setting single-objective evaluator.
        /// </summary>
        /// <param name="evaluator">The single-objective evaluator.</param>
        public void SetEvaluator(ISingleObjEvaluator evaluator)
        {
            _EvalDelegate = new EvaluateDelegate(evaluator.Evaluate);
            _GetSingleObjFuncDelegate = new GetSingleObjFunctionDelegate(evaluator.GetObjectiveFunction);
            _GetObjectiveFunctionStatusDelegate = new GetObjectiveFunctionStatusDelegate(evaluator.GetObjectiveFunctionStatus);
            _GetConstraintsDelegate = new GetConstraintsDelegate(evaluator.GetConstraints);
            _InitDelegate = new SingleObjInitDelegate(evaluator.Initialize);

            // Convert delegates to function pointers and call the native function to set the evaluator.
            nint evalPtr = Marshal.GetFunctionPointerForDelegate(_EvalDelegate);
            nint getObjFuncPtr = Marshal.GetFunctionPointerForDelegate(_GetSingleObjFuncDelegate);
            nint getObjectiveFunctionStatusPtr = Marshal.GetFunctionPointerForDelegate(_GetObjectiveFunctionStatusDelegate);
            nint getConstraintsPtr = Marshal.GetFunctionPointerForDelegate(_GetConstraintsDelegate);
            nint initPtr = Marshal.GetFunctionPointerForDelegate(_InitDelegate);

            SetSingleObjEvaluator(_NomadCore, evalPtr, getObjFuncPtr, getConstraintsPtr, initPtr, getObjectiveFunctionStatusPtr);

            _EvaluatorSet = true;
            _EvaluatorType = NomadEvaluatorType.SingleObjective;
        }

        /// <summary>
        /// Function for setting multi-objective evaluator.
        /// </summary>
        /// <param name="evaluator">The multi-objective evaluator.</param>
        public void SetEvaluator(IMultiObjEvaluator evaluator)
        {
            _EvalDelegate = new EvaluateDelegate(evaluator.Evaluate);
            _GetMultiObjFuncDelegate = new GetMultiObjFunctionDelegate(evaluator.GetObjectiveFunction);
            _GetObjectiveFunctionStatusDelegate = new GetObjectiveFunctionStatusDelegate(evaluator.GetObjectiveFunctionStatus);
            _GetConstraintsDelegate = new GetConstraintsDelegate(evaluator.GetConstraints);
            _MultiObjInitDelegate = new MultiObjInitDelegate(evaluator.Initialize);

            // Convert delegates to function pointers and call the native function to set the evaluator.
            nint evalPtr = Marshal.GetFunctionPointerForDelegate(_EvalDelegate);
            nint getObjFuncPtr = Marshal.GetFunctionPointerForDelegate(_GetMultiObjFuncDelegate);
            nint getObjectiveFunctionStatusPtr = Marshal.GetFunctionPointerForDelegate(_GetObjectiveFunctionStatusDelegate);
            nint getConstraintsPtr = Marshal.GetFunctionPointerForDelegate(_GetConstraintsDelegate);
            nint initPtr = Marshal.GetFunctionPointerForDelegate(_MultiObjInitDelegate);

            SetMultiObjEvaluator(_NomadCore, evalPtr, getObjFuncPtr, getConstraintsPtr, initPtr, getObjectiveFunctionStatusPtr);

            _EvaluatorSet = true;
            _EvaluatorType = NomadEvaluatorType.Multiobjective;
        }
    }
}
