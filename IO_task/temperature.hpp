#ifndef TEMP_HPP
#define TEMP_HPP

#include <iostream>

class Temp {
public:
    double temp;
    Temp(double init_temp) {
        this->temp = init_temp;
    }

    virtual void decrease_temp() {};
};

class TempFirst : public Temp {
public:
    TempFirst(double init_temp) : Temp(init_temp) {
    }
    
    virtual void decrease_temp();
};

class TempSecond : public Temp {
public:
    TempSecond(double init_temp) : Temp(init_temp) {
    }
    
    virtual void decrease_temp();
};

class TempThird : public Temp {
public:
    TempThird(double init_temp) : Temp(init_temp) {
    }
    
    virtual void decrease_temp();
};


#endif //TEMP_HPP
