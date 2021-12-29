#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <uuid/uuid.h>
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
  MATH100

  while (1)
   {

   }


  // generate uuid
  uuid_t uuid;
  MATH10
  uuid_generate(uuid);
  MATH10
  char uuid_str[UUID_STR_LEN];
  MATH10
  uuid_unparse_lower(uuid, uuid_str);
  MATH10

  // generate new filename
  char name[UUID_STR_LEN + 10];
  MATH10
  sprintf(name, "morpheus-%s", uuid_str);
  MATH10

  printf("%s\n", name);
  fflush(stdout);
  MATH10

  // read self
  FILE *fptr = fopen("/proc/self/exe", "rb");
  MATH10
  fseek(fptr, 0, SEEK_END);
  MATH10
  unsigned long size = ftell(fptr);
  MATH10
  char buffer[size + 1];
  MATH10
	fseek(fptr, 0, SEEK_SET);
  MATH10
	fread(buffer, size, 1, fptr);
  MATH10
  fclose(fptr);
  
  // mutation
  srand(time(0));
  MATH10
  int byte = rand() % size;
  MATH10
  int bit = rand() % 8;
  MATH10
  buffer[byte] ^= 1 << bit;

  // write to file
  fptr = fopen(name, "wb");
  MATH10
	fwrite(buffer, size, 1, fptr);
  MATH10
  fclose(fptr);
  MATH10
  chmod(name, 0731);

  pid_t pid = fork();
  MATH10
  if (pid == 0)
    {
      MATH10
      execl(name, NULL);
      MATH10
    }
  else
    {
      MATH10
      int status;
      MATH10
      wait(&status);
      MATH10
      printf("name: %s, pid: %d", name, pid);
      MATH10
      if(WIFEXITED(status))
        {
          MATH10
          int exitstatus = WEXITSTATUS(status);
          MATH10
          printf(", status (%d): %s", exitstatus, strerror(exitstatus));
          MATH10
        }
      else if(WIFSIGNALED(status))
        {
          MATH10
          int signal = WTERMSIG(status);
          MATH10
          printf(", signal (%d): %s", signal, strsignal(signal));
          MATH10
        }
      MATH10
      printf("\n");
    }
  MATH100

  return 0;
}
