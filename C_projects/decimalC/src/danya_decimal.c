#include "danya_additional.h"

int danya_is_less(danya_decimal a, danya_decimal b) {
  if (is_zero(&a) && is_zero(&b)) {
    return 0;
  }

  if (check_sign_dec(a) != check_sign_dec(b)) {
    return check_sign_dec(a) == NEGATIVE;
  }

  normalize_scales(&a, &b);

  if (check_sign_dec(a) == POSITIVE) {
    return compare_mantissas(a, b) == -1;
  } else {
    return compare_mantissas(a, b) == 1;
  }
}

int danya_is_greater(danya_decimal a, danya_decimal b) {
  if (is_zero(&a) && is_zero(&b)) {
    return 0;
  }

  if (check_sign_dec(a) != check_sign_dec(b)) {
    return check_sign_dec(a) == POSITIVE;
  }

  normalize_scales(&a, &b);

  if (check_sign_dec(a) == POSITIVE) {
    return compare_mantissas(a, b) == 1;
  } else {
    return compare_mantissas(a, b) == -1;
  }
}

int danya_is_less_or_equal(danya_decimal a, danya_decimal b) {
  if (is_zero(&a) && is_zero(&b)) {
    return 1;
  }

  if (check_sign_dec(a) != check_sign_dec(b)) {
    return check_sign_dec(a) == 1;
  }

  normalize_scales(&a, &b);

  int cmp = compare_mantissas(a, b);
  if (check_sign_dec(a) == 0) {
    return (cmp <= 0);
  } else {
    return (cmp >= 0);
  }
}

int danya_is_greater_or_equal(danya_decimal a, danya_decimal b) {
  if (is_zero(&a) && is_zero(&b)) {
    return 1;
  }

  if (check_sign_dec(a) != check_sign_dec(b)) {
    return check_sign_dec(a) == 0;
  }

  normalize_scales(&a, &b);

  int cmp = compare_mantissas(a, b);
  if (check_sign_dec(a) == 0) {
    return (cmp >= 0);
  } else {
    return (cmp <= 0);
  }
}

int danya_is_equal(danya_decimal a, danya_decimal b) {
  if (is_zero(&a) && is_zero(&b)) {
    return 1;
  }

  if (check_sign_dec(a) != check_sign_dec(b)) {
    return 0;
  }

  normalize_scales(&a, &b);

  return compare_mantissas(a, b) == 0;
}

int danya_is_not_equal(danya_decimal a, danya_decimal b) {
  return !danya_is_equal(a, b);
}

int danya_sub(danya_decimal value_1, danya_decimal value_2,
              danya_decimal *result) {  // ironscar
  int complete_flag = 0;
  if (is_zero(&value_1)) {
    *result = value_2;
    complete_flag = 1;
    if (is_zero(&value_1) && !is_zero(&value_2)) set_sign_dec(result, 1);
  } else if (is_zero(&value_2)) {
    *result = value_1;
    complete_flag = 1;
  }
  if (complete_flag == 1) return 0;
  danya_big_decimal value_1_big = {0};
  danya_big_decimal value_2_big = {0};
  danya_big_decimal result_big = {0};
  convert_dec_to_big_dec(&value_1, &value_1_big);
  convert_dec_to_big_dec(&value_2, &value_2_big);
  int sign_a = check_sign_big_dec(value_1_big);
  int sign_b = check_sign_big_dec(value_2_big);
  modulus_big_dec(&value_1_big);
  modulus_big_dec(&value_2_big);
  common_scale_bdec(&value_1_big, &value_2_big);
  int scale = check_scale_big_dec(&value_1_big);
  int modulus_comparison = compare_modulus_big_dec(value_1_big, value_2_big);
  if (sign_a == 0 && sign_b == 0 && !complete_flag) {
    if (modulus_comparison >= 0) {
      subtract_modulus_big_dec(value_1_big, value_2_big, &result_big);
      set_sign_big_dec(&result_big, 0);
      set_scale_big_dec(&result_big, scale);
    } else {
      subtract_modulus_big_dec(value_2_big, value_1_big, &result_big);
      set_sign_big_dec(&result_big, 1);
      set_scale_big_dec(&result_big, scale);
    }
  } else if (sign_a == 0 && sign_b == 1 && !complete_flag) {
    sum_modulus_big_dec(value_1_big, value_2_big, &result_big);
    set_sign_big_dec(&result_big, 0);
    set_scale_big_dec(&result_big, scale);
  } else if (sign_a == 1 && sign_b == 0 && !complete_flag) {
    sum_modulus_big_dec(value_1_big, value_2_big, &result_big);
    set_sign_big_dec(&result_big, 1);
    set_scale_big_dec(&result_big, scale);
  } else if (sign_a == 1 && sign_b == 1 && !complete_flag) {
    if (modulus_comparison >= 0) {
      subtract_modulus_big_dec(value_1_big, value_2_big, &result_big);
      set_sign_big_dec(&result_big, 1);
      set_scale_big_dec(&result_big, scale);
    } else {
      subtract_modulus_big_dec(value_2_big, value_1_big, &result_big);
      set_sign_big_dec(&result_big, 0);
      set_scale_big_dec(&result_big, scale);
    }
  }
  complete_flag = 1;
  return convert_big_dec_to_dec(&result_big, result);
}

