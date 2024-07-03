#pragma once
#include "nomad.hpp"
#include <unordered_map>

class Evaluator : public NOMAD::Evaluator
{
private:

    bool eval_x(NOMAD::Eval_Point& x, const NOMAD::Double& h_max, bool& count_eval) const
    {
        NOMAD::Double c1 = 0.0, c2 = 0.0;
        for (int i = 0; i < 5; i++)
        {
            c1 += (x[i] - 1).pow2();
            c2 += (x[i] + 1).pow2();
        }
        x.set_bb_output(0, x[4]); // objective value
        x.set_bb_output(1, c1 - 25); // constraint 1
        x.set_bb_output(2, 25 - c2); // constraint 2

        count_eval = true; // count a black-box evaluation

        return true;       // the evaluation succeeded
    }

public:
    Evaluator(const NOMAD::Parameters& p) :
        NOMAD::Evaluator(p)
    {

    }

    ~Evaluator(void)
    {

    }
};