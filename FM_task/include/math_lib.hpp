#ifndef MATH_LIB_HPP
#define MATH_LIB_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <memory>

class TFunction {
public:
    virtual double operator()(double x) = 0;
    virtual std::string ToString() = 0;
    virtual std::shared_ptr<TFunction> copy() = 0;
};

class CompFunction : public TFunction{
    std::vector<std::shared_ptr<TFunction>> functions;
    std::string operator_name;
public:
    CompFunction(std::vector<std::shared_ptr<TFunction>> functions, std::string name);
    double GetDeriv(int iterations);
    double operator()(double x);
    std::string ToString();
    std::shared_ptr<TFunction> copy();
};

// Constant coef * x;
class Constant : public TFunction {
    double coef;
public:
    Constant(const std::vector<double> &coefs);
    double operator()(double x);
    std::string ToString();
    std::shared_ptr<TFunction> copy();
};

// Identical a*x + b;
class Identical : public TFunction {
    double a;
    double b;
public:
    Identical(const std::vector<double> &coefs);
    double operator()(double x);
    std::string ToString();
    std::shared_ptr<TFunction> copy();
};

// Power x^a;
class Power : public TFunction {
    double a;
public:
    Power(const std::vector<double> &coefs);
    double operator()(double x);
    std::string ToString();
    std::shared_ptr<TFunction> copy();
};

// Exponent a^x
class Exponent : public TFunction {
    double a;
public:
    Exponent(const std::vector<double> &coefs);
    double operator()(double x);
    std::string ToString();
    std::shared_ptr<TFunction> copy();
};

//Polynomial a0*x^n + a1*x^n-1 + ... an
class Polynomial : public TFunction {
    std::vector<double> coefs;
public:
    Polynomial(const std::vector<double> &coefs);
    double operator()(double x);
    std::string ToString();
    std::shared_ptr<TFunction> copy();
};

#endif // MATH_LIB_HPP
