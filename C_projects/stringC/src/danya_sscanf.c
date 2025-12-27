#include "danya_string.h"

int danya_sscanf(const char *str, const char *fstr, ...) {
  int eof_fl = danya_CheckStringEOF(str);
  int result = 0;
  if (!eof_fl) {
    va_list va;
    va_start(va, fstr);
    int tokens_num = 0;
    char *formstr = (char *)fstr;
    int length = (int)danya_strlen(formstr);
    char *src = (char *)str;
    token tokens[BUFF_SIZE];
    while (*formstr && formstr < fstr + length && tokens_num < BUFF_SIZE) {
      tokens[tokens_num] = danya_ParseTokensFSTR(&formstr, &va);
      tokens_num++;
    }
    danya_WriteTokensToMem(&src, tokens, tokens_num, &result);
    va_end(va);
  }
  return eof_fl ? eof_fl : result;
}

int danya_isspace(char c) { return (c == ' ' || c == '\n' || c == '\t'); }

int danya_isalpha(char c) {
  return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int danya_CheckStringEOF(const char *src) {
  int result = -1;
  int flag = 0;
  int i = 0;
  while (src[i] && !flag) {
    if (!danya_isspace(src[i]) && src[i] != '\0') {
      result = 0;
      flag = 1;
    }
    i++;
  }
  return result;
}

token danya_ParseTokensFSTR(char **fstr, va_list *va) {
  token tokens_ar = {.addr = danya_NULL,
                     .lenght_t = NONE_LENGHT,
                     .spec = 0,
                     .width = NONE_WIDTH,
                     .width_n = 0};
  if (danya_isspace(**fstr)) {
    tokens_ar.spec = 'z';
    danya_SkipSpaces(fstr);
  }
  if (**fstr == '%' && !tokens_ar.spec) {
    (*fstr)++;
    if (**fstr == '%') {
      danya_memset(tokens_ar.buff, '\0', BUFF_SIZE - 1);
      tokens_ar.buff[0] = '%';
      (*fstr)++;
      tokens_ar.spec = 'b';
    } else {
      danya_ParseWidthFSTR(fstr, &tokens_ar);
      danya_ParseLenghtFSTR(fstr, &tokens_ar);
      danya_ParseSpecFSTR(fstr, &tokens_ar);
      if (tokens_ar.width != WIDTH_AST) tokens_ar.addr = va_arg(*va, void *);
    }
    if (tokens_ar.spec == 'p') tokens_ar.lenght_t = NONE_LENGHT;
  }
  if (danya_isalpha(**fstr) && !tokens_ar.spec) {
    danya_memset(tokens_ar.buff, '\0', BUFF_SIZE - 1);
    int i = 0;
    while (**fstr && !danya_isspace(**fstr) && **fstr != '%') {
      tokens_ar.buff[i++] = **fstr;
      (*fstr)++;
    }
    tokens_ar.spec = 'b';
  }
  return tokens_ar;
}

void danya_SkipChars(char **src, int *fail, const token *tokens_ar) {
  int check_len = danya_strspn(*src, tokens_ar->buff);
  int length = danya_strlen(tokens_ar->buff);
  if (length == 1 && **src == tokens_ar->buff[0]) {
    (*src) = (*src) + length;
  } else if (check_len != length)
    *fail = 1;
  else
    (*src) = (*src) + length;
}

void danya_ParseWidthFSTR(char **fstr, token *tokens_ar) {
  if (**fstr == '*') {
    (*fstr)++;
    tokens_ar->width = WIDTH_AST;
  } else {
    int parse_width = danya_ParseNumberFSTR(fstr);
    if (parse_width) {
      tokens_ar->width = WIDTH_NUMBER;
      tokens_ar->width_n = parse_width;
    }
  }
}

int danya_ParseNumberFSTR(char **fstr) {
  char tmp[BUFF_SIZE] = {'\0'};
  int result = 0, i = 0;
  while (**fstr >= '0' && **fstr <= '9') {
    tmp[i] = **fstr;
    (*fstr)++;
    i++;
  }
  result = danya_atoi(tmp);
  return result;
}

void danya_ParseLenghtFSTR(char **fstr, token *tokens_ar) {
  switch (**fstr) {
    case 'h':
      tokens_ar->lenght_t = LENGHT_SHORT;
      (*fstr)++;
      break;
    case 'l':
      tokens_ar->lenght_t = LENGHT_LONG;
      (*fstr)++;
      if (**fstr == 'l') {
        tokens_ar->lenght_t = LENGHT_LONG_LONG;
        (*fstr)++;
      }
      break;
    case 'L':
      tokens_ar->lenght_t = LENGHT_LONG_DOUBLE;
      (*fstr)++;
      break;
  }
}

void danya_ParseSpecFSTR(char **fstr, token *tokens_ar) {
  tokens_ar->spec = (**fstr);
  (*fstr)++;
}

void danya_WriteTokensToMem(char **src, token *tokens, int tok_len, int *result) {
  const char *start = *src;
  int i = 0, fail = 0;
  while (i < tok_len && !fail) {
    char spec = tokens[i].spec;
    if (spec == 'c') danya_WriteCharToMem(src, result, (tokens + i), &fail);
    if (spec == 'd') danya_WriteIntToMem(src, &fail, result, (tokens + i));
    if (spec == 'i' || spec == 'p')
      danya_WriteUnspecIntToMem(src, &fail, result, (tokens + i));
    if (spec == 'g' || spec == 'G' || spec == 'f')
      danya_WriteFloatToMem(src, result, (tokens + i));
    if (spec == 's') danya_WriteStrToMem(src, &fail, result, (tokens + i));
    if (spec == 'u') danya_WriteUnsignIntToMem(src, &fail, result, (tokens + i));
    if (spec == 'x' || spec == 'X')
      danya_WriteHexOctToMem(src, &fail, result, (tokens + i), 16);
    if (spec == 'o') danya_WriteHexOctToMem(src, &fail, result, (tokens + i), 8);
    if (spec == 'n') *((int *)tokens[i].addr) = (*src) - start;
    if (spec == 'z') danya_SkipSpaces(src);
    if (spec == 'b') danya_SkipChars(src, &fail, (tokens + i));
    i++;
  }
}

void danya_SkipSpaces(char **src) {
  while (**src && danya_isspace(**src)) (*src)++;
}

void danya_WriteCharToMem(char **str, int *result, token *tokens_ar, int *fail) {
  *fail = 1;
  int stop_flag = 0;
  while (**str && !stop_flag) {
    *fail = 0;
    if (tokens_ar->width == WIDTH_AST) {
      (*str)++;
      stop_flag = 1;
    } else {
      *(char *)tokens_ar->addr = **str;
      (*str)++;
      (*result)++;
      stop_flag = 1;
    }
  }
}

void danya_WriteIntToMem(char **str, int *fail_flag, int *result,
                       token *tokens_ar) {
  long long int result_int = 0;
  char buff[BUFF_SIZE] = {'\0'};
  *fail_flag = 1;
  if (danya_strspn(*str, "0123456789+-")) {
    int sign = danya_strspn(*str, "+-");
    if (!(sign > 1 ||
          (sign && (tokens_ar->width_n <= 1 && tokens_ar->width)))) {
      buff[0] = **str;
      (*str)++;
      danya_WriteCharToBuff(str, "0123456789", buff, tokens_ar->width_n, 1);
      if (tokens_ar->width != WIDTH_AST) (*result)++;
      *fail_flag = 0;
    }
  }
  result_int = danya_atoi(buff);
  if (tokens_ar->spec == 'p' && tokens_ar->width != WIDTH_AST && !*fail_flag) {
    unsigned long long int mem =
        danya_strntollu(buff, danya_NULL, 16, danya_strlen(buff));
    *(int *)tokens_ar->addr = (int)mem;
  } else {
    if (tokens_ar->width != WIDTH_AST && !*fail_flag)
      danya_IntConverter(tokens_ar, result_int, 1);
  }
  if (tokens_ar->width != WIDTH_NUMBER)
    danya_WriteCharToBuff(str, "0123456789", danya_NULL, 0, 0);
}

void danya_WriteUnspecIntToMem(char **str, int *fail_flag, int *result,
                             token *tokens_ar) {
  *fail_flag = 1;
  danya_SkipSpaces(str);
  if (danya_strspn(*str, "0x") == 2) {
    *fail_flag = 0;
    danya_WriteHexOctToMem(str, fail_flag, result, tokens_ar, 16);
  } else if (danya_strspn(*str, "0") == 1) {
    *fail_flag = 0;
    danya_WriteHexOctToMem(str, fail_flag, result, tokens_ar, 8);
  } else if (danya_strspn(*str, "+-0123456789")) {
    *fail_flag = 0;
    danya_WriteIntToMem(str, fail_flag, result, tokens_ar);
  }
}

void danya_WriteCharToBuff(char **str, const char *chars, char *buff,
                         int16_t width, int start_ind) {
  int stop_flag = 0;
  while (**str && danya_strspn(*str, chars) != 0 && !stop_flag) {
    if ((width && start_ind >= width) || (danya_isspace(**str)))
      stop_flag = 1;
    else {
      if (buff) buff[start_ind] = **str;
      (*str)++;
      start_ind++;
    }
  }
}

void danya_WriteFloatToMem(char **str, int *result, token *tokens_ar) {
  int check_legit = 0;
  if (tokens_ar->spec == 'f')
    check_legit = danya_strspn(*str, "0123456789+-");
  else
    check_legit = danya_strspn(*str, "0123456789eE+-NnaAifIF");
  if (check_legit) {
    int sign = danya_strspn(*str, "+-");
    if (!(sign > 1 ||
          (sign && (tokens_ar->width_n <= 1 && tokens_ar->width)))) {
      char buff[BUFF_SIZE] = {'\0'};
      int start_ind = 0;
      if (sign) {
        buff[0] = **str;
        start_ind = 1;
        (*str)++;
      }
      if (tokens_ar->spec == 'f')
        danya_WriteCharToBuff(str, ".0123456789+-", buff, tokens_ar->width_n,
                            start_ind);
      else
        danya_WriteCharToBuff(str, ".0123456789eE+-NnaAifIF", buff,
                            tokens_ar->width_n, start_ind);
      if (tokens_ar->width != WIDTH_AST) {
        long double result_float = danya_strtold(buff);
        (*result)++;
        danya_FloatConverter(tokens_ar, result_float);
      }
    }
  }
  if (tokens_ar->width != WIDTH_NUMBER) {
    if (tokens_ar->spec == 'f')
      danya_WriteCharToBuff(str, ".0123456789", danya_NULL, 0, 0);
    else
      danya_WriteCharToBuff(str, ".0123456789+-NaAifIFn", danya_NULL, 0, 0);
  }
}

void danya_WriteStrToMem(char **str, const int *fail_flag, int *result,
                       token *tokens_ar) {
  int success_read = 0;
  char buff[BUFF_SIZE] = {'\0'};
  unsigned int i = 0;
  while (**str != '\0' && !success_read && !(*fail_flag)) {
    if (!danya_isspace(**str)) {
      success_read = 1;
      int stop_flag = 0;
      while (**str != '\0' && !(*fail_flag) && !stop_flag) {
        buff[i] = **str;
        i++;
        if (tokens_ar->width == WIDTH_NUMBER && i >= tokens_ar->width_n)
          stop_flag = 1;
        else
          (*str)++;
        if (danya_isspace(**str)) {
          (*str)--;
          stop_flag = 1;
        }
      }
    }
    (*str)++;
  }
  if (tokens_ar->width != WIDTH_AST && success_read) {
    danya_strcpy((char *)tokens_ar->addr, buff);
    (*result)++;
  }
}

void danya_WriteUnsignIntToMem(char **str, int *fail_flag, int *result,
                             token *tokens_ar) {
  *fail_flag = 1;
  danya_SkipSpaces(str);
  char buff[BUFF_SIZE] = {'\0'};
  if (danya_strspn(*str, "0123456789+-")) {
    int sign = danya_strspn(*str, "+-");
    if (!((sign > 1 ||
           (sign && (tokens_ar->width_n <= 1 && tokens_ar->width))))) {
      *fail_flag = 0;
      buff[0] = **str;
      (*str)++;
      danya_WriteCharToBuff(str, "0123456789", buff, tokens_ar->width_n, 1);
      if (tokens_ar->width != WIDTH_AST) (*result)++;
    }
  }
  unsigned long long int result_unsigned = danya_atoi(buff);
  if (tokens_ar->width != WIDTH_AST && !*fail_flag)
    danya_UnsignConverter(tokens_ar, result_unsigned, 1);
  if (tokens_ar->width != WIDTH_NUMBER)
    danya_WriteCharToBuff(str, "0123456789", danya_NULL, 0, 0);
}

void danya_WriteHexOctToMem(char **str, int *fail_flag, int *result,
                          token *tokens_ar, int base) {
  int sign = 1;
  char *ptr = danya_NULL;
  if (tokens_ar->spec == 'p') base = 16;
  danya_SkipSpaces(str);
  if (**str == '-') {
    tokens_ar->width_n--;
    sign = -1;
    (*str)++;
  }
  if (base == 16 && **str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X'))
    tokens_ar->width_n -= 2;
  if (danya_strspn(*str, "0123456789abcdefABCDEF") > 0 ||
      danya_strspn(*str, "xX0123456789abcdefABCDEF") >= 2) {
    unsigned long long int result_unsigned =
        danya_strntollu(*str, &ptr, base,
                      tokens_ar->width ? tokens_ar->width_n : danya_strlen(*str));
    if (tokens_ar->width != WIDTH_AST) {
      *result += 1;
      if (tokens_ar->spec == 'p')
        *(int *)tokens_ar->addr = (int)result_unsigned;
      else
        danya_UnsignConverter(tokens_ar, result_unsigned, sign);
    }
  } else
    *fail_flag = 1;
  unsigned int read_symbols =
      (unsigned int)danya_strspn(*str, "xX0123456789abcdefABCDEF");
  if (tokens_ar->width != WIDTH_NUMBER)
    *str += read_symbols;
  else
    *str +=
        read_symbols < tokens_ar->width_n ? read_symbols : tokens_ar->width_n;
}

void danya_UnsignConverter(token *tokens_ar, unsigned long long int result,
                         int sign) {
  if (tokens_ar->lenght_t == NONE_LENGHT) {
    *(unsigned int *)tokens_ar->addr = sign * (unsigned int)result;
  } else if (tokens_ar->lenght_t == LENGHT_SHORT) {
    *(unsigned short int *)tokens_ar->addr = sign * (unsigned short int)result;
  } else if (tokens_ar->lenght_t == LENGHT_LONG) {
    *(unsigned long int *)tokens_ar->addr = sign * (unsigned long int)result;
  } else if (tokens_ar->lenght_t == LENGHT_LONG_LONG) {
    *(unsigned long long int *)tokens_ar->addr =
        sign * (unsigned long long int)result;
  }
}

void danya_IntConverter(token *tokens_ar, long long int result, int sign) {
  if (tokens_ar->spec != 'p') {
    if (tokens_ar->lenght_t == NONE_LENGHT) {
      *(int *)tokens_ar->addr = sign * (int)result;
    } else if (tokens_ar->lenght_t == LENGHT_SHORT) {
      *(short int *)tokens_ar->addr = sign * (short int)result;
    } else if (tokens_ar->lenght_t == LENGHT_LONG) {
      *(long int *)tokens_ar->addr = sign * (long int)result;
    } else if (tokens_ar->lenght_t == LENGHT_LONG_LONG) {
      *(long long int *)tokens_ar->addr = sign * (long long int)result;
    }
  }
}

void danya_FloatConverter(token *tokens_ar, long double result) {
  if (tokens_ar->lenght_t == NONE_LENGHT)
    *(float *)tokens_ar->addr = (float)result;
  if (tokens_ar->lenght_t == LENGHT_LONG)
    *(double *)tokens_ar->addr = (double)result;
  if (tokens_ar->lenght_t == LENGHT_LONG_DOUBLE)
    *(long double *)tokens_ar->addr = (long double)result;
}