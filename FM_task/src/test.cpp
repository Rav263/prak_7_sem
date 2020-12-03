#include "operators.hpp"
#include "math_lib.hpp"
#include "factory.hpp"

//#include "mathlibrary.hpp"
#include <gtest/gtest.h>
#include <typeinfo>

class TestFunFactory: public ::testing::Test
{
protected:
    FunFactory fact;
	void SetUp() {}
	void TearDown() {}
};


TEST(Functions, TestConstantFunction) {
    FunFactory fact;
    auto fun_1 = fact.CreateFunction("constant", {2});
    ASSERT_EQ("2.000*x", fun_1->ToString());

    std::vector<double> test_values{1, 1.3, 0, 1000, -2};
    std::vector<double> test_results{2, 2.6, 0, 2000, -4};

    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*fun_1)(test_values[i]), 0.001);
    }

    auto fun_2 = fact.CreateFunction("constant", {0});
    ASSERT_EQ("0.000*x", fun_2->ToString());
    
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(0, (*fun_2)(test_values[i]), 0.001);
    }

    auto fun_3 = fact.CreateFunction("constant", {-2});
    ASSERT_EQ("-2.000*x", fun_3->ToString());
    test_results = {-2, -2.6, 0, -2000, 4};
    
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*fun_3)(test_values[i]), 0.001);
    }

}
TEST(Functions, TestPowerFunction) {
    FunFactory fact;
    auto fun_1 = fact.CreateFunction("power", {2});
    ASSERT_EQ("x^2.000", fun_1->ToString());

    std::vector<double> test_values{1, 1.3, 0, 100, -2};
    std::vector<double> test_results{1, 1.69, 0, 10000, 4};

    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*fun_1)(test_values[i]), 0.001);
    }

    auto fun_2 = fact.CreateFunction("power", {0});
    ASSERT_EQ("x^0.000", fun_2->ToString());
    
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(1, (*fun_2)(test_values[i]), 0.001);
    }

    auto fun_3 = fact.CreateFunction("power", {-2});
    ASSERT_EQ("x^-2.000", fun_3->ToString());
    test_values = {1, 1.3, -1, 100, -2};
    test_results = {1, 0.592, 1, 0, 0.25};
    
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*fun_3)(test_values[i]), 0.001);
    }
}

TEST(Functions, TestPolynomialFunction) {
    FunFactory fact;
    auto fun_1 = fact.CreateFunction("polynomial", {2, 1, 3, 2});
    ASSERT_EQ("2.000 + 1.000*x^1 + 3.000*x^2 + 2.000*x^3", fun_1->ToString());
    
    std::vector<double> test_values{1, 1.3, 0, -1, -2};
    std::vector<double> test_results{8, 12.764, 2, 2, -4};
    
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*fun_1)(test_values[i]), 0.001);
    }

    auto fun_2 = fact.CreateFunction("polynomial", {0, 1, -2.3});
    ASSERT_EQ("1.000*x^1 - 2.300*x^2", fun_2->ToString());
    test_results = {-1.3, -2.587, 0, -3.3, -11.2}; 

    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*fun_2)(test_values[i]), 0.001);
    }
    auto fun_3 = fact.CreateFunction("polynomial", {0, 0, 1, 0, 0, -1});
    ASSERT_EQ("1.000*x^2 - 1.000*x^5", fun_3->ToString());
}

TEST(Functions, TestIndetFunction) {
    FunFactory fact;
    auto fun_1 = fact.CreateFunction("ident", {1, 2});

    ASSERT_EQ("1.000*x + 2.000", fun_1->ToString());
    
    std::vector<double> test_values{1, 1.3, 0, -1, -2};
    std::vector<double> test_results{3, 3.3, 2, 1, 0};
    
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*fun_1)(test_values[i]), 0.001);
    }
    auto fun_2 = fact.CreateFunction("ident", {0, -2.200});

    ASSERT_EQ("-2.200", fun_2->ToString());
    
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(-2.2, (*fun_2)(test_values[i]), 0.001);
    }
}

TEST(Functions, TestExponentFunction) {
    FunFactory fact;

    auto fun_1 = fact.CreateFunction("exp", {2});
    ASSERT_EQ("2.000^x", fun_1->ToString());
    
    std::vector<double> test_values{1, 1.3, 0, -1, -2};
    std::vector<double> test_results{2, 2.462, 1, 0.5, 0.25};
    
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*fun_1)(test_values[i]), 0.001);
    }
    
    auto fun_2 = fact.CreateFunction("exp", {-2});
    
    test_values = {1, 2, 0, -3, -2};
    test_results = {-2, 4, 1, -0.125, 0.25};

    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*fun_2)(test_values[i]), 0.001);
    }
}


