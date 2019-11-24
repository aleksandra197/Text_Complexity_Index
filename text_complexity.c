#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>


char* read_file()
{
  char filename[100];
  printf("Wczytaj plik z tekstem:\n");
  scanf("%s", filename);
  char *text = NULL;
  size_t size = 0;
  FILE *fp = fopen(filename, "r");
  if(fp==NULL)
  {
   printf("Plik nie istnieje!");
   exit(1);
  }
  fseek(fp, 0, SEEK_END);
  size = ftell(fp);
  rewind(fp);
  text = malloc((size + 1) * sizeof(*text));
  fread(text, size, 1, fp);
  text[size] = '\0';
  return text;
}

void split_text_into_sentences(char *some_text)
{
    printf("\nTekst podzielony na zdania:\n\n");
    int index=0;
    char **res=NULL;
    char *command= malloc(strlen(some_text)+1);
    strcpy(command, some_text);
    char *tok = strtok(command, ".?!");
    while(tok!=NULL) {
        res = realloc(res, sizeof(char*)*(index+1));
        char *dup = malloc(strlen(tok)+1);
        strcpy(dup, tok);
        res[index++] = dup;
        tok = strtok(NULL, ".?!");
    }

    res = realloc(res, sizeof(char*)*(index+1));
    res[index]=NULL;
    free(command);

    for(int j=0;j<index;j++){
      printf("%s\n\n",res[j]);
    }
}

void split_text_into_words(char *some_text)
{
    printf("\nTekst podzielony na slowa:\n\n");
    int index=0;
    char **res=NULL;
    char *command= malloc(strlen(some_text)+1);
    strcpy(command, some_text);
    char *tok = strtok(command, " .,:!?;");
    while(tok!=NULL) {
        res = realloc(res, sizeof(char*)*(index+1));
        char *dup = malloc(strlen(tok)+1);
        strcpy(dup, tok);
        res[index++] = dup;
        tok = strtok(NULL, " .,:!?;");
    }

    res = realloc(res, sizeof(char*)*(index+1));
    res[index]=NULL;
    free(command);

    for(int j=0;j<index;j++){
      printf("%s\n",res[j]);
    }
}

int main()
{
   int x;
   int text;

   printf("Witamy w programie Skladniowiec!\n");
   printf("Z jakiego trybu programu chcesz skorzystac?\n");
   printf("1:Standardowy\n");
   printf("2:Porownywanie\n");
   scanf ("%d", &x);

   switch (x) {
     case 1:
     text=read_file();
     printf("\nWczytany tekst:\n");
     printf("%s\n", text);
     split_text_into_words(text);
     split_text_into_sentences(text);
     break;
   case 2:
        break;
}
return 0;
}












