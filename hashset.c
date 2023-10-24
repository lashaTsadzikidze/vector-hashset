#include "hashset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void HashSetNew(hashset *h, int elemSize, int numBuckets,
                HashSetHashFunction hashfn, HashSetCompareFunction comparefn, HashSetFreeFunction freefn)
{
    assert(elemSize > 0);
    assert(numBuckets > 0);
    assert(hashfn != NULL);
    assert(comparefn != NULL);
    h->number_buckets = numBuckets;
    h->hashFn = hashfn;
    h->compareFn = comparefn;
    h->count = 0;

    h->buckets = malloc(numBuckets * sizeof(vector));

    for (int i = 0; i < numBuckets; i++) {
        VectorNew(&h->buckets[i], elemSize, freefn, 5);
    }
}

void HashSetDispose(hashset *h) {
    for (int i = 0; i < h->number_buckets; i++) {
        VectorDispose(&h->buckets[i]);
    }
    free(h->buckets);
    h->buckets = NULL;
}

int HashSetCount(const hashset *h) {
    return h->count;
}

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void *auxData) {
    if (mapfn != NULL) {
        for (int i = 0; i < h->number_buckets; i++) {
            // mapfn(h->buckets[i], auxData);
            VectorMap(&h->buckets[i], mapfn, auxData);
        }
    }
}

void HashSetEnter(hashset *h, const void *elemAddr) {
    assert(elemAddr != NULL);

    int hash = h->hashFn(elemAddr, h->number_buckets);
    assert(hash >= 0);
    assert(hash <= h->number_buckets);

    if (VectorSearch(&h->buckets[hash], elemAddr, h->compareFn, 0, false) > -1) {
        VectorReplace(&h->buckets[hash], elemAddr,
                      VectorSearch(&h->buckets[hash], elemAddr, h->compareFn, 0, false));
    } else {
        VectorAppend(&h->buckets[hash], elemAddr);
        h->count++;
    }
}

void *HashSetLookup(const hashset *h, const void *elemAddr) {
    assert(elemAddr != NULL);

    int hash = h->hashFn(elemAddr, h->number_buckets);
    assert(hash >= 0);
    assert(hash < h->number_buckets);

    if (VectorSearch(&h->buckets[hash], elemAddr, h->compareFn, 0, false) > -1) {
        return VectorNth(&h->buckets[hash], VectorSearch(&h->buckets[hash], elemAddr, h->compareFn, 0, false));
    } else {
        return NULL;
    }
}
