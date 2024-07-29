#ifndef BASEEVALUATOR_H
#define BASEEVALUATOR_H

#include "nomad.hpp"

class BaseSingleObjEvaluator
{
private:


public:
    BaseSingleObjEvaluator( void );

    ~BaseSingleObjEvaluator( void );

    virtual void Initialize( int numConstraints );
    virtual double GetObjectiveFunction( void );

    virtual bool GetObjectiveFunctionStatus( void );

    virtual std::vector<double> GetConstraints( void );

    virtual void Evaluate( double* x, int m_NumVars );
};

class BaseMultiObjEvaluator
{
private:

public:
    BaseMultiObjEvaluator( void );

    ~BaseMultiObjEvaluator( void );

    virtual void Initialize( int numConstraints, int numObjFunctions );

    virtual std::vector<double> GetObjectiveFunction( void );

    virtual bool GetObjectiveFunctionStatus( void );

    virtual std::vector<double> GetConstraints( void );

    virtual void Evaluate( double* x, int m_NumVars );
};

#endif // BASEEVALUATOR_H