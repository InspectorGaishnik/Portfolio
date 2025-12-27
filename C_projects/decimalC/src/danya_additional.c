#include "danya_additional.h"

void printf_decimal(danya_decimal decimal) {
  for (int i = 0; i < 4; i++) {
    printf("bits[%d]: ", i);
    for (int j = 31; j >= 0; j--) {
      printf("%d", (decimal.bits[i] >> j) & 1);
    }
    printf(" dec: %d, hex: %x\n", decimal.bits[i], decimal.bits[i]);
  }
  printf("\n");
}

// void printf_big_decimal(danya_big_decimal bigdec) {
//   for (int i = 0; i < 8; i++) {
//     printf("bits[%d]: ", i);
//     for (int j = 31; j >= 0; j--) {
//       printf("%d", (bigdec.bits[i] >> j) & 1);
//     }
//     printf(" dec: %d, hex: %x\n", bigdec.bits[i], bigdec.bits[i]);
//   }
//   printf("\n");
// }

void convert_dec_to_big_dec(danya_decimal *decimal, danya_big_decimal *bigdec) {
  for (int i = 0; i < 3; i++) {
    bigdec->bits[i] = decimal->bits[i];
  }
  bigdec->bits[7] = decimal->bits[3];
}

int check_bits_int(const unsigned int *src, int indx) {
  unsigned int mask = 1;
  mask = mask << indx;
  mask = mask & *src;
  mask = mask >> indx;
  int result = mask;
  return result;
}

int check_bits_dec(const danya_decimal decimal, int indx) {
  int result = check_bits_int(&decimal.bits[indx / 32], indx % 32);
  return result;
}

int check_bits_big_dec(const danya_big_decimal bigdec, int indx) {
  int result = check_bits_int(&bigdec.bits[indx / 32], indx % 32);
  return result;
}

void make_bit_to_zero_in_int(unsigned int *src, int indx) {
  unsigned int mask = 1;
  mask = mask << indx;
  *src = *src & ~mask;
}

void make_bit_to_one_in_int(unsigned int *src, int indx) {
  unsigned int mask = 1;
  mask = mask << indx;
  *src = *src | mask;
}

void set_bit_dec(danya_decimal *decimal, int indx, int value) {
  if (value) {
    make_bit_to_one_in_int(&decimal->bits[indx / 32], indx % 32);
  } else {
    make_bit_to_zero_in_int(&decimal->bits[indx / 32], indx % 32);
  }
}

void set_bit_big_dec(danya_big_decimal *bigdec, int indx, int value) {
  if (value) {
    make_bit_to_one_in_int(&bigdec->bits[indx / 32], indx % 32);
  } else {
    make_bit_to_zero_in_int(&bigdec->bits[indx / 32], indx % 32);
  }
}

void set_bit_big_dec_mantissa(unsigned int dest[7], int indx, int value) {
  if (value) {
    make_bit_to_one_in_int(&dest[indx / 32], indx % 32);
  } else {
    make_bit_to_zero_in_int(&dest[indx / 32], indx % 32);
  }
}

int check_sign_dec(danya_decimal decimal) {
  return check_bits_dec(decimal, 32 * 4 - 1);
}

int check_sign_big_dec(danya_big_decimal bigdec) {
  return check_bits_big_dec(bigdec, 32 * 8 - 1);
}

int check_bits_big_dec_mantissa(const unsigned int src[7], int indx) {
  int result = check_bits_int(&src[indx / 32], indx % 32);
  return result;
}

void set_sign_dec(danya_decimal *decimal, int buff) {
  if (buff == 0)
    set_bit_dec(decimal, 127, 0);
  else if (buff == 1) {
    set_bit_dec(decimal, 127, 1);
  }
}

void set_sign_big_dec(danya_big_decimal *bigdec, int buff) {
  if (buff == 0)
    set_bit_big_dec(bigdec, 255, 0);
  else if (buff == 1) {
    set_bit_big_dec(bigdec, 255, 1);
  }
}

bool is_zero(const danya_decimal *decimal) {
  bool ret = 0;
  if (decimal->bits[0] == 0 && decimal->bits[1] == 0 && decimal->bits[2] == 0) {
    ret = 1;
  }
  return ret;
}

