#include "algorithm.h"

void s21_memcpy(void* dst, void* src, size_t size) {
  if (!dst || !src || dst == src || size == 0) return;

  for (size_t i = 0; i < size; i++) Cast<char*>(dst)[i] = Cast<char*>(src)[i];
}
