#ifndef danya_DECIMAL_H
#define danya_DECIMAL_H

typedef struct {
  unsigned int bits[4];
} danya_decimal;

int danya_is_less(danya_decimal a, danya_decimal b);
int danya_is_greater(danya_decimal a, danya_decimal b);
int danya_is_less_or_equal(danya_decimal a, danya_decimal b);
int danya_is_greater_or_equal(danya_decimal a, danya_decimal b);
int danya_is_equal(danya_decimal a, danya_decimal b);
int danya_is_not_equal(danya_decimal a, danya_decimal b);
int danya_sub(danya_decimal value_1, danya_decimal value_2,
              danya_decimal *result);
int danya_add(danya_decimal value_1, danya_decimal value_2,
              danya_decimal *result);
int danya_mul(danya_decimal value_1, danya_decimal value_2,
              danya_decimal *result);
int danya_div(danya_decimal value_1, danya_decimal value_2,
              danya_decimal *result);
int danya_floor(danya_decimal value, danya_decimal *result);
int danya_round(danya_decimal value, danya_decimal *result);
int danya_truncate(danya_decimal value, danya_decimal *result);
int danya_negate(danya_decimal value, danya_decimal *result);
int danya_from_int_to_decimal(int value, danya_decimal *result);
int danya_from_decimal_to_int(danya_decimal value, int *result);
int danya_from_float_to_decimal(float src, danya_decimal *dst);
int danya_from_decimal_to_float(danya_decimal src, float *dst);

#endif