bool is_zero_big_dec(const danya_big_decimal *src) {
  bool ret = 0;
  if (src->bits[0] == 0 && src->bits[1] == 0 && src->bits[2] == 0 &&
      src->bits[3] == 0 && src->bits[4] == 0 && src->bits[5] == 0 &&
      src->bits[6] == 0)
    ret = 1;
  return ret;
}

void shift_left(danya_big_decimal *bigdec, int value) {
  if (value <= 0) {
    return;
  }
  unsigned int carry = 0;
  for (int i = 0; i < 7; i++) {
    unsigned int current = bigdec->bits[i];
    bigdec->bits[i] = (current << value) | carry;
    carry = (current >> (32 - value));
  }
}

void shift_left_big_dec_mantissa(unsigned int dest[7], int value) {
  for (int i = 0; i < value; i++) {
    shift_left_big_dec_mantissa_by_1(dest);
  }
}

void shift_left_big_dec_mantissa_by_1(unsigned int dest[7]) {
  unsigned int carry = 0;
  for (int i = 0; i < 7; i++) {
    unsigned int current = dest[i];
    dest[i] = (current << 1) | carry;
    carry = (current >> (32 - 1)) & 0xFFFFFFFF;
  }
}

void set_scale_dec(danya_decimal *decimal, int scale) {
  if (decimal != NULL) {
    int sign = decimal->bits[3] & 0x80000000;
    int shifted_scale = scale << 16;
    decimal->bits[3] = shifted_scale + sign;
  }
}

void set_scale_big_dec(danya_big_decimal *bigdec, int scale) {
  if (bigdec != NULL) {
    int sign = bigdec->bits[7] & 0x80000000;
    int shifted_scale = scale << 16;
    bigdec->bits[7] = shifted_scale + sign;
  }
}

int check_scale_dec(danya_decimal *decimal) {
  int shifted = decimal->bits[3] >> 16;
  int masked = shifted & 0x000000FF;
  return masked;
}

int check_scale_big_dec(danya_big_decimal *bigdec) {
  int shifted = bigdec->bits[7] >> 16;
  int masked = shifted & 0x000000FF;
  return masked;
}

void normalize_scales(danya_decimal *a, danya_decimal *b) {
  int a_scale = check_scale_dec(a);
  int b_scale = check_scale_dec(b);

  if (a_scale == b_scale) return;

  if (a_scale < b_scale) {
    multiply_mantissa_by_pow10(a, b_scale - a_scale);
    set_scale_dec(a, b_scale);
  } else {
    multiply_mantissa_by_pow10(b, a_scale - b_scale);
    set_scale_dec(b, a_scale);
  }
}

int compare_mantissas(danya_decimal a, danya_decimal b) {
  if (a.bits[2] < b.bits[2]) return -1;
  if (a.bits[2] > b.bits[2]) return 1;

  if (a.bits[1] < b.bits[1]) return -1;
  if (a.bits[1] > b.bits[1]) return 1;

  if (a.bits[0] < b.bits[0]) return -1;
  if (a.bits[0] > b.bits[0]) return 1;

  return 0;
}

int multiply_mantissa_by_pow10(danya_decimal *num, int power) {
  for (int i = 0; i < power; i++) {
    uint64_t temp = 0;
    for (int j = 0; j < 3; j++) {
      temp += (uint64_t)num->bits[j] * 10;
      num->bits[j] = (unsigned int)(temp & 0xFFFFFFFF);
      temp >>= 32;
    }

    if (temp != 0) {
      return ERROR;
    }
  }

  return SUCCESS;
}

