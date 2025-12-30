#ifndef danya_COMMON_FUNC
#define danya_COMMON_FUNC

// Additional functions for Part 2 (sprintf)

int danya_atoi(const char *str);
void *danya_memmove(void *dest, const void *src, danya_size_t n);
char *danya_strcat(char *dest, const char *src);
int danya_strcmp(const char *str1, const char *str2);
char *danya_strcpy(char *dest, const char *src);
danya_size_t danya_strspn(const char *str1, const char *str2);
int danya_isdigit(char c);
void danya_to_upper_string(char *str);

// Additional functions for Part 4 (sscanf)

unsigned long long int danya_strntollu(const char *string, char **endptr,
                                     int basis, int n_byte);
long double danya_strtold(const char *buffer);

// Additional functions for Part 5

char danya_to_upper_single_char(char c);
char danya_to_lower_single_char(char c);
void danya_trim_left(const char **src, const char *trim_chars,
                   danya_size_t *src_len, const danya_size_t trim_chars_len);
void danya_trim_right(const char **src, const char *trim_chars,
                    danya_size_t *src_len, const danya_size_t trim_chars_len);

#endif
