#include "mean_squared_error.h"
#include "value.h"

struct m2err_
{
    unsigned int size;
    value *errors;
};
