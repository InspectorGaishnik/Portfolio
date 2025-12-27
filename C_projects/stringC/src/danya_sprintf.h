#ifndef danya_SPRINTF_H
#define danya_SPRINTF_H

typedef struct {
  bool minus;
  bool plus;
  bool space;
  bool zero;
  bool hash;
  int precision;
  int set_precision;
  int width;
  char length;
  char specifier;
} flags;

int danya_sprintf(char *str, const char *format, ...);

// helper functions

void danya_IntNumberToString(int64_t value, char *return_ar, int base);
void danya_UnsignNumberToString(uint64_t value, char *return_ar, int base);
bool danya_IntSpecCheck(char c);
bool danya_CheckAllZeroes(const char *buff);
void danya_0xPrefAdd(char *buff, flags flag_list);
void danya_DoubleToStringConverter(long double value, char *return_ar,
                                 flags flag_list);
void danya_AddMantiss(char *str, int pow, char sign);
void danya_LastZeroesRemover(char *buff);

// parse format

const char *danya_ParseFlags(const char *format, flags *flag_list);
const char *danya_ParseWidth(const char *format, flags *flag_list, va_list va);
const char *danya_ParsePrecision(const char *format, flags *flag_list,
                               va_list va);
const char *danya_ParseLenght(const char *format, flags *flag_list);

// parse values

void danya_ProcessValue(flags flag_list, char *buff, va_list va);
void danya_IntParser(flags, char *buff, va_list va);
void danya_UnsignParser(flags flag_list, char *buff, va_list va);
void danya_OctalParser(flags flag_list, char *buff, va_list va);
void danya_HexParser(flags flag_list, char *buff, va_list va);
void danya_CharParser(flags flag_list, char *buff, va_list va);
void danya_StringParser(flags flag_list, char *buff, va_list va);
void danya_PointerParser(flags flag_list, char *buff, va_list va);
void danya_FloatParser(flags flag_list, char *buff, va_list va);
void danya_MantissParser(flags flag_list, char *buff, va_list va);
void danya_FloatgGParser(flags flag_list, char *buff, va_list va);

// format values

void danya_ApplyPrecision(char *buff, flags flag_list);
void danya_ApplyFlags(char *buff, flags flag_list);
void danya_ApplyGgPrecision(char *buff, int precision);
void danya_FormatChar(flags flag_list, char *buff, char c);
void danya_FormatWchar(flags flag_list, char *buff, wchar_t w_c);
void danya_FormatWideString(flags flag_list, char *buff, const wchar_t *wstr);
void danya_FormatString(flags flag_list, char *buff, const char *str);

#endif