int convert_big_dec_to_dec(const danya_big_decimal *src, danya_decimal *dest) {
  if (src == NULL || dest == NULL) return danya_ERR_INVALID_ARG;

  int err_flag = danya_SUCCESS;
  int scale_is_valid = 0;
  danya_big_decimal temp = *src;

  while (err_flag == danya_SUCCESS && !scale_is_valid) {
    normalize_big_dec(&temp);
    if (temp.bits[3] != 0 || temp.bits[4] != 0 || temp.bits[5] != 0 ||
        temp.bits[6] != 0) {
      if (check_scale_big_dec(&temp) == 0) {
        if (check_sign_big_dec(temp) == 1)
          err_flag = danya_ERR_TOO_SMALL;
        else if (check_sign_big_dec(temp) == 0)
          err_flag = danya_ERR_TOO_LARGE;
      } else {
        bank_round_big_dec_mantissa(temp.bits, 1);
      }
    } else {
      int scale = check_scale_big_dec(&temp);
      if (scale > 28) {
        bank_round_big_dec_mantissa(temp.bits, (scale - 28));
      } else {
        scale_is_valid = 1;
      }
    }
  }

  if (err_flag == danya_SUCCESS) {
    dest->bits[0] = temp.bits[0];
    dest->bits[1] = temp.bits[1];
    dest->bits[2] = temp.bits[2];
    dest->bits[3] = temp.bits[7];
  }
  return err_flag;
}

int normalize_big_dec(danya_big_decimal *src) {
  if (src == NULL) return danya_ERR_INVALID_ARG;

  int err_flag = danya_SUCCESS;

  const unsigned int sign = (src->bits[7] >> 31) & 1;
  int scale = (src->bits[7] >> 16) & 0x000000FF;
  unsigned int mantissa[7] = {
      (unsigned int)src->bits[0], (unsigned int)src->bits[1],
      (unsigned int)src->bits[2], (unsigned int)src->bits[3],
      (unsigned int)src->bits[4], (unsigned int)src->bits[5],
      (unsigned int)src->bits[6]};

  if (is_zero_big_dec(src))
    src->bits[7] &= 0x80000000;
  else {
    int reductions = 0;
    unsigned int rem = 0;
    while ((reductions < scale) && (rem == 0)) {
      unsigned int temp[7] = {mantissa[0], mantissa[1], mantissa[2],
                              mantissa[3], mantissa[4], mantissa[5],
                              mantissa[6]};
      for (int j = 6; j >= 0; j--) {
        uint64_t val = ((uint64_t)rem << 32) | temp[j];
        temp[j] = (unsigned int)(val / 10);
        rem = (unsigned int)(val % 10);
      }
      if (rem == 0) {
        for (int i = 0; i < 7; i++) mantissa[i] = temp[i];
        reductions++;
      }
    }
    if (reductions > 0) {
      for (int i = 0; i < 7; i++) src->bits[i] = mantissa[i];
      src->bits[7] = (sign << 31) | ((scale - reductions) << 16);
    }
  }

  return err_flag;
}

void bank_round_big_dec_mantissa(unsigned int num[7], int n) {
  uint64_t remainder = 0;
  uint64_t power = 1;
  for (int i = 0; i < n; i++) {
    unsigned int digit = divide_big_dec_mantissa_by_10(num);
    remainder += digit * power;
    power *= 10;
  }

  uint64_t half = power / 2;

  int round_up = 0;
  if (remainder > half) {
    round_up = 1;
  } else if (remainder == half) {
    unsigned int last_digit = rem_mantissa_mod10(num);
    if (last_digit & 1) {
      round_up = 1;
    }
  }

  if (round_up) {
    uint64_t carry = 1;
    for (int i = 0; i < 7 && carry != 0; i++) {
      uint64_t sum = (uint64_t)num[i] + carry;
      num[i] = (unsigned int)(sum & 0xFFFFFFFF);
      carry = sum >> 32;
    }
  }
  multiply_big_dec_mantissa_by_10n(num, n);
}

unsigned int divide_big_dec_mantissa_by_10(unsigned int num[7]) {
  uint64_t rem = 0;
  for (int i = 6; i >= 0; i--) {
    uint64_t cur = (rem << 32) | num[i];
    num[i] = (unsigned int)(cur / 10);
    rem = cur % 10;
  }
  return (unsigned int)rem;
}

unsigned int divide_dec_mantissa_by_10(unsigned int num[3]) {
  uint64_t rem = 0;
  for (int i = 2; i >= 0; i--) {
    uint64_t cur = (rem << 32) | num[i];
    num[i] = (unsigned int)(cur / 10);
    rem = cur % 10;
  }
  return (unsigned int)rem;
}

int danya_div_by_10(danya_decimal *value) {
  if (value == NULL) return 1;

  unsigned long long remainder = 0;

  for (int i = 2; i >= 0; i--) {
    unsigned long long temp = (remainder << 32) | value->bits[i];
    value->bits[i] = (unsigned)(temp / 10);
    remainder = temp % 10;
  }

  return 0;
}

