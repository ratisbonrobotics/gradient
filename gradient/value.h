#ifndef VALUE_H
#define VALUE_H

typedef struct value_ *value;
value Value(value child_left, value child_right);
void setData(value v, double data);

#endif // VALUE_H