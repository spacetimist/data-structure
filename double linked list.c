#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

struct Node{
	int value;
	struct Node *next, *prev;
}*head = NULL, *tail = NULL;

typedef struct Node Node;

Node* create_new_node(int val){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->next = newNode->prev = NULL; //biar ga nunjuk ke mana2
	newNode->value = val;
	
	return newNode;
}

void push_head(int val){
	Node *newNode = create_new_node(val);
	//if head == NULL
	if(!head){
		head = tail = newNode;
	}else{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
	}
}
void push_tail(int val){
	if(!head){
		push_head(val); //karena sama aja head = tail pas di awal
	}else{
		Node *newNode = create_new_node(val);
		tail->next = newNode;
		newNode->prev = tail; //
		tail = newNode;
	}
}
void push_mid(int val){
	if(!head){
		push_head(val); 
	}
	else if(val <= head->value){ 
		push_head(val);
	}
	else if(val >= tail->value){ 
		push_tail(val);
	}
	else{
		Node *curr = head;
		while(curr->next->value < val){
			curr = curr->next;
		}
		
		Node *newNode = create_new_node(val);
		newNode->next = curr->next;
		curr->next->prev = newNode;
		newNode->prev = curr;
		curr->next = newNode;
	}
}

void pop_head(){
	if(!head) return;
	else if(head == tail){ //kalo cuma 1 node
		free(head);
		head = tail = NULL;
	}
	else{
		Node *temp = head;
		head = head->next;
		head->prev = NULL; //klo ga dikasih jg gpp sih
		free(temp);
		temp = NULL;
	}
}
void pop_tail(){
	if(!head) return;
	else if(head == tail){
		pop_head();
	}
	else{
		Node *temp = tail;
		tail = tail->prev;
		free(temp);
		temp = NULL;
		tail->next = NULL;
	}
}
void pop_mid(int value){
	if(!head) return;
	else if(head->value == value){
		pop_head();
	}
	else if(tail->value == value){
		pop_tail();
	}
	else{
		Node *curr = head;
		while(curr->next != NULL && curr->next->value != value){
			curr = curr->next;
		}
		if(curr->next == NULL){
			printf("%d is not in the system\n", value);
		}
		else{
			Node *temp = curr->next;
			curr->next = curr->next->next;
			curr->next->prev = curr;
			free(temp);
			temp = NULL;
		}
	}
}

void print_nodes(){
	Node *curr = head;
	while(curr != NULL){
		if(curr == head){
			printf("(head)");
		}
		if(curr == tail){
			printf("(tail)");
		}
		printf("%d -> ", curr->value);
		curr = curr->next;
	}
	printf("NULL\n");
}

int main(){
	// coba coba di sini
	push_head(5);
	push_tail(10);
	push_mid(7);
	push_mid(3);
	push_mid(12);
	push_head(8);
	
	print_nodes();
	pop_head();
	print_nodes();
	
	return 0;
}
