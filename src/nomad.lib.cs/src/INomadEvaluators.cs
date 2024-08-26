using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace NomadInteropCS
{
    /// <summary>
    /// Interface for a single-objective evaluator used by the NOMAD Core library.
    /// This interface defines methods for initializing, evaluating, and retrieving
    /// objective functions and constraints.
    /// </summary>
    public interface ISingleObjEvaluator
    {
        /// <summary>
        /// Initializes the single-objective evaluator with the given number of constraints.
        /// </summary>
        /// <param name="numConstraints">The number of constraints to initialize.</param>
        void Initialize(int numConstraints);

        /// <summary>
        /// Evaluates the objective function using the provided variable values.
        /// </summary>
        /// <param name="x">Pointer to an array of variable values.</param>
        /// <param name="numVars">The number of variables to evaluate.</param>
        void Evaluate(nint x, int numVars);

        /// <summary>
        /// Retrieves the value of the objective function.
        /// </summary>
        /// <returns>The current value of the objective function.</returns>
        double GetObjectiveFunction();

        /// <summary>
        /// Checks if the objective function is available or valid.
        /// </summary>
        /// <returns>True if the objective function is valid, false otherwise.</returns>
        bool GetObjectiveFunctionStatus();

        /// <summary>
        /// Retrieves the constraints and stores them in the provided pointer.
        /// </summary>
        /// <param name="constraintsPtr">Pointer to an array where constraints will be stored.</param>
        void GetConstraints(nint constraintsPtr);
    }

    /// <summary>
    /// Interface for a multi-objective evaluator used by the NOMAD Core library.
    /// This interface defines methods for initializing, evaluating, and retrieving
    /// objective functions and constraints for multiple objectives.
    /// </summary>
    public interface IMultiObjEvaluator
    {
        /// <summary>
        /// Initializes the multi-objective evaluator with the given number of constraints
        /// and objective functions.
        /// </summary>
        /// <param name="numConstraints">The number of constraints to initialize.</param>
        /// <param name="numObjFunctions">The number of objective functions to initialize.</param>
        void Initialize(int numConstraints, int numObjFunctions);

        /// <summary>
        /// Evaluates the objective functions using the provided variable values.
        /// </summary>
        /// <param name="x">Pointer to an array of variable values.</param>
        /// <param name="numVars">The number of variables to evaluate.</param>
        void Evaluate(nint x, int numVars);

        /// <summary>
        /// Retrieves the values of the objective functions and stores them in the provided pointer.
        /// </summary>
        /// <param name="objFunctionPtr">Pointer to an array where objective function values will be stored.</param>
        void GetObjectiveFunction(nint objFunctionPtr);

        /// <summary>
        /// Checks if the objective functions are available or valid.
        /// </summary>
        /// <returns>True if the objective functions are valid, false otherwise.</returns>
        bool GetObjectiveFunctionStatus();

        /// <summary>
        /// Retrieves the constraints and stores them in the provided pointer.
        /// </summary>
        /// <param name="constraintsPtr">Pointer to an array where constraints will be stored.</param>
        void GetConstraints(nint constraintsPtr);
    }
}