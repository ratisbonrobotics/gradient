#include "value.h"

struct value_
{
    double data;
    double grad;
    value child_left;
    value child_right;
    double (*forward)(value);
    double (*backward)(value);
};

value Value(value child_left, value child_right)
{
    value v = malloc(sizeof(struct value_));
    v->child_left = child_left;
    v->child_right = child_right;
    return v;
}

void setData(value v, double data)
{
    v->data = data;
}