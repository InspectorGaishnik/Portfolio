#include "../H-files/danya_string.h"

void *danya_memchr(const void *str, int c, danya_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  void *out = danya_NULL;
  int stop_flag = 0;
  danya_size_t i = 0;
  while (i < n && ptr && !stop_flag) {
    if (*ptr == (unsigned char)c) {
      out = ptr;
      stop_flag = 1;
    } else {
      ptr++;
      i++;
    }
  }
  return out;
}

int danya_memcmp(const void *str1, const void *str2, danya_size_t n) {
  unsigned char *s1 = (unsigned char *)str1;
  unsigned char *s2 = (unsigned char *)str2;
  int dif = 0;
  int stop_flag = 0;
  danya_size_t i = 0;
  while (i < n && !stop_flag) {
    dif = *s1 - *s2;
    if (*s1 != *s2)
      stop_flag = 1;
    else {
      s1++;
      s2++;
      i++;
    }
  }
  return dif;
}

void *danya_memcpy(void *dest, const void *src, danya_size_t n) {
  unsigned char *destination = (unsigned char *)dest;
  unsigned char *source = (unsigned char *)src;
  danya_size_t i = 0;
  while (i < n) {
    destination[i] = source[i];
    i++;
  }
  return dest;
}

void *danya_memset(void *str, int c, danya_size_t n) {
  char *str_tmp = str;
  for (danya_size_t i = 0; i < n; i++) {
    str_tmp[i] = c;
  }
  return str_tmp;
}

char *danya_strchr(const char *str, int c) {
  char ch = (char)c;
  char *result = danya_NULL;
  danya_size_t flag = 0;
  danya_size_t counter = 0;

  while (str[counter] != '\0' && !flag) {
    if (str[counter] == ch) {
      result = ((char *)str) + counter;
      flag = 1;
    }
    counter++;
  }

  if (ch == '\0') {
    result = ((char *)str) + counter;
  }

  return result;
}

char *danya_strncat(char *dest, const char *src, danya_size_t n) {
  danya_size_t length_of_dest = danya_strlen(dest);
  danya_size_t counter = 0;

  while (counter < n && src[counter]) {
    dest[length_of_dest + counter] = src[counter];
    counter++;
  }
  dest[length_of_dest + counter] = '\0';

  return dest;
}

int danya_strncmp(const char *str1, const char *str2, danya_size_t n) {
  int result = 0;
  danya_size_t counter = 0;
  int flag = 0;

  while (n > 0 && counter < n && !flag) {
    if (str1[counter] == '\0' || str1[counter] != str2[counter]) {
      result = str1[counter] - str2[counter];
      flag = 1;
    }
    counter++;
  }
  return result;
}

char *danya_strncpy(char *dest, const char *src, danya_size_t n) {
  danya_size_t counter = 0;

  while (counter < n) {
    if (src[counter]) {
      dest[counter] = src[counter];
    } else {
      dest[counter] = '\0';
    }
    counter++;
  }
  return dest;
}

danya_size_t danya_strcspn(const char *str1, const char *str2) {
  danya_size_t len = 0;
  int flag = 0;
  danya_size_t j;

  for (danya_size_t i = 0; (flag == 0) && (str1[i] != '\0'); i++) {
    for (j = 0; ((str2[j] != str1[i]) && (str2[j] != '\0')); j++);
    str2[j] == str1[i] ? flag = 1 : len++;
  }

  return len;
}

char *danya_strerror(int errnum) {
  static char err[danya_ERR_LENGTH] = "";

  if (errnum >= 0 && errnum < danya_ERR_LIST_SIZE) {
    const char *err_list[] = danya_ERR_LIST;
    danya_strncpy(err, err_list[errnum], danya_strlen(err_list[errnum]) + 1);
  } else {
#if defined __MACH__ || defined __APPLE__
    danya_sprintf(err, "Unknown error: %d", errnum);
#elif defined __linux__
    danya_sprintf(err, "No error information");
#endif
  }
  return err;
}

danya_size_t danya_strlen(const char *str) {
  danya_size_t count = 0;
  while (*str != '\0') {
    count++;
    str++;
  }
  return count;
}

char *danya_strpbrk(const char *str1, const char *str2) {
  char *result = danya_NULL;
  int stop_flag = 0;

  while (*str1 != '\0' && !stop_flag) {
    const char *temp = str2;
    while (*temp != '\0' && !stop_flag) {
      if (*str1 == *temp) {
        result = (char *)str1;
        stop_flag = 1;
      } else
        temp++;
    }
    if (!stop_flag) str1++;
  }
  return result;
}

char *danya_strrchr(const char *str, int c) {
  const char *last_enter = danya_NULL;

  while (*str != '\0') {
    if (*str == (char)c) {
      last_enter = str;
    }
    str++;
  }

  if (c == '\0') {
    last_enter = (char *)str;
  }

  return (char *)last_enter;
}

char *danya_strstr(const char *haystack, const char *needle) {
  if (*needle == '\0') {
    return (char *)haystack;
  }

  while (*haystack) {
    const char *h = haystack;
    const char *n = needle;

    while (*h && *n && (*h == *n)) {
      h++;
      n++;
    }

    if (*n == '\0') {
      return (char *)haystack;
    }

    haystack++;
  }

  return danya_NULL;
}

char *danya_strtok(char *str, const char *delim) {
  static char *last = danya_NULL;
  if (str != danya_NULL) {
    last = str;
  }

  if (last == danya_NULL) {
    return danya_NULL;
  }

  char *token_start = last;
  while (*token_start && danya_strchr(delim, *token_start)) {
    token_start++;
  }

  if (*token_start == '\0') {
    last = danya_NULL;
    return danya_NULL;
  }

  char *token_end = token_start;
  while (*token_end && !danya_strchr(delim, *token_end)) {
    token_end++;
  }

  if (*token_end) {
    *token_end = '\0';
    last = token_end + 1;
  } else {
    last = danya_NULL;
  }

  return token_start;
}