int danya_add(danya_decimal value_1, danya_decimal value_2,
              danya_decimal *result) {
  danya_big_decimal value_a_big = {0};
  danya_big_decimal value_b_big = {0};
  danya_big_decimal result_big = {0};
  convert_dec_to_big_dec(&value_1, &value_a_big);
  convert_dec_to_big_dec(&value_2, &value_b_big);
  int sign_a = check_sign_big_dec(value_a_big);
  int sign_b = check_sign_big_dec(value_b_big);
  modulus_big_dec(&value_a_big);
  modulus_big_dec(&value_b_big);
  common_scale_bdec(&value_a_big, &value_b_big);
  int scale = check_scale_big_dec(&value_a_big);
  int modulus_comparison = compare_modulus_big_dec(value_a_big, value_b_big);
  if (sign_a == 0 && sign_b == 0) {
    sum_modulus_big_dec(value_a_big, value_b_big, &result_big);
    set_sign_big_dec(&result_big, 0);
    set_scale_big_dec(&result_big, scale);
  } else if (sign_a == 0 && sign_b == 1) {
    if (modulus_comparison >= 0) {
      subtract_modulus_big_dec(value_a_big, value_b_big, &result_big);
      set_sign_big_dec(&result_big, 0);
      set_scale_big_dec(&result_big, scale);
    } else {
      subtract_modulus_big_dec(value_b_big, value_a_big, &result_big);
      set_sign_big_dec(&result_big, 1);
      set_scale_big_dec(&result_big, scale);
    }
  } else if (sign_a == 1 && sign_b == 0) {
    if (modulus_comparison >= 0) {
      subtract_modulus_big_dec(value_a_big, value_b_big, &result_big);
      set_sign_big_dec(&result_big, 1);
      set_scale_big_dec(&result_big, scale);
    } else {
      subtract_modulus_big_dec(value_b_big, value_a_big, &result_big);
      set_sign_big_dec(&result_big, 0);
      set_scale_big_dec(&result_big, scale);
    }
  } else if (sign_a == 1 && sign_b == 1) {
    sum_modulus_big_dec(value_a_big, value_b_big, &result_big);
    set_sign_big_dec(&result_big, 1);
    set_scale_big_dec(&result_big, scale);
  }
  return convert_big_dec_to_dec(&result_big, result);
}

