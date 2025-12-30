#include "../H-files/danya_string.h"

static int danya_ScienceNotationFinder(const char *buffer);
static long double danya_atof(const char *buffer);
static long double danya_ScienceNotattionApplyer(long double result,
                                               const char *buffer);
static int danya_SymbolSearcher(const char *buff, const char *pat);
static int danya_InfNanSearching(const char *buffer);
static long double danya_InfNanReturner(const char *buffer);

long double danya_strtold(const char *buffer) {
  long double result = 0.0;
  int includes_inf_nan = danya_InfNanSearching(buffer);

  if (!includes_inf_nan) {
    result = danya_atof(buffer);
    if (danya_ScienceNotationFinder(buffer))
      result = danya_ScienceNotattionApplyer(result, buffer);
  }
  return (includes_inf_nan) ? danya_InfNanReturner(buffer) : result;
}

static int danya_SymbolSearcher(const char *buff, const char *pat) {
  int found = 0;
  int length = (int)danya_strlen(pat);
  int i = 0;
  while (buff[i] && !found) {
    int counter = 0;
    int j = 0;
    while ((j < length) && !found) {
      if ((buff[i] == (pat[j] - 'A') + 'a') ||
          (buff[i] == (pat[j] - 'a') + 'A') || pat[j] == buff[i]) {
        counter++;
        i++;
      }
      if (length == counter) {
        found = 1;
      }
      j++;
    }
    i++;
  }
  return found;
}

static int danya_InfNanSearching(const char *buffer) {
  bool find_flag = false;

  int find_inf = danya_SymbolSearcher(buffer, "inf");
  int find_nan = danya_SymbolSearcher(buffer, "nan");

  if (find_inf || find_nan) find_flag = true;

  return find_flag;
}

static long double danya_InfNanReturner(const char *buffer) {
  int result = 0;
  int found = 0;
  int i = 0;
  while (buffer[i] && !found) {
    if (buffer[i] == 'i' || buffer[i] == 'I') {
      result = 1;
      found = 1;
    } else if (buffer[i] == 'n' || buffer[i] == 'N') {
      result = 2;
      found = 1;
    }
    i++;
  }
  return (result == 1) ? INFINITY : NAN;
}

static long double danya_ScienceNotattionApplyer(long double result,
                                               const char *buffer) {
  char sign = '+';
  int exponent = 0;
  char *ptr = (char *)buffer;
  while (*ptr) {
    if (*ptr == 'e' || *ptr == 'E') {
      sign = *(ptr + 1);

      exponent = danya_atoi(ptr + 2);
    }
    ptr++;
  }

  while (exponent) {
    if (sign == '-')
      result /= 10.0;
    else
      result *= 10.0;
    exponent--;
  }
  return result;
}

static int danya_ScienceNotationFinder(const char *buffer) {
  int result = 0;
  char *ptr = (char *)buffer;
  while (*ptr && !result) {
    if (danya_strspn(ptr, "eE")) result = 1;
    ptr++;
  }
  return result;
}

static long double danya_atof(const char *buffer) {
  long double fractional_part = 0.0;
  char *ptr = (char *)buffer;
  int minus_flag = (*ptr == '-');
  if (*ptr == '-' || *ptr == '+') ptr++;
  double result = danya_atoi(ptr);
  while (danya_isdigit(*ptr)) ptr++;
  if (*ptr == '.') {
    ptr++;
    int trailing_zeros = danya_strspn(ptr, "0");
    fractional_part = danya_atoi(ptr);
    int temp_fractional = (int)fractional_part;
    while (temp_fractional) {
      fractional_part /= 10.0;
      temp_fractional /= 10;
    }
    while (trailing_zeros) {
      fractional_part /= 10.0;
      trailing_zeros--;
    }
  }
  result += fractional_part;
  return minus_flag ? -result : result;
}