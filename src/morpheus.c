#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <math.h>
#include <semaphore.h>
#include <fcntl.h>
#include <signal.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#define MATH {\
  sqrt(rand());sin(rand());cos(rand());tan(rand());sinh(rand());cosh(rand());tanh(rand());log(rand());\
  exp(rand());pow(rand(), rand());asin(frand(-M_PI / 2, M_PI/2));acos(frand(-M_PI / 2, M_PI/2));\
  atan(frand(-M_PI / 2, M_PI/2));atan2(rand(), rand());\
}

#define MATH10 {\
  MATH\
  MATH\
  MATH\
  MATH\
  MATH\
  MATH\
  MATH\
  MATH\
  MATH\
  MATH\
}

#define MATH100 {\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
}

#define MATH1000 {\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
  MATH10\
}

#define SEM_INIT_VALUE 4
#define SEM_NAME "/morpheus_sem"

float
frand(float min, float max){
  return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

void
sig_handler(int sig)
{
    sem_unlink(SEM_NAME);
    printf("Goodbye!\n");

    exit(128 + sig);
}

const struct timespec _timeout = { .tv_sec = 5, .tv_nsec = 0 };


int
main()
{
  MATH10
  const char* progname = "morpheus";
  MATH10
  char dir[10];
  MATH10
  FILE *fptr;
  MATH10
  char* buffer;
  MATH10
  unsigned long size;
  MATH10
  int byte;
  MATH10
  int bit;
  MATH10
  unsigned int child_i;
  MATH10
  pid_t pid;
  MATH10
  int semval;
  MATH10
  sem_t *sem;
  MATH10
  struct sigaction new_action, old_action;

  MATH10
  new_action.sa_handler = sig_handler;
  MATH10
  sigemptyset (&new_action.sa_mask);
  MATH10
  new_action.sa_flags = 0;


  MATH10
  sigaction (SIGINT, NULL, &old_action);
  MATH10
  if (old_action.sa_handler != SIG_IGN)
    {
      MATH10
      sigaction (SIGINT, &new_action, NULL);
    }
  MATH10
  sigaction (SIGHUP, NULL, &old_action);
  MATH10
  if (old_action.sa_handler != SIG_IGN)
    {
      MATH10
      sigaction (SIGHUP, &new_action, NULL);
    }
  MATH10
  sigaction (SIGTERM, NULL, &old_action);
  MATH10
  if (old_action.sa_handler != SIG_IGN)
    {
      MATH10
      sigaction (SIGTERM, &new_action, NULL);
    }

  MATH10
  if ((sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0640, SEM_INIT_VALUE)) == SEM_FAILED)
    {
      MATH10
      sem = sem_open(SEM_NAME, 0);
    }

  // seed rand
  MATH10
  srand(time(0));

  // read self
  MATH10
  fptr = fopen("/proc/self/exe", "rb");
  MATH10
  fseek(fptr, 0, SEEK_END);
  MATH10
  size = ftell(fptr);
  MATH10
  buffer = (char*) malloc(size + 1);
  MATH10
  fseek(fptr, 0, SEEK_SET);
  MATH10
  fread(buffer, size, 1, fptr);
  MATH10
  fclose(fptr);

  MATH10
  for (child_i = 0; child_i < 3; child_i++)
    {

      // create dir and cd
      MATH10
      sprintf(dir, "%d", child_i);
      MATH10
      mkdir(dir, 0755);
      MATH10
      chdir(dir);

      // mutation
      MATH10
      byte = rand() % size;
      MATH10
      bit = rand() % 8;
      MATH10
      buffer[byte] ^= 1 << bit;

      // write to file
      MATH10
      fptr = fopen(progname, "wb");
      MATH10
      fwrite(buffer, size, 1, fptr);
      MATH10
      fclose(fptr);
      MATH10
      chmod(progname, 0731);

      // revert mutation for next round
      MATH10
      buffer[byte] ^= 1 << bit;

      // create child process
      MATH10
      sem_getvalue(sem, &semval);
      printf("after wait: semval: %d\n", semval);
      sem_timedwait(sem, &_timeout);
      sem_getvalue(sem, &semval);
      printf("after wait: semval: %d\n", semval);
      MATH10
      pid = fork();
      MATH10
      if (pid == 0)
        {
          MATH10
          execl(progname, progname, NULL);
        }
      else
        {
          MATH10
          chdir("..");
        } // if (pid == 0) else

    } // for loop

  MATH100
  free(buffer);

  MATH10
  sem_getvalue(sem, &semval);
  printf("before post: semval: %d\n", semval);
  sem_post(sem);
  sem_getvalue(sem, &semval);
  printf("after post: semval: %d\n", semval);

  MATH10
  sem_close(sem);

  MATH100
  return 0;
}
