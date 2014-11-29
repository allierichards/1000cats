#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void randstr(char *, int, char *);
void mutate(char *, char *, int);
int getscore(char *, char *);

int main(void)
{
  char target[] = "METHINKS IT IS LIKE A WEASEL";
  char characters[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int target_length = strlen(target);
  char survivor[target_length]; 
  int generation = 1;
  int offspring_count = 1000;
  int chance = 2;
  int max_score;
  int max_ordinal;
  char max_offspring[target_length + 1];
  int target_score = target_length;
  int c;
  int offspring_score;

  srand(time(NULL));
  memset(survivor, '\0', sizeof(survivor));
  memset(max_offspring, '\0', sizeof(max_offspring));
  randstr(survivor, target_length, characters);
  max_score = getscore(survivor, target);
  strcpy(max_offspring, survivor);
  printf("0: %s -- score: %d\n", max_offspring, max_score);
  while (max_score < target_score)
  {
    for (c = 0; c < offspring_count; c += 1)
    {
      mutate(survivor, characters, chance);
      offspring_score = getscore(survivor, target);
      if (offspring_score > max_score)
      {
        max_score = offspring_score;
	strcpy(max_offspring, survivor);
      }
    }
    printf("%d: %s -- score: %d\n", generation, max_offspring, max_score);
    generation += 1;
    strcpy(survivor, max_offspring);
  }
}

/* 
 * randstr
 * generates a random string composed of the elements in the string pointed to by *characters
 * the string is stored in the array pointed to by *string
 * length is the lenth of the string to generate
 */
void randstr(char *string, int length, char *characters)
{
  int range = strlen(characters);
  int c;
  int n;

  for (c = 0; c < length; c += 1)
  {
    n = rand() % range;
    string[c] = characters[n];
  }
  string[length] = '\0';
}

/*
 * mutate
 * with a probability of chance% changes each charter in random to a character in characters
 */
void mutate(char *random, char *characters, int chance)
{
  int c;
  int n;
  int p;
  int x = strlen(characters);

  for (c = 0; c < strlen(random); c += 1)
  {
    n = rand() % 100;
    if (n <= chance)
    {
      p = rand() % x;
      random[c] = characters[p];
    }
  }
}

/*
 * getscore
 * returns the number of characters that are identical between string1 and string2
 * both strings should have the same length
 */
int getscore(char *string1, char *string2)
{
  int length1 = strlen(string1);
  int length2 = strlen(string2);
  int c;
  int score = 0;

  if (length1 != length2)
  {
    printf("strings are not same length:\n%s\n%s\n can't continue\n", string1, string2);
    exit(1);
  }
  for (c = 0; c < length1; c += 1)
  {
    if (string1[c] == string2[c])
      score += 1;
  }
  return(score);
}
