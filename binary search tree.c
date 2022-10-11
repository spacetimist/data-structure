//BINARY SEARCH TREE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	int value;
	Node *left, *right;
};

typedef struct Node Node;

Node *create_new_node(int value){
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->left = newNode->right = NULL;
	newNode->value = value;
	
	return newNode;
}

Node *insert(Node *root, int value){
	if(!root) return create_new_node(value);
	else if(value < root->value){
		root->left = insert(root->left, value);
	}else if(value > root->value){
		root->right = insert(root->right, value);
	}
	return root;
}

void preOrder(Node *root){
	if(!root) return;
	printf("%d ", root->value);
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder(Node *root){
	if(!root) return;
	inOrder(root->left);
	printf("%d ", root->value);
	inOrder(root->right);
}

void postOrder(Node *root){
	if(!root) return;
	postOrder(root->left);
	postOrder(root->right);
	printf("%d ", root->value);
}

void summary(Node *root){
	puts("Summary");
	puts("==============================");
	printf("Preorder: "); preOrder(root); printf("\n");
	printf("Inorder: "); inOrder(root); printf("\n");
	printf("Postorder: "); postOrder(root); printf("\n");
	puts("==============================");	
}

int main(){
	Node *root = NULL;
	root = insert(root, 10);
	root = insert(root, 12);
	root = insert(root, 20);
	root = insert(root, 5);
	root = insert(root, 11);
	root = insert(root, 17);
	root = insert(root, 9);
	
	summary(root);
	
	return 0;
}
