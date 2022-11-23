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

//adds a new node to the head of the list. returns new head
Node * add_newNode(Node* head, pid_t new_pid, char * new_path){
	Node * new_node;
	new_node = (Node*)malloc(sizeof(Node));
	new_node->pid = new_pid;
	char *path = (char*)calloc(92,sizeof(char)); 
	strcpy(path, new_path);
	new_node->path = path;
	new_node->next = head;
	return new_node;
}

//deletes node with specific pid
Node * deleteNode(Node* head, pid_t pid){
	if(head->pid == pid){
		free(head->path);
		free(head);
		return head->next;
	}
	Node* last = head;
	Node* temp = head;
	while(temp != NULL){
		if(temp->pid == pid){
			last->next = temp->next;
			free(temp->path);
			free(temp);
			return head;			
		}
		last = temp;
		temp = temp->next;
	}
	return head;
}
//prints list
void printList(Node *node){
	while(node != NULL){
		printf("%d: %s\n", node->pid, node->path);
		node = node->next;
	}
}

//=1 if pid exists in list, =0 otherwise
int PifExist(Node *node, pid_t pid){
	while(node != NULL){
		if(node->pid == pid)
			return 1;
		node = node->next;
	}
	return 0;
}

