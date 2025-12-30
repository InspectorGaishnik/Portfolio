#include "../H-files/danya_string.h"

int danya_sprintf(char *str, const char *format, ...) {
  flags flag_list = {0};
  va_list va;
  va_start(va, format);

  char *str_beginning = str;
  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
    } else {
      format++;
      danya_memset(&flag_list, 0, sizeof(flags));
      format = danya_ParseFlags(format, &flag_list);
      format = danya_ParseWidth(format, &flag_list, va);
      format = danya_ParsePrecision(format, &flag_list, va);
      format = danya_ParseLenght(format, &flag_list);

      flag_list.specifier = *format;
      format++;

      char buff[BUFF_SIZE] = {'\0'};

      danya_ProcessValue(flag_list, buff, va);
      int i = 0;
      while (buff[i]) {
        *str = buff[i];
        i++;
        str++;
      }

      if (flag_list.specifier == 'n') {
        int *return_ar = va_arg(va, int *);
        *return_ar = str - str_beginning;
      }
    }
  }
  *str = '\0';
  va_end(va);
  if (danya_strcmp(str_beginning, "0x0") == 0) {
#if defined __linux__
    danya_strcpy(str_beginning, "(nil)");
    str = str_beginning + 5;
#endif
  }
  return str - str_beginning;
}

const char *danya_ParseFlags(const char *format, flags *flag_list) {
  while (*format == '-' || *format == '+' || *format == ' ' || *format == '0' ||
         *format == '#') {
    switch (*format) {
      case '0':
        flag_list->zero = true;
        break;
      case '-':
        flag_list->minus = true;
        break;
      case '+':
        flag_list->plus = true;
        break;
      case ' ':
        flag_list->space = true;
        break;
      case '#':
        flag_list->hash = true;
        break;
    }
    format++;
  }
  return format;
}

const char *danya_ParseWidth(const char *format, flags *flag_list, va_list va) {
  if (*format == '*') {
    format++;
    flag_list->width = va_arg(va, int);
  } else if (danya_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    int i = 0;
    while (danya_isdigit(*format)) {
      tmp[i] = *format;
      i++;
      format++;
    }
    flag_list->width = danya_atoi(tmp);
  }
  return format;
}

const char *danya_ParsePrecision(const char *format, flags *flag_list,
                               va_list va) {
  if (*format == '.') {
    flag_list->set_precision = true;
    format++;
  }

  if (*format == '*') {
    format++;
    flag_list->precision = va_arg(va, int);
  }

  if (danya_isdigit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    int i = 0;
    while (danya_isdigit(*format)) {
      tmp[i] = *format;
      i++;
      format++;
    }
    flag_list->precision = danya_atoi(tmp);
  }
  return format;
}

const char *danya_ParseLenght(const char *format, flags *flag_list) {
  switch (*format) {
    case 'h':
      flag_list->length = 'h';
      format++;
      break;
    case 'l':
      flag_list->length = 'l';
      format++;
      break;
    case 'L':
      flag_list->length = 'L';
      format++;
      break;
  }
  return format;
}

void danya_ProcessValue(flags flag_list, char *buff, va_list va) {
  if (flag_list.specifier == 'd' || flag_list.specifier == 'i')
    danya_IntParser(flag_list, buff, va);
  else if (flag_list.specifier == 'u')
    danya_UnsignParser(flag_list, buff, va);
  else if (flag_list.specifier == 'o')
    danya_OctalParser(flag_list, buff, va);
  else if (flag_list.specifier == 'x' || flag_list.specifier == 'X')
    danya_HexParser(flag_list, buff, va);
  else if (flag_list.specifier == '%')
    buff[0] = '%';
  else if (flag_list.specifier == 'c')
    danya_CharParser(flag_list, buff, va);
  else if (flag_list.specifier == 's')
    danya_StringParser(flag_list, buff, va);
  else if (flag_list.specifier == 'p')
    danya_PointerParser(flag_list, buff, va);
  else if (flag_list.specifier == 'f')
    danya_FloatParser(flag_list, buff, va);
  else if (flag_list.specifier == 'e' || flag_list.specifier == 'E')
    danya_MantissParser(flag_list, buff, va);
  else if (flag_list.specifier == 'g' || flag_list.specifier == 'G')
    danya_FloatgGParser(flag_list, buff, va);
  if (flag_list.specifier == 'G' || flag_list.specifier == 'E' ||
      flag_list.specifier == 'X')
    danya_to_upper_string(buff);
}

