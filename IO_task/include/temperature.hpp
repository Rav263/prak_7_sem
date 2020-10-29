#ifndef TEMP_HPP
#define TEMP_HPP

#include <iostream>

class Temp {
public:
    double temp;
    double init_temp;
    Temp(double init_temp) {
        this->temp = init_temp;
        this->init_temp = init_temp;
    }

    virtual void decrease_temp(uint32_t iteration) {};
};

class TempFirst : public Temp {
public:
    TempFirst(double init_temp) : Temp(init_temp) {
    }
    
    virtual void decrease_temp(uint32_t iteration);
};

class TempSecond : public Temp {
public:
    TempSecond(double init_temp) : Temp(init_temp) {
    }
    
    virtual void decrease_temp(uint32_t iteration);
};

class TempThird : public Temp {
public:
    TempThird(double init_temp) : Temp(init_temp) {
    }
    
    virtual void decrease_temp(uint32_t iteration);
};


#endif //TEMP_HPP
