/*
 *  ============================
 *  Anthony Nadaletti
 *  https://github.com/SrAnthony/AVL-Tree
 *  ============================
 */
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "avlTreePrinter.h"

avl_node * calc_height(avl_node *node){
		if(node){
				calc_height(node->left);
				calc_height(node->right);

				avl_node* right = node->right;
				avl_node* left = node->left;

				// Increments the height of the node
				if(node->right)
						node->r_height = right->bf > 0 ? right->l_height+1 : right->r_height+1;

				if(node->left)
						node->l_height = left->bf > 0 ? left->l_height+1 : left->r_height+1;

				// Defines the node's balance factor
				node->bf = node->l_height - node->r_height;
		}
		return node;
}

// When RightRight
avl_node* rotationSimpleLeft(avl_node *node){
		printf("[INFO] Simple rotation to the left on node %d...\n", node->data);
		avl_node *pivot = node->right;
		avl_node *rot_root = node->root;
		pivot->root = node->root;
		node->root = pivot;
		node->right = pivot->left;
		pivot->left = node;
		// To fix the height
		node->r_height = 0;

		if(node->position == 0) // 0 is right
				rot_root->right = pivot;
		else if(node->position == 1) // 1 is left
				rot_root->left = pivot;
		else{ // Then position == 3, is the main root
				printf("[INFO] Hey, %d is the new root!\n", pivot->data);
				pivot->root = pivot; // Is itself
				pivot->position = 3;
				node->position = 1; // Node is on left side of pivot
				printf("[INFO] Calculating height after simple left rotating on root\n");
				return calc_height(pivot);
		}
		printf("[INFO] Calculating height after simple left rotating\n");
		return calc_height(node);
}
// When LeftLeft
avl_node* rotationSimpleRight(avl_node *node){
		printf("[INFO] Simple rotation to the right on node %d...\n", node->data);
		avl_node *pivot = node->left;
		avl_node *rot_root = node->root;

		pivot->root = node->root;
		node->root = pivot;
		node->left = pivot->right;
		pivot->right = node;
		// To fix the height
		node->l_height = 0;
		if(node->position == 0) // 0 is right
				rot_root->right = pivot;
		else if(node->position == 1) // 1 is left
				rot_root->left = pivot;
		else{ // Then position == 3, is the main root
				printf("[INFO] Hey, %d is the new root!\n", pivot->data);
				pivot->root = pivot; // Is itself
				pivot->position = 3;
				node->position = 1; // Node is on left side of pivot
				printf("[INFO] Calculating height after simple right rotating on root\n");
				return calc_height(pivot);
		}

		printf("[INFO] Calculating height after simple right rotating\n");
		return calc_height(node);
}
// When LeftRight
avl_node* rotationDoubleRight(avl_node *node){
		printf("[INFO] Double rotation to the right on node %d...\n", node->data);
		avl_node *pivot = node->left->right;
		pivot->l_height = 1;
		node->left->r_height = 0;
		pivot->left = node->left;
		node->left->right = NULL;
		node->left = pivot;
		return rotationSimpleRight(node);
}
// When RightLeft
avl_node* rotationDoubleLeft(avl_node *node){
		printf("[INFO] Double rotation to the left on node %d...\n", node->data);
		avl_node *pivot = node->right->left;
		pivot->r_height = 1;
		node->right->l_height = 0;
		pivot->right = node->right;
		node->right->left = NULL;
		node->right = pivot;
		return rotationSimpleLeft(node);
}

avl_node* rebalance(avl_node *node){

		switch (node->bf) {
				// Quando a diferença das alturas dos filhos de nodo é igual a 2...
				case 2:
						printf("[INFO] Rebalancing right node %d - l_height %d, r_height %d\n", node->data, node->l_height, node->r_height);
						// e a diferença das alturas dos filhos de FE (filho a esquerda) é igual a 1
						// é executado a rotação simples a direita
						if(node->left->bf == 1)
								return rotationSimpleRight(node);
						// e a diferença das alturas dos filhos de FE é igual a -1
						// é executado a rotação dupla a direita
						else if(node->left->bf == -1)
								return rotationDoubleRight(node);
						break;
				case -2:
						printf("[INFO] Rebalancing left node %d - l_height %d, r_height %d\n", node->data, node->l_height, node->r_height);
						// e a diferença das alturas dos filhos de FD (filho a direita) é igual a -1
						// é executado a rotação simples a esquerda
						if(node->right->bf == -1)
								return rotationSimpleLeft(node);
						// e a diferença das alturas dos filhos de FD é igual a 1
						// é executado a rotação dupla a esquerda
						else if(node->right->bf == 1)
								return rotationDoubleLeft(node);
						break;
		}
		return node;
}

avl_node* createNode(){
		// Creates a new node with user input data
		avl_node *newNode = (avl_node*)calloc(1, sizeof(avl_node));
		printf("[USER] Type a number: ");
		scanf("%d", &newNode->data);

		printf("[INFO] Created node: %d\n", newNode->data);
		return newNode;
}

avl_node* addNode(avl_node *tree_root, avl_node *node, avl_node *toAdd){

		if (toAdd->data == node->data) {
				printf("[INFO] The number %d is already on the tree!\n", toAdd->data);
				return node;
		}
		else if (toAdd->data > node->data) {
				printf("[INFO] Adding: going right, %d > %d\n", toAdd->data, node->data);
				if (node->right == NULL) {
						node->right = toAdd; // If right is NULL then toAdd is added to it
						toAdd->position = 0; // Position 0 = right, 1 = left
						toAdd->root = node; // node is toAdd's father
						calc_height(tree_root);
						printf("[INFO] Added on %d's right side, height updated\n", node->data);
				}
				else {
						addNode(tree_root, node->right, toAdd);
				}
		}
		else { //if (toAdd->data < node->data)
				printf("[INFO] Adding: going left, %d < %d\n", toAdd->data, node->data);
				if (node->left == NULL) {
						node->left = toAdd; // If left is NULL then toAdd is added to it
						toAdd->position = 1; // Position 0 = right, 1 = left
						toAdd->root = node; // node is toAdd's father
						calc_height(tree_root);
						printf("[INFO] Added on %d's left side, height updated\n", node->data);
				}
				else {
						addNode(tree_root, node->left, toAdd);
				}
		}
		return rebalance(node);
}

avl_node* startup(){
		avl_node *root = (avl_node*)calloc(1, sizeof(avl_node));
		root->position = 3; // Is root
		root->root = root; // Tree root is itself
		printf("[USER] Number to tree root: ");
		scanf("%d", &root->data);
		return root;
}

int main(void) {
		avl_node *root = startup();
		int option;
		do{
				printStructure(root, 1);
				printf("\n\n----------------\nChoose a option:\n");
				printf("1. Add a new node\n");
        printf("0. Exit\n");
				scanf("%d", &option);
				system("clear");
				switch (option) {
				case 1:
						root = addNode(root, root, createNode());
						break;
				}
		}while(option != 0);
		return 0;
}
