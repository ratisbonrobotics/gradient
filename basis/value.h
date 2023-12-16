#ifndef VALUE_H
#define VALUE_H

typedef struct value_ *value;
typedef double (*operation)(double, double);

value Value(value child_left, value child_right, operation forward, operation backward);
void setData(value v, double data);
double getData(value v);
value getChildLeft(value v);
value getChildRight(value v);
void setGrad(value v, double grad);
double getGrad(value v);
void forward_value(value v);
void backward_value(value v);

#endif // VALUE_H