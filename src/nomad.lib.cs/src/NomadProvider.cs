using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NomadInteropCS
{
    /// <summary>
    /// Provides a container for the NomadCore delegates.
    /// </summary>
    public class NomadProvider : NomadCore
    {
        public EvaluateDelegate EvalDelegate { get; }
        public GetSingleObjFunctionDelegate GetSingleObjFuncDelegate { get; }
        public GetMultiObjFunctionDelegate GetMultiObjFuncDelegate { get; }
        public GetObjectiveFunctionStatusDelegate GetObjectiveFunctionStatusDelegate { get; }
        public GetConstraintsDelegate GetConstraintsDelegate { get; }
        public SingleObjInitDelegate InitDelegate { get; }
        public MultiObjInitDelegate MultiObjInitDelegate { get; }

        /// <summary>
        /// Constructor for single-objective optimization.
        /// </summary>
        /// <param name="evaluator">The single-objective evaluator.</param>
        public NomadProvider(ISingleObjEvaluator evaluator)
        {
            EvalDelegate = new EvaluateDelegate(evaluator.Evaluate);
            GetSingleObjFuncDelegate = new GetSingleObjFunctionDelegate(evaluator.GetObjectiveFunction);
            GetObjectiveFunctionStatusDelegate = new GetObjectiveFunctionStatusDelegate(evaluator.GetObjectiveFunctionStatus);
            GetConstraintsDelegate = new GetConstraintsDelegate(evaluator.GetConstraints);
            InitDelegate = new SingleObjInitDelegate(evaluator.Initialize);
        }

        /// <summary>
        /// Constructor for multi-objective optimization.
        /// </summary>
        /// <param name="evaluator">The multi-objective evaluator.</param>
        public NomadProvider(IMultiObjEvaluator evaluator)
        {
            EvalDelegate = new EvaluateDelegate(evaluator.Evaluate);
            GetMultiObjFuncDelegate = new GetMultiObjFunctionDelegate(evaluator.GetObjectiveFunction);
            GetObjectiveFunctionStatusDelegate = new GetObjectiveFunctionStatusDelegate(evaluator.GetObjectiveFunctionStatus);
            GetConstraintsDelegate = new GetConstraintsDelegate(evaluator.GetConstraints);
            MultiObjInitDelegate = new MultiObjInitDelegate(evaluator.Initialize);
        }
    }
}
