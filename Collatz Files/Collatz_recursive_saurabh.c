//////////////////////////
//
//  Sumedh Saurabh
//
//////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

char* split(int n, int k, int maxN)
{
  pid_t pid;
  char * buffer;
  int initial = k;
  if(n > 0)
  {
      if ((pid = fork()) < 0)
      {
          printf("fork error\n");
      }
      else if (pid == 0) // child stuff
      {
          sprintf(buffer, "Process: \n");
          if(k<=maxN)
          {
            while(k!=1 && k<=maxN){
              k = collatz(k);
              printf("%d\n", k);
              //fprintf(&fileP, "%d\n", k);
              sprintf(buffer, "%d\n", k);
            }
          }
          else
          {
            printf("reached end...\n");
            exit(0);
          }
          k = initial;
          printf("Child %d end\n", n);
      }
      else if(pid > 0) // parent
      {

          strcat(buffer, split(n-1, k+1, maxN));
          printf("was here\n");
      }
  }
  return buffer;
}
int collatz(int n)
{
  if(n % 2 == 0)
  {
    n = n/2;
  }
  else
  {
    n = (3 * n) + 1;
  }
  return n;
}
int main(int argc, char *argv[])
{
  int n = atoi(argv[1]);
  int i, k, minN, maxN;
  FILE *fileP;

  minN = atoi(argv[2]);
  maxN = atoi(argv[3]);
  printf("%d\n", n);
  fileP = fopen("results_Childpid_Parentpid.dat", "w+");

  //temp
  k = minN;
  printf("opened file\n");
  fprintf(fileP, "%s\n", split(n, k, maxN));

  fclose(fileP);
  return 0;
}
