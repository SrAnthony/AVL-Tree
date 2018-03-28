typedef struct node {
    // bf = Balance Factor
    // position = where the node is localized
		// 0 - right, 1 - left
		int data, l_height, r_height, bf, position;
		struct node *right;
		struct node *left;
		struct node *root;
}node;