void danya_IntParser(flags flag_list, char *buff, va_list va) {
  int64_t value = va_arg(va, int64_t);
  switch (flag_list.length) {
    case 0:
      value = (int32_t)value;
      break;
    case 'h':
      value = (int16_t)value;
      break;
  }
  danya_IntNumberToString(value, buff, 10);
  danya_ApplyPrecision(buff, flag_list);
  danya_ApplyFlags(buff, flag_list);
}

void danya_IntNumberToString(int64_t value, char *return_ar, int base) {
  char tmp[BUFF_SIZE] = {'\0'};
  int index = BUFF_SIZE - 2;
  bool negative = value < 0 ? 1 : 0;
  value = negative ? -value : value;

  if (value == 0) tmp[index] = '0';

  while (value > 0) {
    index--;
    tmp[index] = "0123456789abcdef"[value % base];
    value /= base;
  }

  int i = 0;
  while (tmp[index]) {
    if (negative && i == 0) return_ar[i++] = '-';
    return_ar[i] = tmp[index];
    index++;
    i++;
  }
}

void danya_ApplyPrecision(char *buff, flags flag_list) {
  char tmp[BUFF_SIZE] = {'\0'};
  int sign = 0;
  int length = danya_strlen(buff);

  if (buff[0] == '-') {
    tmp[0] = '-';

    length--;
    sign = 1;
  }

  if (flag_list.precision > length) {
    int index = sign;
    while (index < flag_list.precision - length + sign) {
      tmp[index] = '0';
      index++;
    }
    int i = sign;
    while (buff[i]) {
      tmp[index] = buff[i];
      i++;
      index++;
    }
    danya_strcpy(buff, tmp);
  }

  if (flag_list.set_precision && flag_list.precision == 0 &&
      danya_IntSpecCheck(flag_list.specifier) && buff[0] == '0')
    buff[0] = '\0';
}

bool danya_IntSpecCheck(char c) {
  char specifs[] = {'d', 'i', 'o', 'u', 'x', 'X'};
  bool result = false;
  danya_size_t i = 0;
  while (i < sizeof(specifs) && !result) {
    if (specifs[i] == c) {
      result = true;
    }
    i++;
  }
  return result;
}

void danya_ApplyFlags(char *buff, flags flag_list) {
  char tmp[BUFF_SIZE + 1] = {'\0'};
  if (flag_list.plus && flag_list.specifier != 'u') {
    tmp[0] = buff[0] == '-' ? buff[0] : '+';
    danya_strcpy(tmp + 1, buff[0] == '-' ? buff + 1 : buff);
    danya_strcpy(buff, tmp);
  } else if (flag_list.space && buff[0] != '-' && flag_list.specifier != 'u') {
    tmp[0] = ' ';
    danya_strcpy(tmp + 1, buff);
    danya_strcpy(buff, tmp);
  }

  if (flag_list.width > (int)danya_strlen(buff)) {
    int index = flag_list.width - danya_strlen(buff);
    if (!flag_list.minus) {
      danya_memset(tmp, flag_list.zero ? '0' : ' ', index);
      danya_strcpy(tmp + index, buff);
    } else {
      danya_strcpy(tmp, buff);
      danya_memset(tmp + danya_strlen(tmp), ' ', index);
    }
    danya_strcpy(buff, tmp);
  }
}

