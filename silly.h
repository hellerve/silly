#include <math.h>
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
silly silly_idiv(silly, silly);
silly silly_div(silly, silly);

silly silly_from_float(float);
silly silly_from_double(double);
double silly_to_double(silly);
uint64_t silly_to_uraw(silly);
int64_t silly_to_raw(silly);

char* silly_to_string(silly);
