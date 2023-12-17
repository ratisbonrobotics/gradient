#include "mean_squared_error.h"

struct mean_squared_error_
{
    unsigned int size;
    value *target;
    value *output;
};

mean_squared_error MSE(unsigned int size, value *targets, value *outputs) {}