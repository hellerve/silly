#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
  unsigned sign :1;
  unsigned before :31;
  unsigned after :32;
} silly;

silly silly_zeros();
silly make_silly(short, int, int);

silly silly_add(silly, silly);
silly silly_sub(silly, silly);
silly silly_mul(silly, silly);

//silly silly_from_32(float);
//silly silly_from_64(double);
double silly_to_double(silly);

char* silly_to_string(silly);
