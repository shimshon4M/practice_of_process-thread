#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void capitalize(void *str){
  int i;
  for(i=0;i<strlen((char*)str);++i){
    ((char*)str)[i]-=0x20;//大文字に
    printf("capitalizing...\n");
    sleep(1);
  }
}

int main(void){
  pthread_t thread;
  int iret;
  char arg[]={'h','e','l','l','o',0};

  iret=pthread_create(&thread,NULL,(void*)capitalize,(void*)arg);
  
  int i;
  for(i=0;i<5;++i){
    printf("main sleep...\n");
    usleep(500000);
  }
  pthread_join(thread,NULL);

  printf("%s\n",arg);
}
