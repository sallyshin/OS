  1 #include <stdio.h>
  2 #include <stdlib.h>
  3 #include <string.h>
  4 #include <sys/wait.h>
  5 #include <unistd.h>
  6 
  7 int main()
  8 {
  9     printf("<start> PID : %d\n", (int)getpid());
 10     int fork_val = fork();
 11 
 12     if(fork_val < 0) { // fork에 실패하면
 13         printf("fork failed!\n");
 14         exit(1); // 종료
 15     }
 16     else if(fork_val == 0) { // 자식프로세스를 생성하면
 17         printf("<child process> (PID : %d)\n", (int)getpid()); // 자식프로세
    스 PID를 출력하고
 18         execl("/bin/ls", "/bin/ls", "-al", "/tmp", NULL); // execl함수를 통>    해 결과적으로 ls -al /tmp를 터미널에서 수행한 값이 나온다. 
 19     }
 20     else { // 부모프로세스이면
 21         printf("<parent process> (PID : %d)\n", (int)getpid());
 22     }
 23     return 0;
 24 }
~         