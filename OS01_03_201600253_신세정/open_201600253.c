1 #include <stdio.h>
  2 #include <stdlib.h>
  3 #include <string.h>
  4 #include <fcntl.h>
  5 #include <sys/wait.h>
  6 #include <unistd.h>
  7 #include <sys/types.h>
  8 
  9 int main()
 10 {
 11     int file;
 12     pid_t pid;
 13 
 14     file = open("data.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
 15     // data.txt파일이 없으면 생성하고, 이는 쓰기전용, 있다면 덮어쓰고, user>    권한을 갖는다.
 16     if(file == -1) { // 만약 해당 파일을 여는데 문제가 생기면
 17         printf("failed to open file\n");
 18         exit(1);
 19     }
 20     else { // 해당 파일을 열 수 있다면
 21         printf("successfully opened file\n");
 22     }
 23 
 24     int val = fork(); // 시스템콜을 통해서 fork한다
 25 
 26     if(val < 0) { // fork를 실패하면
 27         printf("failed fork\n");
 28         exit(1);
 29     }
 30     else if(val == 0) { // 자식프로세스를 생성하면
 31         printf("child process\n");
 32         char msg[] = "I'm child. I write this letter in file\n";
 33         write(file,msg,strlen(msg)); // 해당 글귀를 file에 적어준다
 34     }
 35     else{ // 부모프로세스이면
 36         printf("parent process\n");
 37         char msg[] = "I'm parent. Closed file won't be called\n";
 38         write(file, msg, strlen(msg)); // 해당 글귀를 file에 적어준다
 39     }
 40     close(file); // open했으니 file을 닫는다
 41     return 0;
 42 }
