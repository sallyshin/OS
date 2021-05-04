#include <stdio.h> //perror

#include <stdlib.h> // close

#include <unistd.h> // open, write, read

#include <semaphore.h>

#include <sys/stat.h> // sem_open

#include <fcntl.h> // mode, flag

#include <string.h>

#define FIFO_PATH "fifo_temp"
#define SEM_NAME "sem_pp"
#define BUF_SIZE 8
#define TURN 5

int main() {
  const char * msg = "pong\n";
  int fd;
  int len;
  int turn = 0;
  int score = 100;
  sem_t * p_sem;
  char buf[BUF_SIZE];

//  mkfifo(FIFO_PATH, 0666);
  fd = open(FIFO_PATH, O_RDWR); // 읽기 쓰기 모두 가능하게 옵션 지정

  /* sem_unlink("mysema"); client shouldn't unlink semaphore */
  /* open semaphore */
  if ((p_sem = sem_open("mysema", O_CREAT, 0600, 0)) == SEM_FAILED) // 세마포어 생성
  {
    perror("sem_open");
    exit(1);
  }

  /* make server start game! */
  sem_post(p_sem);
  sem_post(p_sem);

  usleep(1000);
  /* game loop */
  do {
	  printf("[client] waiting for semaphore.. turn: %d\n", turn);
	  sem_wait(p_sem);

	  printf("[client] acquired! turn: %d\n", turn);
	  /* read from fifo (opponet) */
	  len = read(fd, buf, BUF_SIZE - 1);
	  buf[len] = '\0'; /* assure null-termination of string */
	  printf("[opponet] %s\n", buf);

	  printf("Your turn!\n");
	  /* get user input */
	  fgets(buf, BUF_SIZE, stdin);
	  if (strcmp(buf, msg) != 0) {
	    score -= 20;
	    printf("wrong! -20\n");
	  }

	  write(fd, buf, strlen(buf));
	  turn++;
	  sem_post(p_sem);
    usleep(1000);
	  printf("[client] sem_post! turn: %d\n", turn);
  } while (turn < 5);

  printf("Done! Your score: %d\n", score);
  return 0;
}