unsigned int rem_mantissa_mod10(const unsigned int num[7]) {
  unsigned int temp[7];
  memcpy(temp, num, sizeof(unsigned int) * 7);
  return divide_big_dec_mantissa_by_10(temp);
}

void multiply_big_dec_mantissa_by_10(unsigned int dest[7]) {
  unsigned int var_1[7];
  memcpy(var_1, dest, sizeof(unsigned int) * 7);
  unsigned int var_2[7];
  memcpy(var_2, dest, sizeof(unsigned int) * 7);
  shift_left_big_dec_mantissa_by_1(var_1);
  shift_left_big_dec_mantissa(var_2, 3);
  sum_bitwise_big_dec_mantissa(var_1, var_2, dest);
}

void multiply_big_dec_mantissa_by_10n(unsigned int num[7], int n) {
  for (int i = 0; i < n; i++) {
    multiply_big_dec_mantissa_by_10(num);
  }
}

int compare_big_dec_mantissas(const unsigned int a[7],
                              const unsigned int b[7]) {
  int result = 0;

  for (int i = 6; (i >= 0) && (result == 0); i--) {
    if (a[i] < b[i])
      result = -1;
    else if (a[i] > b[i])
      result = 1;
  }

  return result;
}

void divide_big_dec_mantissa(unsigned int dividend[7], unsigned int divisor[7],
                             unsigned int quotient[7],
                             unsigned int remainder[7]) {
  for (int i = 0; i < 7; i++) {
    quotient[i] = 0;
    remainder[i] = 0;
  }

  if (compare_big_dec_mantissas(divisor, dividend) == 1)
    memcpy(remainder, dividend, sizeof(unsigned int) * 7);
  else
    for (int i = 223; i >= 0; i--) {
      shift_left_big_dec_mantissa_by_1(remainder);
      if (check_bits_big_dec_mantissa(dividend, i)) {
        remainder[0] |= 1u;
      }

      if (compare_big_dec_mantissas(remainder, divisor) >= 0) {
        unsigned int temp[7];
        substract_bitwise_big_dec_mantissa(remainder, divisor, temp);
        memcpy(remainder, temp, sizeof(unsigned int) * 7);
        set_bit_big_dec_mantissa(quotient, i, 1);
      }
    }
}

void modulus_big_dec(danya_big_decimal *src) {
  if (src != NULL) {
    set_sign_big_dec(src, 0);
  }
}

void common_scale_bdec(danya_big_decimal *a, danya_big_decimal *b) {
  int scale_a = check_scale_big_dec(a);
  int scale_b = check_scale_big_dec(b);

  if (scale_a != scale_b) {
    if (scale_a < scale_b) {
      big_dec_mul_10n(a, scale_b - scale_a);
    } else {
      big_dec_mul_10n(b, scale_a - scale_b);
    }
  }
}

int compare_modulus_big_dec(danya_big_decimal a, danya_big_decimal b) {
  modulus_big_dec(&a);
  modulus_big_dec(&b);

  int flag = 0;
  for (int i = 6; i >= 0 && flag == 0; i--) {
    if (a.bits[i] > b.bits[i]) {
      flag = 1;
    } else if (a.bits[i] < b.bits[i]) {
      flag = -1;
    }
  }
  return flag;
}

void subtract_modulus_big_dec(danya_big_decimal a, danya_big_decimal b,
                              danya_big_decimal *result) {
  if (result == NULL) {
    return;
  }

  for (int i = 0; i < 8; i++) {
    result->bits[i] = 0;
  }

  int borrow = 0;

  for (int i = 0; i < 256; i++) {
    int bit_a = (a.bits[i / 32] >> (i % 32)) & 1;
    int bit_b = (b.bits[i / 32] >> (i % 32)) & 1;

    int diff = bit_a - bit_b - borrow;

    if (diff < 0) {
      diff += 2;
      borrow = 1;
    } else {
      borrow = 0;
    }

    if (diff == 1) {
      result->bits[i / 32] |= (1U << (i % 32));
    }
  }
}

