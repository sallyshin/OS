  1 #include <stdio.h>
  2 #include <stdlib.h>
  3 #include <unistd.h>
  4 #include <semaphore.h>
  5 #include <errno.h>
  6 #include <string.h>
  7 #include <fcntl.h>
  8 
  9 int main() {
 10     sem_t *mutex = sem_open("sem_name", O_CREAT, 0644, 0);
 11     pid_t pid = fork();
 12 
 13     if(pid < 0) {
 14         printf("fork failed!\n");
 15         exit(1);
 16     }
 17     else if(pid == 0) {
 18         printf("child process (PID = %d) : ", (int)getpid());
 19         printf("안녕\n");
 20         sem_post(mutex);
 21     }
 22     else {
 23         sem_wait(mutex);
 24         printf("parent process (PID = %d) : 잘가\n", (int)getpid());
 25     }
 26     return 0;
 27 }
