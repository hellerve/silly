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

  uint64_t t0 = (x.before * y.after);
  uint64_t t1 = (y.before * x.after);
  z.before = x.before * y.before + (t0>>32) + (t1>>32);
  uint32_t t0b = t0&0xffffffff;
  uint32_t t1b = t1&0xffffffff;
  uint32_t tsum = t0b + t1b;
  if (tsum < t0b || tsum < t1b) z.before++;
  z.after = x.after * y.after + tsum;

  if (z.after < tsum) z.before++;

  return z;
}

char* silly_to_string(silly s) {
  char* res = malloc(23);

  snprintf(res, 23, "%s%010d.%010d", s.sign? "-" : "+", s.before, s.after);

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