int substract_bitwise_big_dec_mantissa(const unsigned int a[7],
                                       const unsigned int b[7],
                                       unsigned int result[7]) {
  for (int i = 0; i < 7; i++) {
    result[i] = 0;
  }

  int borrow = 0;

  for (int i = 0; i < 224; i++) {
    int bit_a = (a[i / 32] >> (i % 32)) & 1u;
    int bit_b = (b[i / 32] >> (i % 32)) & 1u;

    int diff = bit_a - bit_b - borrow;

    if (diff < 0) {
      diff += 2;
      borrow = 1;
    } else {
      borrow = 0;
    }

    if (diff == 1) {
      result[i / 32] |= (1u << (i % 32));
    }
  }
  return borrow;
}

void sum_modulus_big_dec(danya_big_decimal a, danya_big_decimal b,
                         danya_big_decimal *result) {
  if (result == NULL) {
    return;
  }

  for (int i = 0; i < 7; i++) {
    result->bits[i] = 0;
  }

  int carry = 0;

  for (int i = 0; i < 256; i++) {
    int bit_a = (a.bits[i / 32] >> (i % 32)) & 1;
    int bit_b = (b.bits[i / 32] >> (i % 32)) & 1;

    int sum = bit_a + bit_b + carry;

    if (sum >= 2) {
      sum -= 2;
      carry = 1;
    } else {
      carry = 0;
    }

    if (sum) {
      result->bits[i / 32] |= (1U << (i % 32));
    }
  }
}

int sum_bitwise_big_dec_mantissa(const unsigned int a[7],
                                 const unsigned int b[7],
                                 unsigned int summary[7]) {
  unsigned int result[7] = {0, 0, 0, 0, 0, 0, 0};
  int carry = 0;

  for (unsigned int i = 0; i < 7; i++) {
    for (unsigned int j = 0; j < 32; j++) {
      int bit_a = (a[i] >> j) & 1u;
      int bit_b = (b[i] >> j) & 1u;
      int sum_int = bit_a + bit_b + carry;
      result[i] |= (sum_int & 1u) << j;
      carry = sum_int >> 1u;
    }
  }
  for (int i = 0; i < 7; i++) summary[i] = result[i];
  return carry;
}

void big_dec_mul_10n(danya_big_decimal *dest, int delta_scale) {
  for (int i = 0; i < delta_scale; i++) {
    multiply_big_dec_by_10(dest);
  }
  set_scale_big_dec(dest, check_scale_big_dec(dest) + delta_scale);
}

void multiply_big_dec_by_10(danya_big_decimal *dest) {
  danya_big_decimal var_1 = *dest;
  danya_big_decimal var_2 = *dest;
  shift_left(&var_1, 1);
  shift_left(&var_2, 3);
  sum_bitwise_big_dec(var_1, var_2, dest);
}

int sum_bitwise_big_dec(const danya_big_decimal a, const danya_big_decimal b,
                        danya_big_decimal *summary) {
  danya_big_decimal result = {{0, 0, 0, 0, 0, 0, 0, a.bits[7]}};
  int carry = 0;

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 32; j++) {
      int bit_a = (a.bits[i] >> j) & 1;
      int bit_b = (b.bits[i] >> j) & 1;
      unsigned int sum_int = bit_a + bit_b + carry;
      result.bits[i] |= (sum_int & 1) << j;
      carry = sum_int >> 1;
    }
  }
  *summary = result;
  return carry;
}

void mul_dec_mantissa(danya_decimal a, danya_decimal b,
                      danya_big_decimal *result) {
  danya_big_decimal a_big = {{0}}, b_big = {{0}};
  convert_dec_to_big_dec(&a, &a_big);
  convert_dec_to_big_dec(&b, &b_big);

  *result = (danya_big_decimal){0};
  result->bits[7] = 0;

  for (int i = 0; i < 96; i++) {
    if (check_bits_big_dec(a_big, i)) {
      danya_big_decimal temp = b_big;
      shift_left(&temp, i);
      sum_bitwise_big_dec(*result, temp, result);
    }
  }
}

void danya_abs(danya_decimal value, danya_decimal *result) {
  *result = value;
  set_sign_dec(result, 0);
}

int get_exp_dec(danya_decimal value) {
  return (value.bits[3] & MASK_EXP) >> 16;
}