void danya_UnsignNumberToString(uint64_t value, char *return_ar, int base) {
  char buff[BUFF_SIZE + 1] = {'\0'};
  int index = BUFF_SIZE - 1;

  if (value == 0) {
    buff[index] = '0';
    index--;
  }

  while (value && index) {
    buff[index] = "0123456789abcdef"[value % base];
    index--;
    value /= base;
  }

  int i = 0;
  while (buff[index + 1]) {
    return_ar[i] = buff[index + 1];
    index++;
    i++;
  }
}

void danya_UnsignParser(flags flag_list, char *buff, va_list va) {
  uint64_t value = va_arg(va, uint64_t);
  switch (flag_list.length) {
    case 'h':
      value = (uint16_t)value;
      break;
    case 'l':
      value = (uint64_t)value;
      break;
    case 0:
      value = (uint32_t)value;
      break;
  }
  danya_UnsignNumberToString(value, buff, 10);
  danya_ApplyPrecision(buff, flag_list);
  danya_ApplyFlags(buff, flag_list);
}

void danya_OctalParser(flags flag_list, char *buff, va_list va) {
  buff[0] = '0';
  danya_IntNumberToString(va_arg(va, int64_t), buff + flag_list.hash, 8);
  danya_ApplyPrecision(buff, flag_list);
  danya_ApplyFlags(buff, flag_list);
}

bool danya_CheckAllZeroes(const char *buff) {
  bool result = true;
  int i = 0;
  while (buff[i] && result) {
    if (buff[i] != '0') result = false;
    i++;
  }
  return result;
}

void danya_HexParser(flags flag_list, char *buff, va_list va) {
  uint64_t value = va_arg(va, uint64_t);
  switch (flag_list.length) {
    case 0:
      value = (uint32_t)value;
      break;
    case 'h':
      value = (uint16_t)value;
      break;
    case 'l':
      value = (uint64_t)value;
      break;
  }
  danya_UnsignNumberToString(value, buff, 16);
  danya_ApplyPrecision(buff, flag_list);
  if (flag_list.hash) danya_0xPrefAdd(buff, flag_list);
  danya_ApplyFlags(buff, flag_list);
}

void danya_0xPrefAdd(char *buff, flags flag_list) {
  if (!danya_CheckAllZeroes(buff) || flag_list.specifier == 'p') {
    danya_memmove(buff + 2, buff, danya_strlen(buff));
    buff[0] = '0';
    buff[1] = 'x';
  }
}

void danya_CharParser(flags flag_list, char *buff, va_list va) {
  if (flag_list.length == 'l') {
    wchar_t w_c = va_arg(va, wchar_t);
    danya_FormatWchar(flag_list, buff, w_c);
  } else {
    char c;
    c = va_arg(va, int);
    danya_FormatChar(flag_list, buff, c);
  }
}

void danya_FormatWchar(flags flag_list, char *buff, wchar_t w_c) {
  const wchar_t w_str[2] = {w_c, L'\0'};
  char tmp[BUFF_SIZE] = {'\0'};
  wcstombs(tmp, w_str, BUFF_SIZE);
  if (!flag_list.minus && flag_list.width) {
    for (danya_size_t i = 0; i < flag_list.width - danya_strlen(tmp); i++)
      buff[i] = ' ';
    danya_strcat(buff, tmp);
  } else if (flag_list.width) {
    danya_strcpy(buff, tmp);
    for (int i = danya_strlen(buff); i < flag_list.width; i++) buff[i] = ' ';
  } else
    danya_strcpy(buff, tmp);
}

void danya_FormatChar(flags flag_list, char *buff, char c) {
  if (!flag_list.minus && flag_list.width) {
    int i = 0;
    while (i < flag_list.width) {
      buff[i] = ' ';
      if (i == flag_list.width - 1) buff[i] = c;
      i++;
    }
  } else if (flag_list.width) {
    buff[0] = c;
    int i = 1;
    while (i < flag_list.width) {
      buff[i] = ' ';
      i++;
    }
  } else
    buff[0] = c;
}

