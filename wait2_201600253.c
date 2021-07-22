  1 #include <stdio.h>
  2 #include <stdlib.h>
  3 #include <sys/wait.h>
  4 #include <unistd.h>
  5 
  6 int main()
  7 {
  8     pid_t cpid;
  9     int status;
 10 
 11     cpid = fork();
 12 
 13     if(cpid == 0) { // 자식프로세스가 생성되면
 14         printf("child process (PID = %d) : ", (int)getpid()); // PID값과
 15         sleep(5);
 16         printf("안녕\n"); // 안녕을 출력한다
 17         exit(0);
 18     }
 19     else if(cpid > 0){ // 부모프로세스이면
 20         int ret;
 21         printf("parent process (PID = %d) : ", (int)getpid()); // PID값과
 22         ret = waitpid(cpid, &status, 0);
 23     // waitpid함수를 사용하여 특정 PID의 자식프로세스가 종료하기를 기다린다
 24         printf("잘가\n");
 25         exit(0);
 26     }
 27     else { // 프로세스 생성이 안되면
 28         printf("fork failed\n");
 29         return 1;
 30     }
 31     return 0;
 32 }
