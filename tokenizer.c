// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Return true (non-zero) if c is the delimiter character
   previously chosen by the user.
   Zero terminators are not printable (therefore false) */
bool delim_character(char c, char delim)
{
   if (c == delim) // Here I check if it is a delim
   {
      return true;
   }
   return false;
}

/* Return true (non-zero) if c is a non-delimiter
   character.
   Zero terminators are not printable (therefore false) */
bool non_delim_character(char c, char delim)
{
   if (c != delim) // Here we check if it is a delim
   {
      return true;
   }
   return false;
}

/* Returns a pointer to the first character of the next
   word starting with a non-delimiter character. Return a zero pointer if
   str does not contain any words.*/
char *word_start(char *str, char delim)
{
   int i = 0;
   while (str + i)
   {
      if (delim_character(*(str + i), delim) && non_delim_character(*(str + i + 1), delim))//Here I check for the delim character and make sure the next one is not a delim char.
      {
         return str + i + 1; 
      }
      i++;
   }
   return 0;
}

/* Returns a pointer to the first delimiter character of the zero
   terminated string*/
char *end_word(char *str, char delim)
{
   int i = 0;
   while (str + i)
   {
      if (delim_character(*(str + i), delim)) // Here I check if the delim char 
      {
         return str + i;
      }
      i++;
   }
   return str;
}

/* Counts the number of words or tokens*/
int count_tokens(char *str, char delim)
{
   int count = 0;
   int i = 0;
   while (*(str + i)) //Here I have a while loop until we do not have a charater.
   {
      if (*(str + i) == delim && *(str + i + 1) != delim || *(str + i + 1) == '\0')
      {
         count++;
      }
      i++;
   }
   return count;
}

/* Returns a freshly allocated new zero-terminated string
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len, char delim)
{
   int i = 0;
   char *word = malloc((len + 1) * sizeof(char)); // Here I allocate space to create our array of characters making a word/string
   while (*inStr != '\0' && i <= len && non_delim_character(*inStr, delim)) // Here I check if the string is the end and if i is less than or rqual the length and is not a delim char.
   {
      word[i] = *inStr; // This is where I insert the char into the char array
      inStr++;
      i++;
   }
   word[i] = '\0'; // This is so we know the terminal point
   return word;
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
   while(*str == delim){ // This case is done in case the first inputs are your delimeter consecutively.
      str++;
   }
   int len = count_tokens(str, delim); // Here I get the len of the amount of tokens for a loop.
   char **tokens = malloc((len + 1) * sizeof(char *)); // Here I allocate space to create our array of characters making a word/string
   for (int i = 0; i < len; i++)
   {
      char *end = end_word(str, delim);
      tokens[i] = copy_str(str, end - str, delim); // Here I push the string
      str = word_start(str, delim);
   }
   tokens[len] = ""; // This is done so that the print all tokens undestand when to stop
   return tokens;
}

void print_all_tokens(char **tokens)
{
   int i = 0;
   while (*(*(tokens + i)) != '\0') // Here I continue until the char value of the token is none.
   {
      printf("tokens[%d] = %s\n", i, tokens[i]);
      i++;
   }
   printf("tokens[%d] = \\0\n", i++);
}

/*int main()
{
   char delim;
   char str[30];
   char *ptr = str;
   char temp;
   printf("Please enter your delimeter: \n"); // Here I ask for the user input 
   scanf("%c", &delim); // Here I get delim
   printf("Please enter the string you will like to use today (this must be less then 30 characters long): \n"); // Here I ask for the user input
   scanf("%c",&temp); // Clears buffer
   fgets(str,30,stdin); // Here I get str
   printf("Here are you tokens: \n");
   print_all_tokens(tokenize(ptr, delim)); // Here I print the made tokens
   return 0;
}*/
