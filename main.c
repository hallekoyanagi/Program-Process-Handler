#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include "linked_list.h"

Node* head = NULL;
int status;

void func_BG(char **cmd){
  char const_path[91]; //program full path
  strcpy(const_path,"Assignment_1/");
  strcat(const_path, cmd[1]);

  pid_t pid = fork();
  if (pid == -1)
		perror("\nFail to create a new process.\n");

  if (pid == 0) {            /* Code executed by child */
    char execute[52]; //concatinate executable
    strcpy(execute, "./");
    strcat(execute, cmd[1]);
    if(execvp(execute, cmd)<0){ //if fails to execute
      printf("no file found\n");
      exit(-1);
    }
  } else {                    /* Code executed by parent */
    int w;
    w = waitpid(pid, &status, WNOHANG);

    if (w == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }
    head = add_newNode(head, pid, const_path); //update linked list
  }
} 
//print list of currently running programs
void func_BGlist(char **cmd){
  printList(head);
}

//kill process pid
void func_BGkill(char * str_pid){
	int pid = atoi(str_pid);
  if(PifExist(head,pid)==0){
    printf("PID does not exist");
    return;
  }
  head = deleteNode(head, pid);
  kill(pid, SIGKILL);
}

//stop process pid
void func_BGstop(char * str_pid){
	int pid = atoi(str_pid);
  if(PifExist(head,pid)==0){
    printf("PID does not exist");
    return;
  }
  kill(pid, SIGSTOP);
}

//start process pid
void func_BGstart(char * str_pid){
	int pid = atoi(str_pid);
  if(PifExist(head,pid)==0){
    printf("PID does not exist");
    return;
  }
  kill(pid, SIGCONT);
}


void func_pstat(char * str_pid){
	char* stat_filename = (char*)malloc(sizeof(char)*60);
  char* status_filename = (char*)malloc(sizeof(char)*62);

  sprintf(stat_filename, "/proc/%s/stat", str_pid);
  sprintf(status_filename, "/proc/%s/status", str_pid);

  FILE *stat = fopen(stat_filename, "r");
  FILE *status = fopen(status_filename, "r");

  free(stat_filename);
  free(status_filename);

  if(stat == NULL||status == NULL){ //if file dne
    printf("File does not exist");
    return;
  }
  char comm[50];
  char state;
  long int utime;
  long int stime;
  long int rss;
  int vol_switch = 0;
  int nonvol_switch = 0;
  int t; //temp variable
  char *buf = (char*)malloc(1000); //buffer for fgets


  char* stat_format = "%d %s %c %d %d %d %d %d %u %lu %lu %lu %lu %f %f %ld %ld %ld %ld %ld %ld %llu %lu %ld %s";//format string for stat file
  char* vol_status_format = "voluntary_ctxt_switches: %d";
  char* nonvol_status_format = "nonvoluntary_ctxt_switches: %d";


  fscanf(stat,stat_format,&t,comm,&state,&t,&t,&t,&t,&t,&t,&t,&t,&t,&t,&utime,&stime,&t,&t,&t,&t,&t,&t,&t,&t,&rss,t); //find variables in stat file
  for(int i = 0;i < 54;i++){
    fgets(buf,1000,status); //iterate through status file
  }
  //get variables from status file
  sscanf(buf, vol_status_format, &vol_switch);
  fgets(buf,1000,status);
  sscanf(buf, nonvol_status_format, &nonvol_switch); 
  free(buf);


  printf("comm: %s\nstate: %c\nutime: %ld\nstime: %ld\nrss: %ld\nvoluntary_ctxt_switches: %d\nnonvoluntary_ctxt_switches: %d\n", 
    comm, state, utime, stime, rss, vol_switch, nonvol_switch);
}

 
int main(){
    char user_input_str[50];
    while (true) {
      printf("Pman: > ");
      fgets(user_input_str, 50, stdin);
      printf("User input: %s \n", user_input_str);
      char * ptr = strtok(user_input_str, " \n");
      if(ptr == NULL){
        continue;
      }
      char * lst[50];
      int index = 0;
      lst[index] = ptr;
      index++;
      while(ptr != NULL){
        ptr = strtok(NULL, " \n");
        lst[index]=ptr;
        index++;
      }
      if(strcmp("bg",lst[0]) == 0){
        func_BG(lst);
      } else if (strcmp("bglist",lst[0]) == 0) {
        func_BGlist(lst);
      } else if (strcmp("bgkill",lst[0]) == 0) {
        func_BGkill(lst[1]);
      } else if (strcmp("bgstop",lst[0]) == 0) {
        func_BGstop(lst[1]);
      } else if (strcmp("bgstart",lst[0]) == 0) {
        func_BGstart(lst[1]);
      } else if (strcmp("pstat",lst[0]) == 0) {
        func_pstat(lst[1]);
      } else if (strcmp("q",lst[0]) == 0) {
        printf("Bye Bye \n");
        exit(0);
      } else {
        printf("Invalid input\n");
      }
    }

  return 0;
}

