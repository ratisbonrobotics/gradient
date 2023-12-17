#ifndef MEAN_SQUARED_ERROR_H
#define MEAN_SQUARED_ERROR_H

#include "value.h"

typedef value mean_squared_error;

mean_squared_error MSE(unsigned int size, value *outputs, value *targets);
void freeMSE(mean_squared_error mse);

#endif // MEAN_SQUARED_ERROR_H