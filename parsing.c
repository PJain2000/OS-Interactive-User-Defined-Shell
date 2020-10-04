#include "shell.h"
char** parseSemicolon(char *line,char **tokens)
{
  int position = 0;
  char *token;

  token = strtok (line, ";");

  while (token != NULL) {
    tokens[position] = token;
    token = strtok(NULL, ";");
    position++;
}
tokens[position] = NULL;
return tokens;
}

char** parseArrow(char *line,char **tokens)
{
  int position = 0;
  char *token;

  token = strtok (line, "<>");

  while (token != NULL) {
    tokens[position] = token;
    token = strtok(NULL, "<>");
    position++;
}
tokens[position] = NULL;
return tokens;
}

char** parsePipe(char *line,char **tokens)
{
  int position = 0;
  char *token;

  token = strtok (line, "|");

  while (token != NULL) {
    tokens[position] = token;
    token = strtok(NULL, "|");
    position++;
}
tokens[position] = NULL;
return tokens;
}

char** parseSpace(char *line,char **tokens)
{
  int position = 0;
  char *token;

  token = strtok (line, " ");

  while (token != NULL) {
    tokens[position] = token;
    token = strtok(NULL, " ");
    position++;
}
tokens[position] = NULL;
return tokens;
}

char** parseEOF(char *line,char **tokens)
{
  int position = 0;
  char *token;

  token = strtok (line, "\n");

  while (token != NULL) {
    tokens[position] = token;
    token = strtok(NULL, "\n");
    position++;
}
tokens[position] = NULL;
return tokens;
}
