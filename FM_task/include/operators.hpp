#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include "math_lib.hpp"
#include <type_traits>


std::shared_ptr<TFunction> operator+(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);

template<class Fun>
std::shared_ptr<TFunction> operator+(std::shared_ptr<TFunction> a, Fun &b) {
    throw std::logic_error("OPERATOR +: bad operands");
}

template<class Fun>
std::shared_ptr<TFunction> operator+(Fun &a, std::shared_ptr<TFunction> b) {
    throw std::logic_error("OPERATOR +: bad operands");
}



std::shared_ptr<TFunction> operator-(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);

template<class Fun>
std::shared_ptr<TFunction> operator-(std::shared_ptr<TFunction> a, Fun &b) {
    throw std::logic_error("OPERATOR +: bad operands");
}

template<class Fun>
std::shared_ptr<TFunction> operator-(Fun &a, std::shared_ptr<TFunction> b) {
    throw std::logic_error("OPERATOR +: bad operands");
}




std::shared_ptr<TFunction> operator*(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);

template<class Fun>
std::shared_ptr<TFunction> operator*(std::shared_ptr<TFunction> a, Fun &b) {
    throw std::logic_error("OPERATOR +: bad operands");
}

template<class Fun>
std::shared_ptr<TFunction> operator*(Fun &a, std::shared_ptr<TFunction> b) {
    throw std::logic_error("OPERATOR +: bad operands");
}




std::shared_ptr<TFunction> operator/(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b);

template<class Fun>
std::shared_ptr<TFunction> operator/(std::shared_ptr<TFunction> a, Fun &b) {
    throw std::logic_error("OPERATOR +: bad operands");
}

template<class Fun>
std::shared_ptr<TFunction> operator/(Fun &a, std::shared_ptr<TFunction> b) {
    throw std::logic_error("OPERATOR +: bad operands");
}
#endif // OPERATORS_HPP
