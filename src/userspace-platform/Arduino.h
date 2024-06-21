#pragma once

#ifdef USERSPACE
#include "malloc_wrapper.h"
#endif /* USERSPACE */

#define DEG_TO_RAD 0.017453292519943295769236907684886

extern void delay(int ms);

inline int map(int x, int in_min, int in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