TEST(ArithmeticOperations, TestAddition) {
    FunFactory fact;
    std::vector<std::shared_ptr<TFunction>> functions;
    functions.push_back(fact.CreateFunction("exp", {2}));
    functions.push_back(fact.CreateFunction("constant", {1.5}));
    functions.push_back(fact.CreateFunction("power", {-2}));
    functions.push_back(fact.CreateFunction("polynomial", {1, 3.2, 2}));
    functions.push_back(fact.CreateFunction("ident", {2, -1}));

    auto add = functions[0] + functions[1];
    for (int i = 2; i < functions.size(); i++) {
        add = add + functions[i];
    }
   
    ASSERT_EQ(
            "2.000^x + 1.500*x + x^-2.000 + 1.000 + 3.200*x^1 + 2.000*x^2 + 2.000*x - 1.000",
            add->ToString());

    std::vector<double> test_values{1, 2.2, -3, -1};
    std::vector<double> test_results{11.7, 29.221, -1.864, -3.2};
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*add)(test_values[i]), 0.001);
    }
}

TEST(ArithmeticOperations, TestSubtraction){
    FunFactory fact;
    std::vector<std::shared_ptr<TFunction>> functions;
    functions.push_back(fact.CreateFunction("exp", {2}));
    functions.push_back(fact.CreateFunction("constant", {1.5}));
    functions.push_back(fact.CreateFunction("power", {-2}));
    functions.push_back(fact.CreateFunction("polynomial", {1, 3.2, 2}));
    functions.push_back(fact.CreateFunction("ident", {2, -1}));

    auto sub = functions[0] - functions[1];
    for (int i = 2; i < functions.size(); i++) {
        sub = sub - functions[i];
    }
   
    ASSERT_EQ(
            "((((2.000^x) - (1.500*x)) - (x^-2.000)) - (1.000 + 3.200*x^1 + 2.000*x^2)) - (2.000*x - 1.000)",
            sub->ToString()
    );

    std::vector<double> test_values{1, 2.2, -3, -1};
    std::vector<double> test_results{-7.7, -20.032, 2.114, 4.2};
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*sub)(test_values[i]), 0.001);
    }
}

TEST(ArithmeticOperations, TestMultiplication){
    FunFactory fact;
    std::vector<std::shared_ptr<TFunction>> functions;
    functions.push_back(fact.CreateFunction("exp", {2}));
    functions.push_back(fact.CreateFunction("constant", {1.5}));
    functions.push_back(fact.CreateFunction("power", {-2}));
    functions.push_back(fact.CreateFunction("polynomial", {1, 3.2, 2}));
    functions.push_back(fact.CreateFunction("ident", {2, -1}));

    auto mul = functions[0] * functions[1];
    for (int i = 2; i < functions.size(); i++) {
        mul = mul * functions[i];
    }
   
    ASSERT_EQ(
            "((((2.000^x) * (1.500*x)) * (x^-2.000)) * (1.000 + 3.200*x^1 + 2.000*x^2)) * (2.000*x - 1.000)",
            mul->ToString()
    );

    std::vector<double> test_values{1, 2.2, -3, -1};
    std::vector<double> test_results{18.6, 188.746, 4.113, -0.45};
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*mul)(test_values[i]), 0.001);
    }
}

TEST(ArithmeticOperations, TestDivision){
    FunFactory fact;
    std::vector<std::shared_ptr<TFunction>> functions;
    functions.push_back(fact.CreateFunction("exp", {2}));
    functions.push_back(fact.CreateFunction("constant", {1.5}));
    functions.push_back(fact.CreateFunction("power", {-2}));
    functions.push_back(fact.CreateFunction("polynomial", {1, 3.2, 2}));
    functions.push_back(fact.CreateFunction("ident", {2, -1}));

    auto divs = functions[0] / functions[1];
    for (int i = 2; i < functions.size(); i++) {
        divs = divs / functions[i];
    }
   
    ASSERT_EQ(
            "((((2.000^x) / (1.500*x)) / (x^-2.000)) / (1.000 + 3.200*x^1 + 2.000*x^2)) / (2.000*x - 1.000)",
            divs->ToString()
    );

    std::vector<double> test_values{1, 2.2, -3, -1};
    std::vector<double> test_results{0.215, 0.112, 0.004, -0.556};
    for (int i = 0; i < test_values.size(); i++) {
        ASSERT_NEAR(test_results[i], (*divs)(test_values[i]), 0.001);
    }
}

TEST(ErrorTests, TestErrors) {
    FunFactory fact;
    auto fun = fact.CreateFunction("exp", {2});
    ASSERT_THROW(fun + "wqwd", std::logic_error);
    ASSERT_THROW("wqwd" + fun, std::logic_error);
    auto some = fun + 1;
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();    
}
