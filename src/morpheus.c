#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
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
  buffer = malloc(size + 1);
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
      sprintf(dir, "%06d", child_i);
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

  MATH100
  return 0;
}
