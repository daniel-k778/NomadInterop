/**
 \file   NomadCore.hpp
 \brief  DLL exports for NOMAD core functions and class definitions (headers)
 \date   2024-07-29
 \see    NomadCore.cpp
 */

#ifndef __DEFINES_H__
#define __DEFINES_H__


/// NOMAD variable types.
#define NOMAD_VARIABLE_TYPE_CONTINUOUS      "CONTINUOUS"
#define NOMAD_VARIABLE_TYPE_INTEGER         "INTEGER"
#define NOMAD_VARIABLE_TYPE_BINARY          "BINARY"
#define NOMAD_VARIABLE_TYPE_CATEGORICAL     "CATEGORICAL"

/// Evaluator types.
enum class EvaluatorType
{
    NONE,               ///< No evaluator.
    SINGLE_OBJECTIVE,   ///< Single-objective evaluator.
    MULTI_OBJECTIVE     ///< Multi-objective evaluator.
};

/// Evaluator pointer types.
enum class EvaluatorPointerType
{
    NONE,               ///< No pointer.
    RAW,                ///< Raw pointer.
    SMART               ///< Smart pointer.
};


#endif // __DEFINES_H__