  1 #include <stdio.h>
  2 #include <stdlib.h>
  3 #include <unistd.h>
  4 
  5 int global = 1;
  6 int main()
  7 {
  8     int local;
  9     local = 10;
 10     printf("first : global(%d), local(%d)\n", global, local);
 11 
 12     pid_t childpid = fork();
 13 
 14     if(childpid < 0){
 15         printf("fork failed\n");
 16         return 1;
 17     }
 18 
 19     if(childpid > 0){
 20         global++, local++;
 21         printf("Parent : global(%d), local(%d)\n", global, local);
 22         printf("I'm parents. My PID is %d\n", (int)getpid());
 23         printf("My child's PID : %d\n", childpid);
 24         printf("\n");
 25         sleep(1);
 26     }
 27     else {
 28         global++, local++;
 29         printf("Child : global(%d), local(%d)\n", global, local);
 30         printf("I'm child. My PID is %d\n", (int)getpid());
 31         printf("My parent's PID : %d\n", (int)getppid());
 32         printf("\n");
 33     }
 34     return 0;
 35 }
