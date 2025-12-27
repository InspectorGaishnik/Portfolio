#ifndef danya_SSCANF_H
#define danya_SSCANF_H

typedef enum width_t { NONE_WIDTH, WIDTH_NUMBER, WIDTH_AST } width_t;

typedef enum lenght_t {
  NONE_LENGHT,
  LENGHT_SHORT,
  LENGHT_LONG,
  LENGHT_LONG_LONG,
  LENGHT_DOUBLE,
  LENGHT_LONG_DOUBLE
} lenght_t;

typedef struct token {
  void *addr;
  width_t width;
  unsigned int width_n;
  lenght_t lenght_t;
  char buff[512];
  char spec;
} token;

int danya_sscanf(const char *str, const char *format, ...);

// Helper functions

int danya_CheckStringEOF(const char *src);
void danya_WriteCharToBuff(char **str, const char *chars, char *buff,
                         int16_t width, int start_ind);
int danya_isspace(char c);
void danya_UnsignConverter(token *tokens_ar, unsigned long long int result,
                         int sign);
void danya_IntConverter(token *tokens_ar, long long int result, int sign);
void danya_FloatConverter(token *tokens_ar, long double result);
int danya_isalpha(char c);

// Token parsing

token danya_ParseTokensFSTR(char **fstr, va_list *va);
void danya_ParseWidthFSTR(char **fstr, token *tokens_ar);
void danya_ParseLenghtFSTR(char **fstr, token *tokens_ar);
void danya_ParseSpecFSTR(char **fstr, token *tokens_ar);
int danya_ParseNumberFSTR(char **fstr);
void danya_SkipSpaces(char **str);
void danya_SkipChars(char **src, int *fail, const token *tokens_ar);

// Write to memory

void danya_WriteTokensToMem(char **src, token *tokens, int tok_len, int *result);
void danya_WriteCharToMem(char **str, int *result, token *tokens_ar, int *fail);
void danya_WriteIntToMem(char **str, int *fail_flag, int *result,
                       token *tokens_ar);
void danya_WriteUnspecIntToMem(char **str, int *fail_flag, int *result,
                             token *tokens_ar);
void danya_WriteFloatToMem(char **str, int *result, token *tokens_ar);
void danya_WriteStrToMem(char **str, const int *fail_flag, int *result,
                       token *tokens_ar);
void danya_WriteUnsignIntToMem(char **str, int *fail_flag, int *result,
                             token *tokens_ar);
void danya_WriteHexOctToMem(char **str, int *fail_flag, int *result,
                          token *tokens_ar, int base);

#endif