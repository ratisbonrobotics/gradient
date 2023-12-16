#include "softmax_cross_entropy.h"
#include "value.h"

struct softmax_cross_entropy_
{
    unsigned int size;
    value *errors;
};
