#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>



int main()
{
   int x;
   FILE *file;
   int text;
   char  *words_array[1000];
   char  *sentences_array[1000];


   printf("Witamy w programie Skladniowiec!\n");
   printf("Z jakiego trybu programu chcesz skorzystac?\n");
   printf("1:Standardowy\n");
   printf("2:Porownywanie\n");
   scanf ("%d", &x);

   switch (x) {
     case 1:
     text=read_file();
     //printf("%s\n", text);
     *words_array = split_text_into_words(text);
     *sentences_array = split_text_into_sentences(text);
     break;
   case 2: break;
}
}

int read_file(){
char filename[100];
printf("Wczytaj plik z tekstem:\n");
scanf("%s", filename);
char *text = NULL;
size_t size = 0;
FILE *fp = fopen(filename, "r");
fseek(fp, 0, SEEK_END);
size = ftell(fp);
rewind(fp);
text = malloc((size + 1) * sizeof(*text));
fread(text, size, 1, fp);
text[size] = '\0';
return text;
}


void split_text_into_words(int some_text)
{
     int i =0;
     char *words_array[1000];
     char* words=strtok(some_text," .,:!?;");
     while (words != NULL) {
     words_array[i++]=words;
     words = strtok(NULL, " .,:!?;");
    }
    return *words_array;
}

void split_text_into_sentences(int some_text)
{
     int i =0;
     char *sentences_array[1000];
     char* sentences=strtok(some_text,".?!");
     while (sentences != NULL) {
     sentences_array[i++]=sentences;
     sentences = strtok(NULL, ".?!");
    }
    return *sentences_array;
}

double mean(char array[],int level)
{

}

double median(char array[],int level)
{

}

double sd(char array[],int level)
{

}

double max(char array[],int level)
{

}

double min(char array[],int level)
{

}

double skewness(char array[],int level)
{

}

double kurtosis(char array[],int level)
{

}










