using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NomadInteropCS
{ 
    /// <summary>
    /// Enum for evaluator types.
    /// </summary>
    public enum NomadEvaluatorType
    {
        SingleObjective,
        Multiobjective
    }

    /// <summary>
    /// Enum for variable types.
    /// </summary>
    public enum NomadVariableType
    {
        Continuous,
        Integer,
        Categorical,
        Binary
    }
}
