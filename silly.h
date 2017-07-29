#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  unsigned sign :1;
  unsigned before :31;
  unsigned after :32;
} silly;

silly silly_zeros();

silly silly_add(silly, silly);
silly silly_sub(silly, silly);
silly silly_mul(silly, silly);

//silly silly_from_8(float8_t);
//silly silly_from_16(float16_t);
//silly silly_from_32(float32_t);
//silly silly_from_64(float64_t);
//
//float64_t silly_to_64(silly);

char* silly_to_string(silly);
