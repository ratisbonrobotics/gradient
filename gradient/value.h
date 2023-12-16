#ifndef VALUE_H
#define VALUE_H

typedef struct value_ *value;
typedef double (*operation)(double, double);

value Value(value child_left, value child_right, operation forward, operation backward);
value setData(value v, double data);
double getData(value v);
value getChildLeft(value v);
value getChildRight(value v);
value setGrad(value v, double grad);
double getGrad(value v);

#endif // VALUE_H