
typedef struct value *value;

typedef enum
{
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE
} operation_type;

value Value(double data, operation_type op);