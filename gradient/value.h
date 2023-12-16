#ifndef VALUE_H
#define VALUE_H

typedef struct value_ *value;
typedef void (*pass_function)(value);

value Value(value child_left, value child_right, pass_function forward, pass_function backward);
value setData(value v, double data);
double getData(value v);
value getChildLeft(value v);
value getChildRight(value v);
value setGrad(value v, double grad);
double getGrad(value v);

#endif // VALUE_H