void danya_StringParser(flags flag_list, char *buff, va_list va) {
  if (flag_list.length == 'l') {
    const wchar_t *wstr = va_arg(va, wchar_t *);
    danya_FormatWideString(flag_list, buff, wstr);
  } else {
    const char *str = va_arg(va, char *);
    danya_FormatString(flag_list, buff, str);
  }
}

void danya_FormatString(flags flag_list, char *buff, const char *str) {
  char tmp[BUFF_SIZE] = {'\0'};
  danya_strcpy(tmp, str);
  if (flag_list.set_precision) tmp[flag_list.precision] = '\0';
  int length = danya_strlen(tmp);
  int shift = flag_list.width - length;
  if (flag_list.minus && shift > 0) {
    danya_strcpy(buff, tmp);
    danya_memset(buff + length, ' ', shift);
  } else if (shift > 0) {
    danya_memset(buff, ' ', shift);
    danya_strcpy(buff + shift, tmp);
  } else
    danya_strcpy(buff, tmp);
}

void danya_FormatWideString(flags flag_list, char *buff, const wchar_t *wstr) {
  char tmp[BUFF_SIZE] = {'\0'};
  char str[BUFF_SIZE] = {'\0'};
  wcstombs(str, wstr, BUFF_SIZE);
  danya_strcpy(tmp, str);
  if (flag_list.set_precision) tmp[flag_list.precision] = '\0';
  int len = danya_strlen(tmp);
  int shift = flag_list.width - len;
  if (flag_list.minus && shift > 0) {
    danya_strcpy(buff, tmp);
    danya_memset(buff + len, ' ', shift);
  } else if (shift > 0) {
    danya_memset(buff, ' ', shift);
    danya_strcpy(buff + shift, tmp);
  } else
    danya_strcpy(buff, tmp);
}

void danya_PointerParser(flags flag_list, char *buff, va_list va) {
  danya_UnsignNumberToString(va_arg(va, uint64_t), buff, 16);
  danya_ApplyPrecision(buff, flag_list);
  danya_0xPrefAdd(buff, flag_list);
  danya_ApplyFlags(buff, flag_list);
}

void danya_FloatParser(flags flag_list, char *buff, va_list va) {
  long double value = 0;
  if (flag_list.length == 'L')
    value = va_arg(va, long double);
  else
    value = va_arg(va, double);
  if (!flag_list.set_precision) flag_list.precision = 6;
  danya_DoubleToStringConverter(value, buff, flag_list);
  danya_ApplyFlags(buff, flag_list);
}

void danya_DoubleToStringConverter(long double value, char *return_ar,
                                 flags flag_list) {
  char buff[BUFF_SIZE] = {'\0'};
  int index = BUFF_SIZE - 2;
  bool negative = value < 0 ? 1 : 0;
  value = negative ? value * -1 : value;
  long double whole = 0, fraction = modfl(value, &whole);
  if (flag_list.precision == 0) {
    whole = round(value);
    fraction = 0;
  }
  char fractions[BUFF_SIZE] = {'\0'};
  for (int i = 0; i < flag_list.precision; i++) {
    fraction = fraction * 10;
    fractions[i] = (int)fraction + '0';
  }
  long long right = roundl(fraction), left = whole;
  if (!right) {
    int i = 0;
    while (i < flag_list.precision) {
      buff[index] = '0';
      index--;
      i++;
    }
  } else {
    int i = danya_strlen(fractions);
    while (right || i > 0) {
      buff[index] = (int)(right % 10 + 0.05) + '0';
      right /= 10;
      index--;
      i--;
    }
  }
  if ((flag_list.set_precision && flag_list.precision != 0) || (int)fraction ||
      (!flag_list.set_precision && value == 0) || danya_strlen(fractions))
    buff[index--] = '.';
  if (!left) {
    buff[index] = '0';
    index--;
  } else
    while (left) {
      buff[index] = (int)(left % 10) + '0';
      left /= 10;
      index--;
    }
  int i = 0;
  while (buff[index + 1]) {
    if (negative && i == 0) {
      return_ar[i] = '-';
      i++;
    }
    return_ar[i] = buff[index + 1];
    index++;
    i++;
  }
}

