#include "greatest.h"
#include "../silly.h"

TEST silly_zeros_is_zero() {
  silly x = silly_zeros();

  ASSERT_EQ_FMT(0, x.sign, "%d");
  ASSERT_EQ_FMT(0, x.before, "%d");
  ASSERT_EQ_FMT(0, x.after, "%d");
  PASS();
}

TEST silly_string() {
  silly x = silly_zeros();

  ASSERT_STR_EQ("+0000000000.0000000000", silly_to_string(x));
  x.before = 1;
  ASSERT_STR_EQ("+0000000001.0000000000", silly_to_string(x));
  PASS();
}

TEST silly_addition() {
  silly x = silly_zeros();
  x.before = 1;
  x.after  = 1;
  silly y = silly_zeros();
  y.before = 1;
  y.after  = 0xffffffff;
  x = silly_add(x, y);

  ASSERT_EQ_FMT(3, x.before, "%d");
  ASSERT_EQ_FMT(0, x.after, "%d");

  y = silly_zeros();
  y.sign = 1;
  y.before = 4;
  x = silly_add(x, y);

  ASSERT_EQ_FMT(1, x.sign, "%d");
  ASSERT_EQ_FMT(1, x.before, "%d");
  ASSERT_EQ_FMT(0, x.after, "%d");

  PASS();
}

TEST silly_subtraction() {
  silly x = silly_zeros();
  x.before = 2;
  silly y = silly_zeros();
  y.before = 1;
  y.after  = 0xffffffff;
  x = silly_sub(x, y);

  ASSERT_EQ_FMT(0, x.before, "%d");
  ASSERT_EQ_FMT(1, x.after, "%d");

  x = silly_zeros();
  x.before = 2;
  y = silly_zeros();
  y.sign = 1;
  y.before = 4;
  x = silly_sub(x, y);

  ASSERT_EQ_FMT(6, x.before, "%d");
  ASSERT_EQ_FMT(0, x.after, "%d");

  PASS();
}

TEST silly_multiplication() {
  silly x = silly_zeros();
  x.sign = 1;
  x.before = 3;
  silly y = silly_zeros();
  y.before = 2;
  x = silly_mul(x, y);

  ASSERT_EQ_FMT(1, x.sign, "%d");
  ASSERT_EQ_FMT(6, x.before, "%d");
  ASSERT_EQ_FMT(0, x.after, "%d");

  x = silly_zeros();
  x.before = 3;
  x.after = 1<<31;
  y = silly_zeros();
  y.before = 2;
  x = silly_mul(x, y);

  ASSERT_EQ_FMT(7, x.before, "%d");
  ASSERT_EQ_FMT(0, x.after, "%d");

  PASS();
}

TEST silly_conversion() {
  silly x = silly_zeros();

  ASSERT_EQ_FMT(0.0, silly_to_double(x), "%f");
  x.sign = 1;
  x.before = 1;
  x.after = (int)(((double)0xffffffff)/10);
  ASSERT(-1.1 - silly_to_double(x) <= 0.01);

  x = silly_from_float(0.0);
  ASSERT_EQ_FMT(0.0, silly_to_double(x), "%f");
  x = silly_from_float(-1.1);
  ASSERT(-1.1 - silly_to_double(x) <= 0.01);

  x = silly_from_double((double) 0.0);
  ASSERT_EQ_FMT(0.0, silly_to_double(x), "%f");
  x = silly_from_double((double) -1.1);
  ASSERT(-1.1 - silly_to_double(x) <= 0.01);
  x = silly_from_double((double) -413.25);
  ASSERT(-413.25 - silly_to_double(x) <= 0.01);

  PASS();
}

TEST silly_division() {
  silly x = make_silly(0, 10, 0);
  silly y = make_silly(1, 5, 0);

  ASSERT_EQ_FMT(-2.0, silly_to_double(silly_div(x, y)), "%f");

  y = make_silly(1, 2, 5);

  ASSERT_EQ_FMT(-4.0, silly_to_double(silly_div(x, y)), "%f");

  // :(
  y = make_silly(1, 2, 3);

  ASSERT_EQ_FMT(-4.0, silly_to_double(silly_div(x, y)), "%f");

  PASS();
}

SUITE(tests) {
    RUN_TEST(silly_zeros_is_zero);
    RUN_TEST(silly_string);
    RUN_TEST(silly_addition);
    RUN_TEST(silly_subtraction);
    RUN_TEST(silly_multiplication);
    RUN_TEST(silly_division);
    RUN_TEST(silly_conversion);
}

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(tests);

    GREATEST_MAIN_END();
}
