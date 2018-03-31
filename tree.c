#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "treePrinter.h"

void calc_height(avl_node *node){
	if(node != NULL){
			calc_height(node->left);
			calc_height(node->right);
			// Increments the height of the node
			if(node->right != NULL){
					if(node->right->l_height > node->right->r_height)
							node->r_height = node->right->l_height + 1;
					else
							node->r_height = node->right->r_height + 1;
			}
			if(node->left != NULL){
					if(node->left->l_height > node->left->r_height)
							node->l_height = node->left->l_height + 1;
					else
							node->l_height = node->left->r_height + 1;
			}
	}
}

// When RightRight
void rotationSimpleLeft(avl_node *node){
		// TODO: Don't work if this node is the tree root
		printf("[INFO] Simple rotation to the left on node %d...\n", node->data);
		avl_node *pivot = node->right;
		if(node->position == 0) // 0 is right
				node->root->right = pivot;
		else // if not 0 then 1, is left
				node->root->left = pivot;
		pivot->root = node->root;
		pivot->left = node;
		node->root = pivot;
		node->right = NULL;
		// To fix the height
		node->r_height = 0;

}
// When LeftLeft
void rotationSimpleRight(avl_node *node){
		// TODO: Don't work if this node is the tree root
		printf("[INFO] Simple rotation to the right on node %d...\n", node->data);
		avl_node *pivot = node->left;
		if(node->position == 0) // 0 is right
				node->root->right = pivot;
		else // if not 0 then 1, is left
				node->root->left = pivot;
		pivot->root = node->root;
		pivot->right = node;
		node->root = pivot;
		node->left = NULL;
		// To fix the height
		node->l_height = 0;
}
// When LeftRight
void rotationDoubleRight(avl_node *node){
		printf("[INFO] Double rotation to the right on node %d...\n", node->data);
		avl_node *pivot = node->left->right;
		pivot->l_height = 1;
		node->left->r_height = 0;
		pivot->left = node->left;
		node->left->right = NULL;
		node->left = pivot;
		rotationSimpleRight(node);
}
// When RightLeft
void rotationDoubleLeft(avl_node *node){
		printf("[INFO] Double rotation to the left on node %d...\n", node->data);
		avl_node *pivot = node->right->left;
		pivot->r_height = 1;
		node->right->l_height = 0;
		pivot->right = node->right;
		node->right->left = NULL;
		node->right = pivot;
		rotationSimpleLeft(node);
}

void rebalance(avl_node *node){

	switch (node->bf) {
			// Quando a diferença das alturas dos filhos de nodo é igual a 2...
			case 2:
					printf("[INFO] Rebalancing right node %d - l_height %d, r_height %d\n", node->data, node->l_height, node->r_height);
					// e a diferença das alturas dos filhos de FE (filho a esquerda) é igual a 1
					// é executado a rotação simples a direita
					if(node->left->bf == 1)
						rotationSimpleRight(node);
					// e a diferença das alturas dos filhos de FE é igual a -1
					// é executado a rotação dupla a direita
					else if(node->left->bf == -1)
						rotationDoubleRight(node);
					break;
			case -2:
					printf("[INFO] Rebalancing left node %d - l_height %d, r_height %d\n", node->data, node->l_height, node->r_height);
					// e a diferença das alturas dos filhos de FD (filho a direita) é igual a -1
					// é executado a rotação simples a esquerda
					if(node->right->bf == -1)
						rotationSimpleLeft(node);
					// e a diferença das alturas dos filhos de FD é igual a 1
					// é executado a rotação dupla a esquerda
					else if(node->right->bf == 1)
						rotationDoubleLeft(node);
					break;
	}
}

avl_node* createNode(){
		// Creates a new node with user input data
		avl_node *newNode = (avl_node*)calloc(1, sizeof(avl_node));
		printf("[USER] Type a number: ");
		scanf("%d", &newNode->data);

		printf("[INFO] Created node: %d\n", newNode->data);
		return newNode;
}

void addNode(avl_node *node, avl_node *toAdd){

		if (toAdd->data == node->data) {
				printf("[INFO] Adding: already on the tree!\n");
		}
		else if (toAdd->data > node->data) {
				printf("[INFO] Adding: going right, %d > %d\n", toAdd->data, node->data);
				if (node->right == NULL) {
						node->right = toAdd; // If right is NULL then toAdd is added to it
						toAdd->position = 0; // Position 0 = right, 1 = left
						toAdd->root = node; // node is toAdd's father
				}
				else {
						addNode(node->right, toAdd);
				}
		}
		else { //if (toAdd->data < node->data)
				printf("[INFO] Adding: going left, %d < %d\n", toAdd->data, node->data);
				if (node->left == NULL) {
						node->left = toAdd; // If left is NULL then toAdd is added to it
						toAdd->position = 1; // Position 0 = right, 1 = left
						toAdd->root = node; // node is toAdd's father
				}
				else {
						addNode(node->left, toAdd);
				}
		}

		// Uses a recursive function to calculate the nodes height
		calc_height(node);
		// Defines the node's balance factor
		node->bf = node->l_height - node->r_height;
		rebalance(node);
}

int main() {
		avl_node *root = (avl_node*)calloc(1, sizeof(avl_node));
		root->root = root; // Tree root is itself, just in case
		root->data = 10;

		int option = -1;
		while(option != 0) {
				print_t(root);
				printf("\n\n------------\nChoose a option:\n");
				printf("1. Add a new node\n");
        printf("0. Exit\n");
				scanf("%d", &option);
				system("clear");
				switch (option) {
				case 1:
						addNode(root, createNode());
						break;
				}
		}
		return 0;
}
