#ifndef danya_ADDITIONAL_H
#define danya_ADDITIONAL_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "danya_decimal.h"

#define POSITIVE 0
#define NEGATIVE 1

#define SUCCESS 0
#define ERROR 1

#define danya_SUCCESS 0
#define danya_ERR_INEXACT_DIV 3

#define danya_ERR_TOO_LARGE 1
#define danya_ERR_TOO_SMALL 2
#define danya_ERR_DIVISION_BY_ZERO 3
#define danya_ERR_INVALID_ARG 4
#define danya_ERR_INVALID_SCALE 5
#define MASK_EXP 0x00FF0000
#define danya_MAXDEC 2e96 - 1

typedef struct {
  unsigned int bits[8];
} danya_big_decimal;

void printf_decimal(danya_decimal decimal);
// void printf_big_decimal(danya_big_decimal bigdec);
void convert_dec_to_big_dec(danya_decimal *decimal, danya_big_decimal *bigdec);
int check_bits_int(const unsigned int *src, int indx);
int check_bits_dec(const danya_decimal decimal, int indx);
int check_bits_big_dec(const danya_big_decimal bigdec, int indx);
void make_bit_to_zero_in_int(unsigned int *src, int indx);
void make_bit_to_one_in_int(unsigned int *src, int indx);
void set_bit_dec(danya_decimal *decimal, int indx, int value);
void set_bit_big_dec(danya_big_decimal *bigdec, int indx, int value);
void set_bit_big_dec_mantissa(unsigned int dest[7], int indx, int value);
int check_sign_dec(danya_decimal decimal);
int check_sign_big_dec(danya_big_decimal bigdec);
int check_bits_big_dec_mantissa(const unsigned int src[7], int indx);
void set_sign_dec(danya_decimal *decimal, int buff);
void set_sign_big_dec(danya_big_decimal *bigdec, int buff);
bool is_zero(const danya_decimal *decimal);
bool is_zero_big_dec(const danya_big_decimal *src);
void shift_left(danya_big_decimal *bigdec, int value);
void shift_left_big_dec_mantissa(unsigned int dest[7], int value);
void shift_left_big_dec_mantissa_by_1(unsigned int dest[7]);
void set_scale_dec(danya_decimal *decimal, int scale);
void set_scale_big_dec(danya_big_decimal *bigdec, int scale);
int check_scale_dec(danya_decimal *decimal);
int check_scale_big_dec(danya_big_decimal *bigdec);
void normalize_scales(danya_decimal *a, danya_decimal *b);
int compare_mantissas(danya_decimal a, danya_decimal b);
int multiply_mantissa_by_pow10(danya_decimal *num, int power);
int convert_big_dec_to_dec(const danya_big_decimal *src, danya_decimal *dest);
int normalize_big_dec(danya_big_decimal *src);
void bank_round_big_dec_mantissa(unsigned int num[7], int n);
unsigned int divide_big_dec_mantissa_by_10(unsigned int num[7]);
unsigned int divide_dec_mantissa_by_10(unsigned int num[3]);
int danya_div_by_10(danya_decimal *value);  // for danya_floor
unsigned int rem_mantissa_mod10(const unsigned int num[7]);
void multiply_big_dec_mantissa_by_10(unsigned int dest[7]);
void multiply_big_dec_mantissa_by_10n(unsigned int num[7], int n);
int compare_big_dec_mantissas(const unsigned int a[7], const unsigned int b[7]);
void divide_big_dec_mantissa(unsigned int dividend[7], unsigned int divisor[7],
                             unsigned int quotient[7],
                             unsigned int remainder[7]);
void modulus_big_dec(danya_big_decimal *src);
void common_scale_bdec(danya_big_decimal *a, danya_big_decimal *b);
int compare_modulus_big_dec(danya_big_decimal a, danya_big_decimal b);
void subtract_modulus_big_dec(danya_big_decimal a, danya_big_decimal b,
                              danya_big_decimal *result);
int substract_bitwise_big_dec_mantissa(const unsigned int a[7],
                                       const unsigned int b[7],
                                       unsigned int result[7]);
void sum_modulus_big_dec(danya_big_decimal a, danya_big_decimal b,
                         danya_big_decimal *result);
int sum_bitwise_big_dec_mantissa(const unsigned int a[7],
                                 const unsigned int b[7],
                                 unsigned int summary[7]);
void big_dec_mul_10n(danya_big_decimal *dest, int delta_scale);
void multiply_big_dec_by_10(danya_big_decimal *dest);
int sum_bitwise_big_dec(const danya_big_decimal a, const danya_big_decimal b,
                        danya_big_decimal *summary);
void mul_dec_mantissa(danya_decimal a, danya_decimal b,
                      danya_big_decimal *result);
void danya_abs(danya_decimal value, danya_decimal *result);
int get_exp_dec(danya_decimal value);

#endif
