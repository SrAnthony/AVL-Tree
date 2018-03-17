#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "treePrinter.h"

void debug(const char prefix[], node *debugNode){
		printf("\n%s\n", prefix);
		printf("Node ID: %d\nRight: %p\nLeft: %p\n---------\n\n", debugNode->id, debugNode->right, debugNode->left);
}

node* createNode(){
		// Creates a new node with user input ID
		node *newNode = (node*)calloc(1, sizeof(node));
		printf("Tell me a number: ");
		scanf("%d", &newNode->id);

		debug("Created node", newNode);
		return newNode;
}

void addNode(node *root, node *toAdd){
		int toAddID = toAdd->id;
		int rootID = root->id;
		printf("Adding node %d into the root %d\n", toAddID, rootID);

		if (toAddID == rootID) {
				printf("The node you're trying to add (%d) is already on the tree!\n", toAddID);
		}
		else if (toAddID > rootID) {
				if (root->right != NULL) {
						printf("Node %d is bigger than root %d, root->right is not NULL\n", toAddID, rootID);
						addNode(root->right, toAdd);
				}
				else {
						printf("Node %d is bigger than root %d, root->right IS NULL\n", toAddID, rootID);
						root->right = toAdd;
				}
		}
		else { //if (toAddID < rootID)
				if (root->left != NULL) {
						printf("Node %d is smaller than root %d, root->left is not NULL\n", toAddID, rootID);
						addNode(root->left, toAdd);
				}
				else {
						printf("Node %d is smaller than root %d, root->left IS NULL\n", toAddID, rootID);
						root->left = toAdd;
				}
		}
}

int main() {
		// Creates the main tree with initial ID
		node *root = (node*)calloc(1, sizeof(node));
		root->id = 10;

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
