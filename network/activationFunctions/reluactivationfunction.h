#ifndef RELUACTIVATIONFUNCTION_H
#define RELUACTIVATIONFUNCTION_H

#include "network/activationFunctions/activationfunction.h"

class ReluActivationFunction : public ActivationFunction
{
public:
    ReluActivationFunction();
    virtual double getValue(double x) override;
};

#endif // RELUACTIVATIONFUNCTION_H
