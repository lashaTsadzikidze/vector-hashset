#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <search.h>

void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation) {
    if (initialAllocation <= 0) initialAllocation = 5;
    v->memory_length = initialAllocation;
    v->logical_length = 0;
    v->elem_size_bytes = elemSize;
    v->freeFn = freeFn;

    v->elems_container = malloc(elemSize * initialAllocation);
    assert(v->elems_container != NULL);
}

void VectorDispose(vector *v) {
    if (v->freeFn != NULL) {
        for (int i = 0; i < v->logical_length; i++) {
            v->freeFn(VectorNth(v, i));
        }
    }
    free(v->elems_container);
    v->elems_container = NULL;
}

int VectorLength(const vector *v) {
    return v->logical_length;
}

void *VectorNth(const vector *v, int position) {
    assert(position >= 0 && position <= v->logical_length);
    return (char *)v->elems_container + v->elem_size_bytes * position;
}

void VectorReplace(vector *v, const void *elemAddr, int position) {
    assert(position >= 0);
    assert(position < v->logical_length);
    void *destination = VectorNth(v, position);
    if (v->freeFn != NULL) {
        v->freeFn(destination);
    }
    memcpy(destination, elemAddr, v->elem_size_bytes);
}

// This function added by me
void growVectorElemsContainer (vector *v) {
    if (v->logical_length == v->memory_length) {
        v->elems_container = realloc(v->elems_container, v->elem_size_bytes * (v->memory_length + 20));
        assert(v->elems_container != NULL);
        v->memory_length += 20;
    } else return;
}

void VectorInsert(vector *v, const void *elemAddr, int position) {
    assert(position >= 0);
    assert(position <= v->logical_length);

    if (v->memory_length == v->logical_length) {
        growVectorElemsContainer(v);
    }

    for (int i = v->logical_length; i > position; i--) {
        memcpy(VectorNth(v, i), VectorNth(v, i - 1), v->elem_size_bytes);
    }

    memcpy(VectorNth(v, position), elemAddr, v->elem_size_bytes);
    v->logical_length++;
}

void VectorAppend(vector *v, const void *elemAddr) {
    VectorInsert(v, elemAddr, v->logical_length);
}

void VectorDelete(vector *v, int position) {
    assert(position >= 0);
    assert(position < v->logical_length);

    if (v->freeFn != NULL) {
        v->freeFn(VectorNth(v, position));
    }
    for (int i = position; i < v->logical_length - 1; i++) {
        memcpy(VectorNth(v, i), VectorNth(v, i + 1), v->elem_size_bytes);
    }
    v->logical_length--;
}

void VectorSort(vector *v, VectorCompareFunction compare) {
    if (compare != NULL) {
        qsort(v->elems_container, v->logical_length, v->elem_size_bytes, compare);
    }
}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData) {
    if (mapFn != NULL) {
        for (int i = 0; i < v->logical_length; i++) {
            mapFn(VectorNth(v, i), auxData);
        }
    }
}

static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted) {
    assert(startIndex >= 0 && startIndex <= v->logical_length);
    assert(searchFn != NULL);
    assert(key != NULL);
    void *idx = NULL;
    if (isSorted) {
        idx = bsearch(
                key,
                VectorNth(v, startIndex),
                v->logical_length - startIndex,
                v->elem_size_bytes,
                searchFn
        );
    }
    else {
        size_t n = v->logical_length - startIndex;
        idx = lfind(key, VectorNth(v, startIndex), &n, v->elem_size_bytes, searchFn);
    }
    if (idx == NULL) return kNotFound;
    return ((char *)idx - (char *)v->elems_container) / v->elem_size_bytes;
}
