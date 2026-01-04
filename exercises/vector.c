#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int UINT;

typedef struct int_vector {
  UINT length;
  UINT capacity;
  int *arr;
} IntVector;

IntVector newVector(UINT capacity) {
  if (capacity == 0) {
    capacity = 1;
  }

  return (IntVector){.length = 0,
                     .capacity = capacity,
                     .arr = (int *)malloc(capacity * sizeof(int))};
}

bool vectorFree(IntVector *vector) {
  if (vector == NULL) {
    return false;
  }

  free(vector->arr);
  return true;
}

bool vectorGrow(IntVector *vector, UINT resize_factor) {
  if (vector == NULL) {
    return false;
  }

  UINT newCapacity = vector->capacity * resize_factor;
  vector->arr = realloc(vector->arr, newCapacity * sizeof(int));
  vector->capacity = newCapacity;
  return true;
}

bool vectorShrink(IntVector *vector, UINT resize_factor) {
  if (vector == NULL) {
    return false;
  }

  UINT newCapacity = vector->capacity / resize_factor;
  vector->arr = realloc(vector->arr, newCapacity * sizeof(int));
  vector->capacity = newCapacity;
  return true;
}

bool vectorPush(IntVector *vector, int val) {
  if (vector == NULL) {
    return false;
  }

  if (vector->length >= vector->capacity) {
    vectorGrow(vector, 2);
  }

  *(vector->arr + vector->length) = val;
  vector->length++;
  return true;
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

int vectorGet(IntVector *vector, UINT index) {
  if (vector == NULL || index > vector->length) {
    return 0;
  }
  return *(vector->arr + index);
}

// Delete item at index, shifting all trailing elements left
bool vectorDelete(IntVector *vector, UINT index) {
  if (vector == NULL || index >= vector->length) {
    return false;
  }

  int *targetValPtr = vector->arr + index;
  UINT rightSideLength = vector->length - (index + 1);
  memcpy(targetValPtr, targetValPtr + 1, rightSideLength * sizeof(int));
  vector->length--;
  return true;
}

bool vectorRemove(IntVector *vector, int value) {
  if (vector == NULL) {
    return false;
  }

  for (int i = 0; i < vector->length; i++) {
    int v = *(vector->arr + i);
    if (v == value) {
      *(vector->arr + i) = 0;
    }
  }

  return true;
}

int vectorIndexOf(IntVector *vector, int value) {
  if (vector == NULL) {
    return -1;
  }

  for (int i = 0; i < vector->length; i++) {
    int v = *(vector->arr + i);
    if (v == value) {
      return i;
    }
  }

  return -1;
}

bool vectorInsert(IntVector *vector, int value, UINT index) {
  if (vector == NULL) {
    return false;
  }

  if (index > vector->length) {
    if (index > vector->capacity) {
      vectorGrow(vector, ceil(index / (float)vector->capacity));
    }
    *(vector->arr + index) = value;
    vector->length = index + 1;
  } else {
    vector->length++;
    if (vector->length > vector->capacity) {
      vectorGrow(vector, 2);
    }
    memcpy(vector->arr + index + 1, vector->arr + index,
           vector->length * sizeof(int));
    *(vector->arr + index) = value;
  }

  return true;
}

bool vectorPrepend(IntVector *vector, int value) {
  return vectorInsert(vector, value, 0);
}

bool vectorPrint(IntVector *vector) {
  if (vector == NULL) {
    return false;
  }

  printf("-----\n");
  printf("Capacity: %i\n", vector->capacity);
  printf("Length: %i\n", vector->length);

  printf("Values: ");

  for (int i = 0; i < vector->length; i++) {
    printf("%i ", *(vector->arr + i));
  }

  printf("\n");
  printf("-----\n");
  return true;
}

void multipleTests() {
  IntVector vector = newVector(2);

  vectorPrint(&vector);

  vectorPush(&vector, 5);
  vectorPush(&vector, 99);
  vectorPush(&vector, 75);
  vectorPush(&vector, 1209);

  vectorPrint(&vector);

  vectorPush(&vector, 213);
  vectorPush(&vector, 43223);
  vectorPush(&vector, INT_MAX);
  vectorPush(&vector, INT_MIN);

  vectorPrint(&vector);

  vectorPush(&vector, 1);
  vectorPush(&vector, 2);

  vectorPrint(&vector);

  int atPos5 = vectorGet(&vector, 5);
  printf("Value at 5th index: %i\n", atPos5); // Should be 43223

  int popped = vectorPop(&vector);
  printf("Popped value was: %i\n", popped); // Should be 2

  vectorPrint(&vector);

  vectorDelete(&vector, 5);              // Deleted 43223
  int newAtPos5 = vectorGet(&vector, 5); // So this should now be INT_MAX
  printf("New value at 5th index: %i\n", newAtPos5); // Should be 43223

  vectorPush(&vector, 5);
  vectorPush(&vector, 5);
  vectorPush(&vector, 7);

  vectorPrint(&vector);

  vectorRemove(&vector, 5);

  vectorPrint(&vector);

  int indexOf213 = vectorIndexOf(&vector, 213);
  int indexOfIntMin = vectorIndexOf(&vector, INT_MIN);
  int indexOf999 = vectorIndexOf(&vector, 999);

  printf("Index of 213: %i\n", indexOf213);
  printf("Index of INT_MAX: %i\n", indexOfIntMin);
  printf("Index of 999: %i\n", indexOf999);
}

void testInsertOutOfBounds() {
  IntVector vector = newVector(2);

  vectorPush(&vector, 1);
  vectorPush(&vector, 2);

  vectorPrint(&vector);

  vectorInsert(&vector, 99, 99);

  vectorPrint(&vector);

  int atPos99 = vectorGet(&vector, 99);
  printf("Value at 99th index: %i\n", atPos99);
}

void testPrepend() {
  IntVector vector = newVector(5);

  vectorPush(&vector, 1);
  vectorPush(&vector, 2);
  vectorPush(&vector, 3);
  vectorPush(&vector, 4);
  vectorPush(&vector, 4);

  vectorPrint(&vector);

  vectorPrepend(&vector, 5);

  vectorPrint(&vector);
}

int main() {
  // firstTests();
  // testInsertOutOfBounds();
  testPrepend();
}
