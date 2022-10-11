#include <stdio.h>
#include <stdlib.h>

//AVL TREEEEEEEEEEEEEEEEEEE

struct data{
	int value;
	struct data *left, *right;
}*root = NULL;

struct data *create_new_node(int value){
	struct data *newNode = (struct data*)malloc(sizeof(struct data));
	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

int max(int a, int b){
	return a > b ? a : b;
	
	//if a > b return a
	//return b
}

int get_height(struct data *node){
	if(!node) return 0;
	return 1 + max(get_height(node->left), get_height(node->right));
}

int get_balance(struct data *node){
	if(!node) return 0;
	//balance > 1 -> LEFT HEAVY
	//balance < -1 -> RIGHT HEAVY
	return get_height(node->left) - get_height(node->right);
}

struct data *left_rotate(struct data *node){
	//left rotate berati jomplang di kanan
	struct data *pivot = node->right;
	struct data *temp = pivot->left;
	
	pivot->left = node;
	node->right = temp;
	
	return pivot;
}

struct data *right_rotate(struct data *node){
	struct data *pivot = node->left;
	struct data *temp = pivot->right;
	
	pivot->right = node;
	node->left = temp;
	
	return pivot;
}

struct data *insert(struct data *node, int value){
	if(!node) return create_new_node(value);
	else if(value < node->value){ //value lebih kecil -> kiri
		node->left = insert(node->left, value);
	}else if(value > node->value){ //value lebih besar -> kanan
		node->right = insert(node->right, value);
	}else{ //value sama
		return node;
	}
	
	int bal = get_balance(node);
	
	if(bal > 1){ //LEFT HEAVY
		//left left
		if(get_balance(node->left) >= 0){
			return right_rotate(node);
		}else{
			// left right
			node->left = left_rotate(node->left);
			return right_rotate(node);
		}
	}else if(bal < -1){ // RIGHT HEAVY
		//right right
		if(get_balance(node->right) <= 0){
			return left_rotate(node);
		}else{
			//right left
			node->left = right_rotate(node->right);
			return left_rotate(node);
		}
	}
	return node;
}

struct data *delete_data(struct data *node, int value){
	if(!node) return NULL;
	else if(value < node->value){
		node->left = delete_data(node->left, value);
	}else if(value > node->right){
		node->right = delete_data(node->right, value);
	}else if(value == node->value){
		struct data *temp = NULL;
		//no child node
		if(node->left == NULL && node->right == NULL){
			node = NULL;
			free(node);
		}
		//single child
		else if(node->left == NULL || node->right == NULL){
			if(node->left != NULL){
				temp = node->left;
			}else{
				temp = node->right;
			}
			node = temp;
			free(temp);
		}
		//double child
		else{
			struct data *temp = node->left;
			while(temp->right != NULL){
				temp = temp->right;
			}
			node->value = temp->value;
			node->left = delete_data(node->left, temp->value);
		}
	}
	int bal = get_balance(node);
	if(bal > 1){
		//left left
		if(get_balance(node->left) >= 0){
			return right_rotate(node);
		}else{
			// left right
			node->left = left_rotate(node->left);
			return right_rotate(node);
		}
	}else if(bal < -1){
		//right right
		if(get_balance(node->right) <= 0){
			return left_rotate(node);
		}else{
			//right left
			node->left = right_rotate(node->right);
			return left_rotate(node);
		}
	}
	return node;
}

void pre_order(struct data *node){
	if(!node) return;
	printf("%d\n", node->value);
	pre_order(node->left);
	pre_order(node->right);
}
void in_order(struct data *node){
	if(!node) return;
	in_order(node->left);
	printf("%d\n", node->value);	
	in_order(node->right);
}

int main(){
	printf("balanced tree\n");
	root = insert(root, 41);
	root = insert(root, 22);
	root = insert(root, 5);
	root = insert(root, 51);
	root = insert(root, 48);
	root = insert(root, 29);
	root = insert(root, 18);
	root = insert(root, 21);
	root = insert(root, 45);
	root = insert(root, 3);


	in_order(root);
	
	return 0;
}