void danya_MantissParser(flags flag_list, char *buff, va_list va) {
  long double value = 0;
  if (flag_list.length == 'L')
    value = va_arg(va, long double);
  else
    value = va_arg(va, double);
  int power = 0;
  char sign = (int)value == 0 ? '-' : '+';
  if ((int)value - value)
    while ((int)value == 0) {
      power++;
      value *= 10;
    }
  else
    sign = '+';
  while ((int)value / 10 != 0) {
    power++;
    value /= 10;
  }
  if (!flag_list.set_precision) flag_list.precision = 6;
  danya_DoubleToStringConverter(value, buff, flag_list);
  danya_AddMantiss(buff, power, sign);
  danya_ApplyFlags(buff, flag_list);
}

void danya_AddMantiss(char *str, int power, char sign) {
  int length = danya_strlen(str);
  str[length] = 'e';
  str[length + 1] = sign;
  str[length + 3] = power % 10 + '0';
  power /= 10;
  str[length + 2] = power % 10 + '0';
  str[length + 4] = '\0';
}

void danya_FloatgGParser(flags flag_list, char *buff, va_list va) {
  long double value = 0;
  if (flag_list.length == 'L')
    value = va_arg(va, long double);
  else
    value = va_arg(va, double);
  if (!flag_list.set_precision) flag_list.precision = 6;
  if (flag_list.precision == 0) flag_list.precision = 1;
  int mem_precision = flag_list.precision;
  long double m_val = value;
  int power = 0;
  if ((int)value - value)
    while ((int)m_val == 0) {
      power++;
      m_val *= 10;
    }
  if (power > 4) {
    flag_list.precision = 0;
    danya_DoubleToStringConverter(m_val, buff, flag_list);
  } else {
    flag_list.precision = 10;
    danya_DoubleToStringConverter(value, buff, flag_list);
  }
  danya_ApplyGgPrecision(buff, mem_precision);
  if (power > 4) danya_AddMantiss(buff, power, '-');
  danya_LastZeroesRemover(buff);
  danya_ApplyFlags(buff, flag_list);
}

void danya_LastZeroesRemover(char *buff) {
  int length = danya_strlen(buff);
  char *dot = danya_strchr(buff, '.');
  if (dot) {
    int flag = 0;
    int i = length - 1;
    while (buff[i] != '.' && !flag) {
      if (buff[i] == '0')
        buff[i] = '\0';
      else
        flag = 1;
      i--;
    }
    if (dot[1] == '\0') dot[0] = '\0';
  }
}

void danya_ApplyGgPrecision(char *buff, int precision) {
  int sig_digs = 0;
  int flag = 0;
  danya_size_t length = danya_strlen(buff);
  int not_zero_found = 0;
  danya_size_t i = 0;
  while (i < danya_strlen(buff) && !flag) {
    if (!((buff[i] == '0' && !not_zero_found) || buff[i] == '.')) {
      not_zero_found = 1;
      if (danya_isdigit(buff[i])) sig_digs++;
      if (sig_digs == precision && i + 1 < length) {
        int next = buff[i + 1] == '.' ? 2 : 1;
        buff[i] = buff[i + next] - '0' > 5 ? (char)(buff[i] + 1) : buff[i];
        buff[i + 1] = '\0';
        flag = 1;
      }
    }
    i++;
  }
}