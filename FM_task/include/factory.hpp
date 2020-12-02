#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "math_lib.hpp"

class FunFactory {
    class FunImpl;
    std::shared_ptr<FunImpl> Impl;
public:
    FunFactory();
    ~FunFactory();
    std::shared_ptr<TFunction> CreateFunction(const std::string& name, const std::vector<double> &coofs) const;
    std::vector<std::string> GetAvailableFunctions() const;
};


#endif // FACTORY_HPP
