#include <cmath>
#include <sstream>
#include "math_lib.hpp"


CompFunction::CompFunction(std::vector<std::shared_ptr<TFunction>> functions, std::string name) {
    this->functions = functions;
    this->operator_name = name;
}

double CompFunction::GetDeriv(int iterations) {
    return 1;
}

double CompFunction::operator()(double x) {
    std::vector<double> results;

    for (auto now : this->functions) {
        results.push_back((*now)(x));
    }

    double result = results[0];

    for (int i = 1; i < results.size(); i++) {
        auto now_res = results[i];
        if (this->operator_name == "+") {
            result += now_res;
        } else if (this->operator_name == "*") {
            result *= now_res;
        } else if (this->operator_name == "-") {
            result -= now_res;
        } else if (this->operator_name == "/") {
            result /= now_res;
        }
    }

    return result;
}

std::string CompFunction::ToString() {
    std::stringstream res_stream;

    for (int i = 0; i < this->functions.size(); i++) {
        if (this->operator_name != "+") res_stream << "(";
        res_stream << this->functions[i]->ToString();
        if (this->operator_name != "+") res_stream << ")";
        if (i != this->functions.size() - 1) res_stream << this->operator_name;
    }

    return res_stream.str();
}

std::shared_ptr<TFunction> CompFunction::copy() {
    return std::make_shared<CompFunction>(this->functions, this->operator_name);
}

// Constant class declaration
Constant::Constant(const std::vector<double> &coefs) {
    if (coefs.size() != 1) {
        throw std::logic_error("CONSTANT FUNCTION::bad coefs count");
    } else {
        this->coef = coefs[0];
    }
}

double Constant::operator()(double x) {return this->coef * x;}
std::string Constant::ToString() {return std::to_string(this->coef) + "*x";}

std::shared_ptr<TFunction> Constant::copy() {
    return std::make_shared<Constant>(std::vector<double>{this->coef});
}

// Power class declaration
Power::Power(const std::vector<double> &coefs) {
    if (coefs.size() != 1) {
        throw std::logic_error("POWER FUNCTION::bad coefs count");
    } else {
        this->a = coefs[0];
    }
}

double Power::operator()(double x) {return std::pow(x, this->a);}
std::string Power::ToString() {return "x^" + std::to_string(this->a);}

std::shared_ptr<TFunction> Power::copy() {
    return std::make_shared<Power>(std::vector<double>{this->a});
}

// Identical class declaration
Identical::Identical(const std::vector<double> &coefs) {
    if (coefs.size() != 2) {
        throw std::logic_error("IDENTICAL FUNCTION::bad coefs count");
    } else {
        this->a = coefs[0];
        this->b = coefs[1];
    }
}

double Identical::operator()(double x) {return this->a * x + this->b;}
std::string Identical::ToString() {
    return std::to_string(this->a) + " * x + " + std::to_string(this->b);
}

std::shared_ptr<TFunction> Identical::copy() {
    return std::make_shared<Identical>(std::vector<double>{this->a, this->b});
}

// Exponent class declaration
Exponent::Exponent(const std::vector<double> &coefs) {
    if (coefs.size() != 1) {
        throw std::logic_error("EXPONENT FUNCTION::bad coefs count"); 
    } else {
        this->a = coefs[0]; 
    }
}

double Exponent::operator()(double x) {return std::pow(this->a, x);}
std::string Exponent::ToString() {
    return std::to_string(this->a) + "^x";
}

std::shared_ptr<TFunction> Exponent::copy() {
    return std::make_shared<Exponent>(std::vector<double>{this->a});
}

// Polynomial class declaration
Polynomial::Polynomial(const std::vector<double> &coefs) {
    for (const auto &now : coefs) {
        this->coefs.push_back(now);
    }
}

double Polynomial::operator()(double x) {
    double result = 0;
    for (int i = 0; i < this->coefs.size(); i++) {
        result += coefs[i] * std::pow(x, i);
    }
    return result;
}
std::string Polynomial::ToString() {
    auto res_stream = std::stringstream();

    if (this->coefs.size() != 0 and coefs[0] != 0) {
        res_stream << coefs[0] << " ";
    }
    for (int i = 1; i < this->coefs.size(); i++) {
        if (coefs[i]) { res_stream << " + " << coefs[i] << " * x^" << i;}
    }

    return res_stream.str();
}

std::shared_ptr<TFunction> Polynomial::copy() {
    return std::make_shared<Polynomial>(this->coefs);
}

