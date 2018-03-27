#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "treePrinter.h"

void debug(const char prefix[], node *debugNode){
		printf("\n%s\n", prefix);
		printf("Node Data: %d\nRight: %p\nLeft: %p\n---------\n\n", debugNode->data, debugNode->right, debugNode->left);
}

node* createNode(){
		// Creates a new node with user input data
		node *newNode = (node*)calloc(1, sizeof(node));
		printf("Tell me a number: ");
		scanf("%d", &newNode->data);

		debug("Created node", newNode);
		return newNode;
}

void addNode(node *root, node *toAdd){

		if (toAdd->data == root->data) {
				printf("Adding: already on the tree!\n");
		}
		else if (toAdd->data > root->data) {
				/*DEBUG*/ printf("Adding: else if %d > %d\n", toAdd->data, root->data);
				if (root->right != NULL) {
						addNode(root->right, toAdd);
				}
				else {
						root->right = toAdd; // If right is NULL then toAdd is added to it
				}

				// Increments the height of the node
				if(root->right->l_height > root->right->r_height)
						root->r_height = root->right->l_height + 1;
				else
						root->r_height = root->right->r_height + 1;
		}
		else { //if (toAdd->data < root->data)
				/*DEBUG*/ printf("Adding: else %d < %d\n", toAdd->data, root->data);
				if (root->left != NULL) {
						addNode(root->left, toAdd);
				}
				else {
						root->left = toAdd; // If left is NULL then toAdd is added to it
				}

				// Increments the height of the node
				if(root->left != NULL){
						if(root->left->l_height > root->left->r_height)
								root->l_height = root->left->l_height + 1;
						else
								root->l_height = root->left->r_height + 1;
				}
		}

		// After adding the node and increasing the height
		root->bf = root->l_height - root->r_height;
		if(root->bf < -1 || root->bf > 1){
        printf("Node %d unbalanced (factor of %d)\n", root->data, root->bf);
		}
}

int main() {
		// Creates the main tree with initial Data
		node *root = (node*)calloc(1, sizeof(node));
		root->data = 10;

		int option = -1;
		while(option != 0) {
				printf("\n\n------------\nChoose a option:\n");
				printf("1. Add a new node\n");
				printf("2. View the tree\n-----\n");
        printf("0. Exit\n");
				scanf("%d", &option);
				system("clear");
				switch (option) {
				case 1:
						addNode(root, createNode());
						break;
				case 2:
						print_t(root);
						break;
				}
		}
		return 0;
}
