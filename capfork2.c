#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void child(int child2parent[2],int parent2child[2]){
  char c;
  int pos=0;
  char data[32];
  char *str;
  close(child2parent[0]);
  close(parent2child[1]);
  while(read(parent2child[0],&c,1)>0){
    if(c==0)
      break;
    data[pos++]=(c-=0x20);
  }
  data[pos]=0;

  str=data;

  while(*str){
    c=*str++;
    write(child2parent[1],&c,1);
  }
  close(child2parent[1]);
  close(parent2child[0]);
}

void parent(int child2parent[2],int parent2child[2]){
  char c;
  char arg[]={'h','e','l','l','o',0};
  char *p=arg;
  
  close(child2parent[1]);
  close(parent2child[0]);
  while(*p){
    c=*p++;
    write(parent2child[1],&c,1);
    printf("write...\n");
  }
  write(parent2child[1],p,1);

  while(read(child2parent[0],&c,1)>0){
    write(1,&c,1);
  }
  printf("\n");

  close(child2parent[0]);
  close(parent2child[1]);
}

int main(void){
  int pid;
  int status;
  int child2parent[2];
  int parent2child[2];
  
  if(pipe(child2parent)==-1){
    perror("pipe");
    exit(1);
  }
  if(pipe(parent2child)==-1){
    perror("pipe");
    exit(1);
  }

  if((pid=fork())==0){
    child(child2parent,parent2child);
  }else if(pid>0){
    parent(child2parent,parent2child);
  }else{
    perror("fork");
    exit(1);
  }
  
  return 0;
}
