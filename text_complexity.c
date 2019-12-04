#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#define N 5
#define M 100

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

sentences *s_array;
words *w_array;

char* read_file(char filename[])
{

  char *text = NULL;
  size_t size = 0;
  FILE *fp = fopen(filename, "r");
  if(fp==NULL)
  {
   printf("\nNie znaleziono pliku.\n");
   exit(1);
  }
  else{
      printf("\nWczytanie pliku powiodlo sie! \n");
      fseek(fp, 0, SEEK_END);
      size = ftell(fp);
      rewind(fp);
      text = malloc((size + 1) * sizeof(*text));
      fread(text, size, 1, fp);
      text[size] = '\0';
  }

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

float lexical_complexity(words w)
{
    float *arr_words=chars_in_words(w);

    float words_avg= average(arr_words,w.n);
    float words_median = median(arr_words,w.n);
    float words_sd = standard_deviation(arr_words,w.n);
    float words_max = max(arr_words,w.n);
    float lexical= 4*words_avg+words_sd/words_avg+words_max/4;
    float lexical_complexity_index;

    if(words_avg>1.2*words_median)
        lexical_complexity_index=1.1*lexical;
    else
        lexical_complexity_index=lexical;

    return lexical_complexity_index;

}

float syntax_complexity(sentences s)
{
    float *arr_sentences=number_of_words(s);
    float *arr_punctation=punction_marks(s);

    float sentences_avg = average(arr_sentences,s.n);
    float sentences_median = median(arr_sentences,s.n);
    float sentences_sd = standard_deviation(arr_sentences,s.n);
    float sentences_max = max(arr_sentences,s.n);
    float sentences_min = min(arr_sentences,s.n);

    float punctation_avg= average(arr_punctation,s.n);
    float punctation_median = median(arr_punctation,s.n);
    float punctation_max = max(arr_punctation,s.n);

    float syntax= 4*sentences_avg+(sentences_sd/sentences_avg)+sentences_max/8+2*punctation_avg+punctation_max/2;
    float syntax_complexity_index;

    if(sentences_avg>1.2*sentences_median && punctation_avg>1.2*punctation_median)
        syntax_complexity_index=1,1*syntax;
    else
        {if(sentences_avg>1.2*sentences_median || punctation_avg>1.2*punctation_median)
        syntax_complexity_index=1.05*syntax;
        else
          syntax_complexity_index=syntax;
        }

    return syntax_complexity_index;
}

float complexity_index(sentences s, words w)
{
    float syntax_complexity_index= syntax_complexity(s);
    float lexical_complexity_index= lexical_complexity(w);
    float text_complexity_index=syntax_complexity_index+lexical_complexity_index;
    return text_complexity_index;
}

float* xnorm(float *array,int n)
{
    int i;
    float maximum=max(array,n);
    float minimum=min(array,n);
    float *norm_array=malloc(sizeof(float) * n);

    for(i=0;i<n;i++)
    {
        norm_array[i]=(array[i]-minimum)/(maximum-minimum);
    }

    return norm_array;
}

int my_compare (const void * a, const void * b)
{
    float _a = *(float*)a;
    float _b = *(float*)b;
    if(_a > _b) return -1;
    else if(_a == _b) return 0;
    else return 1;
}



int main()
{
   int x,y,z,w,t;
   char* text;
   char filename[M];
   float text_complexity_index;
   sentences s1;
   words w1;
   printf("Witamy w programie Skladniowiec!\n");
   menu1:
       printf("Z jakiego trybu programu chcesz skorzystac?\n");
       printf("1:Standardowy\n");
       printf("2:Porownywanie\n");
       scanf ("%d", &x);
       printf("Wczytaj plik z tekstem. Powinien byc zapisany w formacie .txt\n");
       printf("Test moze byc w dowolnym jezyku opartym na alfabecie lacinskim.\n");
       printf("Zaklada sie, ze tekst jest napisany zgodnie z regulami danego jezyka.\nNazwa pliku: ");
       scanf ("%s", &filename);
   switch (x) {
     case 1:
    {

     statistics:
            text=read_file(filename);
            s1=split_text_into_sentences(text);
            w1=split_text_into_words(text);
            text_complexity_index=complexity_index(s1,w1);
            printf("\nTekst charakteryzuja nastepujace wartosci indeksow zlozonosci:\n");
            printf("Wartosc indeksu zlozonosci skladniowej %.2f \n", syntax_complexity(s1));
            printf("Wartosc indeksu zlozonosci leksykalnej %.2f \n", lexical_complexity(w1));
            printf("Wartosc indeksu ogolnej zlozonosci tekstu wynosi : %.2f\n",text_complexity_index);
            getch();
            printf("---");
            printf("\nStatystyki dla ilosci wyrazow w zdaniu: \n");
            printf("Srednia arytmetyczna: %.2f\n", average(number_of_words(s1),s1.n)  );
            printf("Mediana: %.2f\n", median(number_of_words(s1),s1.n)  );
            printf("Odchylenie standardowe: %.2f\n", standard_deviation(number_of_words(s1),s1.n)  );
            printf("Max: %.2f\n", max(number_of_words(s1),s1.n)  );
            printf("Min: %.2f\n", min(number_of_words(s1),s1.n)  );
            printf("Kurtoza: %.2f\n",kurtosis(number_of_words(s1),s1.n));
            printf("Skosnocs: %.2f\n",skewness(number_of_words(s1),s1.n));
            getch();
            printf("---");
            printf("\nStatystyki dla ilosci liter w wyrazach: \n");
            printf("Srednia: %.2f\n", average(chars_in_words(w1),w1.n)  );
            printf("Mediana: %.2f\n", median(chars_in_words(w1),w1.n)  );
            printf("Odchylenie standardowe: %.2f\n", standard_deviation(chars_in_words(w1),w1.n));
            printf("Max: %.2f\n", max(chars_in_words(w1),w1.n)  );
            printf("Min: %.2f\n", min(chars_in_words(w1),w1.n)  );
            printf("Kurtoza: %.2f\n",kurtosis(chars_in_words(w1),w1.n));
            printf("Skosnocs: %.2f\n",skewness(chars_in_words(w1),w1.n));
            getch();
            printf("---");
            printf("\nStatystyki dla znakow interpunkcyjnych: \n");
            printf("Srednia arytmetyczna: %.2f\n", average(punction_marks(s1),s1.n)  );
            printf("Mediana: %.2f\n", median(punction_marks(s1),s1.n)  );
            printf("Odchylenie standardowe: %.2f\n", standard_deviation(punction_marks(s1),s1.n)  );
            printf("Max: %.2f\n", max(punction_marks(s1),s1.n)  );
            printf("Min: %.2f\n", min(punction_marks(s1),s1.n)  );
            printf("Kurtoza: %.2f\n",kurtosis(punction_marks(s1),s1.n));
            printf("Skosnocs: %.2f\n",skewness(punction_marks(s1),s1.n));

           printf("\n\nCzy chcesz:\n");
           printf("1. jeszcze raz wyswietlic statystyki opisowe?\n");
           printf("2. przeanalizowac kolejny tekst?\n");
           printf("3. zakonczyc?\n");
           scanf ("%d", &y);
           switch (y) {
           case 1:
           goto statistics;
           case 2:
           goto menu1;
           case 3:
            {
                printf("\nCzy chcesz zapisac wyniki do pliku?");
                printf("\n1. TAK");
                printf("\n2. NIE\n");
                scanf("%d",&t);
                if(t==1)
                {
            FILE *ptr;
            ptr = fopen("results.txt","w");
            fprintf(ptr,"\nTekst charakteryzuja nastepujace wartosci indeksow zlozonosci:\n");
            fprintf(ptr,"Wartosc indeksu zlozonosci skladniowej %.2f \n", syntax_complexity(s1));
            fprintf(ptr,"Wartosc indeksu zlozonosci leksykalnej %.2f \n", lexical_complexity(w1));
            fprintf(ptr,"Wartosc indeksu ogolnej zlozonosci tekstu wynosi : %.2f\n",text_complexity_index);
            fprintf(ptr,"---");
            fprintf(ptr,"\nStatystyki dla ilosci wyrazow w zdaniu: \n");
            fprintf(ptr,"Srednia arytmetyczna: %.2f\n", average(number_of_words(s1),s1.n)  );
            fprintf(ptr,"Mediana: %.2f\n", median(number_of_words(s1),s1.n)  );
            fprintf(ptr,"Odchylenie standardowe: %.2f\n", standard_deviation(number_of_words(s1),s1.n)  );
            fprintf(ptr,"Max: %.2f\n", max(number_of_words(s1),s1.n)  );
            fprintf(ptr,"Min: %.2f\n", min(number_of_words(s1),s1.n)  );
            fprintf(ptr,"Kurtoza: %.2f\n",kurtosis(number_of_words(s1),s1.n));
            fprintf(ptr,"Skosnosc: %.2f\n",skewness(number_of_words(s1),s1.n));
            fprintf(ptr,"---");
            fprintf(ptr,"\nStatystyki dla ilosci liter w wyrazach: \n");
            fprintf(ptr,"Srednia: %.2f\n", average(chars_in_words(w1),w1.n)  );
            fprintf(ptr,"Mediana: %.2f\n", median(chars_in_words(w1),w1.n)  );
            fprintf(ptr,"Odchylenie standardowe: %.2f\n", standard_deviation(chars_in_words(w1),w1.n));
            fprintf(ptr,"Max: %.2f\n", max(chars_in_words(w1),w1.n)  );
            fprintf(ptr,"Min: %.2f\n", min(chars_in_words(w1),w1.n)  );
            fprintf(ptr,"Kurtoza: %.2f\n",kurtosis(chars_in_words(w1),w1.n));
            fprintf(ptr,"Skosnosc: %.2f\n",skewness(chars_in_words(w1),w1.n));
            fprintf(ptr,"---");
            fprintf(ptr,"\nStatystyki dla znakow interpunkcyjnych: \n");
            fprintf(ptr,"Srednia arytmetyczna: %.2f\n", average(punction_marks(s1),s1.n)  );
            fprintf(ptr,"Mediana: %.2f\n", median(punction_marks(s1),s1.n)  );
            fprintf(ptr,"Odchylenie standardowe: %.2f\n", standard_deviation(punction_marks(s1),s1.n)  );
            fprintf(ptr,"Max: %.2f\n", max(punction_marks(s1),s1.n)  );
            fprintf(ptr,"Min: %.2f\n", min(punction_marks(s1),s1.n)  );
            fprintf(ptr,"Kurtoza: %.2f\n",kurtosis(punction_marks(s1),s1.n));
            fprintf(ptr,"Skosnosc: %.2f\n",skewness(punction_marks(s1),s1.n));
            printf("\nWyniki zostaly zapisane w pliku results.txt\n");

                }
           exit(1);
           }
                      }
           break;
   }
   case 2:
    {
    text=read_file(filename);
   float *norm_index_array;
   float *norm_syn_array;
   float *norm_lex_array;
   float text_complexity_index;
   int i,j;
   int index=0;
   char **res=NULL;
   char *command= malloc(strlen(text)+1);
   strcpy(command, text);
   char *tok = strtok(command, "漢");
   while(tok!=NULL) {
        res = realloc(res, sizeof(char*)*(index+1));
        char *dup = malloc(strlen(tok)+1);
        strcpy(dup, tok);
        res[index++] = dup;
        tok = strtok(NULL, "漢");
    }

    res = realloc(res, sizeof(char)*(index+1));
    res[index]=NULL;
    free(command);
    float *index_arr=malloc(sizeof(float) * index);
    float *lex_arr=malloc(sizeof(float) * index);
    float *syn_arr=malloc(sizeof(float) * index);
    s_array = (sentences*) malloc(index * sizeof(sentences));
    w_array = (words*) malloc(index * sizeof(words));


    for(i=0;i<index;i++)
    {
         s_array[i]=split_text_into_sentences(res[i]);
         w_array[i]=split_text_into_words(res[i]);
         lex_arr[i]=lexical_complexity(w_array[i]);
         syn_arr[i]=syntax_complexity(s_array[i]);
         index_arr[i]=complexity_index(s_array[i],w_array[i]);
    }

    norm_index_array=xnorm(index_arr,index);
    norm_lex_array=xnorm(lex_arr,index);
    norm_syn_array=xnorm(syn_arr,index);

    int * idx = malloc(index * sizeof(int));
    float *base_arr = malloc(sizeof(float) * index);
    for (i = 0; i < index; i++) {
        base_arr[i] = norm_index_array[i];
        idx[i] = i;
    }
    qsort(idx, index, sizeof(int),my_compare);
    free(base_arr); base_arr = NULL;



    for(i=0;i<index;i++)
    {
        printf("\n---\n");
        printf("Miejsce %d - teskt nr %d:\n",i+1,idx[i]+1);
        printf("Ekstrakt:");
        for(j=0;j<N;j++)
        {
            printf("%s ",w_array[idx[i]].words_array[j]);
        }
        printf("...");
        printf("\nIndeks ogolnej zlozonosci tekstowej: %.2f",index_arr[idx[i]]);
        printf("\nZnormalizowany indeks ogolnej zlozonosci tekstowej: %.2f",norm_index_array[idx[i]]);
        printf("\nIndeks zlozonosci leksykalnej: %.2f",lex_arr[idx[i]]);
        printf("\nZnormalizowany indeks zlozonosci leksykalnej: %.2f",norm_lex_array[idx[i]]);
        printf("\nIndeks zlozonosci skladniowej: %.2f",syn_arr[idx[i]]);
        printf("\nZnormalizowany indeks zlozonosci skladniowej: %.2f",norm_syn_array[idx[i]]);
    }

    menu2:
     printf("\n\nCzy chcesz:");
     printf("\n1. wyswietlic statystyki opisowe dla tektu o wybranym numerze?");
     printf("\n2. przeanalizowac kolejny teskt?");
     printf("\n3. zakonczyc dzialanie programu?\n");
     scanf("%d",&z);
     switch(z)
     {
        case 1:{
            printf("\nPodaj numer tekstu: ");
            scanf("%d",&w);
            w=w-1;
            printf("\n***Teskt nr %d***\n",w+1);
            printf("---");
            printf("\nStatystyki dla ilosci wyrazow w zdaniu: \n");
            printf("Srednia arytmetyczna: %.2f\n", average(number_of_words(s_array[w]),s_array[w].n)  );
            printf("Mediana: %.2f\n", median(number_of_words(s_array[w]),s_array[w].n)  );
            printf("Odchylenie standardowe: %.2f\n", standard_deviation(number_of_words(s_array[w]),s_array[w].n)  );
            printf("Max: %.2f\n", max(number_of_words(s_array[w]),s_array[w].n)  );
            printf("Min: %.2f\n", min(number_of_words(s_array[w]),s_array[w].n)  );
            printf("Kurtoza: %.2f\n",kurtosis(number_of_words(s_array[w]),s_array[w].n));
            printf("Skosnosc: %.2f\n",skewness(number_of_words(s_array[w]),s_array[w].n));
            getch();
            printf("---");
            printf("\nStatystyki dla ilosci liter w wyrazach: \n");
            printf("Srednia: %.2f\n", average(chars_in_words(w_array[w]),w_array[w].n)  );
            printf("Mediana: %.2f\n", median(chars_in_words(w_array[w]),w_array[w].n)  );
            printf("Odchylenie standardowe: %.2f\n", standard_deviation(chars_in_words(w_array[w]),w_array[w].n));
            printf("Max: %.2f\n", max(chars_in_words(w_array[w]),w_array[w].n)  );
            printf("Min: %.2f\n", min(chars_in_words(w_array[w]),w_array[w].n)  );
            printf("Kurtoza: %.2f\n",kurtosis(chars_in_words(w_array[w]),w_array[w].n));
            printf("Skosnosc: %.2f\n",skewness(chars_in_words(w_array[w]),s_array[w].n));
            getch();
            printf("---");
            printf("\nStatystyki dla ilosci znakow interpunkcyjnych: \n");
            printf("Srednia arytmetyczna: %.2f\n", average(punction_marks(s_array[w]),s_array[w].n)  );
            printf("Mediana: %.2f\n", median(punction_marks(s_array[w]),s_array[w].n)  );
            printf("Odchylenie standardowe: %.2f\n", standard_deviation(punction_marks(s_array[w]),s_array[w].n)  );
            printf("Max: %.2f\n", max(punction_marks(s_array[w]),s_array[w].n)  );
            printf("Min: %.2f\n", min(punction_marks(s_array[w]),s_array[w].n)  );
            printf("Kurtoza: %.2f\n",kurtosis(punction_marks(s_array[w]),s_array[w].n));
            printf("Skosnosc: %.2\n",skewness(punction_marks(s_array[w]),s_array[w].n));
            goto menu2;
        break;
        }
        case 2: goto menu1;
        case 3:
            {
                printf("\nCzy chcesz zapisac wyniki do pliku?");
                printf("\n1. TAK");
                printf("\n2. NIE\n");
                scanf("%d",&t);
                if(t==1)
                {
                    FILE *ptr;
                    ptr = fopen("results.txt","w");
                    for(i=0;i<index;i++)
                       {
                        fprintf(ptr,"\n---\n");
                        fprintf(ptr,"Miejsce %d - teskt nr %d:\n",i+1,idx[i]+1);
                        fprintf(ptr,"Ekstrakt:");
                    for(j=0;j<N;j++)
                        {
                        fprintf(ptr,"%s ",w_array[idx[i]].words_array[j]);
                        }
                        fprintf(ptr,"...");
                    fprintf(ptr,"\nIndeks ogolnej zlozonosci tekstowej: %.2f",index_arr[idx[i]]);
                    fprintf(ptr,"\nZnormalizowany indeks ogolnej zlozonosci tekstowej: %.2f",norm_index_array[idx[i]]);
                    fprintf(ptr,"\nIndeks zlozonosci leksykalnej: %.2f",lex_arr[idx[i]]);
                    fprintf(ptr,"\nZnormalizowany indeks zlozonosci leksykalnej: %.2f",norm_lex_array[idx[i]]);
                    fprintf(ptr,"\nIndeks zlozonosci skladniowej: %.2f",syn_arr[idx[i]]);
                    fprintf(ptr,"\nZnormalizowany indeks zlozonosci skladniowej: %.2f",norm_syn_array[idx[i]]);
                        }
                    printf("\nWyniki zostaly zapisane w pliku results.txt\n");

                }
                exit(2);
            }

     }

}

return 0;

}
}
