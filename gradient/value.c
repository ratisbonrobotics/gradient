#include "value.h"

struct value
{
    double data;
    double grad;
    value child_left;
    value child_right;
    double (*forward)(double, double);
    double (*backward)();
};

value Value(value child_left, value child_right)
{
    value v = malloc(sizeof(struct value));
    v->child_left = child_left;
    v->child_right = child_right;
    return v;
}

void setData(value v, double data)
{
    v->data = data;
}