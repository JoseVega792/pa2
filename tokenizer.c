#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Return true (non-zero) if c is the delimiter character
   previously chosen by the user.
   Zero terminators are not printable (therefore false) */
bool delim_character(char c, char delim)
{
   return c == delim;
}

/* Return true (non-zero) if c is a non-delimiter
   character.
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c, char delim)
{
   return c != delim;
}

/* Returns a pointer to the first character of the next
   word starting with a non-delimiter character. Return a zero pointer if
   str does not contain any words. ""*/
char *word_start(char *str, char delim)
{
   if (str[0] == '\0')
   {
      return str;
   }

   int i = 0;
   while (*(str + i) != '\0')
   {
      if (*(str + i) == delim && *(str + i + 1) != delim)
      {
         return str + i + 1;
      }
      i++;
   }

   return str;
}

/* Returns a pointer to the first delimiter character of the zero
   terminated string*/
char *end_word(char *str, char delim)
{
   if (str[0] == '\0')
   {
      return str;
   }

   int i = 0;
   while (*(str + i) != '\0')
   {
      if (*(str + i) == delim)
      {
         return str + i;
      }
      i++;
   }
   return str + i;
}

/* Counts the number of words or tokens*/
int count_tokens(char *str, char delim)
{
   if (str[0] == '\0')
   {
      return 0;
   }

   while (*str == delim)
   {
      str++;
   }

   int i = 0;
   int counter = 0;
   while (*(str + i) != '\0')
   {
      if (*(str + i) == delim && *(str + i + 1) != delim || *(str + i + 1) == '\0')
      {
         counter += 1;
      }
      i++;
   }

   return counter;
}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len, char delim)
{
   char *new_string = malloc((len + 1) * sizeof(char));

   int i = 0;
   while (i != len)
   {
      if (inStr[i] != delim)
      {
         new_string[i] = inStr[i];
      }
      i++;
   }

   *(new_string + i) = '\0';
   return new_string;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated
   delimiter-separated tokens from zero-terminated str.
   For example, tokenize("hello world string"), with a character delimiter
   of a space " " would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string"
     tokens[3] = 0
*/
char **tokenize(char *str, char delim)
{
   int tokensCount = count_tokens(str, delim);
   char **tokens = malloc((tokensCount + 1) * sizeof(char *));

   while (*str == delim)
   {
      str++;
   }

   char *pointStart = str;
   int tokenLen = end_word(str, delim) - str;

   int iter = 0;
   printf("%d", tokensCount);
   for (int i = 0; i < tokensCount; i++)
   {
      tokens[i] = copy_str(pointStart, tokenLen, delim);
      pointStart = word_start(pointStart, delim);
      tokenLen = end_word(pointStart, delim) - pointStart;
      iter++;
   }

   tokens[tokensCount] = "";
   return tokens;
}

void print_all_tokens(char **tokens)
{

   int i = 0;
   while (*(*(tokens + i)) != '\0')
   {
      printf("Tokens[%d] = \"%s\"\n", i, tokens[i]);
      i++;
   }
   printf("Tokens[%d] = 0\n", i++);
}