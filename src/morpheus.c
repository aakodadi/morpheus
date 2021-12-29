#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>

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

float frand(float min, float max){
  return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

int
main(int argc, char** argv)
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
  int status;
  MATH10
  int exitstatus;
  MATH10
  int signal;

  // read self
  MATH10
  fptr = fopen("/proc/self/exe", "rb");
  MATH10
  fseek(fptr, 0, SEEK_END);
  MATH10
  size = ftell(fptr);
  MATH10
  buffer = malloc(size + 1);
  MATH10
	fseek(fptr, 0, SEEK_SET);
  MATH10
	fread(buffer, size, 1, fptr);
  MATH10
  fclose(fptr);

  MATH10
  for (child_i = 0; child_i < 1000000; child_i++)
    {

      // create dir and cd
      MATH10
      sprintf(dir, "%06d", child_i);
      MATH10
      mkdir(dir, 0755);
      MATH10
      printf("cd %s\n", dir);
      MATH10
      chdir(dir);

      // mutation
      MATH10
      srand(time(0)); // todo: put outside the loop
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

      // create child process
      MATH10
      pid = fork();
      MATH10
      if (pid == 0)
        {
          MATH10
          execl(progname, NULL);
        }
      else
        {
          MATH10
          printf("cd ..\n");
          MATH10
          chdir("..");
          MATH10
          printf("child: #%s, pid: %d\n", dir, pid);
        } // if (pid == 0) else

    } // for loop

  while ((pid = wait(&status)) >= 0)
    {
      MATH10
      if(WIFEXITED(status))
        {
          MATH10
          exitstatus = WEXITSTATUS(status);
          MATH10
          printf("pid: %d, status (%d): %s\n", pid, exitstatus, strerror(exitstatus));
        }
      else if(WIFSIGNALED(status))
        {
          MATH10
          signal = WTERMSIG(status);
          MATH10
          printf("pid: %d, signal (%d): %s", pid, signal, strsignal(signal));
        }
    }

  MATH100
  free(buffer);

  MATH100
  fptr = fopen("success", "wb");
  MATH100
  fprintf(fptr, "1");
  MATH100
  fclose(fptr);

  MATH100
  return 0;
}
