#ifndef SIGMOIDACTIVATIONFUNCTION_H
#define SIGMOIDACTIVATIONFUNCTION_H

#include "network/activationFunctions/activationfunction.h"

class SigmoidActivationFunction : public ActivationFunction
{
public:
    SigmoidActivationFunction();
    virtual double getValue(double x) override;
};

#endif // SIGMOIDACTIVATIONFUNCTION_H
