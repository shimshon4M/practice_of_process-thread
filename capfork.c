#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void child(char *str,int filedsc[2]){
  char c;
  close(filedsc[0]);
  int i;
  for(i=0;i<strlen(str);++i){
    printf("convert...\n");
    str[i]-=0x20;
    sleep(1);
  }
  while(*str){
    c=*str++;
    write(filedsc[1],&c,1);
  }
  close(filedsc[1]);
}

void parent(int filedsc[2]){
  char c;
  printf("parent\n");
  close(filedsc[1]);
  while(read(filedsc[0],&c,1)>0){
    write(1,&c,1);
  }
  printf("\n");
  close(filedsc[0]);
}

int main(void){
  char arg[]={'h','e','l','l','o',0};
  int pid;
  int status;
  int filedsc[2];
  
  if(pipe(filedsc)==-1){
    perror("pipe");
    exit(1);
  }
  
  if((pid=fork())==0){
    child(arg,filedsc);
  }else if(pid>0){
    int i;
    for(i=0;i<5;++i){
      printf("parent sleep...\n");
      usleep(500000);
    }
    parent(filedsc);
  }else{
    perror("fork");
    exit(1);
  }
  
  return 0;
}
