//////////////////////////
//
//  Sumedh Saurabh
//
//////////////////////////

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int collatz(int n)
{
  if(n % 2 == 0)
  {
    n = n/2; // even
  }
  else
  {
    n = (3 * n) + 1; // odd
  }
  return n;
}
int main(int argc, char *argv[])
{
    // Code taken from slides
    int i, n, minN, maxN;
    int status;
    FILE *fileP;
    int next;

    if((fileP = fopen("results_Childpid_Parentpid.dat", "w+")))
    {
      n = atoi(argv[1]);
      minN = atoi(argv[2]);
      maxN = atoi(argv[3]);
      pid_t processes[n];

      // end copy
      if(n>10)
      {
        fprintf(stderr, "Must be less than 10%s\n", argv[1]);
        return 1;
      }
      int s = minN;
      // had this entire for loop in a function; however, errors were
      // caused regarding file reference.
      for(i = 1; i <= n; i++) {
        if(i == n<2)// splits allocations of sequence by 2
        {
          while(s < maxN/3) // allocates for processes
          {
            fprintf(fileP, "Sequence %d: \n", s);
            if((processes[i] = fork())<0)
            {
              perror("Fork error");
              exit(-1); // Fail Exit
            }
            else if(processes[i] > 0) // will split on every sequence
            {
              int k = s;
              do
              {
                k = collatz(k); // calls for each collatz sequence output
                fprintf(fileP, "%d\n", k);
                printf("child is done.\n");
              }while(k!=1 && k>0);
              exit(0);
            }
            else
            {
              printf("Parent is waiting.\n"); // take
              wait(); // wait
              printf("done.\n");
            }

            // Taken from slides
            // Just tracking...
            fprintf(stderr, "i:%d process ID:%ld; \t My parent is:%ld; \t I am child number:%ld;\t I have generated sequence for: %d\n", i, (long)getpid(), (long)getppid(), (long)processes[i], s);
            // end copy
            s++;
          }
        }
        else
        {
          next = s;

          while(s <= maxN)
          {
            fprintf(fileP, "Sequence %d: \n", s);
            if((processes[i] = fork())<0) // error for fork
            {
              perror("Fork error");
              exit(-1);
            }
            else if(processes[i] == 0) // will split on every sequence
            {
              int k = s;
              do
              {
                fprintf(fileP, "%d\n", k);
                k = collatz(k); // calls for each collatz sequence output
              } while(k!=1 && k>0);
              exit(0);

            }
            else
            {
              printf("Parent is waiting.\n"); // take
              wait(&status); // wait
              printf("done.\n");
            }

            // Taken from slides
            // Just tracking...
            fprintf(stderr, "i:%d process ID:%ld; \t My parent is:%ld; \t I am child number:%ld;\t I have generated sequence for: %d\n", i, (long)getpid(), (long)getppid(), (long)processes[i], s);
            // end copy
            s++;
          }
        }
        n--;
      }

    }
    else
    {
      printf("File could not be created.\n");
      exit(0); // exit
    }

    fclose(fileP); // close file

    printf("Processes have been exited");
    return 0;
}
