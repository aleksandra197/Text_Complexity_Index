#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>


typedef struct
{
    char **words_array;
    int n;
}words;

typedef struct
{
    char **sentences_array;
    int n;

}sentences;


char* read_file(char filename[])
{
  //char filename[100];
  //printf("Wczytaj plik z tekstem:\n");
  //scanf("%s", filename);
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

sentences split_text_into_sentences(char *some_text)
{
    sentences s;
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

//    for(int j=0;j<index;j++){
//      printf("%s\n\n",res[j]);
//    }
s.sentences_array=res;
s.n=index;
return s;
}

words split_text_into_words(char *some_text)
{
    words w;
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

//    for(int j=0;j<index;j++){
//      printf("%s\n",res[j]);
//    }
w.words_array=res;
w.n=index;
return w;

}

float *number_of_words(sentences s)
{
    int i,j;
    int sum=0;
    float *arr= malloc(sizeof(float) * s.n);
    for(i=0;i<s.n;i++)
    {
        for (j=0;j<strlen(s.sentences_array[i]);j++)
        {
            if(s.sentences_array[i][j]==' ' || s.sentences_array[i][j]=='\0')
                sum++;
        }
        arr[i]=sum;
    }
    return arr;
}

float *chars_in_words(words w)
{
    int i,j;
    int chars=0;
    float *arr= malloc(sizeof(float) * w.n);
    for(i=0;i<w.n;i++)
    {
        arr[i]=strlen(w.words_array[i]);
    }
    return arr;

}

float *punction_marks(sentences s)
{
    int i,j;
    int sum=0;
    float *arr= malloc(sizeof(float) * s.n);
    for(i=0;i<s.n;i++)
    {
        for (j=0;j<strlen(s.sentences_array[i]);j++)
        {
            if(s.sentences_array[i][j]==',' || s.sentences_array[i][j]==';' || s.sentences_array[i][j]==':'
                || s.sentences_array[i][j]=='-' || s.sentences_array[i][j]=='"'
                 || s.sentences_array[i][j]=='(' || s.sentences_array[i][j]==')')
                sum++;
        }
        arr[i]=sum;
    }
    return arr;
}

float median(float *array , int n)
{
    float median=0;

    if(n%2 == 0)
        median = (array[(n-1)/2] + array[n/2])/2.0;
    else
        median = array[n/2];

    return median;
}

float average(float *array,int n)
{
 int i;
 float sum = 0;
 float average = 0.0;
    for(i = 0; i < n; i++){
       sum = sum + array[i];
    }
 average = sum/n;
 return average;
}

float standard_deviation(float *array,int n)
{
    float avg= average(array,n);
    float sum= 0.0;
    int i;

    for(i = 0; i < n; i++)

        sum+= (array[i] - avg) * (array[i] - avg);

    float sd = sqrt(sum / n);
    return sd;

}

float max(float *array,int n)
{
    int i;
    float max = array[0];

    for ( i = 1 ; i < n ; i++ )
    {
        if ( array[i] > max )
        {
           max = array[i];
        }
    }
    return max;

}


float min(float *array,int n)
{
    int i;
    float min = array[0];

    for ( i = 1 ; i < n ; i++ )
    {
        if ( array[i] < min )
        {
           min = array[i];
        }
    }
    return min;
}

float kurtosis(float *array,int n)
{
    float avg= average(array,n);
    float sd = standard_deviation(array,n);
    float sum= 0.0;
    int i;

    for(i = 0; i < n; i++)

        sum+= pow((array[i] - avg),4);

     float kurt= (sum / n)/pow(sd,4);
     return kurt;

}

float skewness(float *array,int n)
{

    float avg = average(array,n);
    float med=median(array,n);
    float sd=standard_deviation(array,n);
    float skew= (3 * (avg-med))/sd;
    return skew;
}

float complexity_index(sentences s, words w)
{
    float *arr_sentences=number_of_words(s);
    float *arr_words=chars_in_words(w);
    float *arr_punctation=punction_marks(s);

    float sentences_avg = average(arr_sentences,s.n);
    float sentences_median = median(arr_sentences,s.n);
    float sentences_sd = standard_deviation(arr_sentences,s.n);
    float sentences_max = max(arr_sentences,s.n);

    float words_avg= average(arr_words,w.n);
    float words_median = median(arr_words,w.n);
    float words_sd = standard_deviation(arr_words,w.n);
    float words_max = max(arr_words,w.n);

    float punctation_avg= average(arr_punctation,s.n);
    float punctation_median = median(arr_punctation,s.n);
    float punctation_max = max(arr_punctation,s.n);

    float syntax= 4*sentences_avg+(sentences_sd/sentences_avg)+sentences_max/8+2*punctation_avg+punctation_max/2;
    float lexical= 4*words_avg+words_sd/words_avg+words_max/4;
    float syntax_complexity_index;
    float lexical_complexity_index;
    float text_complexity_index;

    if(sentences_avg>1.2*sentences_median && punctation_avg>1.2*punctation_median)
        {syntax_complexity_index=1,1*syntax;}
        else
        {if(sentences_avg>1.2*sentences_median || punctation_avg>1.2*punctation_median)
        syntax_complexity_index=1.05*syntax;
        else
          syntax_complexity_index=syntax;
        }
    if(words_avg>1.2*words_median)
        lexical_complexity_index=1.1*lexical;
    else
        lexical_complexity_index=lexical;

    text_complexity_index=syntax_complexity_index+lexical_complexity_index;

    return text_complexity_index;
}



int main()
{
   int x;
   char* text;
   char filename[] = "text.txt";
   sentences s1;
   words w1;
   float text_complexity_index;

   printf("Witamy w programie Skladniowiec!\n");
   printf("Z jakiego trybu programu chcesz skorzystac?\n");
   printf("1:Standardowy\n");
   printf("2:Porownywanie\n");
   scanf ("%d", &x);

   switch (x) {
     case 1:
     text=read_file(filename);
     text=read_file(filename);
     s1=split_text_into_sentences(text);
     w1=split_text_into_words(text);
     text_complexity_index=complexity_index(s1,w1);
     printf("Indeks wynosi : %.2f",text_complexity_index);
     break;
   case 2:
        break;
}
return 0;
}












