#include "value.h"
#include <assert.h>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdlib.h>

struct value_
{
    double data;
    double grad;
    value child_left;
    value child_right;
    operation operation;
};

value Value(value child_left, value child_right, operation op)
{
    value v = malloc(sizeof(struct value_));
    v->data = 0.0;
    v->grad = 0.0;
    v->child_left = child_left;
    v->child_right = child_right;
    v->operation = op;
    return v;
}

value getChildLeft(value v)
{
    return v->child_left;
}

value getChildRight(value v)
{
    return v->child_right;
}

void setData(value v, double data)
{
    v->data = data;
}

double getData(value v)
{
    return v->data;
}

void setGrad(value v, double grad)
{
    v->grad = grad;
}

double getGrad(value v)
{
    return v->grad;
}

operation getOperation(value v)
{
    return v->operation;
}

void forwardValue(value v)
{
    if (v->child_left == NULL && v->child_right == NULL)
    {
        return;
    }

    double child_left_data = 0.0;
    double child_right_data = 0.0;

    if (v->child_left != NULL)
    {
        forwardValue(v->child_left);
        child_left_data = v->child_left->data;
    }
    if (v->child_right != NULL)
    {
        forwardValue(v->child_right);
        child_right_data = v->child_right->data;
    }

    setData(v, getForward(v->operation)(child_left_data, child_right_data));
}

void backwardValue(value v)
{
    if (v->child_left != NULL)
    {
        setGrad(v->child_left, v->child_left->grad + getBackward(v->operation)(v->child_left->data, v->grad));
        backwardValue(v->child_left);
    }
    if (v->child_right != NULL)
    {
        setGrad(v->child_right, v->child_right->grad + getBackward(v->operation)(v->child_right->data, v->grad));
        backwardValue(v->child_right);
    }
}

void updateValue(value v, double learning_rate)
{
    if (v->child_left == NULL && v->child_right == NULL)
    {
        setData(v, v->data - learning_rate * v->grad);
    }
    if (v->child_left != NULL)
    {
        updateValue(v->child_left, learning_rate);
    }
    if (v->child_right != NULL)
    {
        updateValue(v->child_right, learning_rate);
    }
    setGrad(v, 0.0);
}

static void draw_recursive(value v, Agraph_t *g)
{
    Agnode_t *n = agnode(g, "n", 1);
    agsafeset(n, "shape", "record", "");
    agsafeset(n, "label", "{x2 | data 0.0000 | grad 0.0000}", "");

    Agnode_t *op = agnode(g, "n", 1);
    agsafeset(op, "label", getSymbol(v->operation), "");
}

void draw(value v)
{
    // Create a new graph
    Agraph_t *g = agopen("g", Agdirected, NULL);
    agsafeset(g, "rankdir", "LR", "");
    GVC_t *gvc = gvContext();
}

void freeValue(value v)
{
    assert(v != NULL);
    free(v);
}
