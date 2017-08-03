#include "silly.h"

silly silly_zeros() {
  silly s;
  s.sign = 0;
  s.before = 0;
  s.after = 0;
  return s;
}

silly silly_add(silly x, silly y) {
  if (x.sign ^ y.sign) {
    if (x.sign) {
      x.sign = 0;
      return silly_sub(y, x);
    }
    y.sign = 0;
    return silly_sub(x, y);
  }
  silly z = silly_zeros();

  z.sign = x.sign | y.sign;
  // Note: Overflow
  z.before = x.before + y.before;
  z.after = x.after + y.after;

  if (z.after < x.after && z.after < y.after) z.before++;
  return z;
}

silly silly_sub(silly x, silly y) {
  if (y.sign) {
    y.sign = 0;
    return silly_add(x, y);
  }

  if (x.sign) {
    x.sign = 0;
    x = silly_add(x, y);
    x.sign = 1;
    return x;
  }

  silly z = silly_zeros();

  // Note: Underflow
  z.before = x.before - y.before;

  if (z.before > x.before) {
    z.sign = 1;
    z.before = 0xffffffff - z.before + 1;
  }

  z.after = x.after - y.after;

  if (z.after > x.after) z.before--;

  return z;
}

silly silly_mul(silly x, silly y) {
  silly z = silly_zeros();

  z.sign = x.sign ^ y.sign;

  uint64_t t0 = ((uint64_t) x.before) * y.after;
  uint64_t t1 = ((uint64_t) y.before) * x.after;
  z.before = x.before * y.before + (t0>>32) + (t1>>32);
  uint32_t t0b = t0&0xffffffff;
  uint32_t t1b = t1&0xffffffff;
  uint32_t tsum = t0b + t1b;
  if (tsum < t0b || tsum < t1b) z.before++;
  z.after = x.after * y.after + tsum;

  if (z.after < tsum) z.before++;

  return z;
}

silly silly_idiv(silly x, silly y) {
  silly z;
  z.sign = x.sign ^ y.sign;

  uint64_t x0 = (((uint64_t) x.before) << 32) + x.after;
  uint64_t y0 = (((uint64_t) y.before) << 32) + y.after;
  z.before = x0 / y0;
  z.after = 0;

  return z;
}

int count_zeroes(uint64_t x) {
    int res = 0;
    while (!(x & 0xf000000000000000)) { res += 4; x <<= 4; }
    while (!(x & 0x8000000000000000)) { res += 1; x <<= 1; }
    return res;
}

silly silly_div(silly x, silly y) {
  uint64_t x0 = (((uint64_t) x.before) << 32) + x.after;
  uint64_t y0 = (((uint64_t) y.before) << 32) + y.after;

  uint64_t rem = x0;
  uint64_t div = y0;
  uint64_t quo = 0UL;
  int b = 33; // 64 / 2 + 1

  while ((div & 0xF) == 0 && b >= 4) {
      div >>= 4;
      b -= 4;
  }

  while (rem && b >= 0) {
      int s = count_zeroes(rem);
      if (s > b) s = b;

      rem <<= s;
      b -= s;

      uint64_t d = rem / div;
      rem %= div;
      quo += d << b;

      rem <<= 1;
      --b;
  }

  // rounding
  //++quo;
  uint64_t res = quo >> 1;

  return make_silly(x.sign ^ y.sign, res >> 32, res & 0xffffffff);
}

char* silly_to_string(silly s) {
  char* res = malloc(23);

  snprintf(res, 23, "%s%010d.%010llu", s.sign? "-" : "+", s.before, (uint64_t)((s.after/((double)0xffffffff))*(uint64_t)10000000000));

  return res;
}

double silly_to_double(silly s) {
  return ((double)s.before + ((double)s.after)/(double)0xffffffff) * (s.sign ? -1 : 1);
}

silly make_silly(short sign, int before, int after) {
  silly s;
  s.sign = sign;
  s.before = before;
  s.after = after;
  return s;
}

#define FROM(n) {\
  silly s;\
  s.sign = signbit(x);\
  x = fabs(x);\
  s.before = trunc(x);\
  s.after = (uint32_t)((x-(long)x)*0xffffffff);\
  return s;\
}

silly silly_from_float(float x) {
  FROM(x);
}

silly silly_from_double(double x) {
  FROM(x);
}
