#ifndef TENSOR_H
#define TENSOR_H

typedef struct tensor_ *tensor;
typedef double (*scalar_operation)(double);

tensor Tensor(unsigned int x, unsigned int y, unsigned int z);
unsigned int getX(tensor t);
unsigned int getY(tensor t);
unsigned int getZ(tensor t);
void setDataTensor(tensor t, unsigned int x, unsigned int y, unsigned int z, double data);
double getDataTensor(tensor t, unsigned int x, unsigned int y, unsigned int z);
void fillData(tensor t, double data);
void addTensor(tensor t, tensor a, tensor b);
void subTensor(tensor t, tensor a, tensor b);
void multTensor(tensor t, tensor a, tensor b);
void hadamardTensor(tensor t, tensor a, tensor b);
void applyTensor(tensor t, scalar_operation op);
void copyTensor(tensor t, tensor a);
void freeTensor(tensor t);

#endif // TENSOR_H