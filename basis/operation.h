#ifndef OPERATION_H
#define OPERATION_H

#include "tensor.h"

typedef struct operation_ *operation;
typedef void (*operation_function)(tensor, tensor, tensor);

extern struct operation_ add;
extern struct operation_ sub;
extern struct operation_ hadamard;
extern struct operation_ mult;

extern struct operation_ linear;
extern struct operation_ square;
extern struct operation_ absolute;
extern struct operation_ relu;
extern struct operation_ leaky_relu;
extern struct operation_ sigmoid;
extern struct operation_ tangent;

operation_function getForward(operation op);
operation_function getBackward(operation op);
char *getSymbol(operation op);

#endif // OPERATION_H