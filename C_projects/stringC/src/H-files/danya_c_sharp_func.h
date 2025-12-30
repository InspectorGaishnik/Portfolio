#ifndef danya_C_SHARP_FUNC
#define danya_C_SHARP_FUNC

void *danya_to_upper(const char *str);
void *danya_to_lower(const char *str);
void *danya_trim(const char *src, const char *trim_chars);
void *danya_insert(const char *src, const char *str, danya_size_t start_index);

#endif
