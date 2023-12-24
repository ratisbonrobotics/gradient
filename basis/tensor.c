#include "tensor.h"

struct tensor_
{
    double ***data;
    unsigned int x;
    unsigned int y;
    unsigned int z;
};

tensor Tensor(unsigned int x, unsigned int y, unsigned int z)
{
    tensor t = malloc(sizeof(struct tensor_));
    t->x = x;
    t->y = y;
    t->z = z;
    t->data = malloc(x * sizeof(double **));
    for (unsigned int i = 0; i < x; i++)
    {
        t->data[i] = malloc(y * sizeof(double *));
        for (unsigned int j = 0; j < y; j++)
        {
            t->data[i][j] = malloc(z * sizeof(double));
            for (unsigned int k = 0; k < z; k++)
            {
                t->data[i][j][k] = 0.0;
            }
        }
    }
    return t;
}

unsigned int getX(tensor t)
{
    return t->x;
}

unsigned int getY(tensor t)
{
    return t->y;
}

unsigned int getZ(tensor t)
{
    return t->z;
}

tensor copyTensor(tensor t)
{
    tensor c = Tensor(t->x, t->y, t->z);
    for (unsigned int i = 0; i < t->x; i++)
    {
        for (unsigned int j = 0; j < t->y; j++)
        {
            for (unsigned int k = 0; k < t->z; k++)
            {
                c->data[i][j][k] = t->data[i][j][k];
            }
        }
    }
    return c;
}

void setDataTensor(tensor t, unsigned int x, unsigned int y, unsigned int z, double data)
{
    t->data[x][y][z] = data;
}

void fillData(tensor t, double data)
{
    for (unsigned int i = 0; i < t->x; i++)
    {
        for (unsigned int j = 0; j < t->y; j++)
        {
            for (unsigned int k = 0; k < t->z; k++)
            {
                t->data[i][j][k] = data;
            }
        }
    }
}

double getDataTensor(tensor t, unsigned int x, unsigned int y, unsigned int z)
{
    return t->data[x][y][z];
}

void addTensor(tensor t, tensor a, tensor b)
{
    assert(t->x == a->x && t->y == a->y && t->z == a->z);
    assert(t->x == b->x && t->y == b->y && t->z == b->z);
    for (unsigned int i = 0; i < t->x; i++)
    {
        for (unsigned int j = 0; j < t->y; j++)
        {
            for (unsigned int k = 0; k < t->z; k++)
            {
                t->data[i][j][k] = a->data[i][j][k] + b->data[i][j][k];
            }
        }
    }
}

void subTensor(tensor t, tensor a, tensor b)
{
    assert(t->x == a->x && t->y == a->y && t->z == a->z);
    assert(t->x == b->x && t->y == b->y && t->z == b->z);
    for (unsigned int i = 0; i < t->x; i++)
    {
        for (unsigned int j = 0; j < t->y; j++)
        {
            for (unsigned int k = 0; k < t->z; k++)
            {
                t->data[i][j][k] = a->data[i][j][k] - b->data[i][j][k];
            }
        }
    }
}

void multTensor(tensor t, tensor a, tensor b)
{
    assert(t->x == a->x && t->x == b->x);
    assert(a->z == b->y);
    assert(t->y == a->y && t->z == b->z);
    for (unsigned int i = 0; i < t->x; i++) // Batch dimension
    {
        for (unsigned int j = 0; j < t->y; j++) // Rows in the result
        {
            for (unsigned int k = 0; k < t->z; k++) // Columns in the result
            {
                t->data[i][j][k] = 0;                   // Initialize to zero
                for (unsigned int l = 0; l < a->z; l++) // Sum over this dimension
                {
                    t->data[i][j][k] += a->data[i][j][l] * b->data[i][l][k];
                }
            }
        }
    }
}

void hadamardTensor(tensor t, tensor a, tensor b)
{
    assert(t->x == a->x && t->y == a->y && t->z == a->z);
    assert(t->x == b->x && t->y == b->y && t->z == b->z);
    for (unsigned int i = 0; i < t->x; i++)
    {
        for (unsigned int j = 0; j < t->y; j++)
        {
            for (unsigned int k = 0; k < t->z; k++)
            {
                t->data[i][j][k] = a->data[i][j][k] * b->data[i][j][k];
            }
        }
    }
}

void applyTensor(tensor t, scalar_operation op)
{
    for (unsigned int i = 0; i < t->x; i++)
    {
        for (unsigned int j = 0; j < t->y; j++)
        {
            for (unsigned int k = 0; k < t->z; k++)
            {
                t->data[i][j][k] = op(t->data[i][j][k]);
            }
        }
    }
}

void freeTensor(tensor t)
{
    for (unsigned int i = 0; i < t->x; i++)
    {
        for (unsigned int j = 0; j < t->y; j++)
        {
            free(t->data[i][j]);
        }
        free(t->data[i]);
    }
    free(t->data);
    free(t);
}
