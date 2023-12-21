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

static void draw_recursive(Agraph_t *g, value v, Agnode_t *parent)
{
    if (v->child_left == NULL && v->child_right == NULL && v->operation == NULL)
    {
        return;
    }

    Agnode_t *op = agnode(g, "op", 1);
    agsafeset(op, "label", getSymbol(v->operation), "");
    Agedge_t *e = agedge(g, op, parent, 0, 1);

    if (v->child_left != NULL)
    {
        Agnode_t *child_left = agnode(g, "child_left", 1);
        agsafeset(child_left, "shape", "record", "");
        char label[128];
        snprintf(label, sizeof(label), "{data %.4f | grad %.4f}", v->child_left->data, v->child_left->grad);
        agsafeset(child_left, "label", label, "");

        Agedge_t *e1 = agedge(g, child_left, op, 0, 1);
        draw_recursive(v->child_left, g, child_left);
    }

    if (v->child_right != NULL)
    {
        Agnode_t *child_right = agnode(g, "child_right", 1);
        agsafeset(child_right, "shape", "record", "");
        char label[128];
        snprintf(label, sizeof(label), "{data %.4f | grad %.4f}", v->child_right->data, v->child_right->grad);
        agsafeset(child_right, "label", label, "");

        Agedge_t *e1 = agedge(g, child_right, op, 0, 1);
        draw_recursive(v->child_right, g, child_right);
    }
}

void draw(value v)
{
    Agraph_t *g = agopen("g", Agdirected, NULL);
    agsafeset(g, "rankdir", "LR", "");
    GVC_t *gvc = gvContext();

    Agnode_t *value_node = agnode(g, "n", 1);
    agsafeset(value_node, "shape", "record", "");
    char label[128];
    snprintf(label, sizeof(label), "{data %.4f | grad %.4f}", v->data, v->grad);
    agsafeset(value_node, "label", label, "");

    draw_recursive(g, v, value_node);

    gvLayout(gvc, g, "dot");
    gvRenderFilename(gvc, g, "svg", "graph.svg");

    gvFreeLayout(gvc, g);
    gvFreeContext(gvc);
    agclose(g);
}

void freeValue(value v)
{
    assert(v != NULL);
    free(v);
}