int danya_mul(danya_decimal value_1, danya_decimal value_2,
              danya_decimal *result) {
  danya_big_decimal temp_result = {.bits = {0}};
  mul_dec_mantissa(value_1, value_2, &temp_result);
  set_scale_big_dec(&temp_result,
                    check_scale_dec(&value_1) + check_scale_dec(&value_2));
  int sign_1 = check_sign_dec(value_1);
  int sign_2 = check_sign_dec(value_2);
  if (sign_1 != sign_2) {
    set_sign_big_dec(&temp_result, 1);
  } else {
    set_sign_big_dec(&temp_result, 0);
  }

  return convert_big_dec_to_dec(&temp_result, result);
}

int danya_div(danya_decimal value_1, danya_decimal value_2,
              danya_decimal *result) {
  int err_flag = 0;

  int scale_value_1 = check_scale_dec(&value_1);
  int scale_value_2 = check_scale_dec(&value_2);

  if ((result == NULL) || (scale_value_1 > 28) || (scale_value_2 > 28))
    err_flag = danya_ERR_INVALID_ARG;
  else if (is_zero(&value_2))
    err_flag = danya_ERR_DIVISION_BY_ZERO;
  else {
    unsigned int quotient[7] = {0};
    unsigned int remainder[7] = {0};
    danya_big_decimal quotient_big_dec = {0};
    unsigned int value_1_big_mantissa[7] = {
        value_1.bits[0], value_1.bits[1], value_1.bits[2], 0, 0, 0, 0};
    unsigned int value_2_big_mantissa[7] = {
        value_2.bits[0], value_2.bits[1], value_2.bits[2], 0, 0, 0, 0};
    for (int i = 0; i < 4; i++) result->bits[i] = 0;
    multiply_big_dec_mantissa_by_10n(value_1_big_mantissa, 38);
    divide_big_dec_mantissa(value_1_big_mantissa, value_2_big_mantissa,
                            quotient, remainder);
    if (check_sign_dec(value_1) != check_sign_dec(value_2))
      set_sign_big_dec(&quotient_big_dec, 1);
    set_scale_big_dec(&quotient_big_dec, 38 + scale_value_1 - scale_value_2);
    for (int i = 0; i < 7; i++) quotient_big_dec.bits[i] = quotient[i];
    err_flag = convert_big_dec_to_dec(&quotient_big_dec, result);
  }
  return err_flag;
}

int danya_floor(danya_decimal value, danya_decimal *result) {
  int scale_error = check_scale_dec(&value);
  if (scale_error > 28) return 1;
  if (!result) return 1;

  *result = value;
  int scale = check_scale_dec(&value);
  int sign = check_sign_dec(value);

  if (scale == 0) return 0;
  if (is_zero(&value)) {
    set_scale_dec(result, 0);
    return 0;
  }
  if (!sign) {
    while (scale > 0) {
      danya_div_by_10(result);
      scale--;
    }
    set_scale_dec(result, 0);
  } else {
    danya_decimal one = {{1, 0, 0, 0}};
    danya_decimal tmp = value;
    int original_sign = sign;
    while (scale > 0) {
      danya_div_by_10(&tmp);
      scale--;
      if (is_zero(&tmp)) {
        set_sign_dec(&one, original_sign);
        *result = one;
        set_scale_dec(result, 0);
        return 0;
      }
    }
    set_scale_dec(&tmp, 0);
    set_sign_dec(&tmp, original_sign);

    if (danya_is_not_equal(tmp, value)) {
      danya_sub(tmp, one, result);
    } else {
      *result = tmp;
    }
  }
  return 0;
}

int danya_round(danya_decimal value, danya_decimal *result) {
  int scale = check_scale_dec(&value);
  if (scale > 28) return 1;

  if (!result) return 1;

  danya_decimal half = {{5, 0, 0, 0}};
  set_scale_dec(&half, 1);

  danya_decimal truncated = {0};
  danya_truncate(value, &truncated);

  danya_decimal fractional = {0};
  danya_sub(value, truncated, &fractional);

  int sign = check_sign_dec(value);
  danya_abs(fractional, &fractional);

  int cmp_res = danya_is_less(half, fractional);

  if (cmp_res || danya_is_equal(fractional, half)) {
    danya_decimal one = {{1, 0, 0, 0}};
    if (sign) {
      danya_sub(truncated, one, result);
    } else {
      danya_add(truncated, one, result);
    }
  } else {
    *result = truncated;
  }

  set_scale_dec(result, 0);
  set_sign_dec(result, sign);

  return 0;
}

