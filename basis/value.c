#include "value.h"
#include <assert.h>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>
#include <stdlib.h>

value all_values[1024];
unsigned int all_values_index = 0;

#define SCALE_GRADIENT(g) \
    g /= 100.0;

struct value_
{
    tensor data;
    tensor grad;
    value child_left;
    value child_right;
    operation operation;
};

value Value(unsigned int x, unsigned int y, unsigned int z, value child_left, value child_right, operation op)
{
    value v = malloc(sizeof(struct value_));
    all_values[all_values_index++] = v;
    if (all_values_index == 1024)
    {
        assert(0 && "all_values_index == 1024");
    }
    v->data = Tensor(x, y, z);
    v->grad = Tensor(x, y, z);
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

void setData(value v, tensor data)
{
    v->data = data;
}

tensor getData(value v)
{
    return v->data;
}

void setGrad(value v, tensor grad)
{
    v->grad = grad;
}

tensor getGrad(value v)
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

    tensor child_left_data = NULL;
    tensor child_right_data = NULL;

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

    getForward(v->operation)(v->data, child_left_data, child_right_data);
}

static void backward_recursive(value v)
{
    if (v->child_left != NULL)
    {
        tensor child_right_data = NULL;
        if (v->child_right != NULL)
        {
            child_right_data = v->child_right->data;
        }

        tensor temp = Tensor(getX(v->child_left->grad), getY(v->child_left->grad), getZ(v->child_left->grad));
        copyTensor(temp, v->child_left->grad);
        getBackward(v->operation)(temp, v->child_left->data, child_right_data);
        hadamardTensor(temp, temp, v->grad);
        addTensor(v->child_left->grad, v->child_left->grad, temp);
        freeTensor(temp);

        backward_recursive(v->child_left);
    }

    if (v->child_right != NULL)
    {
        tensor child_left_data = NULL;
        if (v->child_left != NULL)
        {
            child_left_data = v->child_left->data;
        }

        tensor temp = Tensor(getX(v->child_right->grad), getY(v->child_right->grad), getZ(v->child_right->grad));
        copyTensor(temp, v->child_right->grad);
        getBackward(v->operation)(temp, v->child_right->data, child_left_data);
        hadamardTensor(temp, temp, v->grad);
        addTensor(v->child_right->grad, v->child_right->grad, temp);
        freeTensor(temp);

        backward_recursive(v->child_right);
    }
}

void backward(value v)
{
    fillData(v->grad, 1.0);
    backward_recursive(v);
}

void update(value v, double learning_rate)
{
    if (v->child_left == NULL && v->child_right == NULL)
    {
        tensor temp = Tensor(getX(v->grad), getY(v->grad), getZ(v->grad));
        copyTensor(temp, v->grad);
        fillData(temp, learning_rate);
        hadamardTensor(temp, v->grad, temp);
        subTensor(v->grad, v->grad, temp);
        freeTensor(temp);
    }
    if (v->child_left != NULL)
    {
        update(v->child_left, learning_rate);
    }
    if (v->child_right != NULL)
    {
        update(v->child_right, learning_rate);
    }
    fillData(v->grad, 0.0);
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

    char edge_name[128];
    snprintf(edge_name, sizeof(edge_name), "edge_%p_%p", (void *)op, (void *)parent);
    agedge(g, op, parent, edge_name, 1);

    if (v->child_left != NULL)
    {
        char child_left_name[128];
        snprintf(child_left_name, sizeof(child_left_name), "child_left_%p", (void *)v->child_left);

        Agnode_t *child_left = agnode(g, child_left_name, 1);
        agsafeset(child_left, "shape", "record", "");
        char label[128];
        snprintf(label, sizeof(label), "{data %.4f | grad %.4f}", v->child_left->data, v->child_left->grad);
        agsafeset(child_left, "label", label, "");

        snprintf(edge_name, sizeof(edge_name), "edge_%p_%p", (void *)v->child_left, (void *)op);
        agedge(g, child_left, op, edge_name, 1);
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

        snprintf(edge_name, sizeof(edge_name), "edge_%p_%p", (void *)v->child_right, (void *)op);
        agedge(g, child_right, op, edge_name, 1);
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

void freeAllValues()
{
    for (unsigned int i = 0; i < all_values_index; i++)
    {
        free(all_values[i]);
    }
}
