#ifndef MEAN_SQUARED_ERROR_H
#define MEAN_SQUARED_ERROR_H

#include "value.h"

typedef struct mean_squared_error_ *mean_squared_error;

mean_squared_error MSE(unsigned int size, value *targets, value *outputs);

#endif // MEAN_SQUARED_ERROR_H