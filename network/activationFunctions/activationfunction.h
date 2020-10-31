#ifndef ACTIVATIONFUNCTION_H
#define ACTIVATIONFUNCTION_H

class ActivationFunction
{
public:
    ActivationFunction();
    virtual ~ActivationFunction();
    virtual double getValue(double x);
};
#endif // ACTIVATIONFUNCTION_H
