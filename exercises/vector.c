#include <stdlib.h>
#include <string.h>
typedef unsigned int uint;

typedef struct int_vector {
  uint length;
  uint capacity;
  int *arr;
} IntVector;

IntVector newVector(uint capacity) {
  if (capacity == 0) {
    capacity = 1;
  }

  return (IntVector){.length = 0,
                     .capacity = capacity,
                     .arr = (int *)malloc(capacity * sizeof(int))};
}

void vectorFree(IntVector *vector) {
  if (vector == NULL) {
    return;
  }

  free(vector->arr);
}

void vectorGrow(IntVector *vector, uint resize_factor) {
  if (vector == NULL) {
    return;
  }

  uint newCapacity = vector->capacity * resize_factor;
  vector->arr = realloc(vector->arr, newCapacity * sizeof(int));
  vector->capacity = newCapacity;
}

void vectorShrink(IntVector *vector, uint resize_factor) {
  if (vector == NULL) {
    return;
  }

  uint newCapacity = vector->capacity / resize_factor;
  vector->arr = realloc(vector->arr, newCapacity * sizeof(int));
  vector->capacity = newCapacity;
}

void vectorPush(IntVector *vector, int val) {
  if (vector == NULL) {
    return;
  }

  if (vector->length >= vector->capacity) {
    vectorGrow(vector, 2);
  }

  *(vector->arr + vector->length) = val;
  vector->length++;
}

int vectorPop(IntVector *vector) {
  if (vector == NULL || vector->length == 0) {
    return 0;
  }

  int *lastValPtr = vector->arr + (vector->length - 1);
  int lastVal = *(lastValPtr);
  *(lastValPtr) = 0;
  vector->length--;

  if (vector->length < vector->capacity / 4) {
    vectorShrink(vector, 2);
  }

  return lastVal;
}

int vectorGet(IntVector *vector, uint index) {
  if (vector == NULL || index > vector->length) {
    return 0;
  }
  return *(vector->arr + index);
}

// Delete item at index, shifting all trailing elements left
void vectorDelete(IntVector *vector, uint index) {
  if (vector == NULL || index >= vector->length) {
    return;
  }

  int *targetValPtr = vector->arr + index;
  uint rightSideLength = vector->length - (index + 1);
  memcpy(targetValPtr, targetValPtr + 1, rightSideLength * sizeof(int));
  vector->length--;
}

int main() {}
