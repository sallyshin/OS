  1 #include <stdio.h>
  2 #include <stdlib.h>
  3 #include <unistd.h>
  4 #include <sys/wait.h>
  5 
  6 int main()
  7 {
  8     int pid;
  9     int status;
 10 
 11     pid = fork();
 12 
 13     if(pid < 0) {
 14         printf("fork failed\n");
 15         exit(1);
 16     }
 17 
 18     if(pid == 0) {
 19         printf("child's process(PID = %d) : 안녕\n", (int)getpid());
 20         // 자식프로세스가 생성되면 PID값과 "안녕"을 출력한다
 21         sleep(2);
 22     } else {
 23         wait(&status); // wait함수를 써서 자식이 종료할때까지 대기하게 한다
 24         printf("parent's process(PID = %d) : 잘가\n", (int)getpid());
 25         // 부모프로세스이면 PID값과 "잘가"를 출력한다.
 26     }
 27 }
