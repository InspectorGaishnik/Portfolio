#include "danya_string.h"

void *danya_to_upper(const char *str) {
  char *danya_upper_str = danya_NULL;
  if (str != danya_NULL) {
    danya_size_t length = danya_strlen(str);
    danya_upper_str = (char *)malloc(length + 1);
    if (danya_upper_str != danya_NULL) {
      danya_size_t counter = 0;
      while (counter < length) {
        danya_upper_str[counter] = danya_to_upper_single_char(str[counter]);
        counter++;
      }
      danya_upper_str[length] = '\0';
    }
  }
  return danya_upper_str;
}

void *danya_to_lower(const char *str) {
  char *danya_lower_str = danya_NULL;
  if (str != danya_NULL) {
    danya_size_t length = danya_strlen(str);
    danya_lower_str = (char *)malloc(length + 1);
    if (danya_lower_str != danya_NULL) {
      danya_size_t counter = 0;
      while (counter < length) {
        danya_lower_str[counter] = danya_to_lower_single_char(str[counter]);
        counter++;
      }
      danya_lower_str[length] = '\0';
    }
  }
  return danya_lower_str;
}

void *danya_insert(const char *src, const char *str, danya_size_t start_index) {
  if (src == danya_NULL || str == danya_NULL) return danya_NULL;

  danya_size_t src_len = danya_strlen(src);
  if (start_index > src_len) return danya_NULL;

  char *paste = danya_NULL;

  danya_size_t str_len = danya_strlen(str);
  danya_size_t uni_len = src_len + str_len;
  paste = calloc(uni_len + 1, sizeof(char));
  if (paste) {
    danya_size_t i = 0, j = 0, m = 0;
    while (i < uni_len) {
      if (i < start_index || !str[m]) {
        paste[i] = src[j++];
      } else {
        paste[i] = str[m++];
      }
      i++;
    }
    paste[uni_len] = '\0';
  }
  return paste;
}

void *danya_trim(const char *src, const char *trim_chars) {
  char *result = danya_NULL;
  if (src) {
    if (trim_chars && *trim_chars) {
      danya_size_t length = danya_strlen(src);
      danya_size_t chars_length = danya_strlen(trim_chars);
      danya_trim_left(&src, trim_chars, &length, chars_length);
      if (length) danya_trim_right(&src, trim_chars, &length, chars_length);
      result = (char *)malloc(sizeof(char) * (length + 1));
      if (result) {
        danya_size_t counter = 0;
        while (counter < length + 1) {
          if (counter < length)
            result[counter] = src[counter];
          else
            result[counter] = '\0';
          counter++;
        }
      }
    } else {
      result = danya_trim(src, " \t\n");
    }
  }
  return result;
}
