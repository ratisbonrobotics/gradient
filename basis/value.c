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

void forward(value v)
{
    if (v->operation == NULL)
    {
        return;
    }

    double child_left_data = 0.0;
    double child_right_data = 0.0;

    if (v->child_left != NULL)
    {
        forward(v->child_left);
        child_left_data = v->child_left->data;
    }
    if (v->child_right != NULL)
    {
        forward(v->child_right);
        child_right_data = v->child_right->data;
    }

    setData(v, getForward(v->operation)(child_left_data, child_right_data));
}

static void backward_recursive(value v)
{
    if (v->child_left != NULL)
    {
        double child_right_data = 0.0;
        if (v->child_right != NULL)
        {
            child_right_data = v->child_right->data;
        }

        double child_left_new_grad = getBackward(v->operation)(v->child_left->data, child_right_data);
        child_left_new_grad *= v->grad;
        setGrad(v->child_left, v->child_left->grad + child_left_new_grad);

        backward_recursive(v->child_left);
    }

    if (v->child_right != NULL)
    {
        double child_left_data = 0.0;
        if (v->child_left != NULL)
        {
            child_left_data = v->child_left->data;
        }

        double child_right_new_grad = getBackward(v->operation)(v->child_right->data, child_left_data);
        child_right_new_grad *= v->grad;
        setGrad(v->child_right, v->child_right->grad + child_right_new_grad);

        backward_recursive(v->child_right);
    }
}

void backward(value v)
{
    setGrad(v, 1.0);
    backward_recursive(v);
}

void update(value v, double learning_rate)
{
    if (v->child_left == NULL && v->child_right == NULL)
    {
        setData(v, v->data - learning_rate * v->grad);
    }
    if (v->child_left != NULL)
    {
        update(v->child_left, learning_rate);
    }
    if (v->child_right != NULL)
    {
        update(v->child_right, learning_rate);
    }
    setGrad(v, 0.0);
}

void draw_recursive(Agraph_t *g, value v, Agnode_t *parent)
{
    if (v->operation == NULL)
    {
        return;
    }

    char op_name[128];
    snprintf(op_name, sizeof(op_name), "op_%p", (void *)v);

    Agnode_t *op = agnode(g, op_name, 1);
    agsafeset(op, "label", getSymbol(v->operation), "");
    agedge(g, op, parent, 0, 1);

    if (v->child_left != NULL)
    {
        char child_left_name[128];
        snprintf(child_left_name, sizeof(child_left_name), "child_left_%p", (void *)v->child_left);

        Agnode_t *child_left = agnode(g, child_left_name, 1);
        agsafeset(child_left, "shape", "record", "");
        char label[128];
        snprintf(label, sizeof(label), "{data %.4f | grad %.4f}", v->child_left->data, v->child_left->grad);
        agsafeset(child_left, "label", label, "");

        agedge(g, child_left, op, 0, 1);
        draw_recursive(g, v->child_left, child_left);
    }

    if (v->child_right != NULL)
    {
        char child_right_name[128];
        snprintf(child_right_name, sizeof(child_right_name), "child_right_%p", (void *)v->child_right);

        Agnode_t *child_right = agnode(g, child_right_name, 1);
        agsafeset(child_right, "shape", "record", "");
        char label[128];
        snprintf(label, sizeof(label), "{data %.4f | grad %.4f}", v->child_right->data, v->child_right->grad);
        agsafeset(child_right, "label", label, "");

        agedge(g, child_right, op, 0, 1);
        draw_recursive(g, v->child_right, child_right);
    }
}

void draw(value v, char *filename)
{
    Agraph_t *g = agopen("g", Agdirected, NULL);
    agsafeset(g, "rankdir", "LR", "");

    Agnode_t *value_node = agnode(g, "n", 1);
    agsafeset(value_node, "shape", "record", "");
    char label[128];
    snprintf(label, sizeof(label), "{data %.4f | grad %.4f}", v->data, v->grad);
    agsafeset(value_node, "label", label, "");

    draw_recursive(g, v, value_node);

    GVC_t *gvc = gvContext();
    gvLayout(gvc, g, "dot");
    char fname[128];
    snprintf(fname, sizeof(fname), "%s.svg", filename);
    gvRenderFilename(gvc, g, "svg", fname);

    gvFreeLayout(gvc, g);
    gvFreeContext(gvc);
    agclose(g);
}

void freeValue(value v)
{
    assert(v != NULL);
    free(v);
}
