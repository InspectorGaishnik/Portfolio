#include "../H-files/danya_string.h"

int danya_atoi(const char *str) {
  int res = 0, sign = 1, overflow = 0;
  while (*str == ' ') {
    str++;
  }
  if (*str == '-') {
    str++;
    sign = -1;
  }
  if (*str == '+') {
    str++;
  }
  while (*str && *str >= '0' && *str <= '9' && !overflow) {
    res = res * 10 + (*str - '0');
    if (res < 0) overflow = 1;
    str++;
  }
  if (overflow)
    res = sign > 0 ? INT32_MAX : INT32_MIN;
  else
    res *= sign;
  return res;
}

void *danya_memmove(void *dest, const void *src, danya_size_t n) {
  char *to = (char *)dest;
  char *from = (char *)src;
  char *tmp = (char *)malloc(sizeof(char) * n);

  if (tmp) {
    danya_memcpy(tmp, from, n);
    danya_memcpy(to, tmp, n);
    free(tmp);
  }

  return dest;
}

char *danya_strcat(char *dest, const char *src) {
  int dest_len = danya_strlen(dest);
  int counter = 0;

  while (src[counter]) {
    dest[dest_len + counter] = src[counter];
    counter++;
  }

  dest[dest_len + counter] = '\0';

  return dest;
}

int danya_strcmp(const char *str1, const char *str2) {
  int result = 0;

  if (str1 && str2) {
    int counter = 0;
    while (str1[counter] && str2[counter] == str1[counter]) counter++;
    result = str1[counter] - str2[counter];
  }

  return result;
}

char *danya_strcpy(char *dest, const char *src) {
  for (int counter = 0; src[counter]; counter++) dest[counter] = src[counter];
  dest[danya_strlen(src)] = '\0';
  return dest;
}

danya_size_t danya_strspn(const char *str1, const char *str2) {
  danya_size_t count = 0;
  while (*str1) {
    const char *temp = str2;
    int found = 0;
    while (*temp && !found) {
      if (*str1 == *temp) {
        found = 1;
      }
      temp++;
    }
    if (found) {
      count++;
      str1++;
    } else {
      str1 = "";
    }
  }
  return count;
}

int danya_isdigit(char c) { return (c >= '0' && c <= '9'); }

unsigned long long int danya_strntollu(const char *string, char **endptr,
                                     int basis, int n_byte) {
  unsigned long long res = 0;
  short sign = 1;
  if (endptr) *endptr = danya_NULL;
  char dict[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if (*string == '-') {
    sign = -1;
    string++;
  }
  if (basis == 16 &&
      (!danya_strncmp(string, "0x", 2) || !danya_strncmp(string, "0X", 2)))
    string += 2;
  long long val;
  short exit = 0;
  while (*string && n_byte && !exit) {
    char *tmp2;
    char current_sym =
        (*string >= 'a' && *string <= 'z') ? *string - 'a' + 'A' : *string;
    tmp2 = danya_strchr(dict, (int)current_sym);
    if (!tmp2)
      exit = 1;
    else {
      val = (tmp2 - dict) / sizeof(char);
      if (val >= basis)
        exit = 1;
      else {
        res = res * basis + val;
        string++;
        n_byte--;
      }
    }
    if (exit) *endptr = (char *)string;
  }
  return res * sign;
}

void danya_to_upper_string(char *str) {
  while (*str) {
    if (*str >= 'a' && *str <= 'z') *str = *str - 'a' + 'A';
    str++;
  }
}

char danya_to_upper_single_char(char c) {
  char result = c;
  if (c >= 'a' && c <= 'z') {
    result = c - ('a' - 'A');
  }
  return result;
}

char danya_to_lower_single_char(char c) {
  char result = c;
  if (c >= 'A' && c <= 'Z') {
    result = c + ('a' - 'A');
  }
  return result;
}

void danya_trim_left(const char **src, const char *trim_chars,
                   danya_size_t *src_len, const danya_size_t trim_chars_len) {
  danya_size_t counter = 0;
  while (src && counter != trim_chars_len) {
    if ((**src) == trim_chars[counter]) {
      (*src)++;
      (*src_len) -= 1;
      counter = 0;
    } else
      counter++;
  }
}

void danya_trim_right(const char **src, const char *trim_chars,
                    danya_size_t *src_len, const danya_size_t trim_chars_len) {
  danya_size_t counter = 0;
  danya_size_t i = (*src_len) - 1;
  while (src && counter != trim_chars_len) {
    if ((*src)[i] == trim_chars[counter]) {
      i--;
      (*src_len)--;
      counter = 0;
    } else
      counter++;
  }
}