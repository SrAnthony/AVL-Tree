#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "treePrinter.h"

void calc_height(node *root){
	if(root != NULL){
			calc_height(root->left);
			calc_height(root->right);
			// Increments the height of the node
			if(root->right != NULL){
					if(root->right->l_height > root->right->r_height)
							root->r_height = root->right->l_height + 1;
					else
							root->r_height = root->right->r_height + 1;
			}
			if(root->left != NULL){
					if(root->left->l_height > root->left->r_height)
							root->l_height = root->left->l_height + 1;
					else
							root->l_height = root->left->r_height + 1;
			}
	}
}

// When RightRight
void rotationSimpleLeft(node *root){
    // Simple rotation to the left
		// TODO: Don't work if this root is the tree root
		printf("[INFO] Simple rotation to the left on node %d...\n", root->data);
		node *newRoot = root->right;
		if(root->position == 0) // 0 is right
				root->root->right = newRoot;
		else // if not 0 then 1, is left
				root->root->left = newRoot;
		newRoot->root = root->root;
		newRoot->left = root;
		root->root = newRoot;
		root->right = NULL;
		// To fix the height
		root->r_height = 0;

}
// When LeftLeft
void rotationSimpleRight(node *root){
		// Simple rotation to the right
		// TODO: Don't work if this root is the tree root
		printf("[INFO] Simple rotation to the right on node %d...\n", root->data);
		node *newRoot = root->left;
		if(root->position == 0) // 0 is right
				root->root->right = newRoot;
		else // if not 0 then 1, is left
				root->root->left = newRoot;
		newRoot->root = root->root;
		newRoot->right = root;
		root->root = newRoot;
		root->left = NULL;
		// To fix the height
		root->l_height = 0;
}
void rotationLeftRight(){

}
void rotationRightLeft(){

}
void rebalance(node *root){

	switch (root->bf) {
			case 2:
					// Quando a diferença das alturas dos filhos de root é igual a 2
					// e a diferença das alturas dos filhos de FE (filho a esquerda) é igual a 1
					// é executado a rotação simples a direita
					printf("[INFO] Rebalance: node %d, l_height %d, r_height %d\n", root->data, root->l_height, root->r_height);
					if(root->left->bf == 1){
						rotationSimpleRight(root);
					}
					break;
			case -2:
					// Quando a diferença das alturas dos filhos de root é igual a -2
					// e a diferença das alturas dos filhos de FD é igual a -1
					// é executado a rotação simples a esquerda
					printf("[INFO] Rebalance: node %d, l_height %d, r_height %d\n", root->data, root->l_height, root->r_height);
					if(root->right->bf == -1){
						rotationSimpleLeft(root);
					}
					break;
	}
}

node* createNode(){
		// Creates a new node with user input data
		node *newNode = (node*)calloc(1, sizeof(node));
		printf("Tell me a number: ");
		scanf("%d", &newNode->data);

		printf("[INFO] Created node: %d\n", newNode->data);
		return newNode;
}

void addNode(node *root, node *toAdd){

		if (toAdd->data == root->data) {
				printf("[INFO] Adding: already on the tree!\n");
		}
		else if (toAdd->data > root->data) {
				printf("[INFO] Adding: going right, %d > %d\n", toAdd->data, root->data);
				if (root->right != NULL) {
						addNode(root->right, toAdd);
				}
				else {
						root->right = toAdd; // If right is NULL then toAdd is added to it
						toAdd->position = 0; // Position 0 = right, 1 = left
						toAdd->root = root; // root is toAdd's father
				}

				// // Increments the height of the node
				// if(root->right->l_height > root->right->r_height)
				// 		root->r_height = root->right->l_height + 1;
				// else
				// 		root->r_height = root->right->r_height + 1;
		}
		else { //if (toAdd->data < root->data)
				printf("[INFO] Adding: going left, %d < %d\n", toAdd->data, root->data);
				if (root->left != NULL) {
						addNode(root->left, toAdd);
				}
				else {
						root->left = toAdd; // If left is NULL then toAdd is added to it
						toAdd->position = 1; // Position 0 = right, 1 = left
						toAdd->root = root; // root is toAdd's father
				}

				// // Increments the height of the node
				// if(root->left->l_height > root->left->r_height)
				// 		root->l_height = root->left->l_height + 1;
				// else
				// 		root->l_height = root->left->r_height + 1;
		}

		calc_height(root);
		// Defines the node's balance factor
		root->bf = root->l_height - root->r_height;
		rebalance(root);
}

int main() {
		// Creates the main tree with initial Data
		node *root = (node*)calloc(1, sizeof(node));
		root->root = root;
		root->data = 10;

		int option = -1;
		while(option != 0) {
				print_t(root);
				printf("\n\n------------\nChoose a option:\n");
				printf("1. Add a new node\n");
				printf("2. Calcular altura\n");
        printf("0. Exit\n");
				scanf("%d", &option);
				system("clear");
				switch (option) {
				case 1:
						addNode(root, createNode());
						break;
				case 2:
						calc_height(root);
						break;
				}
		}
		return 0;
}
