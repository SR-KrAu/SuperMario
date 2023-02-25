#pragma once

const int VECTOR_INIT_CAPACITY = 10;

class vector {
public:
    bool (*append)(class vector* pVec, void* data);
    void* (*get)(class vector* pVec, int index);
    void (*clear)(class vector* pVec);
    void (*remove)(class vector* pVec, int index);
    void** pData;
    int size;
    int capacity;
};

void vectorInit(class vector*);
void vectorDestroy(class vector* pVec);