int danya_truncate(danya_decimal value, danya_decimal *result) {
  int scale_error = check_scale_dec(&value);
  if (scale_error > 28) return 1;

  if (!result) return 1;

  *result = value;
  int scale = check_scale_dec(&value);

  while (scale-- > 0) {
    danya_div_by_10(result);
  }

  set_scale_dec(result, 0);
  return 0;
}

int danya_negate(danya_decimal value, danya_decimal *result) {
  int scale = check_scale_dec(&value);
  if (scale > 28) return 1;

  if (!result) return 1;

  *result = value;
  int sign = check_sign_dec(value);
  if (sign == 1) {
    set_sign_dec(result, 0);
  } else {
    set_sign_dec(result, 1);
  }
  return 0;
}

int danya_from_int_to_decimal(int src, danya_decimal *dst) {
  if (dst == NULL) {
    return 1;
  }
  int sign = 0;
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;

  if (src < 0) {
    sign = 1;
  } else {
    sign = 0;
  }

  if (src == INT32_MIN) {
    dst->bits[0] = (unsigned int)INT32_MAX + 1;
  } else if (sign > 0) {
    dst->bits[0] = (unsigned int)(-src);
  } else {
    dst->bits[0] = (unsigned int)(src);
  }

  set_scale_dec(dst, 0);
  set_sign_dec(dst, sign);
  return 0;
}

int danya_from_decimal_to_int(danya_decimal src, int *dst) {
  if (dst == NULL) {
    return 1;
  }

  int sign = check_sign_dec(src);
  int scale = check_scale_dec(&src);

  while (scale > 0) {
    danya_div_by_10(&src);
    scale--;
  }

  if (src.bits[1] != 0 || src.bits[2] != 0 ||
      src.bits[0] > INT32_MAX + (sign ? 1U : 0U)) {
    *dst = 0;
    return 1;
  }

  int temp = (int)src.bits[0];

  if (sign > 0) {
    if (temp == (int)(INT32_MAX + 1U)) {
      *dst = INT32_MIN;
    } else {
      *dst = -temp;
    }
  } else {
    *dst = temp;
  }

  return 0;
}

int danya_from_float_to_decimal(float src, danya_decimal *dst) {
  int status_error = 0;
  if (fabs(src) < 2e-28) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    status_error = 1;
  } else if (fabs(src) > danya_MAXDEC) {
    status_error = 1;
  } else if (dst) {
    for (int i = 0; i < 4; i++) {
      dst->bits[i] = 0;
    }
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = -(src);
    }
    long int new = (long int)src;
    long int exp = 0;
    while (src - ((float)new / (long int)(pow(10, exp))) != 0) {
      exp++;
      new = src *(long int)(pow(10, exp));
    }
    danya_from_int_to_decimal(new, dst);
    if (sign) {
      set_sign_dec(dst, 1);
    }
    dst->bits[3] += exp << 16;
  } else {
    status_error = 1;
  }
  return status_error;
}

int danya_from_decimal_to_float(danya_decimal src, float *dst) {
  int status_error = 0;
  if (dst == NULL) {
    status_error = 1;
  } else {
    *dst = 0;
    int minus = 1;
    long double res = 0, two = 1;
    int exp = get_exp_dec(src);
    if (check_sign_dec(src) == 1) minus = -1;
    for (int k = 0; k < 96; k++) {
      if (check_bits_dec(src, k)) {
        res += two;
      }
      two *= 2;
    }
    for (int k = 0; k < exp; k++) {
      res /= 10;
    }
    *dst = minus * res;
  }
  return status_error;
}
