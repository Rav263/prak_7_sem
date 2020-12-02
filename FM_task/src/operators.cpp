#include "operators.hpp"


std::shared_ptr<TFunction> operator+(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) {
    std::vector<std::shared_ptr<TFunction>> functions;
    functions.push_back(a->copy());
    functions.push_back(b->copy());

    return std::make_shared<CompFunction>(functions, "+");
}

std::shared_ptr<TFunction> operator-(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) {
    std::vector<std::shared_ptr<TFunction>> functions;
    functions.push_back(a->copy());
    functions.push_back(b->copy());

    return std::make_shared<CompFunction>(functions, "-");
}

std::shared_ptr<TFunction> operator*(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) {
    std::vector<std::shared_ptr<TFunction>> functions;
    functions.push_back(a->copy());
    functions.push_back(b->copy());

    return std::make_shared<CompFunction>(functions, "*");
}

std::shared_ptr<TFunction> operator/(std::shared_ptr<TFunction> a, std::shared_ptr<TFunction> b) {
    std::vector<std::shared_ptr<TFunction>> functions;
    functions.push_back(a->copy());
    functions.push_back(b->copy());

    return std::make_shared<CompFunction>(functions, "/");
}
