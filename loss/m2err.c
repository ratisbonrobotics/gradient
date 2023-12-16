#include "m2err.h"
#include "value.h"

struct m2err_
{
    unsigned int size;
    value *errors;
};
